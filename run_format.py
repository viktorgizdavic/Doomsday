#!/usr/bin/python

import sys,os,subprocess
from functools import partial

def has_ext(file_name:str,ext:str) -> bool:
    return filename.endswith(f'.{ext}')

def has_ext_multiple(file_name:str,exts:[str]) -> bool:
    return any(map(partial(has_ext,file_name),exts))

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) < 2:
        print('Usage: ./run_format.py <dir> <ext>...')
        exit(1)

    dir   = args[0]

    for dir, _, files in os.walk(dir):
        for filename in files:
            filepath = dir + '/' + filename
            if has_ext_multiple(filename, args):
                subprocess.run(f'clang-format -i {filepath}', shell=True)