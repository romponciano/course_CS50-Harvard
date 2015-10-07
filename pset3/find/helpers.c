/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm   
    if(n<0)
    {   return false;   }
    
    int mid=0, beg=0, end=0;
    beg=0;
    end=n;
    mid=(beg+end)/2;
    
    while(beg<=end)
    {
        if(values[mid]==value)
        {   return true;    }
        else if(values[mid]>value)
        {   end=mid-1;  }
        else
        {   beg=mid+1;  }
        
        mid=(beg+end)/2;
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int tmp;
    for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(values[i]<values[j])
            {   
                tmp=values[i];
                values[i]=values[j];
                values[j]=tmp;    
            }
        }
    }    
}
