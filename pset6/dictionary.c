/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include "dictionary.h"
 
//store the word file here
store_t s = {};
 
//the hash array (it will become an array later)
dict_node_t **d;
 
uint32_t indexsize;
uint32_t INDXSZ; // = indexsize - 1;
 
int q_streq_called = 0;
 
bool check(const char *word) {
    //the word's length... comes in handy
    length_t wlen = strlen(word);
    if (wlen == 0)
        return false;

    char *lowerword = strtolower(word, wlen);
 
    uint32_t index = djb2_ci(lowerword);
 
    dict_node_t *cursor = d[index];
    bool ret = false;
    while (1)
    {
        if (!(cursor)) // loop exit condition.
        {
            ret = false;
            break;
        }
        if (q_streq(cursor->w, lowerword, cursor->l, wlen))
        {
            ret = true;
            break;
        }
        cursor = cursor->next;
    }
    free(lowerword);
    return ret;
}
 
bool load(const char *dict) {
    static bool calledme = false;
    if (calledme)
    {
        printf("Warning, load may only be called once.\n");
        return false;
    }
    calledme = true;
    //initialize store
    s.s = NULL;
    s.size = 0;
    s.wordcount = 0;
 
    FILE *dfp;
    if (!(dict) || !(dict[0]) || (dfp = fopen(dict, "r")) == NULL)
        return false;
 
    if (!(load_storage(dfp)))
    {
        fclose(dfp);
        return false;
    }
    fclose(dfp);
 
    /*
     * from: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
     * compute the next highest power of 2 of 32-bit 
     */
    uint32_t v = s.wordcount / ITEMSPERINDEX;
 
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    indexsize = v;
 
    INDXSZ = indexsize - 1; // defines the INDXSZ used in the hash function.
 
    //allocate the hash array
    d = malloc(indexsize * sizeof (dict_node_t *));
    if (d == NULL)
    {
        return false;
    }
    for (int i = 0; i < indexsize; i++)
    {
        d[i] = NULL; //initialize to NULL
    }
 
    uint32_t cur = 0;
    char *seek;
    while (cur < s.size) // move word by word across s.s until the end.
    {
        seek = &s.s[cur];
        length_t len = (length_t) strlen(seek);
        if (len == 0) 
        {
            cur++;
            continue;
        }
        uint32_t index = djb2_ci(seek);
        d_unshift(index, len, seek); 
        cur += len + 1; 
    } 
 
    return true;
}
 
unsigned int size(void) {
    if (s.s != NULL)
        return s.wordcount;
    return 0;
}
 
bool unload(void) { 
    if (d != NULL)
    {
        //loop around the array d
        dict_node_t *node;
        for (int i = 0; i < indexsize; i++)
            while ((node = d_shift(i)) != NULL)
                free(node);
        //free d itself
        free(d);
    }
    //free the storage space
    if (s.s != NULL)
        free(s.s);
    printf("q_streq_called=%d\n", q_streq_called);
    return true;
}

bool load_storage(FILE *dfp) {
    
    if (s.size || s.s || s.wordcount)
    {
        printf("store structure was already initialized\n");
        return false;
    }
 
    // capacity of store
    unsigned int capacity = 0;
 
    while (1)
    {
        char c = fgetc(dfp);
 
        // grow buffer if necessary
        if (s.size + 1 > capacity)
        {
            if (capacity == 0)
                capacity = 32;
            else
            {
                capacity *= 2;
                if (capacity >= (UINT_MAX))
                {
                    if (s.s) free(s.s);
                    return false;
                }
            }
 
            // extend buffer's capacity
            char *temp = realloc(s.s, capacity * sizeof (char));
            if (temp == NULL)
            {
                if (s.s) free(s.s);
                return false;
            }
            s.s = temp;
        }
 
        if (feof(dfp)) //reached eof
        {
            if (s.size == 0)
            {
                if (s.s) free(s.s);
                return false;
            }
            //at the end of it all make sure there is a '\0'
            if (s.s[ s.size - 1 ] != '\0')
            {
                s.s[ s.size ] = '\0';
                s.wordcount++;
            }
            else 
            {
                s.size--;
            }
            break;
        }
 
        // append current character to s.s
        if (isalpha((int) c) || c == '\'')
        {
            s.s[ s.size ] = c;
            s.size++;
        }
            //but if char is \n
        else if (c == '\n')
        {
            if (s.s[ s.size - 1 ] != '\0')
            {
                s.s[ s.size ] = '\0';
                s.wordcount++;
                s.size++;
            }
        }
        else
        {
            continue; 
        }
    }
 
    s.size = s.size + 1;
 
    // minimize buffer
    char *minimal = malloc(s.size * sizeof (char));
    memcpy(minimal, s.s, s.size);
    free(s.s);
    s.s = minimal;
 
    return true;
}
 
/**
 * a case insensitive version of djb2,
 * from: http://www.cse.yorku.ca/~oz/hash.html
 * @param str
 * @return the hash value of the string, an unsigned 32 bit integer.
 */
uint32_t djb2_ci(const char *str) {
    unsigned long hash = 5381;
    int c;
 
    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(abs(c)); /* hash * 33 + c */
    //case sensitive:   hash = ((hash << 5) + hash) + abs(c); /* hash * 33 + c */
 
    return (uint32_t) hash & INDXSZ;
    /* faster than doing hash % indexsize + 1;
     * from: http://forums.devshed.com/showpost.php?p=231648&postcount=3
     */
}
 
void d_unshift(uint32_t index, length_t len, char *str) {
    //create node
    dict_node_t *newnode = malloc(sizeof (dict_node_t));
    newnode->w = str;
    newnode->l = len;
    newnode->next = NULL;
 
    //check for empty list
    if (d[index] == NULL)
    {
        d[index] = newnode;
    }
        //else unshift into it.
    else
    {
        newnode->next = d[index];
        d[index] = newnode;
    }
}

dict_node_t *d_shift(uint32_t index) {
    if (d[index] != NULL)
    {
        dict_node_t *tmp = d[index];
        d[index] = tmp->next;
        return tmp;
    }
    return NULL;
}
 
bool q_streq(const char *str1, const char *str2, length_t l1, length_t l2) {
    q_streq_called++;
    if (l1 == l2)
    {
        for (int i = 0; i < l1; i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
 
char *strtolower(const char *word, length_t len) {
    char *str = malloc(1 + (len * sizeof (char)));
    for (length_t i = 0; i < len; i++)
    {
        str[i] = tolower((int) word[i]);
    }
    str[len] = '\0';
    return str;
}
