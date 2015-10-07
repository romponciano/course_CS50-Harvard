/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: comment me
    /* Checks if the main function is receiving a number 
    of arguments, different from 2 AND 3. If so, a message 
    informs the user and the function returns 1. */
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // TODO: comment me
    /* Grab the string that's in argv[1] and 
    transforms into int, associating this value (int) 
    to the variable n. 
    To see how many numbers will be generated. */
    int n = atoi(argv[1]);

    // TODO: comment me
    /* Here we check if we receive 3 arguments (program 
    name, how many numbers will be generated and the seed).
    If so, the seed will be generated from the value of 
    the 3rd argument (using the function atoi(argv [2])). 
    If we don't receive a third argument, the function
    time(NULL) will transform the seed according to time.
    */
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // TODO: comment me
    /* Generate n "random" numbers, where n equals 
    the number of the second argument (argv[1]). 
    The random numbers ranging from 0 until LIMIT 
    (which was set to 65536 in the "header"). */
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // that's all folks
    return 0;
}
