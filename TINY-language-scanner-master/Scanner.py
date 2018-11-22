import re
reservedWords = ['if','then','else','repeat','until','read','write','end']
specialSymbols = {'+':'Adding','-':'subtracting','=':'equal','*':'multiply','/':'division','<':'less than','(':'open brackets',')':'end brackets','{':'comment start','}':'comment end'}
numbers=re.compile(r"[0-9][0-9]*", re.UNICODE)
identifier = re.compile(r"[a-zA-Z_][0-9a-zA-Z_]*", re.UNICODE)
f = open ('test.txt','r')
outfile=open('output.txt','w')
f_contents = f.read()
lines = f_contents.split('\n')
Temp_Token = ""
Temp_Assign=""
for line in lines:

    for i in line:
        if i == "{":
            if line.find('}') != -1:
                outfile.write("Comment:" + line[line.find('{'):] + "\n")
                break
        elif i == ":":
            Temp_Assign += i
            continue
        elif i =="=":
            Temp_Assign +=i
            if Temp_Assign==":=":
                outfile.write("Special symbol for Assignment: := \n")
                Temp_Assign=""
            else:
                outfile.write("Special symbol for Equal: = \n")
        elif i !=" " and i !="\n" and i not in specialSymbols and i !=";":
            Temp_Token += i
        elif i==" " or i=="\n":
            if Temp_Token in reservedWords:
                outfile.write("Reserved Word: "+ Temp_Token+"\n")
            else:
                result = re.match(identifier, Temp_Token)
                if (result is not None) == True:
                    outfile.write("Identifier: "+ Temp_Token+"\n")
                else:
                    resultn = re.match(numbers, Temp_Token)
                    if (resultn is not None) == True:
                        outfile.write("Number: " + Temp_Token + "\n")
            Temp_Token=""
        elif i in specialSymbols:
            if Temp_Token in reservedWords:
                outfile.write("Reserved Word: " + Temp_Token + "\n")
            else:
                result = re.match(identifier, Temp_Token)
                if (result is not None) == True:
                    outfile.write("Identifier: " + Temp_Token + "\n")
                else:
                    resultn = re.match(numbers, Temp_Token)
                    if (resultn is not None) == True:
                        outfile.write("Number: " + Temp_Token + "\n")
            outfile.write("Special symbol for "+ specialSymbols[i]+ ": "+ i+"\n")
            Temp_Token=""
        elif i ==";":
            if Temp_Token in reservedWords:
                outfile.write("Reserved Word: "+ Temp_Token+"\n")
            else:
                result = re.match(identifier, Temp_Token)
                if (result is not None) == True:
                    outfile.write("Identifier: " + Temp_Token + "\n")
                else:
                    resultn = re.match(numbers, Temp_Token)
                    if (resultn is not None) == True:
                        outfile.write("Number: " + Temp_Token + "\n")
            Temp_Token=""
            outfile.write("; \n")
    if Temp_Token in reservedWords:
        outfile.write("Reserved Word: " + Temp_Token + "\n")
    else:
        result = re.match(identifier, Temp_Token)
        if (result is not None) == True:
            outfile.write("Identifier: " + Temp_Token + "\n")
        else:
            resultn = re.match(numbers, Temp_Token)
            if (resultn is not None) == True:
                outfile.write("Number: " + Temp_Token + "\n")
    Temp_Token=""
f.close()
outfile.close()
