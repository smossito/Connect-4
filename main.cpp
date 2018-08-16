#include <iostream>
#include <conio.h>
#include <windows.h>

//initialise functions

int run(int map, int size);
int slot(int map[], int xpos, int width, int height, int player);
void printMap(int map[], int width, int height, int player);
void initMap(int map[], int width, int size, int player);
int checkLength(int map[], int xpos, int ypos, int width, int height, int player, int win);
int checkV(int map[], int xpos, int ypos, int width, int height, int player, int win);
int checkH(int map[], int xpos, int ypos, int width, int height, int player, int win);
int checkDN(int map[], int xpos, int ypos, int width, int height, int player, int win);
int checkDP(int map[], int xpos, int ypos, int width, int height, int player, int win);
int counter(int player);
char getMapValue(int value);
bool endGame(int winner);

using namespace std;

//This is the code for running a game

int run(){

    //define board size

    int height = 6;
    int width = 7;
    int size = width * height;
    int map[size];

    //initialises player counter to track whose turn it is

    int player = 1 ;

    //initialises the number in a row needed to win

    int win = 4;

    //the 'winner' variable. Once someone wins, this will tell us who

    int winner = 0;

    //the position coordinates - where has the most recent counter been player

    int xpos = 0;
    int ypos = 0;

    //initialises the board

    initMap(map, width, size, player);

    //this game will run whilst this is true

    bool running = true;

    while (running)
    {
            //sets xpos from 1 tp width

            xpos = getch()-48;

            //checking if a valid digit has been pressed

            if (xpos > 0 && xpos <= width)
            {
                //given where you put the counter in along the x , slot function will put the counter
                //on the board and tell us where it is along the y axis

                ypos = slot(map, xpos, width, height, player);

                //clears the console

                system("cls");

                //prints the updated board

                printMap(map, width, height, player+1);

                //checks to see if someone has won

                winner = checkLength(map, xpos, ypos, width, height, player, win);

                //next players go

                player++;

                //if there has been a winner, the end game sequence is executed

                if (winner != 0) running = endGame(winner);

            }
    }
    //returns the winner

    return winner;

}

//This is the function for initialising the board.

void initMap(int map[], int width, int size, int player){
    //clears console
    system("cls");
    //sets each value in the array to 0
    for (int i = 0 ; i < size ; i ++) map[i] = 0;
        //prints the board
        printMap(map, width, size/width, player);
}

//This is the function for putting a counter into the board
int slot(int map[], int xpos, int width, int height, int player){
    //Assumes the counter has fallen to the bottom
    int ypos = height;
    //If there is a counter in the bottom hole, it will keep moving up until
    //it finds an empty space
    for (int i = xpos + width * (height - 1) - 1 ; i >= 0 ; i = i - width)
    {
        if (map[i] == 0){
    //puts the counter in the board
            map[i] = counter(player);
            break;
        }
        ypos --;
    }
    //returns the y coordinate
    return ypos;
}

//This is the function for printing the board
void printMap(int map[], int width, int height, int player)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Prints the value at current x,y location
            cout << getMapValue(map[x + y * width])<<" ";
        }
        // Ends the line for next x value
        cout << std::endl;
    }
    //prints guidance numbers along the bottom edge of the board
    for (int i = 0; i < width; i++)
        cout<<i+1<<" ";
    cout<<endl<<endl<<getMapValue(counter(player))<<"'s turn";
}

//This is the function to check if anyone has won
int checkLength(int map[], int xpos, int ypos, int width, int height, int player, int win){
        int winner = 0;

        //checks for a vertical winner
        if (ypos < height-win+2)
            winner =checkV(map, xpos, ypos, width, height, player, win);
        if (winner != 0)
            return winner;

        //checks for a horizontal winner
        winner = checkH(map, xpos, ypos, width, height, player, win);
        if (winner != 0)
            return winner;

        //checks for a diagonal winner
        winner = checkDN(map, xpos, ypos, width, height, player, win);
        if (winner != 0)
            return winner;
        winner = checkDP(map, xpos, ypos, width, height, player, win);
        if (winner != 0)
            return winner;

        //otherwise there's no winner yet
        else return 0;
}

//This function checks for a vertical winner
int checkV(int map[],int xpos, int ypos, int width, int height, int player, int win){
    int length = 0;
    //Keeps checking the next counter down
    for (int ycheck = ypos ; ycheck <= height ; ycheck++)
        if (map[xpos-1+width*(ycheck-1)] == counter(player)) length ++;
        else break;
    //If the length is the win length, we have a winner!
    if (length>=win){
        //returns the winner
        return counter(player);
    }
    return 0;
}

//This function checks for a horizontal winner
int checkH(int map[], int xpos, int ypos, int width, int height, int player, int win){
    int length = 0;
    //checks the counters to the left until it's not the same counter
    for (int xcheck = xpos ; xcheck > 0 ; xcheck -- )
        if (map[xcheck-1+width*(ypos-1)] == counter(player)) length++;
        else break;
    //checks the counters to the right until it's not the same counter
    for (int xcheck = xpos +1 ; xcheck < width ; xcheck ++)
        if (map[xcheck-1+width*(ypos-1)] == counter(player)) length++;
        else break;
    //If the length is the win length, we have a winner!
    if (length>=win){
        //returns the winner
        return counter(player);
    }
    return 0;
}

//This function checks for a diagonal (\) winner
int checkDN(int map[], int xpos, int ypos, int width, int height, int player, int win){
    int xcheck = xpos;
    int ycheck = ypos;
    int length = 0;
    //keeps checking diagonally until it's not the same counter
    while (xcheck > 0 && ycheck > 0 && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck--;
        ycheck--;
    }
    xcheck = xpos + 1;
    ycheck = ypos + 1;
    //checks the other direction
    while (xcheck <= width && ycheck <= height && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck++;
        ycheck++;
    }
    //If the length is the win length, we have a winner!
    if (length >=win) {
        //returns the winner
        return counter(player);
    }
    return 0;
}

//This function checks for a diagonal (/) winner
int checkDP(int map[], int xpos, int ypos, int width, int height, int player, int win){
    int xcheck = xpos;
    int ycheck = ypos;
    int length = 0;
    //keeps checking diagonally until it's not the same counter
    while (xcheck > 0 && ycheck <=height && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck--;
        ycheck++;
    }
    xcheck = xpos + 1;
    ycheck = ypos - 1;
    //checks the other direction
    while (xcheck <= width && ycheck > 0 && map[xcheck-1+width*(ycheck-1)] == counter(player)){
        length++;
        xcheck++;
        ycheck--;
    }
    //If the length is the same as the win length, we have a winner!
    if (length>=win){
        //returns the winner
        return counter(player);
    }
    return 0;
}

//This function converts the number of turns into the player whose turn it is
int counter (int player){
    if (player%2 == 0) return 2;
    return 1;
}

//This function converts the player whose turn it is into their counter
char getMapValue(int value)
{
    //checks which player has gone
    switch (value) {
    //returns gaps
    case 0: return '.';
    //returns X
    case 1: return 'X';
    //returns O
    case 2: return 'O';

    }
    return 0;
}

//This function is the end game sequence
bool endGame(int winner)
{
    //Declares the winner
    cout<<endl<<endl<<"The game is won!"<<endl;
    cout<<"Winner is: Player "<<getMapValue(winner)<<endl<< "Wanna play again? (Y/N)";
    //Ends the game
    return false;
}

void calculateScore ( int winner, int &xwin, int &owin){
    if (winner == 1) xwin++;
    else owin++;
    cout<<endl<<endl<< "X: "<<xwin << "   O: "<<owin;
}

int main()
{
    int xwin = 0, owin = 0, winner = run();
    calculateScore(winner, xwin, owin);
    while (true)
    {
        if (getch() == 'Y') {
            winner = run();
            calculateScore(winner, xwin, owin);
        }
        else return 0;
    }
    return 0;
}
