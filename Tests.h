/*
 * Tests.h
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */

#include "Production.h"
#include "Board.h"
#include "Checker.h"
#ifndef TESTS_H_
#define TESTS_H_

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();
	bool testInitBoard();
	bool testDoesPieceExist();
	bool testGetPiece();
	bool testMoveUpwards();
	bool testMoveDownwards();
	bool testJumpUpwards();
	bool testJumpDownwards();
	bool testCheckMove();
	bool testCanMove();
	bool testCanMove2();
	bool testCanMove3();
	bool testCanJump();
	bool testChoosePossibleMoves();
	bool testCheckMove2();
	bool testSetAndGet();
	bool testJumpDownwards2();
	bool testMustJump();
};

#endif /* TESTS_H_ */
