import sys
from genfun import *

genout = sys.argv[1]
goutput = open(genout, "r")
transmittedMessage = goutput.readline().rstrip()
transmittedMessage = int(transmittedMessage,base=2)
transmittedMessage = bin(transmittedMessage)[2:]
gen = int(goutput.readline(), base=2)
gen = bin(gen)[2:]
goutput.close()

_, r = divide(transmittedMessage, gen)

if int(r) == 0:
    print("Correct")
else:
    print("Not Correct")
