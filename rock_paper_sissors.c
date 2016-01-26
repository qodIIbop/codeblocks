#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define PLAYERWIN 10
#define COMPWIN 11
#define DRAW 12
#define CERTAIN -1

/************************************************
 * This Program let's you play the classic game *
 * of Rock,Paper,Scissors against the computer  *
 *              0=rock                          *
 *              1=paper                         *
 *              2=scissors                      *
 ************************************************/
/*make a program to play rock, paper, sissors against the computer.
Comp chooses at random. Player types a number between 0-3. Ask player if he wants to go another round.

Algorithm:
0<2,1<0,2<1,*/
int comp_choice;
int player_choice;

void seedrnd()
{
    srand(time(NULL));
}

void rnd()
{
    comp_choice=(rand()%3)+1;
    printf("%d\n\n",comp_choice);
    sleep(1);
}

int compare_choice()
{
    if(comp_choice==ROCK && player_choice==SCISSORS)
    {
        return COMPWIN;
    }
    else if(comp_choice==PAPER && player_choice==ROCK)
    {
        return COMPWIN;
    }
    else if(comp_choice==SCISSORS && player_choice==PAPER)
    {
        return COMPWIN;
    }
    else if(comp_choice==player_choice)
    {
        return DRAW;
    }
    else
    {
        return PLAYERWIN;
    }
}

int main()
{
    int win,error;

    printf("Press a number between 1-4.\nRock=1\nPaper=2\nScissors=3!\n");
    error=scanf("%d",&player_choice);
//debug        printf("error=%d\n",error);
    if(error=0 || player_choice>SCISSORS || player_choice<ROCK)
    {
        printf("Invalid input!");
        return 0;
    }

    seedrnd();
    rnd();
    win=compare_choice();
    if(win==PLAYERWIN)
    {
        printf("You have won!\n\n");
    }
    return 0;
}









