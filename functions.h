#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 20

#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

struct pixel
{
    int line;
    int pos;
};
struct block
{
    pixel firstDot;
    pixel secondDot;
    const char *shape;
};

void print_line(int num);
void print_spaces(int num);
void print_tabs();
void borders(int width, int height);
void replace_line(int line, const char text[], int after_space);
void edit_line(int line, const char text[], int start_pos);
void moveLinesDown(int line);
void checkforFilledLines();
int KeyPressed(block b);
int isEmpty(int line);
int isFilled(int line);
int lineSize(int line);
void construct(block b);
void deconstruct(block b);
int collision(block b, int side);
int MinScore(int lev);

using namespace std;
