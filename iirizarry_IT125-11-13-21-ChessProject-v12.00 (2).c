/*
 *    Program: iirizarry_IT125-11-13-21-ChessProject-v12.00.c
 *    Name: Israel Irizarry (iirizarry33@students.cumberland.edu)
 *    Date:10/25/2021
 *    Honor Code
 *
 *    Objective (Completed): Create a chess program to where the player can play basic chess against another player or the computer.
 *
 *    Algorithm: 1. Create chessboard using arrays of characters and numbers.
 *               2. Add user input for piece movement and replacement across the board.
 *               3. Make it so that if there are less than 2 kings on the board, the program terminates with a winner declared.
 *               4. Add player turn alternations.
 *                   4.1 - Allow for user input to select gamemode.
 *               5. Add rules for all pieces.
 *               6. Make Basic PvC availability.
 *                   6.1 - For every piece that is the computer's, check if it can move to any other space on the board.
 *                   6.2 - Store all the pieces that can move into an array.
 *                   6.3 - Randomly choose from that array a piece to move.
 *               7. Revised the computer to prioritize capturing pieces over random movement.
 *                   7.1 - Create an array to store all piece positions that can capture.
 *                   7.2 - Use that array to fill another array with all the positions in order without gaps.
 *                   7.3 - Randomly choose a piece from the array.
 *                   7.4 - If no pieces can capture, then randomly choose a piece that can move.
 *               8. Copy the portion of code that controls computer 2 and use it to make a second computer to have the first play against.
 *                   8.1 - Change the values in the code to reflect player 1's pieces and movement.
 *                   8.1 - Add a 3rd option to have the player choose to have the computer play against itself.
 *
 *    Versions (All working):
 *     1.00 - Created chessboard.
 *     2.00 - Added user input to be able to change places in the chessboard.
 *     3.00 - Created player turns and piece movement to each specific player.
 *     4.00 - Added rules for pawn movement.
 *     5.00 - Added rules for rook movement.
 *     6.00 - Added rules for bishop movement.
 *     7.00 - Added rules for knight movement.
 *     8.00 - Added rules for king and queen movement.
 *     9.00 - Made PvC an available option.
 *    10.00 - Made the computer prioritize capturing over random placement.
 *    11.00 - Added a time delay.
 *    12.00 - Added the CvC option.
 *
 *    Credits: time.h seed syntax learned from https://www.tutorialspoint.com/c_standard_library/c_function_srand.html.
 *             clock() syntax for delays learned from https://newbedev.com/c-how-to-delay-function-in-c-code-example.
 *
 *    Compiled and run via:
 *            Visual Studio Code and GCC
 *            GCC version: 6.3.0
 *            OS: Windows 10 Version 10.0.19043 Build 19043
 *
 *    Output:
    
       ***Run Code for custom result.
       
       
 *     PS C:\Users\israe\Desktop\C Programming> cd "c:\Users\israe\Desktop\C Programming\" ; if ($?) { gcc iirizarry_IT125-10-31-21-ChessProject-v12.00.c -o Test } ; if ($?) { .\Test }
PS C:\Users\israe\Desktop\C Programming> 
 */

//------------------------------------------------------------------------------------------------------|

//Prints out to the terminal.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Functions Used.
char _ChessBoard_(char chessBoard[8][8], char xAxis[8]);
int _Pawn_(int x, char y, int x1, char y1, char chessBoard[8][8], char xAxis[8], char player1[2][8], char player2[2][8], int playerTurn);
int _Rook_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn);
int _Bishop_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn);
int _Knight_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn);
int _King_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn);
int _Queen_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn);

//Functions---------------------------------------------------------------------------------------------------------------------------------------------------|
int main(void) {
    
    //Declare and initialize arrays.
    char chessBoard[8][8] = {{'R','N','B','Q','K','B','N','R'},{'P','P','P','P','P','P','P','P'},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' '},{'p','p','p','p','p','p','p','p'},{'r','n','b','q','k','b','n','r'}};
    char xAxis[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char player2[2][8] = {{'R','N','B','Q','K','B','N','R'},{'P','P','P','P','P','P','P','P'}};
    char player1[2][8] = {{'r','n','b','q','k','b','n','r'},{'p','p','p','p','p','p','p','p'}};
    
    //Array declarations for PvC and CvC.
    int player2PosX[64];
    int player2PosY[64];
    int player2DestX[64];
    int player2DestY[64];
    int player2Capture[64];
    
    char player1Pieces[6] = {'b', 'p', 'r', 'k', 'q', 'n'};
    char player2Pieces[6] = {'B', 'P', 'R', 'K', 'Q', 'N'};
    char player2CurPosY[16];
    int player2CurPosX[16];
    
    //Declares and initializes paying state variables.
    int pState;
    char playerState1[] = "0";
    pState = 0;
    
    //Inititializes PvC arrays.
    for (int i = 0; i < 16; i++) {
        player2CurPosX[i] = 0;
        player2CurPosY[i] = '0';
    }
    for (int i = 0; i < 64; i++) {
        player2PosX[i] = -1;
        player2Capture[i] = -1;
        player2PosY[i] = -1;
        player2DestX[i] = -1;
        player2DestY[i] = -1;
    }
    
    //Intro Section------------------------------------------------------------------------------------------------------|
    
    //Prints the introduction and how to play the game.
    printf("*******************************************************************");
    printf("\n*    Welcome to ASCII Chess! Below are the basics\n*    on how to play.\n*\n*    First enter the piece's letter position and then the number position.");
    printf("\n*    Player 1 goes first and is represented as the lowercase pieces.\n*    Player 2 is represented by the uppercase pieces.\n*\n*    Enter a piece to move and then press enter.\n*    Then the program will prompt you to enter the destination.\n*         Ex.\n*\n*         Enter piece to move: d2\n*         Enter the destination location: d4");
    printf("\n*\n*    Note: This version of chess does not have all the chess rules implemented.\n*         It has all basic piece movement, but it does not have, for example, \n*         castling and queening.");
    printf("\n*\n*    Have Fun!\n******************************************************************");

    //Prints the chessboard to the screen.
    printf("\n\nWould you rather play against another person (take turns on the same computer)\nor play against the computer?\nYou can also have the program play against itself.\n\nEnter 1 for PvP, 2 for PvC:, or 3 for CvC: ");
    
    //Takes user input to see what state the player wants to play in.
    scanf("%s", playerState1);
    pState = playerState1[0];
    pState -= '0';
    
    //Checks if the input is valid or not.
    while (pState != 2 && pState != 1 && pState != 3) {
        printf("Invalid input. Enter 1, 2, or 3: ");
        scanf("%s", playerState1);
        pState = playerState1[0];
        pState -= '0';
    }
    
    //Prints the initial chessboard.
    _ChessBoard_(chessBoard, xAxis);
    
    //------------------------------------------------------------------------------------------------------|
    
    //Delcared and initialized variables.
    int kingCount, x, x1, isValid, playerTurn, isYours, qPos, qPos1, canMove;
    char y, y1, current;
    char input[] = "00";
    kingCount = 2;
    isValid = 0;
    playerTurn = 1;
    isYours = 0;
    canMove = 0;
    
    time_t t;
    
    //------------------------------------------------------------------------------------------------------|
    
    //Loop that only terminates when one king remains.
    while (kingCount == 2) {
        
        if (playerTurn == 1 && kingCount == 2 && isYours != 0 && isValid == 2 && canMove == 1 && pState == 1) {
            playerTurn = 2;
            printf("\nPlayer 2's turn.");
        }
        else {
            if (kingCount == 2 && isYours != 0 && isValid == 2 && canMove == 1 && pState == 1) {
                playerTurn = 1;
                printf("\nPlayer 1's turn.");
            }
        }
        //Resets error checking variables.
        isValid = 0;
        isYours = 0;
        canMove = 0;
        
        //Start of Computer playing portion------------------------------------------------------------------------------------------------------|
        
        //CvC computer rules for computer 1.
        if (playerTurn == 1 && pState == 3) {
            
            //Delays the computer's response.
            printf("\nComputer 1 is thinking...");
            int milliSec = 1000 * 1;
            time_t startTime = clock();
            while(clock() < startTime + milliSec);
            printf("\n.\n");
            
            //Declares and initializes computer variables.
            int counter, stopSearch;
            counter = 0;
            stopSearch = 0;
            
            //Records all piece positions for the computer's side.
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 6; k++) {
                        if (player1Pieces[k] == chessBoard[i][j]) {
                            player2CurPosX[counter] = 8-i;
                            player2CurPosY[counter] = xAxis[j];
                            counter += 1;
                        }
                    }
                }
            }
            
            //For all the computer's pieces, check for every spot on the board if it can move to that spot.
            for (int i = 0; i < 16; i++) {
                // x and y printf("%c%d, ", player2CurPosY[i], player2CurPosX[i]);
                
                for (int k = 0; k < 8; k++) {
                    
                    for (int j = 0; j < 8; j++) {
                        // x1 and y1 printf("%c at %c%d", chessBoard[i][j], xAxis[j], 8-i);
                        
                        //Gets the numerical position for each letter variable.
                        for (int q = 0; q < 8; q++) {
                            if (xAxis[q] == player2CurPosY[i]) {
                                qPos = q;
                            }
                            if (xAxis[q] == xAxis[j]) {
                                qPos1 = q;
                            }
                        }
                        
                        //Checks if the computer can move the piece or not.
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'p' && ((k-2 == player2CurPosX[i] && xAxis[qPos1] == xAxis[qPos])|| k-1 == player2CurPosX[i])) {
                            canMove = _Pawn_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, xAxis, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'r') {
                            canMove = _Rook_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'b') {
                            canMove = _Bishop_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'n') {
                            canMove = _Knight_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'k') {
                            canMove = _King_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'q') {
                            canMove = _Queen_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        
                        //If the player can move, then it is added to an array.
                        if (canMove == 1) {
                            for (int w = 0; w < 64; w++) {
                                if (player2PosY[w] == -1 && stopSearch == 0) {
                                    stopSearch = 1;
                                    player2PosY[w] = qPos;
                                    player2PosX[w] = player2CurPosX[i];
                                    
                                    player2DestX[w] = k;
                                    player2DestY[w] = qPos1;
                                    
                                    //If the piece can capture, it records it's position.
                                    if (chessBoard[8-player2DestX[w]][player2DestY[w]] != ' ') {
                                        player2Capture[w] = 1;
                                    }
                                }
                            }
                            //printf("\ncanMove %c at %c%d to %c at %c%d", chessBoard[8-player2CurPosX[i]][qPos], xAxis[qPos], player2CurPosX[i], chessBoard[8-k][qPos1], xAxis[qPos1], k);
                        }
                        
                        //Resets some variables.
                        stopSearch = 0;
                        canMove = 0;
                    }   
                }
            }
            
            //Declares and initializes variables used for random assignment.
            int probCount, randCount, captureCount, capturePos[64];
            probCount = 0;
            randCount = 0;
            captureCount = 0;
            
            //Checks if a piece can capture.
            for (int i = 0; i < 64; i++) {
                capturePos[i] = -1;
                if (player2Capture[i] != -1) {
                    captureCount = 1;
                }
            }
            
            //If a piece can capture, Choose a random piece that can capture.
            if (captureCount == 1) {
                for (int i = 0; i < 64; i++) {
                    if (player2Capture[i] != -1) {
                        capturePos[probCount] = i;
                        probCount += 1;
                    }
                }
                //Chooses one piece that can move and moves it to the new spot.
                srand((unsigned) time(&t));
                randCount = rand() % probCount;
                printf("___________________________________\n");
                printf("Computer 1 moved %c at %c%d to %c%d", chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]], xAxis[player2PosY[capturePos[randCount]]], player2PosX[capturePos[randCount]], xAxis[player2DestY[capturePos[randCount]]], player2DestX[capturePos[randCount]]);
                chessBoard[8-player2DestX[capturePos[randCount]]][player2DestY[capturePos[randCount]]] = chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]];
                chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]] = ' ';
            }
            
            //If no pieces can capture, move a random piece.
            if (captureCount == 0) {
                for (int i = 0; i < 64; i++) {
                    if (player2PosY[i] != -1) {
                        probCount += 1;
                    }
                }
                //Chooses one piece that can move and moves it to the new spot.
                srand((unsigned) time(&t));
                randCount = rand() % probCount;
                printf("___________________________________\n");
                printf("Computer 1 moved %c at %c%d to %c%d", chessBoard[8-player2PosX[randCount]][player2PosY[randCount]], xAxis[player2PosY[randCount]], player2PosX[randCount], xAxis[player2DestY[randCount]], player2DestX[randCount]);
                chessBoard[8-player2DestX[randCount]][player2DestY[randCount]] = chessBoard[8-player2PosX[randCount]][player2PosY[randCount]];
                chessBoard[8-player2PosX[randCount]][player2PosY[randCount]] = ' ';
                
            }
            //Resets the available pieces array.
            for (int i = 0; i < 64; i++) {
                player2PosX[i] = -1;
                player2PosY[i] = -1;
                player2DestX[i] = -1;
                player2DestY[i] = -1;
            }
            for (int i = 0; i < 64; i++) {
                player2Capture[i] = -1;
            }
            //Prints the updated board and changes the player turn.
            _ChessBoard_(chessBoard, xAxis); 
            playerTurn = 2;
            
            //Checks the king count.
            kingCount = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (chessBoard[i][j] == 'K' || chessBoard[i][j] == 'k') {
                        kingCount += 1;
                    }
                }
            }
        }
        
        //End of Computer 1's code/Beginning of Computer 2's code---------------------------------------------------------------------------------------|
        
        //Controls computer 2.
        if (playerTurn == 2 && (pState == 2 || pState == 3) && kingCount == 2) {
            
            //Delays the computer's response.
            if (pState == 2) {
                printf("\nThe computer is thinking...");
            }
            else {
                printf("\nComputer 2 is thinking...");
            }
            int milliSec = 1000 * 1;
            time_t startTime = clock();
            while(clock() < startTime + milliSec);
            printf("\n.\n");
            if (pState == 2) {
                startTime = clock();
                while(clock() < startTime + milliSec);
                printf("\n.\n");
                startTime = clock();
                while(clock() < startTime + milliSec);
                printf("\n.\n");
                startTime = clock();
                while(clock() < startTime + milliSec);
            }
            
            //Declares and initializes computer variables.
            int counter, stopSearch;
            counter = 0;
            stopSearch = 0;
            
            //Records all piece positions for the computer's side.
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 6; k++) {
                        if (player2Pieces[k] == chessBoard[i][j]) {
                            player2CurPosX[counter] = 8-i;
                            player2CurPosY[counter] = xAxis[j];
                            counter += 1;
                        }
                    }
                }
            }
            
            //For all the computer's pieces, check for every spot on the board if it can move to that spot.
            for (int i = 0; i < 16; i++) {
                // x and y printf("%c%d, ", player2CurPosY[i], player2CurPosX[i]);
                
                for (int k = 0; k < 8; k++) {
                    
                    for (int j = 0; j < 8; j++) {
                        // x1 and y1 printf("%c at %c%d", chessBoard[i][j], xAxis[j], 8-i);
                        
                        //Gets the numerical position for each letter variable.
                        for (int q = 0; q < 8; q++) {
                            if (xAxis[q] == player2CurPosY[i]) {
                                qPos = q;
                            }
                            if (xAxis[q] == xAxis[j]) {
                                qPos1 = q;
                            }
                        }
                        
                        //Checks if the computer can move the piece or not.
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'P' && ((k+2 == player2CurPosX[i] && xAxis[qPos1] == xAxis[qPos])|| k+1 == player2CurPosX[i])) {
                            canMove = _Pawn_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, xAxis, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'R') {
                            canMove = _Rook_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'B') {
                            canMove = _Bishop_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'N') {
                            canMove = _Knight_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'K') {
                            canMove = _King_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        if (chessBoard[8-player2CurPosX[i]][qPos] == 'Q') {
                            canMove = _Queen_(player2CurPosX[i], player2CurPosY[i], k, xAxis[j], chessBoard, qPos, qPos1, player1, player2, playerTurn);
                        }
                        
                        //If the player can move, then it is added to an array.
                        if (canMove == 1) {
                            for (int w = 0; w < 64; w++) {
                                if (player2PosY[w] == -1 && stopSearch == 0) {
                                    stopSearch = 1;
                                    player2PosY[w] = qPos;
                                    player2PosX[w] = player2CurPosX[i];
                                    
                                    player2DestX[w] = k;
                                    player2DestY[w] = qPos1;
                                    
                                    //If the piece can capture, it records it's position.
                                    if (chessBoard[8-player2DestX[w]][player2DestY[w]] != ' ') {
                                        player2Capture[w] = 1;
                                    }
                                }
                            }
                            //printf("\ncanMove %c at %c%d to %c at %c%d", chessBoard[8-player2CurPosX[i]][qPos], xAxis[qPos], player2CurPosX[i], chessBoard[8-k][qPos1], xAxis[qPos1], k);
                        }
                        
                        //Resets some variables.
                        stopSearch = 0;
                        canMove = 0;
                    }   
                }
            }
            
            //Declares and initializes variables used for random assignment.
            int probCount, randCount, captureCount, capturePos[64];
            probCount = 0;
            randCount = 0;
            captureCount = 0;
            
            //Checks if a piece can capture.
            for (int i = 0; i < 64; i++) {
                capturePos[i] = -1;
                if (player2Capture[i] != -1) {
                    captureCount = 1;
                }
            }
            
            //If a piece can capture, Choose a random piece that can capture.
            if (captureCount == 1) {
                for (int i = 0; i < 64; i++) {
                    if (player2Capture[i] != -1) {
                        capturePos[probCount] = i;
                        probCount += 1;
                    }
                }
                //Chooses one piece that can move and moves it to the new spot.
                srand((unsigned) time(&t));
                randCount = rand() % probCount;
                printf("___________________________________\n");
                if (pState == 2) {
                    printf("The computer moved %c at %c%d to %c%d", chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]], xAxis[player2PosY[capturePos[randCount]]], player2PosX[capturePos[randCount]], xAxis[player2DestY[capturePos[randCount]]], player2DestX[capturePos[randCount]]);
                }
                else {
                    printf("Computer 2 moved %c at %c%d to %c%d", chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]], xAxis[player2PosY[capturePos[randCount]]], player2PosX[capturePos[randCount]], xAxis[player2DestY[capturePos[randCount]]], player2DestX[capturePos[randCount]]);
                }
                chessBoard[8-player2DestX[capturePos[randCount]]][player2DestY[capturePos[randCount]]] = chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]];
                chessBoard[8-player2PosX[capturePos[randCount]]][player2PosY[capturePos[randCount]]] = ' ';
            }
            
            //If no pieces can capture, move a random piece.
            if (captureCount == 0) {
                for (int i = 0; i < 64; i++) {
                    if (player2PosY[i] != -1) {
                        probCount += 1;
                    }
                }
                //Chooses one piece that can move and moves it to the new spot.
                srand((unsigned) time(&t));
                randCount = rand() % probCount;
                printf("___________________________________\n");
                if (pState == 2) {
                    printf("The computer moved %c at %c%d to %c%d", chessBoard[8-player2PosX[randCount]][player2PosY[randCount]], xAxis[player2PosY[randCount]], player2PosX[randCount], xAxis[player2DestY[randCount]], player2DestX[randCount]);
                }
                else {
                    printf("Computer 2 moved %c at %c%d to %c%d", chessBoard[8-player2PosX[randCount]][player2PosY[randCount]], xAxis[player2PosY[randCount]], player2PosX[randCount], xAxis[player2DestY[randCount]], player2DestX[randCount]);
                }
                chessBoard[8-player2DestX[randCount]][player2DestY[randCount]] = chessBoard[8-player2PosX[randCount]][player2PosY[randCount]];
                chessBoard[8-player2PosX[randCount]][player2PosY[randCount]] = ' ';
                
            }
            //Resets the available pieces array.
            for (int i = 0; i < 64; i++) {
                player2PosX[i] = -1;
                player2PosY[i] = -1;
                player2DestX[i] = -1;
                player2DestY[i] = -1;
            }
            for (int i = 0; i < 64; i++) {
                player2Capture[i] = -1;
            }
            //Prints the updated board and changes the player turn.
            _ChessBoard_(chessBoard, xAxis); 
            playerTurn = 1;
            
            //Checks the king count.
            kingCount = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (chessBoard[i][j] == 'K' || chessBoard[i][j] == 'k') {
                        kingCount += 1;
                    }
                }
            }
        }
    
        //End of computer paying rules/Start of player interaction------------------------------------------------------------------------------------------|
        
        //If there still two kings on the board it proceeds with the game.
        if (kingCount == 2 && (pState == 1 || (pState == 2 && playerTurn == 1))) {
            
            //Gets input on what piece to move.
            printf("\nEnter piece to move: ");
            scanf("%s", input);
            x = input[1];
            y = input[0];
            x -= '0';
            
            //Gets input on where to move the piece.
            printf("Enter the destination location: ");
            scanf("%s", input);
            x1 = input[1];
            y1 = input[0];
            x1 -= '0';
            
            //Formatting.
            printf("___________________________________\n");
            for (int q = 0; q < 8; q++) {
                //Checks if the piece is part of the current player's team.
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 8;j++) {
                        if (xAxis[q] == y && playerTurn == 1 && chessBoard[8-x][q] == player1[i][j]) {
                            isYours += 1;
                        }
                        if (xAxis[q] == y && playerTurn == 2 && chessBoard[8-x][q] == player2[i][j]) {
                            isYours += 1;
                        }
                    }
                }
            }
            
            //Checks if valid input was entered and places pieces in proper positions.
            for (int q = 0; q < 8; q++) {
                
                //If the piece is part of the team, then the piece's position is replaced by a space.
                if ((xAxis[q] == y && x>0 && x<9) && isYours >= 1) {
                    isValid += 1;
                    qPos = q;
                }
                
                //Places the piece in its new position if the new position is within the rules.
                if ((xAxis[q] == y1 && x1>0 && x1<9) && isYours >= 1) {
                    isValid += 1;
                    qPos1 = q;
                }
            }
            
            //Prints an error message if invalid input was entered.
            if (isValid != 2 && isYours != 0) {
                printf("***Incorrect format. You must enter a valid letter and number: ex. 'e7'.");
            }
            
            //Prints an error method if you try to move a piece that is not yours.
            if (isYours == 0) {
                printf("***You have to choose a piece on your team and on the board.");
                if (playerTurn == 1) {
                    printf("\nStill Player 1's turn.");
                }
                else {
                    printf("\nStill Player 2's turn.");
                }
            }
            
            //Changes the turn to the next player and prints it to screen.
            if (isYours >= 1 && isValid == 2) {
                if (chessBoard[8-x][qPos] == 'p' || chessBoard[8-x][qPos] == 'P') {
                    canMove = _Pawn_(x, y, x1, y1, chessBoard, xAxis, player1, player2, playerTurn);
                }
                if (chessBoard[8-x][qPos] == 'r' || chessBoard[8-x][qPos] == 'R') {
                    canMove = _Rook_(x, y, x1, y1, chessBoard, qPos, qPos1, player1, player2, playerTurn);
                }
                if (chessBoard[8-x][qPos] == 'b' || chessBoard[8-x][qPos] == 'B') {
                    canMove = _Bishop_(x, y, x1, y1, chessBoard, qPos, qPos1, player1, player2, playerTurn);
                }
                if (chessBoard[8-x][qPos] == 'n' || chessBoard[8-x][qPos] == 'N') {
                    canMove = _Knight_(x, y, x1, y1, chessBoard, qPos, qPos1, player1, player2, playerTurn);
                }
                if (chessBoard[8-x][qPos] == 'k' || chessBoard[8-x][qPos] == 'K') {
                    canMove = _King_(x, y, x1, y1, chessBoard, qPos, qPos1, player1, player2, playerTurn);
                }
                if (chessBoard[8-x][qPos] == 'q' || chessBoard[8-x][qPos] == 'Q') {
                    canMove = _Queen_(x, y, x1, y1, chessBoard, qPos, qPos1, player1, player2, playerTurn);
                }
                if (canMove == 1) {
                    current = chessBoard[8-x][qPos];
                    chessBoard[8-x][qPos] = ' ';
                    chessBoard[8-x1][qPos1] = current;
                    _ChessBoard_(chessBoard, xAxis);
                    
                    //If player is playing against the computer, than it changes to player 2.
                    if (pState == 2) {
                        playerTurn = 2;
                    }
                }
                else {
                    printf("***You cannot move this piece here.");
                }
            }
        }
        //Checks the king count.
        kingCount = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessBoard[i][j] == 'K' || chessBoard[i][j] == 'k') {
                    kingCount += 1;
                }
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------------|
    
    //Identifies the winner.
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j] == 'K') {
                printf("\n********************************\n");
                printf("\nPlayer 2 Wins!");
                printf("\n\n********************************\n");
            }
            if (chessBoard[i][j] == 'k') {
                printf("\n********************************\n");
                printf("\nPlayer 1 Wins!");
                printf("\n\n********************************\n");
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|
int _Pawn_(int x, char y, int x1, char y1, char chessBoard[8][8], char xAxis[8], char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the pawn selected can move to the desired location.
    */
    int yPos, y1Pos, canMove;
    y1Pos = 0;
    yPos = 0;
    canMove = 0;
    //printf("Stats: x:%d y:%c x1:%d y1:%c\n", x, y, x1, y1);
    
    //For player 1 gets the index of y and y1.
    for (int i = 0; i < 8; i++) {
        if (xAxis[i] == y1) {
            y1Pos = i;
        }
        if (xAxis[i] == y) {
            yPos = i;
        }
    }
    
    //Checks if the pawn can move forward for player 1.
    if (y == y1 && playerTurn == 1) {
        if (((x == 2 && x1 == 4) && y1 == y && chessBoard[7-x][y1Pos] == ' ' && chessBoard[6-x][y1Pos] == ' ') || (x1 == (x+1) && chessBoard[8-x1][y1Pos] == ' ')) {
            canMove = 1;
        }
    }
    
    //Allows the pawn to capture diagonal pieces.
    if ((yPos+1 == y1Pos || yPos-1 == y1Pos) && (x1=x+1) && playerTurn == 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessBoard[8-x1][y1Pos] == player2[i][j]) {
                    canMove = 1;
                }
            }
        }
    }
    
    //Checks if the pawn can move forward for player 2.
    if (y == y1 && playerTurn == 2) {
        if (((x == 7 && x1 == 5) && y1 == y && chessBoard[9-x][y1Pos] == ' ' && chessBoard[10-x][y1Pos] == ' ') || (x1 == (x-1) && chessBoard[8-x1][y1Pos] == ' ')) {
            canMove = 1;
        }
    }
    
    //Allows the pawn to capture diagonal pieces.
    if ((yPos+1 == y1Pos || yPos-1 == y1Pos) && (x1=x-1) && playerTurn == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessBoard[8-x1][y1Pos] == player1[i][j]) {
                    canMove = 1;
                }
            }
        }
    }
    
    //Returns 1 if the pawn can move to the desired location.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

int _Rook_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the pawn selected can move to the desired location.
    */
    
    //Local Variables used.
    int canMove, isEnemy;
    canMove = 0;
    isEnemy = 0;
    
    //Checks if all vertical positions are empty until destination position.
    for (int i = 1; i < abs(x1-x); i++) {
        if (x1 > x && y == y1 && chessBoard[8-x-i][yPos] == ' ') {
            canMove += 1;
        }
        if (x1 < x && y == y1 && chessBoard[8-x+i][yPos] == ' ') {
            canMove += 1;
        }
    }
    
    //Checks if all horizontal positions are empty until destination position.
    for (int i = 1; i < abs(y1Pos-yPos); i++) {
        if (x1 == x && yPos <= y1Pos && chessBoard[8-x][yPos+i] == ' ') {
            canMove += 1;
        }
        if (x1 == x && yPos >= y1Pos && chessBoard[8-x][yPos-i] == ' ') {
            canMove += 1;
        }
    }
    
    //Checks if the destination is an enemy piece so it can capture it.
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            if (playerTurn == 2) {
                if (chessBoard[8-x1][y1Pos] == player1[i][j]) {
                    isEnemy = 1;
                }
            }
            if (playerTurn == 1) {
                if (chessBoard[8-x1][y1Pos] == player2[i][j]) {
                    isEnemy = 1;
                }
            }
        }
    }
    
    //Checks if the destination path is empty and the destination position is either empty or an enemy piece so it can move the piece or not.
    if (((canMove == abs(x1-x)-1 && y == y1) || (canMove == abs(y1Pos - yPos)-1 && x == x1)) && (chessBoard[8-x1][y1Pos] == ' ' || isEnemy == 1)) {
        canMove = 1;
    }
    else {
        canMove = 0;
    }
    
    //Returns the value that dictates whether the destination is valid.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

int _Bishop_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the bishop selected can move to the desired location.
    */
    
    //Local Variables used
    int canMove, isEnemy;
    canMove = 0;
    isEnemy = 0;
    
    //Checks if the slope of the current position and the destination is 1 (or -1) and checks if the path to the destination is empty or an enemy piece.
    if (abs(x1-x) == abs(y1Pos-yPos)) {
        
        //Checks slope for -1/1.
        for (int i = 1; i < abs(x1-x); i++) {
            if ((((x1-x) < 0 && (y1Pos-yPos) > 0) && chessBoard[8-x+i][yPos+i] == ' ') || (((x1-x) > 0 && (y1Pos-yPos) > 0) && chessBoard[8-x-i][yPos+i] == ' ') || (((x1-x) > 0 && (y1Pos-yPos) < 0) && chessBoard[8-x-i][yPos-i] == ' ') || (((x1-x) < 0 && (y1Pos-yPos) < 0) && chessBoard[8-x+i][yPos-i] == ' ')) {
                canMove += 1;
            }
        }
        
        //Checks to see if the destination position is an eenmy piece.
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                if (playerTurn == 2) {
                    if (chessBoard[8-x1][y1Pos] == player1[i][j]) {
                        isEnemy = 1;
                    }
                }
                if (playerTurn == 1) {
                    if (chessBoard[8-x1][y1Pos] == player2[i][j]) {
                        isEnemy = 1;
                    }
                }
            }
        }
        
        //Returns true if the piece has a valid destination position.
        if (abs(x1-x) == canMove+1 && (isEnemy == 1 || chessBoard[8-x1][y1Pos] == ' ')) {
            canMove = 1;
        }
        else{
            canMove = 0;
        }
    }
    
    //Returns the value that dictates whether the destination is valid.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

int _Knight_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the knight selected can move to the desired location.
    */
    
    //Local Variables used
    int canMove, isEnemy;
    canMove = 0;
    isEnemy = 0;
    
    //Checks if the knight's destination is a valid destination.
    if ((y1Pos-yPos == 2 && (x1 == x-1 || x1 == x+1)) || (yPos - y1Pos == 2 && (x1 == x-1 || x1 == x+1)) || (x1-x == 2 && (y1Pos == yPos-1 || y1Pos == yPos+1)) || (x-x1 == 2 && (y1Pos == yPos-1 || y1Pos == yPos+1))) {
        
        //Checks to see if the destination position is an eenmy piece.
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                if (playerTurn == 2) {
                    if (chessBoard[8-x1][y1Pos] == player1[i][j]) {
                        isEnemy = 1;
                    }
                }
                if (playerTurn == 1) {
                    if (chessBoard[8-x1][y1Pos] == player2[i][j]) {
                        isEnemy = 1;
                    }
                }
            }
        }
        
        //Returns true if the piece has a valid destination position.
        if (isEnemy == 1 || chessBoard[8-x1][y1Pos] == ' ') {
            canMove = 1;
        }
    }
    
    //Returns the value that dictates whether the destination is valid.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

int _King_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the king selected can move to the desired location.
    */
    
    //Local Variables used
    int canMove;
    canMove = 0;
    
    //Uses the bishop and rook functions to check if the king's destination is valid.
    if ((abs(x1-x) == 1 || abs(x1-x) == 0) && ((abs(y1Pos-yPos) == 1 || abs(y1Pos-yPos) == 0))) {
        canMove += _Bishop_(x, y, x1, y1, chessBoard, yPos, y1Pos, player1, player2, playerTurn);
        canMove += _Rook_(x, y, x1, y1, chessBoard, yPos, y1Pos, player1, player2, playerTurn);
    }
    
    //If the destination is valid, then the king can move.
    if (canMove == 2) {
        canMove = 1;
    }
    
    //Returns the value that dictates whether the destination is valid.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

int _Queen_(int x, char y, int x1, char y1, char chessBoard[8][8], int yPos, int y1Pos, char player1[2][8], char player2[2][8], int playerTurn) {
    /*
        This function checks if the queen selected can move to the desired location.
    */
    
    //Local Variables used.
    int canMove;
    canMove = 0;
    
    //Checks if the queen's destination is valid.
    canMove += _Bishop_(x, y, x1, y1, chessBoard, yPos, y1Pos, player1, player2, playerTurn);
    canMove += _Rook_(x, y, x1, y1, chessBoard, yPos, y1Pos, player1, player2, playerTurn);
            
    //If the destination is valid, then the king can move.
    if (canMove == 2) {
        canMove = 1;
    }
    
    //Returns the value that dictates whether the destination is valid.
    return(canMove);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------|

char _ChessBoard_(char chessBoard[8][8], char xAxis[8]) {
    /*
        This function displays the chessboard for every turn.
    */
    
    //Prints the formatted board.
    printf("\n   ---------------------------------\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j == 0) {
                printf("%d  ", 8-i);
            }
            printf("| %c ",chessBoard[i][j]);
            if (j == 7) {
                printf("|\n   --------------------------------");
            }
        }
        printf("\n");
    }
    
    printf("   ");
    for (int i = 0; i < 8; i++) {
        printf("  %c ", xAxis[i]);
    }
}
