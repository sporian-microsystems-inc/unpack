#!/usr/bin/python
#
# Read a binary file from the named argument, and decode it
# courtesy of the builtin "unpack" string.
#

import sys
import struct

with open(sys.argv[1], "r") as f:
    scan = f.read()

# grab the unpack string...
u = struct.unpack("!30s", scan[0:30])
x = u[0].strip('\0')
start = struct.calcsize(x)      
print "unpack string is ", x

# ...and use it to grab the data
(u,v,x1,y1,desc,x2,y2,nattrs) = struct.unpack(x, scan[0:start])
print v,x1,y1,desc,x2,y2

attrs = struct.unpack("!{}I".format(nattrs), scan[start:])
print attrs

