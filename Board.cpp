/*
 * Board.cpp
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */
#include <stdio.h>
#include <stdbool.h>
#include "Board.h"
#include <iostream>
#include <fstream>
using namespace std;

Board::Board() {
	// TODO Auto-generated constructor stub

}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

void Board::initBoard(Checker** board, char* file){
	FILE* fp = fopen(file, "r"); //read the file
	if (fp == NULL)
	{
		puts("Error! opening file");
	}
	else
	{
		printf("\t");
		for(int i = 0; i <8; i++){
			printf("   %d    ", i);
		}
		printf("\n 	_______________________________________________________________\n");
		char temp='w';
		for(int row = 0; row<8; row++)
		{
			printf("   %d   ", row);
			for(int col = 0; col<8; col++)
			{
				Checker* x=new Checker();
				fscanf(fp,"%s", &temp);
				if(temp=='0'){
					x->setIsEmpty(true);
					x->setIsRed(false);
					x->setChar(' ');
					printf("|   %c   ",x->getChar());
				}else if(temp=='r'){
					x->setIsEmpty(false);
					x->setIsRed(true);
					x->setIsPawn(true);
					x->setChar('r');
					printf("|   %c   ",x->getChar());
				}else if(temp=='R'){
					x->setIsEmpty(false);
					x->setIsRed(true);
					x->setIsPawn(false);
					x->setChar('R');
					printf("|   %c   ",x->getChar());
				}else if(temp=='b'){
					x->setIsEmpty(false);
					x->setIsRed(false);
					x->setIsPawn(true);
					x->setChar('b');
					printf("|   %c   ",x->getChar());
				}else if(temp=='B'){
					x->setIsEmpty(false);
					x->setIsRed(false);
					x->setIsPawn(false);
					x->setChar('B');
					printf("|   %c   ",x->getChar());
				}else{
					printf("The Character I found was: |%c|",temp);
				}
				x->setCol(col);
				x->setRow(row);
				Checker** thatCellP = board + row*8 + col ;
				*thatCellP = x;
			}
			printf("|");
			printf("\n 	_______________________________________________________________\n");
		}

	}
	fclose(fp);

}
void Board::displayBoard(Checker** board){
	printf("\t");
	int howManyCols=8;
	int blue=0;
	int red=0;
	for(int i = 0; i <howManyCols; i++){
		printf("   %d    ", i);
	}
	printf("\n 	_______________________________________________________________\n");
	for(int row = 0; row<howManyCols; row++)
	{
		printf("   %d   ", row);
		for(int col = 0; col <howManyCols; col++)
		{
			Checker** thatCellP = board + row*howManyCols + col;
			Checker* x=*thatCellP;
			printf("|   %c   ", x->getChar());
			if(x->getChar()=='b'||x->getChar()=='B'){
				blue++;
			}else if(x->getChar()=='r'||x->getChar()=='R'){
				red++;
			}

		}
		printf("|");
		printf("\n 	______________________________________________________________\n");
	}
	printf("%d Blue pieces remaining\n",blue);
	printf("%d Red pieces remaining\n",red);
}
bool Board::doesPieceExist(Checker** board, int row, int col, bool isRed){
	bool answer;
	Checker** thatCellP = board + row*8 + col;
	Checker* x=*thatCellP;
	if(x->getChar()!=' '&&!(x->isEmpty())&&(isRed==x->isRed())){
		answer=true;
	}
	return answer;
}
Checker* Board::getPiece(Checker** board, int row, int col){
	Checker** thatCellP = board + row*8 + col;
	Checker* x=*thatCellP;
	return x;
}
bool Board::checkMove(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	if(space->isEmpty()&&space->getChar()==' '){
		if((piece->getCol()!=space->getCol())){
			if((space->getCol()<=7 && space->getCol()>=0)&&(space->getRow()<=7 && space->getRow()>=0)){
				if(jumpDownwardsL(board, piece, space)||
						jumpDownwardsR(board, piece, space)||
							jumpUpwardsL(board, piece, space)||
							jumpUpwardsR(board, piece, space)||
					moveUpwards(board, piece, space)||
					moveDownwards(board, piece, space)){
					//printf("(%d,%d)\n", piece->getRow(), piece->getCol());
					answer=true;
				}
			}
		}
	}
	return answer;
}

bool Board::canMove(Checker** board, Checker* piece){

	bool answer=false;
	//printf("Can Move\n");
	if((piece->getRow()==0) && (piece->getCol()==0)){//(0,0)->bottom right +Row +Col
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, bottomRight);
	}else if(piece->getRow()==7 && piece->getCol()==0){//(7,0)->top right -Row +Col
		Checker** thatCellP= board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		//printf("CM (7,0)\n");
		answer=canJump(board, piece)||checkMove(board, piece, topRight)||checkMove(board, piece, topRight);
	}else if(piece->getRow()==0 && piece->getCol()==7){//(0,7)->bottom left +Row -Col
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, bottomLeft)||checkMove(board, piece, bottomLeft);
	}else if(piece->getRow()==7 && piece->getCol()==7){//(7,7)->top left -Row -Col
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, topLeft);
	}else if(piece->getRow()==0){//down right and left
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		answer= canJump(board, piece)||checkMove(board, piece, bottomLeft)||checkMove(board, piece, bottomRight);
	}else if(piece->getRow()==7){//Up left and right
		//printf("Row 7");
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, topLeft)||checkMove(board, piece, topRight);
	}else if(piece->getCol()==0){//Right up and down
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, topRight) || checkMove(board, piece, bottomRight);
	}else if(piece->getCol()==7){//Left up and down
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		answer= canJump(board, piece)||checkMove(board, piece, topLeft)|| checkMove(board, piece, bottomLeft);
		//printf("Up: %d\n", checkMove(board, piece, topLeft));
		//printf("Down: %d\n", checkMove(board, piece, bottomLeft));
	}else{//Middle: All else
		//printf("Else\n");
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		answer=canJump(board, piece)||checkMove(board, piece, topLeft)||checkMove(board, piece, topRight)||checkMove(board, piece, bottomLeft)||checkMove(board, piece, bottomRight);
	}
	return answer;
}
bool Board::canJump(Checker** board, Checker* piece){
	bool answer=false;
	//printf("Can Jump\n");
	if(piece->getRow()==0 && piece->getCol()==0){//(0,0)->bottom right
		Checker** thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
		Checker* bottomRight=*thatCellP;
		answer=jumpDownwardsR(board, piece, bottomRight);
	}else if(piece->getRow()==7 && piece->getCol()==0){//(7,0)->top right
		//printf("CJ (7,0)\n");
		Checker** thatCellP= board + (piece->getRow()-2)*8 + (piece->getCol()+2);
		Checker* topRight=*thatCellP;
		answer=jumpUpwardsR(board, piece, topRight);
	}else if(piece->getRow()==0 && piece->getCol()==7){//(0,7)->bottom left
		//printf("CJ (0,7)\n");
		Checker** thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
		Checker* bottomLeft=*thatCellP;
		answer=jumpDownwardsL(board, piece, bottomLeft);
	}else if(piece->getRow()==7 && piece->getCol()==7){//(7,7)->top left
		Checker** thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
		Checker* topLeft=*thatCellP;
		answer=jumpUpwardsL(board, piece, topLeft);
	}else if(piece->getRow()==0 && piece->getCol()>1 && piece->getCol()<6){//down right and left
		Checker** thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		answer= jumpDownwardsL(board, piece, bottomLeft)||jumpDownwardsR(board, piece, bottomRight);
	}else if(piece->getRow()==7 && piece->getCol()>1 && piece->getCol()<6){//Up left and right
		Checker** thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
		Checker* topRight=*thatCellP;
		answer=jumpUpwardsL(board, piece, topLeft)||jumpUpwardsR(board, piece, topRight);
	}else if(piece->getCol()==0 && piece->getRow()>1 && piece->getRow()<6){//Right up and down
		Checker** thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
		Checker* bottomRight=*thatCellP;
		answer=jumpUpwardsR(board, piece, topRight)||jumpDownwardsR(board, piece, bottomRight);
	}else if(piece->getCol()==7 && piece->getRow()>1 && piece->getRow()<6){//Left up and down
		Checker** thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
		Checker* bottomLeft=*thatCellP;
		answer=jumpUpwardsL(board, piece, topLeft)||jumpDownwardsL(board, piece, bottomLeft);
	}else if(piece->getRow()<6 && piece->getRow()>1 && piece->getCol()>1 && piece->getCol()<6){//Middle: All else
		//printf("Else\n");
		Checker** thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
		Checker* bottomRight=*thatCellP;
		answer=jumpUpwardsL(board, piece, topLeft)||jumpUpwardsR(board, piece, topRight)||jumpDownwardsL(board, piece, bottomLeft)||jumpDownwardsR(board, piece, bottomRight);
	}
	return answer;
}

Checker* Board::choosePossibleMove(Checker** board, Checker* piece){
	Checker* space=new Checker();
	//printf("Here\n");
	if(piece->getRow()==0 && piece->getCol()==0){//(0,0)->bottom right
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		if(canJump(board, piece)){
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
			Checker* bottomRightJ=*thatCellP;
			space=bottomRightJ;
		}else{
		space=bottomRight;
		}
	}else if(piece->getRow()==7 && piece->getCol()==0){//(7,0)->top right
		Checker** thatCellP= board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		if( canJump(board, piece)){
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
			Checker* topRightJ=*thatCellP;
			space=topRightJ;
		}else{
		space=topRight;
		}
	}else if(piece->getRow()==0 && piece->getCol()==7){//(0,7)->bottom left
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		if( canJump(board, piece)){
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
			Checker* bottomLeftJ=*thatCellP;
			space=bottomLeftJ;
		}else{
		space=bottomLeft;
		}
	}else if(piece->getRow()==7 && piece->getCol()==7){//(7,7)->top left
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		if(canJump(board, piece)){
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
			Checker* topLeftJ=*thatCellP;
			space=topLeftJ;
		}else{
			space=topLeft;
		}
	}else if(piece->getRow()==0){//down right and left
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		if(canJump(board, piece)){
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
			Checker* bottomLeftJ=*thatCellP;
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
			Checker* bottomRightJ=*thatCellP;
			if(jumpDownwardsL(board, piece, bottomLeftJ)){
				space=bottomLeftJ;
			}else{
				space=bottomRightJ;
			}
		}else{
			if( moveDownwards(board, piece, bottomLeft)){
				space=bottomLeft;
			}else{
				space=bottomRight;
			}
		}
	}else if(piece->getRow()==7){//Up left and right
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		if( canJump(board, piece)){
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
			Checker* topLeftJ=*thatCellP;
			thatCellP  = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
			Checker* topRightJ=*thatCellP;
			if( jumpUpwardsL(board, piece, topLeftJ)){
				space=topLeftJ;
			}else{
				space=topRightJ;
			}
		}else{
			if( moveUpwards(board, piece, topLeft)){
				space=topLeft;
			}else{
				space=topRight;
			}
		}
	}else if(piece->getCol()==0){//Right up and down
		Checker** thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		if( canJump(board, piece)){
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
			Checker* topRightJ=*thatCellP;
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
			Checker* bottomRightJ=*thatCellP;
			if( jumpUpwardsR(board, piece, topRightJ)){
				space=topRightJ;
			}else{
				space=bottomRightJ;
			}
		}else{
			if( moveDownwards(board, piece, bottomRight)){
				space=bottomRight;
			}else{
				space=topRight;
			}
		}
	}else if(piece->getCol()==7){//Left up and down
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		if( canJump(board, piece)){
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
			Checker* topLeftJ=*thatCellP;
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
			Checker* bottomLeftJ=*thatCellP;
			if(jumpUpwardsL(board, piece, topLeftJ)){
				space=topLeftJ;
			}else{
				space=bottomLeftJ;
			}
		}else{
			if(moveDownwards(board, piece, bottomLeft)){

				space=bottomLeft;
			}else{
				space=topLeft;
			}
		}
	}else{//Middle: All else
		//printf("Big Else\n");
		Checker** thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()-1);
		Checker* topLeft=*thatCellP;
		thatCellP = board + (piece->getRow()-1)*8 + (piece->getCol()+1);
		Checker* topRight=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()-1);
		Checker* bottomLeft=*thatCellP;
		thatCellP = board + (piece->getRow()+1)*8 + (piece->getCol()+1);
		Checker* bottomRight=*thatCellP;
		if(canJump(board, piece)){
			//printf("Big Else Jump\n");
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()-2);
			Checker* topLeftJ=*thatCellP;
			thatCellP = board + (piece->getRow()-2)*8 + (piece->getCol()+2);
			Checker* topRightJ=*thatCellP;
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()-2);
			Checker* bottomLeftJ=*thatCellP;
			thatCellP = board + (piece->getRow()+2)*8 + (piece->getCol()+2);
			Checker* bottomRightJ=*thatCellP;

			if(checkMove(board, piece, topLeftJ)){
				space=topLeftJ;
				//printf("TL\n");
			}else if(checkMove(board, piece, topRightJ)){
				space=topRightJ;
				//printf("TR\n");
			}else if(checkMove(board, piece, bottomLeftJ)){
				space=bottomLeftJ;
				//printf("BL\n");
			}else if(checkMove(board, piece, bottomRightJ)){
				space=bottomRightJ;
				//printf("TL\n");
			}
		}else{
			if( checkMove(board, piece, topLeft)){
				space=topLeft;
			}else if( checkMove(board, piece, topRight)){
				space=topRight;
			}else if( checkMove(board, piece, bottomLeft)){
				space=bottomLeft;
			}else if( checkMove(board, piece, bottomRight)){
				space=bottomRight;
			}
		}
	}
	return space;

}

bool Board::moveUpwards(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	if(space->isEmpty()||space->getChar()==' '){
		if(piece->getChar()=='B'||piece->getChar()=='b'||piece->getChar()=='R'){
			int pR=piece->getRow();
			int pC=piece->getCol();
			int sR=space->getRow();
			int sC=space->getCol();
			if((pR-1)==sR){
				if(((pC+1)==sC)){
					answer=true;
				}else if(((pC-1)==sC)){
					answer=true;
				}
			}
		}
	}
	return answer;
}
bool Board::moveDownwards(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	if(space->isEmpty()){
		//printf("Color: %c\n", piece->getChar());
		if((piece->getChar()=='R'||piece->getChar()=='r')||piece->getChar()=='B'){
			int pR=piece->getRow();
			int pC=piece->getCol();
			int sR=space->getRow();
			int sC=space->getCol();
			if(pR+1==sR){
				if((pC+1)==sC){
					answer=true;
					if(piece->getRow()==3 && piece->getCol()==1){
							//printf("Move Downwards->(%d,%d)\n", space->getRow(), space->getCol());
						}
				}else if((pC-1)==sC){
					answer=true;
					if(piece->getRow()==3 && piece->getCol()==1){
							//printf("Move Downwards->(%d,%d)\n", space->getRow(), space->getCol());
						}
				}
			}
		}
	}
	return answer;
}
bool Board::jumpUpwardsL(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	if(space->isEmpty()){
		if(piece->getRow()>=2 && piece->getCol()>=2){
			//printf("(%d,%d)->(%d,%d)\n", piece->getRow(), piece->getCol(), space->getRow(), space->getCol());
			if((!(piece->isPawn())||!(piece->isRed()))){
				int pR=piece->getRow();
				int pC=piece->getCol();
				int sR=space->getRow();
				int sC=space->getCol();
				Checker* topLeft=getPiece(board, pR-1, pC-1);
				Checker* topRight=getPiece(board, pR-1, pC+1);
				//printf("Top Left - (%d,%d): \n", topLeft->getRow(), topLeft->getCol());
				//printf("Top Right - (%d,%d): \n", topRight->getRow(), topRight->getCol());
				//printf("SC: %d\tPC:%d\n", sC, pC);
				if((pC-2)==sC){
					//printf("Left - Columns\n");
					if((!(topLeft->getChar()==' '))||(!(topLeft->isEmpty()))){
						//printf("Left Empty\n");
						if(((topLeft->getChar()=='R'||topLeft->getChar()=='r') && (piece->getChar()=='B'||
								piece->getChar()=='b')) ||
								(((piece->getChar()=='R') && (topLeft->getChar()=='B'||topLeft->getChar()=='b')))){
							//printf("Jump upwards Left\n");
							//printf("Left Success\n");
							answer=true;
						}
					}
				}
			}
		}
	}
	return answer;
}
bool Board::jumpUpwardsR(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	if(space->isEmpty()){
		if(piece->getRow()>=2 && piece->getCol()<=5){
		//printf("(%d,%d)->(%d,%d): |%c|\n", piece->getRow(), piece->getCol(), space->getRow(), space->getCol(), piece->getChar());
		if((!(piece->isPawn())||!(piece->isRed()))){
			int pR=piece->getRow();
			int pC=piece->getCol();
			int sR=space->getRow();
			int sC=space->getCol();
			Checker* topRight=getPiece(board, pR-1, pC+1);
			//printf("Top Right - (%d,%d): |%c| \n", topRight->getRow(), topRight->getCol(), topRight->getChar());
			//printf("SC: %d\tPC:%d\n", sC, pC);
				if((pC+2)==sC){
					//printf("Right - Columns\n");
					if(!(topRight->getChar()==' ' || (topRight->isEmpty()))){
						//printf("Right Empty\n");
						if(((topRight->getChar()=='R'||topRight->getChar()=='r') &&
								(piece->getChar()=='B'||piece->getChar()=='b'))
							||((piece->getChar()=='R') && (topRight->getChar()=='B'||topRight->getChar()=='b') )){
							//printf("Right Success\n");
							answer=true;
						}
					}
				}
			}
		}
	}
	return answer;
}
bool Board::jumpDownwardsL(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	//printf("(%d,%d) %c ->(%d,%d) %c\n", piece->getRow(), piece->getCol(),piece->getChar(), space->getRow(), space->getCol(), space->getChar());
	if(space->isEmpty()){
		if(!(piece->isPawn())|| (piece->getChar()=='R'||piece->getChar()=='r')){
			if(piece->getRow()<=5 && piece->getCol()>=1){
				if((piece->getRow()+2)==space->getRow()&& (piece->getRow()!=6)&& (piece->getRow()!=7)){
					int pR=piece->getRow();
					int pC=piece->getCol();
					int sR=space->getRow();
					int sC=space->getCol();
					Checker* bottomLeft=getPiece(board, sR-1,sC+1);
					//printf("Is Piece Red: %d:\n", piece->isRed());
					//printf("Is Bottom Left Red: %d:\n", bottomLeft->isRed());
					//printf("Bottom Left: (%d,%d), |%c|, isEmpty: %d\n", bottomLeft->getRow(), bottomLeft->getCol(), bottomLeft->getChar(), bottomLeft->isEmpty());
					if(((pC-2)==sC)){
						//printf("Jump downwards Left\n");
						if((!(bottomLeft->getChar()==' '))||(!(bottomLeft->isEmpty()))){
							//printf("Empty\n");
							if((((bottomLeft->getChar()=='B')||(bottomLeft->getChar()=='b')) && ((piece->getChar()=='R')||(piece->getChar()=='r'))) ||
									((bottomLeft->getChar()=='R'||bottomLeft->getChar()=='r') && (piece->getChar()=='B'))){
								//printf("Left Success\n");
								answer=true;
							}
						}
					}
				}
			}
		}
	}
	return answer;
}
bool Board::jumpDownwardsR(Checker** board, Checker* piece, Checker* space){
	bool answer=false;
	//printf("(%d,%d) %c ->(%d,%d) %c\n", piece->getRow(), piece->getCol(),piece->getChar(), space->getRow(), space->getCol(), space->getChar());
	if(space->isEmpty()){
		if(!(piece->isPawn())|| (piece->getChar()=='R'||piece->getChar()=='r')){
			if(piece->getRow()<=5 && piece->getCol()<=5){
				if((piece->getRow()+2)==space->getRow()&& (piece->getRow()!=6)&& (piece->getRow()!=7)){
					int pR=piece->getRow();
					int pC=piece->getCol();
					int sR=space->getRow();
					int sC=space->getCol();Checker* bottomRight=getPiece(board, pR+1,pR+1);
					//printf("Bottom Right: (%d,%d), |%c|, isEmpty: %d\n", bottomRight->getRow(), bottomRight->getCol(), bottomRight->getChar(), bottomRight->isEmpty());
					if((pC+2==sC)){
						//printf("Jump downwards right\n");
						 if(!(bottomRight->getChar()==' ' || (bottomRight->isEmpty()))){
							 //printf("Empty\n");
							if(((bottomRight->getChar()=='B'||bottomRight->getChar()=='b') && (piece->getChar()=='R'||piece->getChar()=='r')) ||
									((bottomRight->getChar()=='R'||bottomRight->getChar()=='r') && (piece->getChar()=='B'))){
								//printf("Success\n");
								answer=true;

							}
						}
					}
				}
			}
		}
	}
	return answer;
}
