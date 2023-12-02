#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 7

char *zero[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *one[5][3] = {
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *two[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"}};

char *three[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *four[5][3] = {
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *five[5][3] = {
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *six[5][3] = {
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *seven[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *eight[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *nine[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *colon[5][3] = {
    {" ", " ", " "},
    {" ", "█", " "},
    {" ", " ", " "},
    {" ", "█", " "},
    {" ", " ", " "}};

// create an array of pointers to the arrays of pointers to the digits
char *(*digits[10])[5][3] = {&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine};

void printDigit(int digit, int x, int y)
{
    // get the array of pointers to the arrays of pointers to the digits
    char *(*digitArray)[5][3] = digits[digit];
    // print the digit
    for (int i = 0; i < 5; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        for (int j = 0; j < 3; j++)
        {
            printf("%s", (*digitArray)[i][j]);
        }
    }
}

void printColon(int x, int y)
{
    // print the colon
    for (int i = 0; i < 5; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        for (int j = 0; j < 3; j++)
        {
            printf("%s", colon[i][j]);
        }
    }
}

void printClock(int hour, int minute, int second, int width, int height)
{
    // print the hour
    int digit = hour / 10;
    printDigit(digit, width / 2 - 8, height / 2 - 2);
    digit = hour % 10;
    printDigit(digit, width / 2 - 3, height / 2 - 2);
    // print the colon
    printColon(width / 2 + 2, height / 2 - 2);
    // print the minute
    digit = minute / 10;
    printDigit(digit, width / 2 + 5, height / 2 - 2);
    digit = minute % 10;
    printDigit(digit, width / 2 + 10, height / 2 - 2);
    
    printColon(width / 2 + 15, height / 2 - 2);
    digit = second / 10;
    printDigit(digit, width / 2 + 18, height / 2 - 2);
    digit = second % 10;
    printDigit(digit, width / 2 + 23, height / 2 - 2);

}

int hour, minute, second;

void signalhandler(int signum)
{
    printf("Caught signal %d, coming out...\n", signum);
    // clear screen
    system("clear");
    // make cursot white
    printf("\033[37m");
    // move cursor to the top left corner
    printf("\033[1;1H");
    // make cursor visible
    printf("\033[?25h");
    exit(1);
}

int main(int argc, char *argv[])
{
    hour = 0;
    minute = 0;
    second = 0;
    //hide cursor
    printf("\033[?25l");
    signal(SIGINT, signalhandler);
    system("clear");
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            second = atoi(argv[i + 1]); 
        }
        else if (strcmp(argv[i], "-m") == 0)
        {
            minute = atoi(argv[i + 1]) * 60;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            hour = atoi(argv[i + 1]) * 3600;
        }
    }
    int total = hour + minute + second;
    
    while(1){

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;
    int height = w.ws_row;

    int x = width - 2-15;
    int y = height - 2;

    printf("\033[31m");
    
    system("clear");

    int newHour = total / 3600;
    int newMinute = (total - newHour * 3600) / 60;
    int newSecond = total - newHour * 3600 - newMinute * 60;

    
    printClock(newHour, newMinute, newSecond, x, y);
    fflush(stdout);
    sleep(1);
    total--;
    if(total == 0){
        printf("\033[?25h");
        printf("\033[1;1H");
        printf("\033[37m");
        printf("Time is up!\n");
        break;
    }
    }
    return 0;
}