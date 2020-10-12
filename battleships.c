#include "battleships.h"

void printBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]){
	int alphabet = 65; // 'A' in ASCII
	printf(" ");
	for (int i = 0; i < BOARD_WIDTH; i++){
		printf("% d", i+1);
	}
	printf("\n");
	
	for(int i =0; i < BOARD_HEIGHT; i++){
		printf("%c|", alphabet);
		alphabet++;
		for(int j =0; j < BOARD_WIDTH; j++){
			printf("%c|", board[i][j].cellState);
		}
		printf("\n");
	}
}

void initialiseBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]){
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			board[i][j].cellState = None;
		}
	}

}

int checkInputs(int y, int x, char direction){
	int isValidInput;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49). 
	if((direction == 'V' || direction =='H')  && (x>= 0 && x< 8) && (y>= 0 && y< 8)){ // Check inputs [A-H][1-8][V||H].
		isValidInput = 1;
	} else {
		isValidInput = 0;
	}
	
	return isValidInput;
}

int checkOutOfBound(int y, int x, char direction, int shipSize){
	int isValidInput = checkInputs(y, x, direction);
	int isValidBound = 1;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49).
	if(direction == 'H' && isValidInput == 1){ //
		for(int i =0; i <shipSize; i++){
			if(x + shipSize <= BOARD_WIDTH + i){ //Check if the shipsize is out of the board(width).
				isValidBound = 1;
				x++;
			}else{
				isValidBound = 0;
				break;
			}
		}
	}else if((direction == 'V' && isValidInput == 1)){
		for(int i =0; i <shipSize; i++){
			if(y + shipSize <= BOARD_HEIGHT + i){ //Check if the shipsize is out of the board(height).
				isValidBound = 1;
				y++;
			} else{
				isValidBound = 0;
				break;
			}	
		}
	}
	
	return isValidBound;
}

int checkShipCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, char direction, int shipSize){
	int isValidInput = checkInputs(y, x, direction);
	int checkCollision = 1;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49).
	if(direction == 'H' && isValidInput == 1){
		for(int i = x; i < x + shipSize; i++){ //Check if there is a collision. e.g. x = 3, shipsize = 3 indexes between 3-6 must be checked in order to place a ship.
			if(board[y][i].cellState == isShip){
				checkCollision = 0;
			} 
		}
	}else if (direction =='V' && isValidInput == 1){
		for(int i = y; i < y + shipSize; i++){
			if(board[i][x].cellState == isShip){
				checkCollision = 0;
			} 
		}
	}
	return checkCollision;
}


void resetBoardTestCases(int *isValidInput, int *checkCollision, int *isValidBound, int *cont){ //set the test caeses value = 0.
	*isValidInput = 0;
	*checkCollision = 0;
	*isValidBound = 0;
	*cont = 0;
}

void placeShip(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, char direction ,ShipType shipType, int shipSize){
	int isValidInput = checkInputs(y, x, direction);
	int checkCollision =  checkShipCollision(board, y, x, direction, shipSize);
	int isValidBound =  checkOutOfBound(y, x, direction, shipSize);
	y-= 65; // Convert Char into Int ('A' = 65 in ASCII).
	x-= 49; // Convert Char into Int ('1' = 49).   
	if(isValidInput == 1 && direction == 'H'){ // Check inputs [A-H][1-8][V||H].
		for(int i =0; i <shipSize; i++){
			if(board[y][x].cellState == None && checkCollision == 1 && isValidBound == 1){ //Check if the shipsize is out of the board(width) AND cellState AND checkShipCollision
				board[y][x].cellState = isShip;
				board[y][x].shipType = shipType;
				x++;
			}else {
				printf("Invalid ship configuration\n");
				break;
			}
		}
	}else if(isValidInput == 1 && direction == 'V') { //Check inputs [A-H][1-8][V||H].
		for(int i =0; i <shipSize; i++){
			if(board[y][x].cellState == None && checkCollision == 1 && isValidBound == 1){ //Check if the shipsize is out of the board(height) AND cellState AND checkShipCollision
				board[y][x].cellState = isShip;
				board[y][x].shipType = shipType;
				y++;
			}else {
				printf("Invalid ship configuration\n");
				break;
			}
		}
	} else {
		printf("Invalid ship configuration\n");
	}
}

int checkFireInputs(int y, int x){ //checks coordinates when a player tries to fire.
	int isValidInput;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49). 
	if((x>= 0 && x< 8) && (y>= 0 && y< 8)){ // Check inputs [A-H][1-8][V||H].
		isValidInput = 1;
	} else {
		isValidInput = 0;
	}
	
	return isValidInput;
}

int checkPlayerWins(Ship *carrier, Ship *battleship, Ship *destroyer, Ship *submarine, Ship *patrolBoat){
	int isPlayerWin = 0;
	if (carrier->size == 0 && battleship->size == 0 && destroyer->size == 0 && submarine->size == 0 && patrolBoat->size == 0){
		isPlayerWin = 1;
	}
	
	return isPlayerWin; 
}

void fire(Board playerBoard[BOARD_HEIGHT][BOARD_WIDTH], Board playerShotBoard[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Ship *carrier, Ship *battleship, Ship *destroyer, Ship *submarine, Ship *patrolBoat, int playerNumber){
	int isPlayerWin;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49)
	
	if(playerBoard[y][x].cellState == 42){
		
		playerBoard[y][x].cellState = 88;
		playerShotBoard[y][x].cellState = 88;
		
		if(playerBoard[y][x].shipType == carrier->shipType){
			carrier->size--;
		}else if(playerBoard[y][x].shipType == battleship->shipType){
			battleship->size--;
		}else if(playerBoard[y][x].shipType == destroyer->shipType){
			destroyer->size--;
		}else if(playerBoard[y][x].shipType == submarine->shipType){
			submarine->size--;
		}else if(playerBoard[y][x].shipType == patrolBoat->shipType){
			patrolBoat->size--;
		}
		
		if(carrier->size == 0 && carrier->isSunk == 0){
			printf("\n");
    		printf("We have sunk your Carrier!\n");
			printf("\n");
			carrier->isSunk = 1;
		} else if(battleship->size == 0 && battleship->isSunk == 0){
			printf("\n");
    		printf("We have sunk your Battleship!\n");
			printf("\n");
			battleship->isSunk = 1;
		} else if(destroyer->size == 0 && destroyer->isSunk == 0){
			printf("\n");
    		printf("We have sunk your Destroyer!\n");
			printf("\n");
			destroyer->isSunk = 1;
		} else if(submarine->size == 0 && submarine->isSunk == 0){
			printf("\n");
    		printf("We have sunk your Submarine!\n");
			printf("\n");
			submarine->isSunk = 1;
		} else if(patrolBoat->size == 0 && patrolBoat->isSunk == 0){
			printf("\n");
    		printf("We have sunk your Patrol Boat!\n");
			printf("\n");
			patrolBoat->isSunk = 1;
		} else {
			printf("\n");
    		printf("We have hit the target!\n");
			printf("\n");
		}
	} else if(playerBoard[y][x].cellState == 32){
		playerBoard[y][x].cellState = 48;
		playerShotBoard[y][x].cellState = 48;
		printf("\n");
    	printf("You have missed!\n");
		printf("\n");
	}
	isPlayerWin  = checkPlayerWins(carrier, battleship, destroyer, submarine, patrolBoat);
	if(isPlayerWin == 0){
		printf("Player %d's turn\n", playerNumber);
		printf("\n");
	} else {
		if(playerNumber == 2){
			printf("Player 1 wins!\n");
		}else if(playerNumber == 1){
			printf("Player 2 wins!\n");
		}
	}
}

int checkFired(Board playerShotBoard[BOARD_HEIGHT][BOARD_WIDTH], int y, int x){
	int isFired = 0;
	y-= 65; // Convert Char into Int ('A' = 65).
	x-= 49; // Convert Char into Int ('1' = 49)

	if(playerShotBoard[y][x].cellState == 88){
		isFired = 1;
	} else if(playerShotBoard[y][x].cellState == 48){
		isFired = 1;
	}
	
	return isFired;
}

void playerConfiguration(Board player1Board[BOARD_HEIGHT][BOARD_WIDTH], Board player2Board[BOARD_HEIGHT][BOARD_WIDTH], Board player1ShotBoard[BOARD_HEIGHT][BOARD_WIDTH], Board player2ShotBoard[BOARD_HEIGHT][BOARD_WIDTH]){
	char y, x, orientation; //All inputs are stored as char for fixing errors.
	int isValidInput = 0;
	int checkCollision = 0;
	int isValidBound = 0;
	int cont = 0;
	int playerNumber = 1;
	int isPlayerWin = 0;

	char command[20];
    char firstCommand[5];
    int shotsCommand, exitCommand, fireCommand, totalRead, isValidCoordinates, isFired, iToC;
	
	Ship p1Carrier = {Carrier, CARRIER_SIZE, 0};
	Ship p1Battleship = {Battleship, BATTLESHIP_SIZE, 0};
	Ship p1Destroyer = {Destroyer, DESTROYER_SIZE, 0};
	Ship p1Submarine = {Submarine, SUBMARINE_SIZE, 0};
	Ship p1PatrolBoat = {PatrolBoat, PATROLBOAT_SIZE, 0};
	
	Ship p2Carrier = {Carrier, CARRIER_SIZE, 0};
	Ship p2Battleship = {Battleship, BATTLESHIP_SIZE, 0};
	Ship p2Destroyer = {Destroyer, DESTROYER_SIZE, 0};
	Ship p2Submarine = {Submarine, SUBMARINE_SIZE, 0};
	Ship p2PatrolBoat = {PatrolBoat, PATROLBOAT_SIZE, 0};
	

//Player 1's configuration
	printf("Player 1, please set up your ships (y, x, orientation)\n");
	initialiseBoard(player1Board);
	initialiseBoard(player1ShotBoard); // Initialise player's shotboard after configuration.
	
	
	while(cont !=1){
		printf("Carrier: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR; // A defined macro that fixes the issue(prints error meesage twice after using scanf).
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player1Board, y, x, orientation, CARRIER_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, CARRIER_SIZE);
			
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		
		placeShip(player1Board, y, x, orientation, Carrier, CARRIER_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont); //set the test caeses value = 0.
	
	while(cont !=1){
		printf("Battleship: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player1Board, y, x, orientation, BATTLESHIP_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, BATTLESHIP_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player1Board, y, x, orientation, Battleship, BATTLESHIP_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Destroyer: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player1Board, y, x, orientation, DESTROYER_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, DESTROYER_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player1Board, y, x, orientation, Destroyer, DESTROYER_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Submarine: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player1Board, y, x, orientation, SUBMARINE_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, SUBMARINE_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player1Board, y, x, orientation, Submarine, SUBMARINE_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Patrol Boat: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player1Board, y, x, orientation, PATROLBOAT_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, PATROLBOAT_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player1Board, y, x, orientation, PatrolBoat, PATROLBOAT_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	printf("\n");
	printf("\n");
	
//Player 2's configuration
	printf("Player 2, please set up your ships (y, x, orientation)\n");
	initialiseBoard(player2Board);
	initialiseBoard(player2ShotBoard); // Initialise player's shotboard after configuration.
	
	while(cont !=1){
		printf("Carrier: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR; // A defined macro that fixes the issue(prints error meesage twice after using scanf).
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player2Board, y, x, orientation, CARRIER_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, CARRIER_SIZE);
			
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		
		placeShip(player2Board, y, x, orientation, Carrier, CARRIER_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont); //set the test caeses value = 0.
	
	while(cont !=1){
		printf("Battleship: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player2Board, y, x, orientation, BATTLESHIP_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, BATTLESHIP_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player2Board, y, x, orientation, Battleship, BATTLESHIP_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Destroyer: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player2Board, y, x, orientation, DESTROYER_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, DESTROYER_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player2Board, y, x, orientation, Destroyer, DESTROYER_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Submarine: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player2Board, y, x, orientation, SUBMARINE_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, SUBMARINE_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player2Board, y, x, orientation, Submarine, SUBMARINE_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	while(cont !=1){
		printf("Patrol Boat: ");
		scanf("%c %c %c", &y, &x, &orientation);
		GETCHAR;
		isValidInput = checkInputs(y, x, orientation);
		checkCollision = checkShipCollision(player2Board, y, x, orientation, PATROLBOAT_SIZE);
		isValidBound = checkOutOfBound(y, x, orientation, PATROLBOAT_SIZE);
		
		if(isValidInput && checkCollision && isValidBound == 1){
			cont = 1;
		}
		placeShip(player2Board, y, x, orientation, PatrolBoat, PATROLBOAT_SIZE);
	}
	resetBoardTestCases(&isValidInput, &checkCollision, &isValidBound, &cont);
	
	printf("\n");
	printf("All boats set up, Player 1 can now strike.\n");
    printf("\n");
	

	
	while(1){
        fgets(command, 20, stdin);
        totalRead = sscanf(command, "%s %c %d", firstCommand, &y, &iToC);
		x = iToC + '0'; // Convert int iToC to char x for the issue: char read only 1 character. e.g. if 12 was given, only 1 will be read.
        shotsCommand=strcmp(firstCommand, "shots");
        fireCommand=strcmp(firstCommand, "fire");
        exitCommand=strcmp(firstCommand, "exit");
        isValidCoordinates = checkFireInputs(y, x);
        
		if(playerNumber==1){
        	if(shotsCommand == 0 && totalRead == 1){
            	printf("\n");
				printBoard(player1ShotBoard);
				printf("\n");
        	}
        
        	if(exitCommand == 0 && totalRead == 1){
            	break;
        	}
        
        	if(fireCommand == 0 && totalRead == 3){
            	if(isValidCoordinates == 1){
					isFired = checkFired(player1ShotBoard, y, x);
					if(isFired == 0){
						playerNumber = 2;
						fire(player2Board, player1ShotBoard, y, x, &p2Carrier, &p2Battleship, &p2Destroyer, &p2Submarine, &p2PatrolBoat, playerNumber);
						isPlayerWin  = checkPlayerWins(&p2Carrier, &p2Battleship, &p2Destroyer, &p2Submarine, &p2PatrolBoat);
						if(isPlayerWin == 1){
							break;
						}
					}else{
    					printf("You have already fired at this location\n");	
					}
            	} else {
                	printf("Invalid coordinates\n");
            	}
        	}
        
        	if(exitCommand != 0 && (shotsCommand !=0 || (shotsCommand == 0 && totalRead > 1)) && (fireCommand !=0 || (fireCommand == 0 && totalRead < 3))){
            	printf("Unrecognised command\n");
        	}
    	}else if(playerNumber == 2){
        	if(shotsCommand == 0 && totalRead == 1){
            printf("\n");
			printBoard(player2ShotBoard);
			printf("\n");
	        }
        
        	if(exitCommand == 0 && totalRead == 1){
            	break;
        	}
        
        	if(fireCommand == 0 && totalRead == 3){
            	if(isValidCoordinates == 1){
					isFired = checkFired(player2ShotBoard, y, x);
					if(isFired == 0){
						playerNumber = 1;
						fire(player1Board, player2ShotBoard, y, x, &p1Carrier, &p1Battleship, &p1Destroyer, &p1Submarine, &p1PatrolBoat, playerNumber);
						isPlayerWin  = checkPlayerWins(&p1Carrier, &p1Battleship, &p1Destroyer, &p1Submarine, &p1PatrolBoat);
						if(isPlayerWin == 1){
							break;
						}
					}else {
						printf("You have already fired at this location\n");
					}
            	} else {
                	printf("Invalid coordinates\n");
            	}
        	}
        
        	if(exitCommand != 0 && (shotsCommand !=0 || (shotsCommand == 0 && totalRead > 1)) && (fireCommand !=0 || (fireCommand == 0 && totalRead < 3))){
            	printf("Unrecognised command\n");
        	}
			
		}
	}	

}

int main(){
    Board player1Board[BOARD_HEIGHT][BOARD_WIDTH];
    Board player2Board[BOARD_HEIGHT][BOARD_WIDTH];
	Board player1ShotBoard[BOARD_HEIGHT][BOARD_WIDTH];
	Board player2ShotBoard[BOARD_HEIGHT][BOARD_WIDTH];
	
	
	playerConfiguration(player1Board, player2Board, player1ShotBoard, player2ShotBoard);
	
}
