#!/usr/bin/env python3

import re

with open('ErrorCode.txt', 'r') as f:
    nv = [ ]
    for line in f:
        #print(line)
        line = re.sub(r',.*$', '', line.strip())
        line = re.sub(r'//.*$', '', line)
        if len(line) == 0:
            continue
        #print(line)
        name, value = re.split(r'\s*=\s*', line)
        nv.append((name, value))

    for n, v in nv:
        print(f'    case ctre::phoenix::{n}: // {v}')
        print(f'      return "{n}";')

    for n, v in nv:
        print(f' m_errorcode.attr("{n}") = py::int_({v});')
