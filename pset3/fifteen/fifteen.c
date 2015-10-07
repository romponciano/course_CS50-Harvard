/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);


int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

// -------------------------------CREATED FUNCTIONS -----------------------------

// variables to search-swap-move
int posi=0, posj=0;

// search tile
bool search(int tile)
{
    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(board[i][j]==tile)
            {   
                posi=i;
                posj=j;
                return true;    
            }
        }
    }
    
    return false;
}

// swap variables
void swap(int i2, int j2)
{
    int tmp=0;
    tmp=board[posi][posj];
    board[posi][posj]=board[i2][j2];
    board[i2][j2]=tmp;
}

// check if it's possible move and direction, to swap
bool check(void)
{
    int left, right, top, bot;
    left=board[posi][posj-1];
    right=board[posi][posj+1];
    top=board[posi-1][posj];
    bot=board[posi+1][posj];
    
    if(left==179)
    { 
        swap(posi, posj-1);
        return true;
    }
    else if(right==179)
    { 
        swap(posi, posj+1);
        return true;  
    }
    else if(top==179)
    { 
        swap(posi-1, posj);
        return true;
    }
    else if(bot==179)
    { 
        swap(posi+1, posj);
        return true; 
    }
    
    return false;
}

// god cheat for fast tests
// Obs. Go to move function to see how turn on the cheat
void godmode(void)
{
    int cont=1;
    
    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            board[i][j]=cont;
            cont++;
            if((i==d-1) && (j==d-1))
            {   board[i][j]=179; }
        }
     }
} 


// ------------------- ALL THE OTHERS FUNCTIONS ------------------------------ 

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    int cont=d*d-1, check=0;

    if((cont%2)!=0)
    {   check=1;    }
    
    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            board[i][j]=cont;
            cont--;
            if((i==d-1) && (j==d-1))
            {   board[i][j]=179; }
            else if(board[i][j]==1)
            {
                if(check==1)
                {   
                    int tmp;
                    tmp=board[i][j];
                    board[i][j]=board[i][j-1];
                    board[i][j-1]=tmp;
                }
            }
        }
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(board[i][j]==179)
            {   printf(" %c  ", board[i][j]);   }
            else if(board[i][j]>=10)
            {   printf("%d  ", board[i][j]);    }
            else
            {   printf(" %d  ", board[i][j]);   }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */

bool move(int tile)
{
    // turn off coment to use cheat
    /* 
    if(tile==999)
    {   godmode();  }
    */

    // TODO
    if( (!search(tile)) || (!check()) )
    {   return false;   }
    else
    {   return true;   }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int cont=1;

    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(( i==d-1) && (j==d-1))
            {   return true;    }
            else if(board[i][j]==cont)
            {   cont++;         }
            else
            {   return false;   }
        }
    }
    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
