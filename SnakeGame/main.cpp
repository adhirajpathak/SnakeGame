//
//  main.cpp
//  SnakeGame
//
//  Created by Adhiraj Pathak on 7/30/19.
//  Copyright © 2019 Adhiraj Pathak. All rights reserved.
//

#include <cstdlib>
#include <ncurses.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP =0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int TailX[100], TailY[100];
int nTail = 0;

void Setup() {
    
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    
    gameOver = false;
    dir = STOP; //the snake will not move until we start moving it
    x = width /2; //so its in the middle
    y = height /2;
    fruitX = (rand() % width) + 1;
    fruitY = (rand() % height) + 1;
    score = 0;
    
}
//#####
//#   #
//#####
void Draw() {
    
    clear();
    
    for(int i = 0; i < width+2; i++)
        mvprintw(0,i,"+");
    
    for(int i = 0; i < height+2; i++) {
        for(int j = 0; j < width+2; j++) {
            if(i == 0 | i == 21)
                mvprintw(i,j,"+"); //Boundaries Row
            else if(j ==0 | j ==21)
                mvprintw(i,j,"+"); //Boundaries Column
            else if(i == y && j == x)
                mvprintw(i,j,"O"); //Snake
            else if(i == fruitY && j == fruitX)
                mvprintw(i,j,"0"); //to get the fruit
            else
                //find all the points where tail section needs to be
                for(int k = 0; k < nTail; k++) {
                    if(TailX[k] == j && TailY[k] == i)
                        mvprintw(i, j, "o"); //tail trailing
                }
        }
    }
    
    mvprintw(23,0,"Score %d",score);
    
    refresh();
    
    
}

void Input() {
    
    keypad(stdscr, TRUE); //be prepared for any input to use the arrow keys
    halfdelay(1); //press it once and the snake keeps moving in that direction
    
    int c = getch();
    
    switch (c) {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 113:
            gameOver = true;
            break;
    }
}

void Logic() {

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    
    for(int i = 1; i < nTail; i++) {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
            
        default:
            break;
    }
    if(x > width || x < 1 || y < 1 || y> height)
        gameOver = true;
    
    if(x == fruitX && y == fruitY) {
        score++;
        fruitX = (rand() % width) +1;
        fruitY = (rand() % height) + 1;
        nTail++;
    }
    
    for(int i = 0; i < nTail; i++)
        if(TailX[i] == x && TailY[i] == y) {
            gameOver = true;
        }
}

int main() {
    
    Setup();
//    Draw(); //stop the computer from getting stuck in the loop
        while(!gameOver) {
            Draw();
            Input();
            Logic();
        }
    getch();
    endwin();
    
    return 0;
}
