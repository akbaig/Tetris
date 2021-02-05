#include "functions.h"

extern int lives;
extern int level;
extern int score;

char majorText[HEIGHT+1][WIDTH+1];

void replace_line(int line, const char text[], int after_space = 0)
{
    for(int i=0; i < after_space; i++)
    {
        majorText[line][i] = ' ';
    }
    for(unsigned int i = after_space; i < after_space+strlen(text); i++)
    {
        majorText[line][i] = text[i-after_space];
    }
    for(int i = after_space+strlen(text); i < WIDTH; i++)
    {
        majorText[line][i] = ' ';
    }
}
void edit_line(int line, const char text[], int start_pos=0)
{
    if(!isEmpty(line))
    {
        for(int i = start_pos; i < start_pos+ (int)strlen(text); i++)
            majorText[line][i] = text[i-start_pos];
    }
    else
        replace_line(line, text, start_pos);

}
void moveLinesDown(int line)
{
    for(int i = line; isEmpty(i-1) == 0; i--)
    {
        replace_line(i, majorText[i-1]);
        replace_line(i-1, " ");
    }
}
void checkforFilledLines()
{
    for(int i = HEIGHT-1; i > 1; i--)
    {
        if(isFilled(i))
        {
            replace_line(i," ");
            moveLinesDown(i);
            score += 10;
        }
    }
}
int lineSize(int line)
{
    int ret_val = 0;
    for(int i = 0; i < WIDTH; i++)
    {
        if(majorText[line][i] != ' ') ret_val = i;
    }
    return ret_val;
}
int textSize(int line)
{
    int starting = 0, ret_val = 0;
    for(int i = 0; i < WIDTH; i++)
    {
        if(majorText[line][i] != ' ')
        {
                if(starting == 0) starting = i;
                else ret_val = i;
        }
    }
    ret_val -= starting;
    return ret_val;
}
int isEmpty(int line)
{
    int check = 1;
    for(int i=0;i<WIDTH;i++)
        if(majorText[line][i] != ' ') check = 0;
    return check;
}
int isFilled(int line)
{
    int check = 1;
    for(int i=0;i<WIDTH;i++)
    {
        if(majorText[line][i] == ' ')
        {
            check = 0;
            break;
        }
    }

    return check;
}
int KeyPressed(block b)
{
    int left_end = (b.firstDot.pos < b.secondDot.pos ? b.firstDot.pos : b.secondDot.pos);
    int right_end = (b.firstDot.pos > b.secondDot.pos ? b.firstDot.pos : b.secondDot.pos);
    if((GetKeyState(VK_LEFT) & 0x8000) && left_end != 0 &&  !collision(b, LEFT)) return LEFT;
    else if((GetKeyState(VK_RIGHT) & 0x8000) && right_end < WIDTH-1 && !collision(b, RIGHT)) return RIGHT;
    else if((GetKeyState(VK_UP) & 0x8000)) return UP;
    else return NONE;
}
void print_line(int num)
{
    printf(" ");
    for(int i = 0; i < num; i++) printf("-");
}
void print_spaces(int num)
{
    for(int i = 0; i < num; i++) printf(" ");
}
void print_tabs()
{
     printf("\t\t\t");
}
void borders(int width, int height)
{

    printf("\t\t\t(Level: %d)\n\n", level);
    printf("- Lives: %d\n", lives);
    printf("- Score: %d (%d to reach next level)\n", score, MinScore(level) - score);
    for(int i=0; i<=height;i++)
    {
        print_tabs();
        if(i == 0 || i == height)
        {
            print_line(width);
        }
        else
        {
            printf("|");
            printf("%s", majorText[i]);
            printf("|");
        }
        puts("");
    }
}
int MinScore(int lev)
{
    return 22+(lev*lev);
}
void construct(block b)
{
    replace_line(b.firstDot.line, b.shape, b.firstDot.pos);
    replace_line(b.secondDot.line, b.shape, b.secondDot.pos);
}
void deconstruct(block b)
{
    edit_line(b.firstDot.line, " ", b.firstDot.pos);
    edit_line(b.secondDot.line, " ", b.secondDot.pos);
}
int collision(block b, int side)
{
    switch(side)
    {
        case DOWN:
            if(majorText[b.firstDot.line+1][b.firstDot.pos] != ' ' && !((b.firstDot.line+1) == b.secondDot.line && b.firstDot.pos == b.secondDot.pos)) return 1;
            else if(majorText[b.secondDot.line+1][b.secondDot.pos] != ' ') return 1;
            break;
        case LEFT:
            if(/*majorText[b.firstDot.line][b.firstDot.pos-1] != ' ' || */majorText[b.firstDot.line+1][b.firstDot.pos-1] != ' ') return 1;
            else if(/*majorText[b.secondDot.line][b.secondDot.pos-1] != ' '|| */majorText[b.secondDot.line+1][b.secondDot.pos-1] != ' ') return 1;
            break;
        case RIGHT:
            if(/*majorText[b.firstDot.line][b.firstDot.pos+1] != ' ' || */majorText[b.firstDot.line+1][b.firstDot.pos+1] != ' ') return 1;
            else if(/*majorText[b.secondDot.line][b.secondDot.pos+1] != ' ' || */majorText[b.secondDot.line+1][b.secondDot.pos+1] != ' ') return 1;
            break;
        case UP:
            break;
    }
    return 0;
}
