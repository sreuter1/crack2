#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

// compares the hash of the plaintext to the hashes in the hashFile.


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext to compare to the hashes in the file
    char *hash = md5(plaintext, strlen(plaintext));
    
    // declaring the variable to store the lines from the hashFile
    char hashLine[HASH_LEN];

    // Open the hash file
    FILE * hashFile = fopen(hashFilename, "r");

    // Loop through the hash file, one line at a time.
    while (fgets(hashLine, HASH_LEN, hashFile)) // getting the line from the hashFile and storing it in hashLine
    {
        // trim off the newline 
        for(int i = 0; i < strlen(hashLine) ; i++)
        {
            if(hashLine[i] == '\n')
            {
                hashLine[i] = '\0';
                break;
            }
        }
        
        // If there is a match, you'll return the hash.
        // If not, return NULL.
        if (strcmp(hash, hashLine))
        {
            fclose(hashFile);
            return hash; // rather than hashLine because this isn't local
        }

    }

    // closing file and checking the memory
    fclose(hashFile);

    // returning null because this accounts for the case that 
    return NULL;

}


int main(int argc, char *argv[])
{
    // makes sure that it gets the correct arguments.
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }
    
    // Open the dictionary file for reading.
    FILE * dictFile = fopen(argv[2], "r");
    char hash[HASH_LEN];
    char plainText[PASS_LEN];
    char str[HASH_LEN];
    int count = 0;

    while(fgets(plainText, PASS_LEN, dictFile)) // gets the plaintext word from the file and runs it into tryWord
    {
        // trim the newline off of the plainText
        for(int i = 0; i < strlen(plainText) ; i++)
        {
            if(plainText[i] == '\n')
            {
                plainText[i] = '\0';
                break;
            }
        }

        // enters in the line from the plantext and the name of the hash file
        char * hash = tryWord(plainText, argv[1]);

        // If it doesn't return null print it and count it
        if (hash != NULL)
        {
            count++;
            printf("%-25s%s\n", plainText, hash);
        }
        free(hash);
        hash = NULL;

    }

    // Close the dictionary file.
    fclose(dictFile);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!\n", count);

    // Free up any malloc'd memory... probably hash from calling the 
    
}

