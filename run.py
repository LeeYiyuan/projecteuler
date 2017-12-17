#!/usr/bin/env python3

import argparse
import queue
import os
import re
import threading
import time
import subprocess
import sys

devnull = open(os.devnull, 'w')

def check_jobs(value):
    ivalue = int(value)
    if ivalue <= 0:
         raise argparse.ArgumentTypeError("Invalid argument for JOBS: %s." % value)
    return ivalue

def check_solution(value):
    if (value.upper() == 'ALL'):
        return 'ALL';
    ivalue = int(value)
    if ivalue <= 0:
         raise argparse.ArgumentTypeError("Invalid argument for SOLUTION: %s." % value)
    return value

parser = argparse.ArgumentParser(description="Utility to run the solutions to ProjectEuler.")
parser.add_argument('-j', '--jobs', metavar='JOBS', type=check_jobs, default=1, help='Specifies the number of jobs to create.')
parser.add_argument('solutions', metavar='SOLUTION', nargs='+', type=check_solution, default='ALL', help='Specifies the solution(s) to run by problem number. Use ALL to run all existing solutions.')
args = parser.parse_args()

solutions_queue = queue.Queue()
solutions_count = 0
results = []

for solution in [f.strip('.cpp') for f in sorted(os.listdir()) if re.match('[0-9]+.cpp', f)] if 'ALL' in args.solutions else args.solutions:
    solutions_queue.put(solution)
    solutions_count += 1

subprocess.call(['make', 'clean'], stdout=devnull, stderr=devnull)

global_start = time.perf_counter()

subprocess.call(['make', 'utils'], stdout=devnull, stderr=devnull)

def worker():
    while True:
        solution = solutions_queue.get()
        if solution is None:
            break
        start = time.perf_counter()

        subprocess.call(['make', '{0}.run'.format(solution)], stdout=devnull, stderr=devnull)
        popen = subprocess.Popen(['./{0}.run'.format(solution)], stdout=subprocess.PIPE)
        popen.wait()
        output = popen.stdout.read().decode('utf-8')
        subprocess.call(['rm', '{0}.run'.format(solution)])
        elapsed = time.perf_counter() - start
        results.append((solution, int(round(1000 * elapsed, 0)), output))
        
        sys.stdout.write("\033[K\r")
        print('Completed {0} / {1} solutions.'.format(len(results), solutions_count), end='\r')

        solutions_queue.task_done()

jobs = []
for i in range(args.jobs):
    j = threading.Thread(target=worker)
    j.start()
    jobs.append(j)

solutions_queue.join()

for i in range(args.jobs):
    solutions_queue.put(None)
for j in jobs:
    j.join()

global_elapsed = time.perf_counter() - global_start

subprocess.call(['make', 'clean'], stdout=devnull, stderr=devnull)

sys.stdout.write("\033[K\r")
for result in sorted(results, key=lambda x: x[0]):
    print('{0: >4s} | {1: >6d} ms | {2}'.format(*result))

print(' ALL | {0: >6d}  s |\n'.format(int(round(global_elapsed, 0))))
