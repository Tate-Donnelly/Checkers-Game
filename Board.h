/*
 * Board.h
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>//strncpy
#include <stdlib.h>
#include "Checker.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#ifndef BOARD_H_
#define BOARD_H_

class Board {
public:
	Board();
	virtual ~Board();
	void initBoard(Checker** board, char* file);
	void displayBoard(Checker** board);
	bool doesPieceExist(Checker** board, int row, int col, bool isRed);
	Checker* getPiece(Checker** board, int row, int col);
	bool checkMove(Checker** board, Checker* piece, Checker* space);
	bool canMove(Checker** board, Checker* piece);
	bool canJump(Checker** board, Checker* piece);
	Checker* choosePossibleMove(Checker** board, Checker* piece);
	bool moveUpwards(Checker** board, Checker* piece, Checker* space);
	bool moveDownwards(Checker** board, Checker* piece, Checker* space);
	bool jumpUpwardsL(Checker** board, Checker* piece, Checker* space);
	bool jumpUpwardsR(Checker** board, Checker* piece, Checker* space);
	bool jumpDownwardsR(Checker** board, Checker* piece, Checker* space);
	bool jumpDownwardsL(Checker** board, Checker* piece, Checker* space);
	int countPossibleRedMoves(Checker** board);
};

#endif /* BOARD_H_ */
