// Mario Pset 1
// CS50x - 2014 - HarvardX
// Rômulo Ponciano - romulo_37@hotmail.com

/* 
Write, in a file called mario.c in your 
~/Dropbox/pset1 directory, a program that recreates 
this half-pyramid using hashes (#) for blocks. 
However, to make things more interesting, first prompt 
the user for the half-pyramid’s height, a non-negative 
integer no greater than 23. (The height of the 
half-pyramid pictured above happens to be 8.) If the 
user fails to provide a non-negative integer no 
greater than 23, you should re-prompt for the same 
again. Then, generate (with the help of printf and 
one or more loops) the desired half-pyramid. Take care 
to align the bottom-left corner of your half-pyramid 
with the left-hand edge of your terminal window, as in 
the sample output below, wherein underlined text 
represents some user’s input. 
*/

#include <stdio.h>
#include <cs50.h>
#define LIMIT_H 23

int main()
{   int height, endlp, i, j, cont;
    
    endlp=0;
    //loop for test numbers
    while (endlp!=1)
    {   // pyramid's height
        printf("\nPlease, insert the pyramid\'s height: ");
        height=GetInt();
        //test height
        if ((height<0)||(height>LIMIT_H))
        {   endlp=0;
            printf("\nPlease, insert a number between 1 and 23");
        }
        else { endlp=1; }
    }
    
    // pyramid
    for(i=height; i>0; i--)
    {   //right align
        for(cont=i-1; cont>0; cont--) { printf(" "); }
        //hashtags
        for(j=i-2; j<height; j++) { printf("#"); }
        printf("\n");
    }
    
    return 0;
}
