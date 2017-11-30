This is quite simple implementation for RC4 stream encryption algorithm, so you will find a header file “RC4.h” which contains the RC4 function prototype, and implementation file which contains the implementation in “RC4.c”.
for compiling you can have 3 options:
	
	1. Mac osx user ==>

		please use XCode, by creating new project, then add the 3 files to it, change the Running option to be from Terminal instead of XCode, from XCode you can find the path of the executable file, so you can call it and passing the paramters like the below:
	
        	pathToTheExecutable Encrypt ~/Desktop/plainText.txt ~/Desktop/key.txt ~/Desktop/Cipher.txt
        	pathToTheExecutable Decrypt ~/Desktop/Cipher.txt ~/Desktop/key.txt ~/Desktop/plainText.txt

	for more info about XCode, please refer to XCode help guide, or just Google it.
	OR you can follow the below steps as Mac OSX is based on unix, so we can do it, just follow it.

	2. Linux/unix user ==> please use GCC compiler to compiler the files using the below command:
	
		gcc main.c -o main.o -c
		gcc RC4.c -o RC4.o -c
		gcc -o RC4 main.o RC4.o

	then you can run it by the below command for example:
	
	To Decrypt Cipher File, just give it the path (relative or absolute) for the Cipher file, then the path of the key file, then path or file name to create it if not exist to write the decrypted plain text on it.
	./RC4 Decrypt ~/Desktop/Cipher.txt ~/Desktop/key.txt ~/Desktop/plainText.txt

	To Encrypt plain text File, just give it the path (relative or absolute) for the plain text file, then the path of the key file, then path or file name to create it if not exist to write the encrypted plain text on it.
	./RC4 Decrypt ~/Desktop/Cipher.txt ~/Desktop/key.txt ~/Desktop/plainText.txt


	3. Windows user ==> just install GCC compiler and follow the previous steps, for more info about installing GCC, please refer to this link: https://gcc.gnu.org/install/binaries.html
