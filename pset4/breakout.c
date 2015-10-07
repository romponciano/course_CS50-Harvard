//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

void removeGWindow(GWindow gw, GObject gobj);
GLabel GameOver(GWindow window);
GLabel Winner(GWindow window);

// global var
int p=0;

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    double velY=drand48()+2.70;
    double velX=-drand48()+2.70;

    // wait for click before stating
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // pad move
        double yp = (getHeight(window)- getHeight(paddle));
        GEvent event = getNextEvent(MOUSE_EVENT);
        if(event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double xp = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, xp, yp);
            }
        }

        // ball move
        move(ball, velX, velY);
        pause(15);

        // collisions
        GObject obj = detectCollision(window, ball);

        // paddle
        if(obj==paddle)
        {   velY = -velY;   }

        // brick
        else if(strcmp(getType(obj), "GRect") == 0)
        {
            removeGWindow(window, obj);
            velY = -velY;
            p++;
            bricks--;
            updateScoreboard(window, label, p);
        }

        // right
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {   velX = -velX;   }
        // left
        else if (getX(ball) <= 0)
        {   velX = -velX;   }
        // top
        if (getY(ball) <= 0)
        {   velY = -velY;  }
        // bot | -1 live
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            removeGWindow(window, ball);
            ball = initBall(window);
            // if game over
            if(lives==0)
            {   GLabel word = GameOver(window); }
            waitForClick();
        }
    }

    // if winner
    if(bricks==0)
    {
        GLabel word = Winner(window);
        waitForClick();
    }

    closeGWindow(window);
    return 0;
}

// ------------ FUNCTIONS FOR GAME OVER/WIN ---------------
GLabel GameOver(GWindow window)
{
    GLabel word = newGLabel("");
    setFont(word, "SansSerif-36");
    setColor(word, "BLACK");
    add(window, word);

    string go="Game Over =/";
    double x = (getWidth(window)*0.15);
    double y = (getHeight(window) - getHeight(window)*0.2);

    setLocation(word, x, y);
    setLabel(word, go);
    return word;
}

GLabel Winner(GWindow window)
{
    GLabel word = newGLabel("");
    setFont(word, "SansSerif-36");
    setColor(word, "BLACK");
    add(window, word);

    string go="You Win! =)";
    double x = (getWidth(window)*0.15);
    double y = (getHeight(window) - getHeight(window)*0.2);

    setLocation(word, x, y);
    setLabel(word, go);
    return word;
}

// ----------------------- END ---------------------------
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    int y, x;
    string rgb;

    y=30;
    rgb="AA00DD";
    int i, j;
    for(i=ROWS; i>0; i--)
    {
        x=10;
        for(j=COLS; j>0; j--)
        {
            GRect brc = newGRect(x, y, 33, 10);
            setColor(brc, rgb);
            setFilled(brc, true);
            add(window, brc);
            x=x+38;
        }
        y=y+25;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    int r=RADIUS*2;
    double x = (getWidth(window) - r) / 2;
    double y = (getHeight(window)-((getHeight(window))*0.40));
    GOval circle = newGOval(190, 300, r, r);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    int w, h;

    w=50; h=7;
    double x = (getWidth(window) - w) / 2;
    double y = (getHeight(window)- h);
    GRect pad = newGRect(x, y, w, h);
    setColor(pad, "BLACK");
    setFilled(pad, true);
    add(window, pad);
    return pad;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "LIGHT_GRAY");
    add(window, label);

    updateScoreboard(window, label, p);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    object = ball;
    return object;
}
