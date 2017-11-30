//
//  main.c
//  RC4 Implementation
//
//  Created by khaled salem on 11/23/17.
//  Copyright © 2017 khaled Fawzy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "RC4.h"

//Function to read file by getting pointer to the file name to return the file contents and file size
unsigned char * readFile(FILE *f,long *fsize)
{
    unsigned char * data;
    fseek (f,0,2);
    long x =ftell(f);
    *fsize = x;
    fseek (f,0,0);
    data = (unsigned char *) calloc(*fsize+10,sizeof(unsigned char));
    memset (data,0,*fsize+10);
    fread(data,1,*fsize,f);
    fclose (f);
    return data;
}


// function to decrypt data in the sourceFile using keyFile then store the Cipher in resultFile
void Encryptor(const char *sourceFile, const char  *keyFile, const char *resultFile)
{
    unsigned char * data;
    unsigned char * Cypher;
    long fsize,ksize ;

    FILE * f = fopen (sourceFile,"rb");
    data = readFile(f,&fsize);
    Cypher = (unsigned char *) calloc(fsize+10,sizeof(unsigned char));
    memset (Cypher,0,fsize+10);
    unsigned char* key;
    f = fopen (keyFile,"rb");
    key = readFile(f,&ksize);
    
    if(ksize > 256) // check length key to keep sure that it's less than or equal 256 byte
    {
        printf("Key length can not be more than 256 byte according to the RC4 algorithm");
        exit(0);
    }
    
    //printing plain text on console
    printf("\nPlain Text from %s:\n%s\n",sourceFile, data);
    
    //printing Key text on console
    printf("\nKey from %s:\n%s\n",keyFile, key);
    
    //Calling the RC4 function to do the encryption and return result in Cypher
    RC4(data, fsize-1, key,ksize,Cypher);
    
    //printing Cipher result on console to the user in HEX format
    printf("\n\nCipher written to %s: \n",resultFile);
    for (int i = 0 ; i < fsize-1;i++)
    {
        printf("%02hhX  ",Cypher[i]);
    }
    printf("\n\n");
    
    /* Write Cipher to the resultFile */
    f = fopen(resultFile, "w");
    fwrite(Cypher, 1, fsize, f);
    fclose(f);
    
    //release the pointers in memory
    free (data);
    free (Cypher);
    free (key);
}


void Decryptor(const char *sourceFile, const char  *keyFile, const char *resultFile)
{
    unsigned char * data;
    unsigned char * Cypher;
    long fsize,ksize;

    FILE * f = fopen (sourceFile,"rb");
    Cypher = readFile(f,&fsize);
    data = (unsigned char *) calloc(fsize+10,sizeof(unsigned char));
    memset (data,0,fsize+10);
    unsigned char* key;
    f = fopen (keyFile,"rb");
    key = readFile(f,&ksize);
    if(ksize > 256)
    {
        printf("Key length can not be more than 256 byte according to the RC4 algorithm");
        exit(0);
    }
    
     //printing Cipher result on console to the user in HEX format
    printf("\n\nCipher from  %s: \n",sourceFile);
    for (int i = 0 ; i < fsize-1;i++)
    {
        printf("%02hhX  ",Cypher[i]);
    }
    printf("\n\n");
    
    //printing Key text on console
    printf("\nKey from %s:\n%s\n",keyFile, key);
    
    //Calling the RC4 function to do the decryption and return result in Cypher
    RC4(Cypher, fsize-1, key,ksize,data);
    
    //printing plain text on console
    printf("\n\nPlain Text written to  %s: \n%s\n\n",resultFile,data);

    /* Write data to the file */
    f = fopen(resultFile, "w");
    fwrite(data, 1, fsize, f);
    fclose(f);
    
    //release the pointers in memory
    free (data);
    free (Cypher);
    free(key);
}




int main(int argc, const char * argv[]) {
    const char *choice = argv[1];
    const char *sourceFile = argv[2];
    const char *keyFile = argv[3];
    const char *resultFile = argv[4];
    if(argc < 5)
    {
        printf("Missing input, it has to be like this: \n");
        printf("\t gcc Encrypt ~/Desktop/plainText.txt ~/Desktop/key.txt ~/Desktop/Cipher.txt\n");
        printf("\t gcc Decrypt ~/Desktop/Cipher.txt ~/Desktop/key.txt ~/Desktop/plainText.txt\n");
        exit(0);
    }
    
    if(strcmp(choice,"Encrypt") == 0)
    {
        Encryptor(sourceFile, keyFile, resultFile);
    }
    else if(strcmp(choice,"Decrypt") == 0)
    {
        Decryptor(sourceFile,keyFile,resultFile);
    }
    else
    {
        printf("usage has to be like :\n");
        printf("\t gcc Encrypt ~/Desktop/plainText.txt ~/Desktop/key.txt ~/Desktop/Cipher.txt\n");
        printf("\t gcc Decrypt ~/Desktop/Cipher.txt ~/Desktop/key.txt ~/Desktop/plainText.txt\n");
        exit(0);
    }
    
    
    exit(1);
 
}
