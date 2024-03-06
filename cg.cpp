

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>

int size = 240,i,j;
char board[3][3];
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

// Function prototypes
void p1(int, int);
void p2(int, int);
void resetBoard();
void printBoard();
int checkBoard();
void playerMove(char);
char checkWinner();
void printWinner(char);

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\tc\\BGI");

    char winner = ' ';
    resetBoard();

    while (winner == ' ' && checkBoard() != 0) {
      // Clear the screen before printing the board
	printBoard();

	playerMove(PLAYER1);
	winner = checkWinner();
	if (winner != ' ' || checkBoard() == 0) {
	    break;
	}

	delay(500);  // Introduce a delay to slow down the game



	playerMove(PLAYER2);
	winner = checkWinner();
	if (winner != ' ' || checkBoard() == 0) {
	    break;
	}
	delay(500);
    }
    printWinner(winner);

    closegraph();
    return 0;
}

void resetBoard() {
    for (i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    board[i][j] = ' ';
	}
    }
}

void printBoard() {
    rectangle(0 + 200, 0 + 200, size + 200, size + 200);
    line((size / 3) + 200, 0 + 200, (size / 3) + 200, size + 200);
    line((2 * size / 3) + 200, 0 + 200, (2 * size / 3) + 200, size + 200);
    line(0 + 200, (size / 3) + 200, size + 200, (size / 3) + 200);
    line(0 + 200, (2 * size / 3) + 200, size + 200, (2 * size / 3) + 200);
}

void p1(int a, int b) {
    line(b * (size / 3) + 200, a * (size / 3) + 200, (b + 1) * (size / 3) + 200, (a + 1) * (size / 3) + 200);
    line((b + 1) * (size / 3) + 200, a * (size / 3) + 200, b * (size / 3) + 200, (a + 1) * (size / 3) + 200);
}

void p2(int a, int b) {
    circle(b * (size / 3) + (size / 6) + 200, a * (size / 3) + (size / 6) + 200, size / 6);
}

int checkBoard() {
    int freeSpace = 9;
    for (i = 0; i < 3; i++) {
	for (j = 0; j < 3; j++) {
	    if (board[i][j] != ' ') {
		freeSpace--;
	    }
	}
    }
    return freeSpace;
}

void playerMove(char player) {
    int x, y, n;
    do {
	printf("Player %c\n", player);
	printf("Enter number (1-9): ");
	scanf("%d", &n);

	// Convert input to board coordinates
	x = (n - 1) / 3;
	y = (n - 1) % 3;

	if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
	    printf("Invalid move\n");
	} else {
	    board[x][y] = player;
	    if (player == PLAYER1) {
		p1(x, y);
	    } else {
		p2(x, y);
	    }
	    break;
	}
    } while (board[x][y] != ' ');
}

char checkWinner() {
    for ( i = 0; i < 3; i++) {
	if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') {
	    return board[i][0];
	}
    }

    for ( i = 0; i < 3; i++) {
	if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ') {
	    return board[0][i];
	}
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
	return board[0][0];
    }

    if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != ' ') {
	return board[2][0];
    }

    return ' ';  // No winner yet
}

void printWinner(char win) {
    if (win != ' ') {
	printf("Player %c wins!\n", win);
    } else {
	printf("It's a draw!\n");
    }
    getch();
}

