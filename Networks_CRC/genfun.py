import sys

val1 = '1'
val2 = '1'


def toList(x):
    l = []
    for i in range(0, len(x)):
        l.append(int(x[i]))
    return (l)


def toString(x):
    str1 = ""
    for i in range(0, len(x)):
        str1 += str(x[i])
    return str1


def divide(val1, val2):
    a = toList(val1)
    b = toList(val2)
    working = ""
    res = ""

    while len(b) <= len(a) and a:
        if a[0] == 1:
            del a[0]
            for j in range(len(b) - 1):
                a[j] ^= b[j + 1]
            if len(a) > 0:
                working += toString(a)
                res += "1"
        else:
            del a[0]
            working += toString(a)
            res += "0"

    return res, toString(a)


if __name__ == "__main__":
    inputfile = sys.argv[1]

    print(inputfile)

    ginput = open(inputfile, "r")
    message = ginput.readline().rstrip()
    listMessage = list(map(int, message))

    generator = ginput.readline().rstrip()
    binaryGen = int(generator, base=2)
    listGenerator = list(map(int, generator))

    ginput.close()

    outputfile = sys.argv[2]
    print(outputfile)
    _, rem = divide(listMessage, listGenerator)
    goutput = open(outputfile, "w+")
    goutput.write(message + str(rem) + '\n')
    goutput.write(generator)

    goutput.close()
