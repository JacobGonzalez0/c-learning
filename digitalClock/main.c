#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int main()
{
    int hour = 0,
        min = 0,
        second = 0;

    initscr(); // starts ncurses
    curs_set(1); 
    keypad(stdscr, true);
    nodelay(stdscr, FALSE); 

    bool ready = false;

    while(!ready)
    {
        printw("Please enter a time format in HH:MM:SS\n");
        refresh();

        scanw("%d:%d:%d", &hour, &min, &second); // ask for format
    
        if(hour < 25 && min < 61 && second < 61) // input validation
        {
            ready = true;
            break;
        }    
        
        printw("Please enter a valid time \n");
        refresh();
    }


    nodelay(stdscr, TRUE); 
    noecho(); // do not echo input 
    curs_set(0); // no cursor

    while(1)
    {
        clear();

        printw("%02d:%02d:%02d", hour, min, second);

        if( hour < 12)
        {
            printw(" AM\n");
        }
        else
        {
            printw(" AM\n");
        }

        second++;

        //clock logic
        if( second == 60)
        {
            second = 0;
            min++;
            if(min == 60)
            {
                hour++;
                if(hour == 24)
                {
                    hour = 0;
                }
            }
        }

        refresh();
        sleep(1);

        int ch = getch();
        if( ch == ' ')
        {
            break; // leave the loop if space press
        }
    }
    endwin();
    return 0;

}