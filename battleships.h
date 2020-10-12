#include <stdio.h>
#include <string.h>
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define DESTROYER_SIZE 3
#define SUBMARINE_SIZE 2
#define PATROLBOAT_SIZE 2
#define GETCHAR while (getchar() != '\n')

typedef enum
{
	Carrier,
	Battleship,
	Destroyer,
	Submarine,
	PatrolBoat
}ShipType;


typedef enum {	
	None = 32, // white space in ASCII
	Missed = 48, // 0 in ASCII
	Hit = 88, // X in ASCII
	isShip = 42 // * in ASCII
	
}CellState;

typedef struct {
	CellState cellState;
	ShipType shipType;
}Board;

typedef struct {
	ShipType shipType;
	int size;
	int isSunk;
}Ship;

void printBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]);

void initialiseBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]);

int checkInputs(int y, int x, char direction);

int checkOutOfBound(int y, int x, char direction, int shipSize);

int checkShipCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, char direction, int shipSize);

void resetBoardTestCases(int *isValidInput, int *checkCollision, int *isValidBound, int *cont);

void placeShip(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, char direction ,ShipType shipType, int shipSize);

int checkFireInputs(int y, int x);

int checkPlayerWins(Ship *carrier, Ship *battleship, Ship *destroyer, Ship *submarine, Ship *patrolBoat);

void fire(Board playerBoard[BOARD_HEIGHT][BOARD_WIDTH], Board playerShotBoard[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Ship *carrier, Ship *battleship, Ship *destroyer, Ship *submarine, Ship *patrolBoat, int playerNumber);

int checkFired(Board playerShotBoard[BOARD_HEIGHT][BOARD_WIDTH], int y, int x);

void playerConfiguration(Board player1Board[BOARD_HEIGHT][BOARD_WIDTH], Board player2Board[BOARD_HEIGHT][BOARD_WIDTH], Board player1ShotBoard[BOARD_HEIGHT][BOARD_WIDTH], Board player2ShotBoard[BOARD_HEIGHT][BOARD_WIDTH]);



