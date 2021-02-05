#include "functions.h"

int lives;
int level;
int score;
int total_score;
int SPEED = 1;
int multiplier;

extern char majorText[HEIGHT+1][WIDTH+1];
extern int sizeText[HEIGHT+1];

//Function Definitions

void main_loop();

void colourize()
{
    //char f = (rand()%9)+48;
    char s = (rand()%8)+48;
    char f = (rand()%8)+48;
    //char s = (rand()%16)+48;
    //if(f > 57) f+= 7;
    //if(s > 57) s+= 7;
    string color = "Color ";
    color = color + f + s;
    system(color.c_str());
    //system("Color 02");
}

void main_loop()
{
    for(;;)
    {
        int break_loop = 0;
        int rand_pos = (rand()%(WIDTH-3))+2;
        block b = {{1,rand_pos}, {2-(rand()%2),(rand_pos+1)-(rand()%3)}, "+"};
        construct(b);
        for(int line=1; line < HEIGHT; line++)
        {
            borders(WIDTH,HEIGHT);
            Sleep(SPEED*multiplier);
            if(collision(b, DOWN))
            {
                if(line == 1 || line == 2) break_loop = 1;
                //br_line = line;
                system("cls");
                break;
            }
            if(b.secondDot.line < HEIGHT-1)
            {
                deconstruct(b);
                switch(KeyPressed(b))
                {
                    case LEFT:
                    {
                        --b.firstDot.pos;
                        --b.secondDot.pos;
                        break;
                    }
                    case RIGHT:
                    {
                        ++b.firstDot.pos;
                        ++b.secondDot.pos;
                        break;
                    }
                    case UP:
                    {
                        if((b.firstDot.line > b.secondDot.line || b.secondDot.line > b.firstDot.line) && b.firstDot.pos == (b.secondDot.pos-1))
                        {
                            b.firstDot.pos++;
                            b.secondDot.pos--;
                        }
                        else if((b.firstDot.line > b.secondDot.line || b.secondDot.line > b.firstDot.line) && b.firstDot.pos == (b.secondDot.pos+1))
                        {
                            b.firstDot.pos--;
                            b.secondDot.pos++;
                        }
                        else if(b.firstDot.line != b.secondDot.line && b.firstDot.pos == b.secondDot.pos && (b.secondDot.pos+1) != WIDTH)
                        {
                            b.secondDot.line = b.firstDot.line;
                            b.secondDot.pos++;
                        }
                        else if(b.firstDot.line == b.secondDot.line && b.firstDot.pos != b.secondDot.pos)
                        {
                            b.secondDot.line++;
                            b.secondDot.pos = b.firstDot.pos;
                        }
                        break;
                    }
                }
                edit_line(++b.firstDot.line, b.shape, b.firstDot.pos);
                edit_line(++b.secondDot.line, b.shape, b.secondDot.pos);
            }
            system("cls");
            //for(int i=0; i < 62; i++) printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        }
        score++;
        checkforFilledLines();
        if(score >= MinScore(level))
        {
            colourize();
            level++;
            total_score+=score;
            score = 0;
            multiplier-=2;
            for(int i=0; i<HEIGHT;i++) replace_line(i," ", 0);
            system("cls");
            printf("\n\n\t\t\tLEVEL UP!!\n\n");
            Sleep(1000);
            system("cls");
            printf("\n\n\t\t\tLevel %d", level);
            Sleep(1000);
            system("cls");
        }
        if(break_loop) break;
    }
    lives--;
    score = 0;
    system("cls");
    system("Color 04");
    printf("\n\n\t\t\tYou lost! %d lives REMAINING\n\n", lives);
    Sleep(2000);
    system("cls");

    if(lives != 0)
    {
        colourize();
        system("cls");
        printf("\n\n\t\t\tLevel %d", level);
        Sleep(2000);
        system("cls");
    }

}

int main()
{
    int opt;
    MAIN_MENU:
    cout << "Welcome to TETRIS!\n" << endl;
    cout << "1. Play game" << endl;
    cout << "2. Settings" << endl;
    cout << "3. Quit\n" << endl;
    cout << "[INPUT]: ";
    cin >> opt;
    switch(opt)
    {

        case 1: //PLAY GAME
        {
            int try_again = 1;
            srand (time(NULL));
            while(try_again)
            {
                system("cls");
                lives = 3;
                level = 1;
                score = 0;
                total_score = 0;
                multiplier = 18;
                int response;
                while(1)
                {
                    for(int i=0; i<HEIGHT;i++) replace_line(i," ", 0);
                    if(lives == 0) break;
                    main_loop();
                }
                system("cls");
                system("Color 40");
                printf("\n\n\t\t\t\tGAME OVER\n\n");
                Sleep(2000);
                system("cls");
                system("Color 07");
                printf("Your total score is %d.\n", total_score);
                printf("Do you want to play again? (1 - Yes / 0 - No) ");
                cin >> response;
                if(response != 1) try_again = 0;
                system("cls");
            }
            //printf("Enter your name: ");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "- SETTINGS - \n" << endl;
            cout << "1. Change Speed\n"
                 << "2. Go back\n\n"
                 << "[INPUT]: ";
            cin >> opt;
            system("cls");
            switch(opt)
            {
                case 1:
                cout << "Current speed = " << SPEED << endl;
                cout << "Enter speed (1 = FASTEST, 10 = SLOWEST): ";
                cin >> SPEED;
                cout << "Speed has been set to " << SPEED << ".\n\n";
                break;
            }
            break;
        }
        case 3:
        {
            exit(0);
        }
    }
    goto MAIN_MENU;
    return 0;
}
