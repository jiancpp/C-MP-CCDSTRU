#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define PINK "\033[1;35m" // UNO
#define RED "\033[1;31m" // DOS
#define BLUE "\033[1;34m" // TRES
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

typedef int Matrix[4][4][2];
typedef int WinMatrix[3][4][2];

struct GameVariables {
    int     A[4];
    Matrix  P;
    WinMatrix  C;
    bool    B[2];
    int     F[4][4][2];
    Matrix  Uno;
    Matrix  Dos;
    Matrix  Tres;
    bool    turn;
    bool    go;
    int     over;
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
    0        
};

//********************FUNCTIONS*********************//

int 
CheckPlayerHand (int pos[2], Matrix player) {
  int i, j, k;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      int flag = 0;

      for (k = 0; k < 2; k++) {
        if (pos[k] == player[i][j][k]) 
          flag++;
      }

      if (flag == 2) 
        return 1;
    }
  }
  return 0;
}

void
UpdateFreeSpaces() {
  int i, j;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      int uno_hand = CheckPlayerHand(game.P[i][j], game.Uno);
      int tres_hand = CheckPlayerHand(game.P[i][j], game.Tres);
      if (!uno_hand && !tres_hand) {
        game.F[i][j][0] = game.P[i][j][0];
        game.F[i][j][1] = game.P[i][j][1];
      } else {
        game.F[i][j][0] = 0;
        game.F[i][j][1] = 0;
      }
    }
  }
}

void
DisplayBoard(int visible) {
    printf("%6d%6d%6d%6d\n", 1, 2, 3, 4);
    int pos[2] = {1, 1};
    for (int i = 0; i < 4; i++) {
        pos[1] = 1;
        printf("  +-----+-----+-----+-----+\n");
        printf("%d ", i + 1);
        for (int j = 0; j < 4; j++) {
            printf("| ");
            if (game.F[i][j][0] == 0) {
                int uno_hand = CheckPlayerHand(pos, game.Uno);
                int tres_hand = CheckPlayerHand(pos, game.Tres);
                char *color = (uno_hand && visible) ? PINK : (tres_hand && visible) ? BLUE : RESET;
                printf("%s%d %d %s", color, pos[0], pos[1], RESET);
            } else {
                printf("    ");
            }
            pos[1]++;
        }
        printf("|\n");
        pos[0]++;
    }
    printf("  +-----+-----+-----+-----+\n");
}

void
DisplayFreeSpaces()
{
    printf("\n\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("| ");
            for (int k = 0; k < 2; k++){
                printf("%d ", game.F[i][j][k]);
            }
        }
        printf("|\n");
    }
}

int
isNotOccupied(int pos[2]) {
  int x = pos[0];
  int y = pos[1];

  if (game.F[x-1][y-1][0] == 0 && game.F[x-1][y-1][1] == 0) {
    return 0;
  }
  return 1;
}

int 
isConditionMet(Matrix player, int condition_idx) {
    int pos[4][2];
    for (int i = 0; i < 3; i++) {
        pos[i][0] = game.C[condition_idx][i][0];
        pos[i][1] = game.C[condition_idx][i][1];
    }

    int condition_met = CheckPlayerHand(pos[0], player) &&
                        CheckPlayerHand(pos[1], player) &&
                        CheckPlayerHand(pos[2], player) &&
                        CheckPlayerHand(pos[3], player);

    return condition_met;
}

int
NoFreeSpaces() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++){
      if (game.F[i][j][0] != 0) 
        return 0;
    }
  }
  return 1;
}

// ******************** REQUIRED FUNCTIONS ******************** //

void
NextPlayerMove(int pos[2]) {
    srand(time(NULL));
    int x, y; 
    x = pos[0];
    y = pos[1];

    if (game.turn && !game.go && isNotOccupied(pos)) {
        game.Uno[x - 1][y - 1][0] = x;
        game.Uno[x - 1][y - 1][1] = y;

        game.F[x - 1][y - 1][0] = 0;
        game.F[x - 1][y - 1][1] = 0;

        game.go = true;
        game.turn = false;
    }

    else if (!game.turn && !isNotOccupied(pos)) {
        if (CheckPlayerHand(pos, game.Uno)) {
            game.Uno[x - 1][y - 1][0] = 0;
            game.Uno[x - 1][y - 1][1] = 0;

            game.F[x - 1][y - 1][0] = x;
            game.F[x - 1][y - 1][1] = y;
        }
        else if (CheckPlayerHand(pos, game.Tres)) {
            game.Tres[x - 1][y - 1][0] = 0;
            game.Tres[x - 1][y - 1][1] = 0;

            game.F[x - 1][y - 1][0] = x;
            game.F[x - 1][y - 1][1] = y;
        }        
        game.turn = true;
    }

    else if (game.go && isNotOccupied(pos)) {
        game.Tres[x - 1][y - 1][0] = x;
        game.Tres[x - 1][y - 1][1] = y;

        game.F[x - 1][y - 1][0] = 0;
        game.F[x - 1][y - 1][1] = 0;

        game.go = false;
    }
}

bool 
GameOver(int over) {
    switch (over) {
    case 1:
        DisplayBoard(1);
        printf("%sPlayer Uno%s wins!", PINK, RESET);
        return true;
        break;
    case 2:
        DisplayBoard(1);
        printf("%sPlayer Dos%s wins!", RED, RESET);
        return true;
        break;
    case 3:
        DisplayBoard(1);
        printf("%sPlayer Tres%s wins!", BLUE, RESET);
        return true;
        break;
    case 0:
    default:
        return false; //replace with false
    }
}



int main() {
    //INITIALIZE GAME
    srand(time(NULL));
    int players = 0;
    int pos[2] = {1, 1};
    char buffer[50] = "";
    UpdateFreeSpaces();

    printf("How many playes? [2p / 3p]: ");
    scanf(" %d", &players);
    system("cls");
    
    do {
        // PLAYER UNO
        if (game.turn && !game.go && !game.over) {
            printf("%s", buffer);
            DisplayBoard(1);
            // DisplayFreeSpaces();
            printf("%sPlayer Uno%s, which space do you wish to occupy (row column) . . . \n", PINK, RESET);
            printf("%s(Input format: row <space> column)%s\n", YELLOW, RESET);
            do {
                scanf("%d %d", &pos[0], &pos[1]);
            } while (pos[0] > 4 || pos[0] < 1 || pos[1] > 4 || pos[1] < 1 || !isNotOccupied(pos));
            NextPlayerMove(pos);
            
            // Check Win Condition for Uno
            game.over = (isConditionMet(game.Uno, 0) || 
                         isConditionMet(game.Uno, 1) ||
                         isConditionMet(game.Uno, 2) ||
                         isConditionMet(game.Uno, 3)) ? 1 : 
                         (NoFreeSpaces()) ? 2 : 0;
            system("cls");
        }
        // PLAYER DOS
        if (!game.turn && !game.over) {
            if (players == 3) {
                DisplayBoard(0);

                printf("%sPlayer Dos%s, which space do you wish to delete (row column) . . . \n", RED, RESET);
                printf("%s(Input format: row <space> column)%s\n", YELLOW, RESET);
                do {
                    scanf("%d %d", &pos[0], &pos[1]);
                } while (pos[0] > 4 || pos[0] < 1 || pos[1] > 4 || pos[1] < 1 || isNotOccupied(pos));  // is Dos required to delete?
                NextPlayerMove(pos);
                system("cls");
            } else {
                do {
                    pos[0] = (rand() % 4) + 1;
                    pos[1] = (rand() % 4) + 1;
                } while (pos[0] > 4 || pos[0] < 1 || pos[1] > 4 || pos[1] < 1 || isNotOccupied(pos));  // is Dos required to delete?
                NextPlayerMove(pos);
            }   
            sprintf(buffer, "%sPlayer Dos%s picked (%d %d)\n\n", RED, RESET, pos[0], pos[1]);
        }

        // PLAYER TRES
        if (game.go && !game.over) {
            printf("%s", buffer);
            DisplayBoard(1);
            // DisplayFreeSpaces();
            printf("%sPlayer Tres%s, which space do you wish to occupy (row column) . . . \n", BLUE, RESET);
            printf("%s(Input format: row <space> column)%s\n", YELLOW, RESET);
            do {
                scanf(" %d %d", &pos[0], &pos[1]);
            } while (pos[0] > 4 || pos[0] < 1 || pos[1] > 4 || pos[1] < 1 || !isNotOccupied(pos));
            NextPlayerMove(pos);

            // Check Win Condition for Tres
            game.over = (isConditionMet(game.Tres, 0) || 
                         isConditionMet(game.Tres, 1) ||
                         isConditionMet(game.Tres, 2) ||
                         isConditionMet(game.Tres, 3)) ? 3 : 
                         (NoFreeSpaces()) ? 2 : 0;

            system("cls");
        }
    } while (!GameOver(game.over));
    return 0;
}