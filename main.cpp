#include <iostream>
#include <conio.h>
#include <windows.h>

void run();
void slot();
void printMap();
void initMap();
void checkLength();
void checkV();
void checkH();
void checkDN();
void checkDP();
int counter(int val);
char getMapValue(int value);

using namespace std;

const int width = 7;
const int height = 6;
const int win = 4;

const int size = width*height;

int map[size];

int xpos;
int ypos;

int player = 1 ;

bool running;

void run(){
    initMap();
    running = true;
    while (running)
    {
            xpos = getch()-48;

            if (xpos > 0 && xpos <= width)
                {
                    slot();

            system("cls");

            printMap();

            checkLength();

            player++;
                }
    }

}

void initMap(){
    for (int i = 0 ; i < size ; i ++) map[i] = 0;
    printMap();
}

void slot(){
    ypos = height;
    for (int i = xpos + width * (height - 1) - 1 ; i >= 0 ; i = i - width)
    {
        if (map[i] == 0){
            map[i] = counter(player);
            break;
        }
        ypos --;
    }
}

void printMap()
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Prints the value at current x,y location
            std::cout << getMapValue(map[x + y * width]);
        }
        // Ends the line for next x value
        std::cout << std::endl;
    }
}

void checkLength(){
        if (ypos < height-win+2) checkV();
        checkH();
        checkDN();
        checkDP();
}

void checkV(){
    int length = 0;
    for (int ycheck = ypos ; ycheck <= height ; ycheck++)
        if (map[xpos-1+width*(ycheck-1)] == counter(player)) length ++;
        else break;
    if (length>=win){
        cout<<"The game is won!";
        running = false;
    }
}

void checkH(){
    int length = 0;
    for (int xcheck = xpos ; xcheck > 0 ; xcheck -- )
        if (map[xcheck-1+width*(ypos-1)] == counter(player)) length++;
        else break;
    for (int xcheck = xpos +1 ; xcheck < width ; xcheck ++)
        if (map[xcheck-1+width*(ypos-1)] == counter(player)) length++;
        else break;
    if (length>=win){
        cout<<"the game is won!";
        running = false;
    }
}

void checkDN(){
    int xcheck = xpos;
    int ycheck = ypos;
    int length = 0;
    while (xcheck > 0 && ycheck > 0 && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck--;
        ycheck--;
    }
    xcheck = xpos + 1;
    ycheck = ypos + 1;
    while (xcheck <= width && ycheck <= height && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck++;
        ycheck++;
    }
    if (length >=win) {
        cout<<"The game is won!";
        running = false;
    }
}

void checkDP(){
    int xcheck = xpos;
    int ycheck = ypos;
    int length = 0;
    while (xcheck > 0 && ycheck <=height && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck--;
        ycheck++;
    }
    xcheck = xpos + 1;
    ycheck = ypos - 1;
    while (xcheck <= width && ycheck > 0 && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck++;
        ycheck--;
    }
    if (length>=win){
        cout<<"The game is won!";
        running = false;
    }
}

int counter (int val){
    if (player%2 == 0) return 1;
    return -1;
}

char getMapValue(int value)
{
    // Returns a part of snake body


    switch (value) {
        // Return wall
    case 0: return '.';

    case -1: return 'X';
        // Return food
    case 1: return 'O';

    }
    return 0;
}

int main()
{
    run();
    while (true)
    {
        cout<<"Wanna play again? (Y/N)";
        if (getch() == 'Y') {
            system("cls");
            run();
        }
        else return 0;
    }
    return 0;
}
