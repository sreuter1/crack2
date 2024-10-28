#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));
    char hashLine[HASH_LEN];
    int isMatch = 0;

    // Open the hash file
    FILE * inFile = fopen(hashFilename, "r");

    // Loop through the hash file, one line at a time.
    while (fgets(hashLine, HASH_LEN, inFile))
    {
        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        isMatch = strcmp(hash, hashLine);

        // If there is a match, you'll return the hash.
        // If not, return NULL.
        if (isMatch)
        {
            break;
        }

    }

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
    fclose(inFile);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    if (!isMatch)
    {
        return NULL;
    }
    return hash;

}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }
    
    // Open the dictionary file for reading.
    FILE * dictFile = fopen(argv[2], "r");
    char hash[HASH_LEN];
    char dictLine[PASS_LEN];
    char str[HASH_LEN];
    int count = 0;

    while(fgets(dictLine, PASS_LEN, dictFile))
    {
        // For each dictionary word, pass it to tryWord, which
        // will attempt to match it against the hashes in the hash_file.
        strcpy(str, dictLine);
        char * hash = tryWord(str, argv[1]);

        // If we got a match, display the hash and the word. For example:
        //   5d41402abc4b2a76b9719d911017c592 hello
        if (strcmp(hash, str))
        {
            count++;
            printf("%s   %s", hash, dictLine);
        }
        

    }

    // Close the dictionary file.
    fclose(dictFile);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!\n", count);

    // Free up any malloc'd memory?
    
}

