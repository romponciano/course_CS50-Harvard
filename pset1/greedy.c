// Greedy Pset 1
// CS50x - 2014 - HarvardX
// Rômulo Ponciano - romulo_37@hotmail.com

/* Write, in a file called greedy.c in your 
~/Dropbox/pset1 directory, a program that first 
asks the user how much change is owed and then 
spits out the minimum number of coins with which 
said change can be made. Use GetFloat from the 
CS50 Library to get the user’s input and printf 
from the Standard I/O library to output your 
answer. Assume that the only coins available are 
quarters (25¢), dimes (10¢), nickels (5¢), and 
pennies (1¢).
*/

#include <stdio.h>
#include <cs50.h>

// constants
#define Q25 0.25
#define D10 0.10
#define N05 0.05
#define P01 0.01

int main()
{   float value;
    int n_coins, nc25, nc10, nc05, nc01, endlp;  
    
    n_coins=0; nc25=0; nc10=0; nc05=0; nc01=0; 
    
    // test value
    while(endlp!=1)
    {   printf("\n\nHow much change is owed? ");
        value=GetFloat();
        if(value<0)
        {   printf("Please, insert a non-negativa number");
        }
        else { endlp=1; }
    }
    
    
    // $0.25 coins
    nc25=value/Q25;
    value=value-(Q25*nc25);
    // $0.10 coins
    nc10=value/D10;
    value=value-(D10*nc10);
    // $0.05 coins
    nc05=value/N05;
    value=value-(N05*nc05);
    // $0.01 coins
    if((value<=0.04)&&(value>0.031))
    {   nc01=4;
        value=value-0.04;
    }
    if((value<=0.031)&&(value>0.021))
    {   nc01=3; 
        value=value-0.03;
    }
    if((value<=0.021)&&(value>0.011))
    {   nc01=2; 
        value=value-0.02;
    }
    if((value<=0.011)&&(value>0.001))
    {   nc01=1;  
        value=value-0.01;
    }
    
    // total
    n_coins=nc25+nc10+nc05+nc01;

// If you want know the exact number of each coin
/*    
    printf("\n\n%d", nc25);
    printf("\n%d", nc10);
    printf("\n%d", nc05);
    printf("\n%d", nc01);
*/

    printf("%d\n", n_coins);
}
