/*
 * Checker.h
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */

#ifndef CHECKER_H_
#define CHECKER_H_

class Checker {
public:
	Checker();
	virtual ~Checker();
	int getRow();
	int getCol();
	void setRow(int row);
	void setCol(int col);
	void setIsPawn(bool isP);
	void setChar(char letter);
	char getChar();
	bool isRed();
	void setIsRed(bool r);
	void setIsEmpty(bool e);
	bool isEmpty();
	bool isPawn();
	Checker* pawnMoveLeft(Checker** board, Checker* p);
	Checker* pawnMoveRight(Checker** board, Checker* p);
private:
	bool isE;
	bool isP;
	bool isR;
	char c;
	int col;
	int row;
};

#endif /* CHECKER_H_ */
