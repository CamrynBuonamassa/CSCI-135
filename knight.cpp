//Camryn Buonamassa
//Knight's Tour using backtracking 
#include <iostream>
#include <string>

void initializeBoard(int board[][5], int size);
void printBoard(int board[][5], int size);
bool solve(int board[][5], int size, int row, int col);
void loop(int board[][5], int size);

int main() {
	const int size = 5;
	int board[size][size];
	initializeBoard(board, size);
	loop(board, size);
}

void initializeBoard(int board[][5], int size){
	for(int row = 0; row < size; row++){
		for(int col = 0; col < size; col++){
			board[row][col] = 0;
		}
	}
}

void printBoard(int board[][5], int size){
	for(int row = 0; row < size; row++){
		for(int col = 0; col < size; col++){
			std::cout << board[row][col] << " ";
		}
	std::cout << std::endl;
	}
}

bool solve(int board[][5], int size, int row, int col, int count){

	int current = board[row][col];

	if(current != 0 || row < 0 || row >= size || col < 0 || col >= size){
		return false;
	}
	board[row][col]=count;

	if(count == 1){
		return true;
	}

	else{
		if(solve(board, size, row+2, col+1, count-1)){
			return true;
		}
		else if(solve(board, size, row+1, col+2, count-1)){
			return true;
		}
		else if(solve(board, size, row-2, col-1, count-1)){
			return true;
		}
		else if(solve(board, size, row-1, col-2, count-1)){
			return true;
		}
		else if(solve(board, size, row-2, col+1, count-1)){
			return true;
		}
		else if(solve(board, size, row+2, col-1, count-1)){
			return true;
		}
		else if(solve(board, size, row-1, col+2, count-1)){
			return true;
		}
		else if(solve(board, size, row+1, col-2, count-1)){
			return true;
		}
		else{
			board[row][col]=0;
			count++;
			return false;
		}
	}
}

void loop(int board[][5], int size){
	for(int row = 4; row < size; row++){
		for(int col = 3; col < size; col++){
			if(solve(board, size, row, col, 25)){
				std::cout << "Starting position: " << row << ", " << col << " | Solution found:" << std::endl;
				printBoard(board, size);
				return;
			}
			else{
				std::cout << "Starting position: " << row << ", " << col << " | No solution" << std::endl;
			}
		}
	}
}

