// Vigenere Pset 2
// CS50x - 2014 - HarvardX
// Rômulo Ponciano - romulo_37@hotmail.com

/* Your final challenge this week is to write, 
in vigenere.c, a program that encrypts messages 
using Vigenère’s cipher. 
You must treat A and a as 0, B and b as 1, … , 
and Z and z as 25.
ci = (pi + kj) % 26
*/


#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{   int i, j, Slength, Klength, crpt;
   
    //errors 
    if(argc!=2)
    {   printf("Error. Insert 2 arguments.\n");   
        return 1;
    }
    
    string k=argv[1];

    Slength=strlen(argv[1]);
    for(i=0; i<Slength; i++)
    {   
        if((k[i]>='0') && (k[i]<='9'))
        {   printf("Insert a keyword without numbers.\n");
            return 1;
        }
    } //end-erros
                    
    string orgtext=GetString();
    
    Slength=strlen(orgtext);
    Klength=strlen(k);
    
    // encrypt
    for(i=0, j=0; i<Slength; i++, j++)
    {   if( j>(Klength-1) ) {  j=0; }
        
        if((orgtext[i]>='A') && (orgtext[i]<='Z'))
        {   if((k[j]>='A') && (k[j]<='Z'))
            {   crpt=((((orgtext[i]-'A')+(k[j]-'A'))%26)+'A');
                printf("%c", crpt);        
            }
            else
            {   crpt=((((orgtext[i]-'A')+(k[j]-'a'))%26)+'A');
                printf("%c", crpt);        
            }
        }
        
        if((orgtext[i]>='a') && (orgtext[i]<='z'))
        {   if((k[j]>='a') && (k[j]<='z'))
            {   crpt=((((orgtext[i]-'a')+(k[j]-'a'))%26)+'a');
                printf("%c", crpt);        
            }
            else
            {   crpt=((((orgtext[i]-'a')+(k[j]-'A'))%26)+'a');
                printf("%c", crpt);        
            }
        }
        
        if(!(isalpha(orgtext[i])))
        {   printf("%c", orgtext[i]); 
            j--;
        }
    }
    
    printf("\n");
    
    return 0;
}
