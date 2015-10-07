// Caesar Pset 2
// CS50x - 2014 - HarvardX
// Rômulo Ponciano - romulo_37@hotmail.com

/*
your next goal is to write, in caesar.c, a program that 
encrypts messages using Caesar’s cipher. 
ci = (pi + k) % 26
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{   int i, Slenght;
   
    //errors 
    if(argc!=2)
    {   printf("Error. Insert 2 arguments.\n");   
        return 1;
    }
    
    int k=atoi(argv[1]);
    if(k<0)
    {   printf("Insert a non-negative caracter.\n");
        return 1;
    }
    
    Slenght=strlen(argv[1]);
    for(i=0; i<Slenght; i++)
    {   if(isalpha(argv[1][i]))
        {   printf("You need insert english alphabetic characteres (A - Z; a - z).\n");
            return 1;
        }
    } //end-erros
        
                
    string orgtext=GetString();
    Slenght=strlen(orgtext);
    // encrypt
    for(i=0; i<Slenght; i++)
    {   if((orgtext[i]>='A') && (orgtext[i]<='Z'))
        {   orgtext[i]=orgtext[i]-'A';
            orgtext[i]=(orgtext[i]+k)%26;
            orgtext[i]=orgtext[i]+'A';
            printf("%c", orgtext[i]);
        }
        
        if((orgtext[i]>='a') && (orgtext[i]<='z'))
        {   orgtext[i]=orgtext[i]-'a';
            orgtext[i]=(orgtext[i]+k)%26;
            orgtext[i]=orgtext[i]+'a';
            printf("%c", orgtext[i]);        
        }
        
        if(!(isalpha(orgtext[i])))
        {   printf("%c", orgtext[i]); }
    }
    
    printf("\n");
    
    return 0;
}
