#!/usr/bin/python
#-*- coding: utf-8 -*-
import sys
import os
import commands
from optparse import OptionParser

parser = OptionParser()
parser.add_option('-n', '--dimension',default=10,\
        help='dimension', dest='N')
parser.add_option('-m', '--num_of_vp',default=10,\
        help='number of vantage point', dest='M')
parser.add_option('-f', '--filename', default='10.dat',\
        help='file name', dest='filename')

(options, args) = parser.parse_args(sys.argv[1:])

N = int(options.N)
M = int(options.M)
filename = options.filename

if N <= 10:
    command = './a.out '+str(N)+' '+str(M)
    lines = commands.getoutput(command)
    
    bits = lines.split('\n')
    for bit in bits:
        print bit.rstrip()
else:
    command = './a.out 10 '+str(M)
    lines = commands.getoutput(command)

    bits = lines.split('\n')
    a = []
    for bit in bits:
        bit = bit.rstrip()
        a.append(bit.split(' '))

    ans = []
    for i in xrange(M):
        now = ''
        for j in xrange(N//10):
            now = now + bits[i]
        for j in xrange(N%10):
            now = now + a[i][j] + ' '
        ans.append(now)

    with open('vp/'+filename,'w') as fp:
        for p in ans:
            fp.write(p+'\n')
