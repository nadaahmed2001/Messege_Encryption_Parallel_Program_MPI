# Messege_Encryption_Parallel_Program_MPI
Assignment 3 in High performance Computing(Parrallel processing) Encrypt a message using Caesar Cipher.

# Assignment Describtion
#### [Using BCast, Scatter and Gather ONLY]

You are required to take a message from a file and encrypt the message using caesar cipher and store the output in a new file.\
The encryption can be represented using modular arithmetic by first transforming the letters into
numbers, according to the scheme, A = 0, B = 1,…, Z = 25.\

For example :\
Encryption of a letter x by
a shift n can be described mathematically as:
#### En(x) = (x + n) mod 26
Any other character outside the range from A to Z (or a to z) is transferred to the output file as it is.\
**Input:** filename and key/shift value.\
**Output:** new file that contains the encrypted message.

## ScreenShots of my source code output:

**First case:** a messege length is divisible by number of processes, in myfile.txt I have written a string of 16 characters\
so 16/4 = 4 and 16%4=0 ... then each process will handle 4 charachters

![Problem1WithoutRemainder](https://user-images.githubusercontent.com/60941223/233894524-49cae15b-9b89-4f9a-ba23-9fe4299bbaf4.JPG)


**Second case:** a messege length is not divisible by number of processes, in myfile.txt I have written a string of 18 characters\
but 18%4=2...so I have added white spaces to the message with number equals to the number of remainder...so that each process will take equal number of charachters


![Problem1WithRemainder](https://user-images.githubusercontent.com/60941223/233894547-a9a5fe6c-852a-4b3a-997f-438efef206c1.JPG)
