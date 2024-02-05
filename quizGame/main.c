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

int main(void)
{
    //init ncurses
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE); 

    quiz_question quiz[TOTAL_QUESTIONS];

    strcpy(quiz[0].question, "What does the ++ operator do?");
    strcpy(quiz[0].answerA, "Add two to a number");
    strcpy(quiz[0].answerB, "Add one to a number");
    strcpy(quiz[0].answerC, "Subtract two to a number");
    strcpy(quiz[0].answerD, "Subtract one to a number");
    quiz[0].correct_answer = 'b';

    strcpy(quiz[1].question, "What does the ++ operator do?");
    strcpy(quiz[1].answerA, "Add two to a number");
    strcpy(quiz[1].answerB, "Add one to a number");
    strcpy(quiz[1].answerC, "Subtract two to a number");
    strcpy(quiz[1].answerD, "Subtract one to a number");
    quiz[1].correct_answer = 'b';

    strcpy(quiz[2].question, "What does the ++ operator do?");
    strcpy(quiz[2].answerA, "Add two to a number");
    strcpy(quiz[2].answerB, "Add one to a number");
    strcpy(quiz[2].answerC, "Subtract two to a number");
    strcpy(quiz[2].answerD, "Subtract one to a number");
    quiz[2].correct_answer = 'b';

    strcpy(quiz[3].question, "What does the ++ operator do?");
    strcpy(quiz[3].answerA, "Add two to a number");
    strcpy(quiz[3].answerB, "Add one to a number");
    strcpy(quiz[3].answerC, "Subtract two to a number");
    strcpy(quiz[3].answerD, "Subtract one to a number");
    quiz[3].correct_answer = 'b';

    strcpy(quiz[4].question, "What does the ++ operator do?");
    strcpy(quiz[4].answerA, "Add two to a number");
    strcpy(quiz[4].answerB, "Add one to a number");
    strcpy(quiz[4].answerC, "Subtract two to a number");
    strcpy(quiz[4].answerD, "Subtract one to a number");
    quiz[4].correct_answer = 'b';

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