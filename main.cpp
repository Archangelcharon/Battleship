/* Project #: CSProject3 BattleShip
 * Author: Zach Oryszak-Ley
 * Due: 10/10/2011
 * Description
 *	Battleship
 */

#include <iostream>
#include<ctime>


using namespace std;

//Global ship size constants
const int SIZE = 10;
//Global Ship sizes
const int CARRIER = 5;
const int BSHIP = 4;
const int CRUISER = 3;
const int SUB = 3;
const int DESTROYER = 2;

//Function Prototypes
int returnRandom();
int returnRandom2();
void intro();
void clearScreen();  
void initializeBoard(char[][SIZE], char[][SIZE], char[][SIZE], char[][SIZE]);
void placePiece(char [][SIZE], int, int, int, char);
void printBoards(char[][SIZE], char[][SIZE]);
void move(char[][SIZE], char[][SIZE]);
void isAllShipsHit();
bool ValidShips(char[][SIZE], int, int, int, bool,  bool);
void getComputerMove(char[][SIZE]);
void playerHitBoard(int [], int);
bool isAllShipsHit(char[][SIZE]);


int main() {
   char pHBoard[SIZE][SIZE];
   char pSBoard[SIZE][SIZE];
   char cHBoard[SIZE][SIZE];
   char cSBoard[SIZE][SIZE];
   int col, row;
   bool x = false;
 
   
   intro();
   
   //generating random numbers
   srand(time(0));
   
   //initializing boards
   initializeBoard(pHBoard,pSBoard,cHBoard,cSBoard);
   //Loop until game is won or lost.
   while (x == false){
        move(pHBoard, cSBoard);
        getComputerMove(pSBoard);
        clearScreen();
        printBoards(pHBoard, pSBoard);
        //Check to see if all the ships have been hit
        x=isAllShipsHit(pSBoard);
        if (x == true){
            cout << "YOU LOSE!!!! >=(" << endl;
            return 0;
        }
        cout << endl << endl;
        x=isAllShipsHit(cSBoard);
        if (x == true){
            cout << "YOU WIN!!! =D" << endl;
            return 0;
        }
   }
    return 0;
}
void clearScreen(){
#if defined(__CYGWIN__)
    printf("\e[1;1H\e[2J");
#elif defined(WINDOWS)
       system("cls");
#else
       system("clear");
#endif
}

int returnRandom(){
    return (rand()%(10));
}
//return a random bool to determine vertical or horizontal ship placement
int returnRandom2(){
    return (rand()%(2));
}
//Redisplays the updated boards after moves have been made
void printBoards(char pHB[][SIZE], char pSB[][SIZE]){
    
    cout << "    Player's Moves" << "             Player's Ships" << endl;
    cout << endl;
    cout << "  A B C D E F G H I J" << "        A B C D E F G H I J" << endl;
    for (int i = 0; i < SIZE; i++){
        cout << i << " ";
        for (int j = 0; j < SIZE; j++){
            cout << pHB[i][j] << " ";
        }
        cout << "     " << i << " ";
        for (int j = 0; j < SIZE; j++){
            cout << pSB[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "\t\t x = Hit, 0 = Miss" << endl;
    cout << endl;
}

//Initializes the boards
void initializeBoard(char pHB[][SIZE],char pSB[][SIZE],char cHB[][SIZE], char cSB[][SIZE]){
    int x, y;
    
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            pHB[i][j] = pSB[i][j] = '-';
            cHB[i][j] = cSB[i][j] = '-';
        }
    }
    
    for (int i = 0; i < 10; i++){
        char c;
        x = returnRandom();
        y = returnRandom();
        
        switch(i){
            //Player Ship Placement
            case 0: c = 'C';
                placePiece(pSB, x, y, CARRIER, c);
                
            break;
            case 1: c = 'B';
                placePiece(pSB, x, y, BSHIP, c);
            break;
            case 2: c = 'K';
                placePiece(pSB, x, y, CRUISER, c);
            break;
            case 3: c = 'S';
                placePiece(pSB, x, y, SUB, c);
            break;
            case 4: c = 'D';
                placePiece(pSB, x, y, DESTROYER, c);
            break;
            //Computer Ship Placement
            case 5: c = '+';
                placePiece(cSB, x, y, CARRIER, c);
            break;
            case 6: c = '+';
                placePiece(cSB, x, y, BSHIP, c);
            break;
            case 7: c = '+';
                placePiece(cSB, x, y, CRUISER, c);
            break;
            case 8: c = '+';
                placePiece(cSB, x, y, SUB, c);
            break;
            case 9: c = '+';
                placePiece(cSB, x, y, DESTROYER, c);
            break;
        }
    }
    printBoards(pHB, pSB);
}

//Placing the ships
void placePiece(char sB[][SIZE], int x, int y, int shipSize, char c){  
    bool z = false;
    int p = returnRandom2();
    
    while (z == false){
        x = returnRandom();
        y = returnRandom();
        z = ValidShips(sB, x, y, shipSize, p, z);
      }   
    //Vertical Placement
    if (p == 1 ){
       if (x > 10 - shipSize){
          for (int i = 0; i < shipSize; i++){
              sB[x][y] = c;
              x--;
          }
       }
    else if (x < 10-shipSize){
          for (int i = 0; i < shipSize; i++){   
              sB[x][y] = c;
              x++;
          }
    }
    }  
//Horizontal Placement
    if (p == 0){
       if (y > 10 - shipSize){
          for (int i = 0; i < shipSize; i++){   
              sB[x][y] = c;
              y--;
          }
       }
   else if (y < 10-shipSize){
        for (int i = 0; i < shipSize; i++){   
            sB[x][y] = c;
            y++;
        }
    }  
    }
}

//Player Move
void move(char pHB[][SIZE], char cSB[][SIZE]){
    bool v = 0;
    int col = 20;
    int row = 20;
    char number, letter;
    /* The first while loop checks to see if the move has already been attempted
       The second while loop makes sure it is a valid input.*/
    while (v == 0){    
        while (col > 9 ){
            cout << "Enter coordinate (Example: A7)" << endl;
                cin >> letter; 
                //Changing the inputed letter to the corresponding number.
                if(letter == 'A')
                        col = 0;
                else if(letter == 'B')
                        col = 1;
                else if(letter == 'C')
                        col = 2;
                else if(letter == 'D')
                        col = 3;
                else if(letter == 'E')
                        col = 4;
                else if(letter == 'F')
                        col = 5;
                else if(letter == 'G')
                        col = 6;
                else if(letter == 'H')
                        col = 7;
                else if(letter == 'I')
                        col = 8;
                else if(letter == 'J')
                        col = 9; 
                else 
                        cout << "Invalid Letter\n";
                }
                //User input for number coordinate.    
        while (row > 9 || row < 0 && v == 0){
                cout << "Please input a number. 0 - 9." << endl;
                cin >> number;
                //Setting the inputed number to represent the row.
                if(number == '0')
                        row = 0;
                else if(number == '1')
                        row = 1;
                else if(number == '2')
                        row = 2;
                else if(number == '3')
                        row = 3;
                else if(number == '4')
                        row = 4;
                else if(number == '5')
                        row = 5;
                else if(number == '6')
                        row = 6;
                else if(number == '7')
                        row = 7;
                else if(number == '8')
                        row = 8;
                else if(number == '9')
                        row = 9;
                else
                        cout << "Invalid Number\n";
                }
        if (pHB[row][col] != '-'){
                col=20;
                row=20;
                cout << endl << "Location already attempted, try again" << endl;
                v = false;
        }
        else
                v = true;
        }     
    if (cSB[row][col] == '+'){
        pHB[row][col] = 'x';
        cSB[row][col] = 'x';
    }
    else
        pHB[row][col] = '0';
}

//Checks to see if the all the ships have been hit
bool isAllShipsHit(char sB[][SIZE]){
    int x = true;
        for (int i=0; i < SIZE; i++){
            for (int j=0; j < SIZE; j++){
                if (sB[i][j] == '+'||sB[i][j] == 'C' || sB[i][j] == 'B'||sB[i][j] == 'K'||sB[i][j] == 'S'||sB[i][j] == 'D')
                   x = false;
            }
        }
    return x;
}

//Checks for valid ship placement
bool ValidShips(char sB[][SIZE],int x, int y, int shipSize, bool p, bool z){
//Checks for valid ship placement, both vertically and horizontally
    //Vertical Check
    if(p == 1){
    if (x > 10 - shipSize){
       for (int i = 0; i < shipSize; i++){   
          if (sB[x][y] != '-'){
             return z = false;
          }
          else if (sB[x][y] == '-'){
              z = true;
              x--;
          }
          }
    }
    else if (x < 10-shipSize){
       for (int i = 0; i < shipSize; i++){   
          if (sB[x][y] != '-'){
             return z = false;
          }
          else{
              z = true;
              x++;
          }
       }
    }
    }
    //Horizontal Check
    if(p == 0){
    if (y > 10 - shipSize){
       for (int i = 0; i < shipSize; i++){   
          if (sB[x][y] != '-'){
              return z = false;
          }
          else if (sB[x][y] == '-'){
              z = true;
                y--;
          }
       }
    }
    else if (y < 10-shipSize){
       for (int i = 0; i < shipSize; i++){   
          if (sB[x][y] != '-'){
               return z = false;
          }
          else if (sB[x][y] == '-'){
              z = true;
                y++;
          }
       }
    }
    }
    return z;
}
//Generates a move for the computer.
void getComputerMove(char pSB[][SIZE]){
    int x, y;
    bool v = false;   
    //While loop checks if the move has already been attempted
    while (v == false){
    x = returnRandom();
    y = returnRandom();
    if (pSB[x][y] == 'x' || pSB[x][y] == '0'){
        v = false;
    }
    else
        v = true;
    }
    if (pSB[x][y] != '-'){
        pSB[x][y] = 'x';
    }
    else
        pSB[x][y]= '0';
}