To run, please open a shell/terminal at the location of the scripts then:

-> Type: python genfun.py "inputfile.txt" "outputfile.txt"
	to perform the generator function on an inputfile, provided with the code is an example of an inputfile so the command would be:
>> python genfun.py geninput.txt genoutput.txt

Please add double quotation marks around each file name if the input file isn't recognized correctly when you enter the command.

This would generate a text file with the transmitted message and the generator polynomial once again (to be transmitted to the verifier)


-> Type: python ver.py "genoutput.txt"
	where genoutput.txt is the outputfile from the genfun

-> Type: python alter.py "genoutput.txt" index-to-be-altered
	and this would toggle the bit at the index specified (starting from 1)

And that's it.

Provided with the scripts are an input text file, an output text file and screenshots from the terminal running the code.