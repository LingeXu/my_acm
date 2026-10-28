#!/usr/bin/env python3
#交互题对拍: 批量随机/穷举测试交互题, 失败时打印完整对话并保存回放文件
#用法:
#  python3 交互题对拍.py sol.cpp                 # 自动编译后随机对拍(默认 200 组)
#  python3 交互题对拍.py ./sol                   # 已编译好, 直接对拍
#  python3 交互题对拍.py sol.cpp --exhaust 8     # 穷举 n=2..8 全部 2^n 种隐藏答案
#  python3 交互题对拍.py sol.cpp --iters 1000 --seed 42 --trace
#通用部分(直接抄): PipeIO 带超时读行 / judge_case 对话循环 / 对拍主循环 / 失败回放
#按题修改: gen_case 生成数据 / case_input 组输入 / init_state+respond 模拟 / check_answer 判答案
#          以 CF2134E Power Boxes 为例
#注意1: 每组单独起一个进程(一个测试点), 所以组输入里要先写 t=1; 好处是一组错立刻定位
#注意2: 失败时生成的 replay_test.txt 可以直接喂给 C++ 裁判复现: ./judge ./sol < replay_test.txt
#配套: 交互题本地裁判.cpp(单组调试、断点、sanitizer 用)

import os, sys, subprocess, select, random, argparse
from itertools import product

#================ 通用: 带超时的按行管道读写 ================
class PipeIO:
    """从子进程 stdout 按行读(自带缓冲, 单行超时), 向子进程 stdin 即时写一行.
    注意: 全程只用 os.read 直读 fd, 绝不调用 proc.stdout.read/readline,
          否则 select 会被 Python 缓冲区里已读入的数据骗到."""
    def __init__(self, proc):
        self.proc = proc
        self.buf = b''
    def readline(self, timeout=5.0):
        while b'\n' not in self.buf:
            r, _, _ = select.select([self.proc.stdout], [], [], timeout)
            if not r:
                raise TimeoutError('等程序输出超时: 查 endl/flush, 或程序在空转')
            chunk = os.read(self.proc.stdout.fileno(), 4096)
            if not chunk:                        # EOF: 把最后半行(可能无换行)吐出来
                line, self.buf = self.buf, b''
                return line.decode() if line else None
            self.buf += chunk
        line, self.buf = self.buf.split(b'\n', 1)
        return line.decode()
    def writeline(self, s):
        os.write(self.proc.stdin.fileno(), (s + '\n').encode())

#================ 按题修改 1: 隐藏数据与生成 ================
class Case:
    def __init__(self, n, a):           # a: 1-indexed(带哨兵)的隐藏答案
        self.n, self.a = n, a

def gen_case(rng, maxn=8):
    n = rng.randint(2, maxn)
    return Case(n, [0] + [rng.randint(1, 2) for _ in range(n)])

def all_cases(maxn):                    # 穷举模式: n=2..maxn 全部 2^n 种答案
    for n in range(2, maxn + 1):
        for bits in product([1, 2], repeat=n):
            yield Case(n, [0] + list(bits))

def case_input(c):
    return f'1\n{c.n}'                  # 每组单独一个进程: 先写 t=1, 再写本组输入

def limit(c):
    return (3 * c.n + 1) // 2            # ceil(3n/2)

#================ 按题修改 2: 模拟与判定 ================
def init_state(c):
    return {'n': c.n, 'arr': c.a[:]}     # 当前排列; swap 永久生效
#注意: respond 吃 state(当前环境), limit/check_answer 吃 Case(隐藏数据), 别传混

def respond(st, op, x):
    """返回响应字符串; None = 无响应(如 swap, 程序不会读, 别写).
    非法参数直接 raise, 外层记为非法."""
    n, arr = st['n'], st['arr']
    if op == 'swap':
        if not (1 <= x <= n - 1): raise ValueError(f'非法 swap {x}')
        arr[x], arr[x + 1] = arr[x + 1], arr[x]
        return None
    if op == 'throw':
        if not (1 <= x <= n): raise ValueError(f'非法 throw {x}')
        pos, jumps = x, 0
        while pos <= n:
            pos += arr[pos]
            jumps += 1
        return str(jumps)
    raise ValueError(f'未知指令 {op}')

def check_answer(c, rest):
    got = list(map(int, rest.split()))
    return len(got) == c.n and got == c.a[1:]

#================ 通用: 单组对话裁判 ================
def judge_case(builder, case, trace=False):
    proc = builder()
    io = PipeIO(proc)
    state = init_state(case)
    lim = limit(case)                      # 上限只和隐藏数据有关, 提前算好
    inp = case_input(case)
    io.writeline(inp)
    log = [('judge>', inp)]
    verdict, used = 'ERR', 0
    try:
        while True:
            line = io.readline()
            if line is None:
                verdict = 'EOF(没给答案就退出)'
                break
            line = line.strip()
            if not line:
                continue
            log.append(('sol>', line))
            if trace: print('sol>', line, flush=True)
            op, _, rest = line.partition(' ')
            if op == '!':
                verdict = 'OK' if check_answer(case, rest) else 'WA'
                break
            used += 1                       # 按题确认: 哪些操作计入次数(这里 swap/throw 都算)
            if used > lim:
                io.writeline('-1')          # 评测机惯例: 超限回 -1
                log.append(('judge>', '-1'))
                verdict = '查询超限'
                break
            resp = respond(state, op, int(rest))
            if resp is None:
                log.append(('judge>', '(无响应)'))
            else:
                io.writeline(resp)
                log.append(('judge>', resp))
                if trace: print('judge>', resp, flush=True)
    except TimeoutError as e:
        verdict = '超时'
        log.append(('judge>', f'(超时) {e}'))
    except (ValueError, TypeError) as e:
        verdict = f'非法({e})'
        log.append(('judge>', f'(非法) {e}'))
    except Exception as e:                  # 兜底: 别让裁判自己崩
        verdict = f'ERR({type(e).__name__}: {e})'
    finally:
        proc.kill()
        proc.wait()
    return verdict, used, log

#================ 通用: 对拍主循环 ================
def compile_if_needed(target):
    if target.endswith('.cpp'):
        bin_ = target[:-4]
        subprocess.run(['g++', '-std=c++17', '-O2', target, '-o', bin_], check=True)
        return os.path.abspath(bin_)
    return os.path.abspath(target)

def save_replay(case, log):
    with open('replay_test.txt', 'w') as f:   # 按题修改: 测试文件格式
        f.write(f"1\n{case.n} {' '.join(map(str, case.a[1:]))}\n")
    with open('replay_log.txt', 'w') as f:
        for who, s in log:
            f.write(f'{who} {s}\n')
    print('已保存 replay_test.txt(可 ./judge ./sol < replay_test.txt 复现) 与 replay_log.txt')

def main():
    ap = argparse.ArgumentParser(description='交互题对拍(以 CF2134E 为例)')
    ap.add_argument('target', help='sol.cpp(自动编译) 或 ./sol')
    ap.add_argument('--iters', type=int, default=200, help='随机组数')
    ap.add_argument('--exhaust', type=int, nargs='?', const=8, metavar='N', help='穷举 n=2..N 全部答案')
    ap.add_argument('--seed', type=int, default=None)
    ap.add_argument('--maxn', type=int, default=8, help='随机 n 上限')
    ap.add_argument('--trace', action='store_true', help='实时打印每组对话')
    args = ap.parse_args()

    sol = compile_if_needed(args.target)
    builder = lambda: subprocess.Popen([sol], stdin=subprocess.PIPE,
                                       stdout=subprocess.PIPE,
                                       stderr=subprocess.DEVNULL)   # 想看程序 cerr: 改 None

    rng = random.Random(args.seed)
    cases = (all_cases(args.exhaust) if args.exhaust else
             (gen_case(rng, args.maxn) for _ in range(args.iters)))

    ok = 0
    for i, case in enumerate(cases, 1):
        verdict, used, log = judge_case(builder, case, trace=args.trace)
        if verdict != 'OK':
            print(f'\n第 {i} 组失败: {verdict}(查询 {used}/{limit(case)}), n={case.n}, 答案={case.a[1:]}')
            for who, s in log:
                print(f'  {who} {s.replace(chr(10), "\\n")}')
            save_replay(case, log)
            return 1
        ok += 1
        if i % 100 == 0:
            print(f'{i} 组通过...', flush=True)
    print(f'全部通过: {ok} 组')
    return 0

if __name__ == '__main__':
    sys.exit(main())
