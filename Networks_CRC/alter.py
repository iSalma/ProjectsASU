import sys


genout = sys.argv[1]
index = int(sys.argv[2])

goutput = open(genout, "r+")
binMessage = list(goutput.readline().rstrip())
gen = int(goutput.readline(),base=2)

if int(binMessage[index-1]) == 0:
    binMessage[index-1] = int(1)
else:
    binMessage[index-1] = 0

binMessage = ''.join(str(i) for i in binMessage)
goutput.seek(0)
goutput.truncate()
goutput.write(binMessage + '\n')
goutput.write(bin(gen)[2:])

print "Message after altering: " + binMessage

goutput.close()