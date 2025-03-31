#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


#define PINK "\033[1;35m" // UNO
#define RED "\033[1;31m" // DOS
#define BLUE "\033[1;34m" // TRES
#define YELLOW "\033[38;2;255;255;153m"
#define RESET "\033[0m"


typedef int Matrix[4][4][2];
struct GameVariables {
    int     A[4];
    Matrix  P;
    Matrix  C;
    bool    B[2];
    int     F[4][4][2];
    Matrix  Uno;
    Matrix  Dos;
    Matrix  Tres;
    bool    turn;
    bool    go;
    bool    over;
} game = {
    // Initialize A[];
    {1, 2, 3, 4},


    // Initialize P[]
    {{{1, 1}, {1, 2}, {1, 3}, {1, 4}},
     {{2, 1}, {2, 2}, {2, 3}, {2, 4}},
     {{3, 1}, {3, 2}, {3, 3}, {3, 4}},
     {{4, 1}, {4, 2}, {4, 3}, {4, 4}}},
     
     // Initialize C
     {{{1,1}, {1,2}, {1,3}, {1,4}},
      {{1,1}, {2,2}, {3,3}, {4,4}},    
      {{1,4}, {2,3}, {3,2}, {4,1}},  
      {{4,1}, {4,2}, {4,3}, {4,4}}},  


    // Initialize B[]
    {true, false},  


    // Initialize F (Empty Example)
    {{{0}}},


    // Initialize Uno (Empty Example)
    {{{0}}},


    // Initialize Dos (Empty Example)
    {{{0}}},


    // Initialize Tres
    {{{0}}},


    // Initialize boolean var
    true,
    false,
    false        
};

char uno_symbol = '1';
char tres_symbol = '3';

//******************** GAME INTERFACE *********************//

/*
    Function: printDivider()
    -----------------------------
    - Displays a 120 character long divider
*/
void
printDivider() {
    for (int i = 0; i < 120; i++) {
        printf("=");
    }
    printf("\n");
}

/*
    Function: printHeader()
    -----------------------------
    - Displays the game title
*/
void
printHeader() {
    printDivider();
    printf("\n%76s", "Under the Shadow: Mafia Edition\n\n");
    printDivider();
}

/*
    Function: gameInstructions()
    -----------------------------
    - Introduces the game variables and objectives
    - Displays the winning patterns
*/
void
gameInstructions() {
    system("cls");
    printDivider();
    printf("\n%s%69s%s", YELLOW, "GAME INSTRUCTIONS\n\n", RESET);
    printDivider();

    printf("\n\n");
    printf("%104s", "\"Under The Shadow: Mafia Edition\" is a board game that requires high-level thinking\n");
    printf("%106s", "where players play as either Uno and Tres, two lovers-turned-enemies who are fugitives\n");
    printf("%105s", "on the run from Detective Dos. The two players plant misleading evidences pointing to\n");
    printf("%106s", "the other by occupying the spaces on the board. The first player to complete one of the\n");
    printf("%106s", "winning patterns wins and successfully escapes from suspicion, leaving the other taking\n");
    printf("%74s", "the fall for their crime.\n\n");

    printDivider();
    printf("\n\n%sPLAYERS MODES:%s     (1) Two-Player-Mode   (2) Three-Player-Mode\n", YELLOW, RESET);

    printf("\n%sPLAYERS:%s\n", YELLOW, RESET);
    printf("%sUno%s & %sTres%s         their objective is to be the first to complete a winning pattern.\n", PINK, RESET, BLUE, RESET);

    printf("\n%sSPECIAL PLAYER:%s\n", YELLOW, RESET);
    printf("%sDos%s                their objective is to capture both Uno and Tres. They needs to strategically\n", RED, RESET); 
    printf("                   pick a position on the board that is currently occupied by any of the players,\n"); 
    printf("                   removing it from the board and stopping both players from winning. Dos wins \n");
    printf("                   if the game is a draw.\n\n");

    printf("\n%sWINNING PATTERNS:%s\n", YELLOW, RESET);
    // First row of patterns (Top row win, Bottom row win, Correct diagonal win)
    printf("                   +-----+-----+-----+-----+    +-----+-----+-----+-----+    +-----+-----+-----+-----+\n");
    printf("                   |  %sO%s  |  %sO%s  |  %sO%s  |  %sO%s  |    |     |     |     |     |    |     |     |     |  %sO%s  |\n",
           YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET);
    printf("                   +-----+-----+-----+-----+    +-----+-----+-----+-----+    +-----+-----+-----+-----+\n");
    printf("                   |     |     |     |     |    |     |     |     |     |    |     |     |  %sO%s  |     |\n",
           YELLOW, RESET);
    printf("                   +-----+-----+-----+-----+    +-----+-----+-----+-----+    +-----+-----+-----+-----+\n");
    printf("                   |     |     |     |     |    |     |     |     |     |    |     |  %sO%s  |     |     |\n",
           YELLOW, RESET);
    printf("                   +-----+-----+-----+-----+    +-----+-----+-----+-----+    +-----+-----+-----+-----+\n");
    printf("                   |     |     |     |     |    |  %sO%s  |  %sO%s  |  %sO%s  |  %sO%s  |    |  %sO%s  |     |     |     |\n",
           YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET);
    printf("                   +-----+-----+-----+-----+    +-----+-----+-----+-----+    +-----+-----+-----+-----+\n");


}

/*
    Function: setCharacter()
    -----------------------------
    - Allows players to customize symbols for Uno and Tres
*/
void
setCharacter() {
    system("cls");
    printHeader();

    int willCustomize;

    printf("\n\n%69s", "CURRENT SYMBOLS\n");
    printf("\n%51s", " ");
    printf("Uno: %s%c%s\t", PINK, uno_symbol, RESET);
    printf("Tres: %s%c%s\n\n", BLUE, tres_symbol, RESET);

    printDivider();
    printf("\n%76s\n", "Customize [1]  Keep Current [2]");
    printf("\n%69s", "Select option > ");
    scanf(" %d", &willCustomize);

    printf("\n\n");

    switch (willCustomize) {
    case 1:
        printf("%72s", "Change Symbol for Uno: ");
        scanf(" %c", &uno_symbol);
        printf("\n\n");
        printf("%72s", "Change Symbol for Tres: ");
        scanf(" %c", &tres_symbol);
        break;
    
    default:
        break;
    }
    printf("\n\n");
}

//******************** GAME FUNCTIONS *********************//

/*
    Function: CheckPlayerHand()
    -----------------------------------
    - Checks if a given position (`pos[2]`) exists in the player's 4x4 matrix.
    - Used to determine if a player occupies a specific spot.


    Parameters:
    - pos[2]: The (x, y) coordinates of the position being checked.
    - player: A 4x4 matrix representing the player's occupied positions.


    Returns:
    - 1 if the position exists in the player's matrix (i.e., player occupies the space).
    - 0 if the position is not found.
*/
int
CheckPlayerHand (int pos[2], Matrix player) {
  int i, j, k;
  for (i = 0; i < 4; i++) { // Iterate over the 4x4 matrix of the player
    for (j = 0; j < 4; j++) {
      int flag = 0; // Counter to track matches


      for (k = 0; k < 2; k++) {
        if (pos[k] == player[i][j][k]) // Compare with player's matrix element
          flag++;
      }


      if (flag == 2)
        return 1; //if the position exists in the player's matrix
    }
  }
  return 0; //if the position is not found
}


/*
    Function: UpdateFreeSpaces
    -----------------------------------
    - Updates the `game.F` matrix to track available spaces on the board.
    - If a position is occupied by Player Uno or Player Tres, it marks it as unavailable (0).
    - If a position is unoccupied, it retains its original coordinates from `game.P`.
*/
void
UpdateFreeSpaces() {
  int i, j;


  for (i = 0; i < 4; i++) { // Iterate through the 4x4 board
    for (j = 0; j < 4; j++) {
      int uno_hand = CheckPlayerHand(game.P[i][j], game.Uno);  
      int tres_hand = CheckPlayerHand(game.P[i][j], game.Tres);
      if (!uno_hand && !tres_hand) { // Check if the current position is occupied by Player Uno or Player Tres
        game.F[i][j][0] = game.P[i][j][0]; // Store x-coordinate
        game.F[i][j][1] = game.P[i][j][1]; // Store y-coordinate
      } else {
        game.F[i][j][0] = 0; // If occupied, mark the space as unavailable (0)
        game.F[i][j][1] = 0;
      }
    }
  }
}


/*
    Function: DisplayBoard
    -----------------------------------
    - Prints the current state of the game board.
    - Displays row and column numbers for reference.
    - Shows Player Uno’s moves in pink and Player Tres’s moves in blue.
    - If a position is unoccupied, it remains blank.
   
    Parameters:
    - int visible: Determines whether player hands should be displayed in color.
   
    No return value. (Outputs the board to the console)
*/
void
DisplayBoard(int visible) {
    printf("%6d%6d%6d%6d\n", 1, 2, 3, 4);
    int pos[2] = {1, 1};                            // Position tracker for checking player hands
    for (int i = 0; i < 4; i++) {                   // Loop through each row of the board
        pos[1] = 1;                                 // Reset column position at the start of each row
        printf("  +-----+-----+-----+-----+\n");    // Print horizontal line separator
        printf("%d ", i + 1);                       // Print row number
        for (int j = 0; j < 4; j++) {               // Loop through each column of the board
            printf("|");
            if (game.F[i][j][0] == 0) {
                int uno_hand = CheckPlayerHand(pos, game.Uno);                  // If the space is occupied (game.F[i][j][0] == 0), check player hands
                int tres_hand = CheckPlayerHand(pos, game.Tres);                
                char *color = (uno_hand && visible) ? PINK : (tres_hand && visible) ? BLUE : RESET; // Pink for Player Uno, Blue for Player Tres
                char symbol = (uno_hand && visible) ? uno_symbol : (tres_hand && visible) ? tres_symbol : '0'; // Pink for Player Uno, Blue for Player Tres
                printf("%s  %c  %s", color, symbol, RESET);
            } else {
                printf("     ");    // Print empty space if position is unoccupied
            }
            pos[1]++; // Move to the next column
        }
        printf("|\n");
        pos[0]++; // Move to the next row
    }
    printf("  +-----+-----+-----+-----+\n");
}


/*
    Function: isNotOccupied
    -----------------------------------
    - Checks if a given position on the board is **free** (not occupied by any player).
   
    Parameters:
    - int pos[2]: The position to check (pos[0] = X, pos[1] = Y).
   
    Returns:
    - 0 if the position is free.
    - 1 if the position is occupied.
*/
int
isNotOccupied(int pos[2]) {
  int x = pos[0];  // Extract X coordinate
  int y = pos[1];   // Extract Y coordinate


  if (game.F[x-1][y-1][0] == 0 && game.F[x-1][y-1][1] == 0) {
    return 0; // Position is free
  }
  return 1; // Position is occupied
}


/*
    Function: isConditionMet
    -----------------------------------

    - Checks if a player has met a **winning condition** by occupying a specific set of 4 positions.

    Parameters:
    - Matrix player: The player's matrix (Uno, Tres, etc.).
    - int condition_idx: The index representing a winning condition (1st row, 4th column, diagonal from right to left).


    Returns:
    - 1 if the player has occupied all 4 positions in the winning condition.
    - 0 if the player has NOT met the condition.
*/
int
isConditionMet(Matrix player, int condition_idx) {
    int pos[4][2];
    for (int i = 0; i < 4; i++) { // Retrieve the 4 positions corresponding to the condition index
        pos[i][0] = game.C[condition_idx][i][0];
        pos[i][1] = game.C[condition_idx][i][1];
    }


    // Check if all 4 positions of the winning pattern are occupied by the player
    int condition_met = CheckPlayerHand(pos[0], player) &&
                        CheckPlayerHand(pos[1], player) &&
                        CheckPlayerHand(pos[2], player) &&
                        CheckPlayerHand(pos[3], player);


    return condition_met; // Returns 1 if all positions match, otherwise 0
}


/*
    Function: NoFreeSpaces
    - Checks if there are **any available spaces** left on the board.


    Returns:
    - 1 if there are no free spaces (board is full).
    - 0 if there are still available spaces.
*/
int
NoFreeSpaces() {
  for (int i = 0; i < 4; i++) { // Iterate over 4x4 rows
    for (int j = 0; j < 4; j++){
      if (game.F[i][j][0] != 0) // If any position is not zero, a space is available
        return 0; // There are still free spaces
    }
  }
  return 1; // No free spaces left
}


// ******************** REQUIRED FUNCTIONS ******************** //

/*
    Function: NextPlayerMove
    -------------------------

    Handles the movement logic for Player Uno and Player Tres.
    Determines the next move based on whose turn it is.
*/
void
NextPlayerMove(int pos[2]) {
    srand(time(NULL));
    int x, y;
    x = pos[0]; // Extract X coordinate from position
    y = pos[1]; // Extract Y coordinate from position

    /*
        PLAYER UNO'S TURN (First Move)
        - Executes only if it's Player Uno's turn (`game.turn == false`)
        - Ensures that the chosen position is NOT occupied (`isNotOccupied(pos) == true`)
        - Places Player Uno's piece at (x, y)
        - Marks the space as occupied in `game.F`
        - Transfers the turn to the next phase (`game.go = true`, `game.turn = false`)
    */
    if (game.turn && game.go && isNotOccupied(pos)) {
        game.Uno[x - 1][y - 1][0] = x; // Store X coordinate in Uno's matrix
        game.Uno[x - 1][y - 1][1] = y; // Store Y coordinate in Uno's matrix


        game.F[x - 1][y - 1][0] = 0; // Mark the space as occupied in game.F
        game.F[x - 1][y - 1][1] = 0;


        game.go = !game.go;     // Indication that Player Uno has moved (game.go == false) 
        game.turn = !game.turn; // Indication that Dos is next to move (game.turn == false) 
    }


    /*
        PLAYER DOS'S TURN (Remove Opponent's Piece)
        - Executes only after Uno's turn (`game.turn == false`)
        - Ensures the chosen position IS occupied (`isNotOccupied(pos) == false`)
        - Checks if the position belongs to Player Uno or Player Tres
        - If Player Uno occupies the position, remove their piece
        - If Player Tres occupies the position, remove their piece
        - Updates the board (`game.F`) to make the space available again
        - Transfers the turn to the next phase (`game.turn = false`)
    */


    else if (!game.turn && !isNotOccupied(pos)) {
        if (CheckPlayerHand(pos, game.Uno)) { //If chosen by Player Dos is from Player Uno
            game.Uno[x - 1][y - 1][0] = 0; // Remove X coordinate
            game.Uno[x - 1][y - 1][1] = 0; // Remove Y coordinate


            game.F[x - 1][y - 1][0] = x; // Mark the space as free again
            game.F[x - 1][y - 1][1] = y;
        }
        else if (CheckPlayerHand(pos, game.Tres)) {
            game.Tres[x - 1][y - 1][0] = 0; // Remove X coordinate
            game.Tres[x - 1][y - 1][1] = 0; // Remove Y coordinate


            game.F[x - 1][y - 1][0] = x; // Mark the space as free again
            game.F[x - 1][y - 1][1] = y;
        }        
        game.turn = !game.turn; // Indication that Player Dos has moved
    }


    /*
        PLAYER TRES'S TURN (Second Move)
        - Executes only if `game.go == true`, meaning it's the last phase
        - Ensures the chosen position is NOT occupied (`isNotOccupied(pos) == true`)
        - Places Player Tres's piece at (x, y)
        - Marks the space as occupied in `game.F`
        - Transfers the turn back to the next round (`game.go = false`)
    */
    else if (!game.go && isNotOccupied(pos)) {
        game.Tres[x - 1][y - 1][0] = x; // Store X coordinate in Tres's matrix
        game.Tres[x - 1][y - 1][1] = y; // Store Y coordinate in Tres's matrix


        game.F[x - 1][y - 1][0] = 0; // Mark the space as occupied in game.F
        game.F[x - 1][y - 1][1] = 0;


        game.go = !game.go; // Indication that Player Tres has moved
    }
}


/*
    Function: GameOver
    ------------------
    - Checks if the game has reached a terminal state (win condition or no more moves).
    - Determines which player wins based on conditions.
    - Displays the final board and announces the winner.


    Parameters:
    - over: Boolean flag indicating whether to check for game-over conditions.


    Returns:
    - true if a player wins or the game is over.
    - false otherwise.
*/
bool
GameOver(bool over) {
    int result; //stores the number of the winning player
    /*
        CHECK IF THE BOARD IS FULL (Player Dos Wins)
        - If `over` is true AND there are no free spaces left (`NoFreeSpaces()` returns true),
          Player Dos (RED) is declared the winner.
        - Player Dos wins when all spaces are filled, as they are responsible for removing pieces.
    */
    if (over && NoFreeSpaces()) {
        result = 2;
    }

    /*
        CHECK IF PLAYER UNO WINS
        - If `over` is true AND Player Uno has met one of four possible win conditions,
          Player Uno (PINK) is declared the winner.
        - `isConditionMet(game.Uno, i)` checks for a specific winning condition.
    */
    else if (over && (isConditionMet(game.Uno, 0) ||
                      isConditionMet(game.Uno, 2) || 
                      isConditionMet(game.Uno, 3))) {
        result = 1;
    }

    /*
        CHECK IF PLAYER TRES WINS
        - If `over` is true AND Player Tres has met one of four possible win conditions,
          Player Tres (BLUE) is declared the winner.
    */
    else if (over && (isConditionMet(game.Tres, 0) || 
                      isConditionMet(game.Tres, 2) || 
                      isConditionMet(game.Tres, 3))) {
        result = 3;
    }


    /*
        DISPLAY GAME RESULT
        - If result is either 1, 2, 3, the game ends (GameOver() == true)
        - Otherwise, the game continues (GameOver() == false)
    */
    switch (result) {
    case 1: //Player Uno Wins
        DisplayBoard(1);
        printf("%sPlayer Uno%s wins!", PINK, RESET);
        return true;
        break;
    case 2://Player Dos Wins
        DisplayBoard(1);
        printf("%sPlayer Dos%s wins!", RED, RESET);
        return true;
        break;
    case 3: //Player Tres Wins
        DisplayBoard(1);
        printf("%sPlayer Tres%s wins!", BLUE, RESET);
        return true;
        break;
    case 0:
    default: // No winner yet, game continues
        return false; //replace with false
    }
}


int main() {
    //INITIALIZE GAME
    srand(time(NULL));
    int players = 0;
    int pos[2] = {1, 1};
    int start = 0;
    int error_check;
    char buffer[50] = "";
    char enter[2];
    UpdateFreeSpaces();

    // Welcome Screen for Players
    system("cls");
    while (start != 3) {
        printHeader();
        printf("\n\n");
        printf("%93s", "[1] Game Instructions   [2] Customize Character  [3]  Start Game\n\n");
        printf("%69s", "Select option > ");
        scanf(" %d", &start);

        switch (start) {
        case 1:
            gameInstructions();
            printf("\n%74s", "Press [Enter] to continue...");
            getch();
            break;
        case 2:
            setCharacter();
            printf("\n%74s", "Press [Enter] to continue...");
            getch();
            break;
        default:
            break;
        }
        system("cls");
    }

    printHeader();
    printf("\n\n%75s", "How many players? [2p / 3p]: ");
    scanf(" %d", &players);
    system("cls");
   
    do {
        // PLAYER UNO
        if (game.turn && game.go && !game.over) {
            printf("%s", buffer);
            DisplayBoard(1);

            // Prompt user for position they wish to occupy
            printf("%sPlayer Uno%s, which space do you wish to occupy . . . \n", PINK, RESET);
            do {
                do {
                    printf("Enter row number: ");
                    scanf(" %d", &pos[0]);
                } while (pos[0] > 4 || pos[0] < 1 );
                
                do {
                    printf("Enter column number: ");
                    scanf(" %d", &pos[1]);
                } while (pos[1] > 4 || pos[1] < 1);
                
            } while (!isNotOccupied(pos));
            NextPlayerMove(pos);
           
            // Check Win Condition for Uno
            // over if and only if (Uno ∈ W ∨ Tres ∈ W ∨ F = ∅)
            game.over = (isConditionMet(game.Uno, 0) ||
                         isConditionMet(game.Uno, 2) ||
                         isConditionMet(game.Uno, 3)) ||
                         (NoFreeSpaces()) ? true : false;
            system("cls");
        }
        // PLAYER DOS
        if (!game.turn && !game.over) {
            // Check Player Mode [2p / 3p]
            if (players == 3) {
                DisplayBoard(0);


                // Prompt user for a currently occupied position they wish to delete
                printf("%sPlayer Dos%s, which space do you wish to delete (row column) . . . \n", RED, RESET);
                printf("%s(Input format: row <space> column)%s\n", YELLOW, RESET);
                do {
                    do {
                        printf("Enter row number: ");
                        scanf(" %d", &pos[0]);
                    } while (pos[0] > 4 || pos[0] < 1 );
                    
                    do {
                        printf("Enter column number: ");
                        scanf(" %d", &pos[1]);
                    } while (pos[1] > 4 || pos[1] < 1);

                } while (isNotOccupied(pos));  // is Dos required to delete?
                NextPlayerMove(pos);
                system("cls");
            } else {
                // Randomize position that will be deleted
                do {
                    pos[0] = (rand() % 4) + 1;
                    pos[1] = (rand() % 4) + 1;
                } while (pos[0] > 4 || pos[0] < 1 || pos[1] > 4 || pos[1] < 1 || isNotOccupied(pos));  // is Dos required to delete?
                NextPlayerMove(pos);
            }  
            sprintf(buffer, "%sPlayer Dos%s picked (%d %d)\n\n", RED, RESET, pos[0], pos[1]);
        }


        // PLAYER TRES
        if (!game.go && !game.over) {
            printf("%s", buffer);
            DisplayBoard(1);


            // Prompt user for position they wish to occupy
            printf("%sPlayer Tres%s, which space do you wish to occupy . . . \n", BLUE, RESET);
            do {
                do {
                    printf("Enter row number: ");
                    scanf(" %d", &pos[0]);
                } while (pos[0] > 4 || pos[0] < 1 );
                
                do {
                    printf("Enter column number: ");
                    scanf(" %d", &pos[1]);
                } while (pos[1] > 4 || pos[1] < 1);

            } while (!isNotOccupied(pos));
            NextPlayerMove(pos);


            // Check Win Condition for Tres
            game.over = (isConditionMet(game.Tres, 0) ||
                         isConditionMet(game.Tres, 2) ||
                         isConditionMet(game.Tres, 3)) ||
                         (NoFreeSpaces()) ? true : false;


            system("cls");
        }
    } while (!GameOver(game.over));
    return 0;
}

