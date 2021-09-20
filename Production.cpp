/*
 * Production.cpp
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */

#include "Production.h"
#include <iostream>
#include <fstream>
using namespace std;

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[]){
	bool answer=false;
	bool done=false;
	Checker* movableRed[12];
	char file[100];
	printf("Starting Production\n");

	if(argc <=1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		answer = false;
	}
	else //there is interesting information
	{

		printf("Found %d interesting arguments.\n", argc-1);
		fflush(stdout);
		char* eptr=(char*) malloc(sizeof(char*));
		long aL=-1L;
		int maxTurns;
		for(int i = 1; i<argc; i++) //don't want to read argv[0]
		{//argv[i] is a string
			switch(i){
				case 1:
					printf("The length of the filename is %d.\n",strlen(argv[i]));
					printf("The proposed filename is |%s|.\n", argv[i]);
					if(strlen(argv[i])>=100)
					{
						puts("Filename is too long.");
						fflush(stdout);
						answer = false;
					}
					else
					{
						strcpy(file, argv[i]);
						printf("Filename was |%s|.\n", file);
						fflush(stdout);
					}
					break;
				case 2:
					aL = strtol(argv[i], &eptr, 10);
					maxTurns = (int) aL;
					printf("Number of turns is %d\n",maxTurns);fflush(stdout);
					break;
				default:
					puts("Unexpected argument count."); fflush(stdout);
					answer = false;
					break;
		}
	}
	puts("after reading arguments"); fflush(stdout);
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game= new Board();

	printf("Initializing Board\n");
	game->initBoard(board, file);
	int remainingRed=12;
	int remainingBlue=12;
	int turn=1;
	int movableR=4;
	int movableB=4;
	while(!done ){
		if(remainingRed==0||movableB==0){
			printf("Blue wins\n");
			done=true;
		}else if(remainingBlue==0||movableR==0){
			printf("Red wins\n");
			done=true;
		}else{
			printf("Turn #%d\n", turn);
			bool isRed=true;
			bool pieceExists=false;
			bool canMove=false;
			int pRow=0;
			int pCol=0;
			int row=0;
			int col=0;
			Checker* piece=new Checker();
			Checker* space=new Checker();
			if(turn%2){
				bool blueTurn=true;
				isRed=false;
				printf("Blue's turn\n");
				while(blueTurn){
					//cout <<"Please enter your piece's row and col and the location you would like to move to '(Row,Col) to (Row,Col)': "<< endl;
					printf("Enter your piece's row: ");
					cin>>pRow;
					printf("Enter your piece's col: ");
					cin>>pCol;
					printf("Enter the row you want to move to: ");
					cin>>row;
					printf("Enter the col you want to move to: ");
					cin>>col;
					pieceExists=game->doesPieceExist(board, pRow, pCol, isRed);
					piece=game->getPiece(board, pRow, pCol);
					space=game->getPiece(board, row, col);
					canMove=game->checkMove(board, piece, space);
					bool spaceEmpty=(space->isEmpty());
					if(pieceExists){
						printf("Piece Exists\n");
						if(canMove && spaceEmpty){
							blueTurn=false;
						}else{
							printf("Sorry that move can not be made. Please try again\n");
						}
					}else{
						printf("Sorry that piece does not exist. Please try again\n");
					}
				}
			}else{
				isRed=true;
				printf("Red's turn\n");
				Checker* redPieces[remainingRed];
				int red=0;
				int blue=0;
				movableR=0;
				movableB=0;
				Checker* x=new Checker();
				for(int row = 0; row<8; row++)
				{
					for(int col = 0; col<8; col++)
					{
						//printf("(%d,%d), ", row, col);
						Checker** thatCellP = board + row*8 + col;
						Checker* x=*thatCellP;
						if(x->getChar()=='R'||x->getChar()=='r'){
							redPieces[red]=x;
							if(game->canMove(board, x)){
								movableR++;
								//printf("(%d,%d)\n", x->getRow(), x->getCol());
							}
							red++;
						}else if(x->getChar()=='B'||x->getChar()=='b'){
							if(game->canMove(board, x)){
								movableB++;
								//printf("(%d,%d)\n", x->getRow(), x->getCol());
							}
							blue++;
						}
					}
				}
				remainingRed=red;
				remainingBlue=blue;
				//printf("\nThere are %d remaining red pieces\n", remainingRed);
				printf("There are %d movable red pieces\n", movableR);
				printf("There are %d movable blue pieces\n", movableB);
				if(movableR==0){
					printf("Red cannot move\n");
					printf("Blue wins\n");
					done=true;
				}else if(movableB==0){
					printf("Blue cannot move\n");
					printf("Red wins\n");
					done=true;
				}
				int j=0;
				printf("Finding movable red pieces from among %d remaining red\n", remainingRed);
				for(int i=0; i<remainingRed; i++){
					Checker* x= redPieces[i];
					//printf("Working with %d (%d,%d)\n", i, x->getRow(), x->getCol());
					if(game->canMove(board, x)){
						movableRed[j]=x;
						//printf("(%d,%d)\n", x->getRow(), x->getCol());
						j++;
					}
				}
				printf("Choosing Piece\n");

				int randNum=rand()%movableR;
				piece=movableRed[randNum];
				//printf("Piece Chosen: (%d,%d)\n", piece->getRow(), piece->getCol());
				Checker* t=game->choosePossibleMove(board, piece);
				space=t;
			}
			printf("Moving Piece (%d,%d) to (%d,%d)\n", piece->getRow(), piece->getCol(), space->getRow(), space->getCol());
			if(game->jumpDownwardsR(board, piece, space)){
				Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
				Checker* between=*thatCellP;
				between->setIsEmpty(true);
				between->setIsRed(false);
				between->setChar(' ');
				between->setIsPawn(false);
			}else if(game->jumpDownwardsL(board, piece, space)){
				Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
				Checker* between=*thatCellP;
				between->setIsEmpty(true);
				between->setIsRed(false);
				between->setChar(' ');
				between->setIsPawn(false);
			}else if(game->jumpUpwardsR(board, piece, space)){
				Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
				Checker* between=*thatCellP;
				between->setIsEmpty(true);
				between->setIsRed(false);
				between->setChar(' ');
				between->setIsPawn(false);
			}else if(game->jumpUpwardsL(board, piece, space)){
				Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
				Checker* between=*thatCellP;
				between->setIsEmpty(true);
				between->setIsRed(false);
				between->setChar(' ');
				between->setIsPawn(false);
			}
			char char1=piece->getChar();
			//printf("Piece Char: %c\n", char1);
			//printf("Piece isRed: %d\n", piece->isRed());
			space->setChar(char1);
			//printf("Space Char: %c\n", space->getChar());
			space->setIsRed(piece->isRed());
			//printf("Space isRed: %d\n", space->isRed());
			if(!(piece->isPawn())){
				if((space->getRow()==0&&(piece->getChar()=='b'||piece->getChar()=='B'))||
						(space->getRow()==7&&(piece->getChar()=='r'||piece->getChar()=='R'))){
					//King
					space->setIsPawn(false);
					space->setChar(piece->getChar()-32);
				}else{
					space->setIsPawn(piece->isPawn());
				}
			}
			space->setIsEmpty(false);
			piece->setChar(' ');
			piece->setIsEmpty(true);
			game->displayBoard(board);
			if(turn == maxTurns-1){
				printf("No more turns\n");
				done=true;
			}
			turn++;

		}
	}

	free(board);
	}
	return done;
}
