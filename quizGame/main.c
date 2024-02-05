#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#define MAX_QUESTION 256
#define MAX_ANSWER 128
#define TOTAL_QUESTIONS 5

typedef struct 
{
    char question[MAX_QUESTION];
    char answerA[MAX_ANSWER];
    char answerB[MAX_ANSWER];
    char answerC[MAX_ANSWER];
    char answerD[MAX_ANSWER];
    char correct_answer;
} quiz_question;

quiz_question quiz[TOTAL_QUESTIONS];

void loadQuiz();

int main(void)
{
    //init ncurses
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE); 

    loadQuiz();

    int total_correct = 0;
    char answer;

    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        clear();
        printw("Question %d: %s\n\n", (i+1), quiz[i].question);
        printw("A) %s\n", quiz[i].answerA);
        printw("B) %s\n", quiz[i].answerB);
        printw("C) %s\n", quiz[i].answerC);
        printw("D) %s\n", quiz[i].answerD);
        printw("\n Enter Answer (A,B,C or D): ");
        refresh();
        scanw("%c", &answer);

        if(answer == quiz[i].correct_answer)
        {
            total_correct++;
        }

    }

    clear();
    int total_questions = (sizeof(quiz)/sizeof(quiz[0]));
    float score_percent = ((float)total_correct / total_questions) * 100;
    printw("You got a total of %d correct out of %d \n", total_correct, total_questions);
    printw("Score Percent %.0f%%", score_percent);
     
    printw("\n\n\n Press enter to exit...");
    refresh();

    // hahaha extra wasted cpu cycles
    scanw("%c", &answer);
   
    endwin(); 

    return 0;
}

void loadQuiz()
{
    FILE *fh;

    fh = fopen("quiz.txt", "r");

    if(fh == NULL)
    {
        printw("Cannot read quiz data (quiz.txt)");
        scanw("%c", NULL);
        refresh();

        endwin(); 
        return;
    }

    char c;
    char state = 's'; // states are start = s, and then first char of linebreak
    char qBuffer[MAX_QUESTION]; 
    int q = 0;
    int i = 0;
    char aBuffer[MAX_ANSWER]; 
    while( (c = fgetc(fh)) != EOF)
    {

        //Questions
        if(c == ':')
        {
            // reset the buffer index and clear buffers
            q = 0;
            memset(aBuffer, 0, sizeof(aBuffer)); 
            memset(qBuffer, 0, sizeof(qBuffer));
        }
        else if(state == 'q')
        {
            if(c == '\n')
            {
                qBuffer[q+1] = '\0';
                strcpy(quiz[i].question, qBuffer);
                state = 's';
            }
            else
            {
                qBuffer[q] = c;
                q++;
            }
            
        }
        else if(state == 'a' || state == 'b' || state == 'c' || state == 'd' )
        {

            if(c == '\n'){
                aBuffer[q+1] = '\0';
                switch(state)
                {
                    case 'a': strcpy(quiz[i].answerA, aBuffer);
                        break;
                    case 'b': strcpy(quiz[i].answerB, aBuffer);
                        break;
                    case 'c': strcpy(quiz[i].answerC, aBuffer);
                        break;
                    case 'd': strcpy(quiz[i].answerD, aBuffer);
                        break;
                }
                state = 's';
            }
            else
            {
                aBuffer[q] = c;
                q++;
            }
            
        }
        else if(state == '-')
        {
            if(c == '\n')
            {
                state = 's';
            }
            else
            {
                quiz[i].correct_answer = c;
                i++;
            }
        }

        
        if(state == 's')
        {
            state = c;
        }
        // End of line resets the state
        if(c == '\n')
        {  
            state = 's';
        }
        
    }


    fclose(fh);

}