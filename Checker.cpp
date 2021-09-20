/*
 * Checker.cpp
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */

#include "Checker.h"

Checker::Checker() {
	// TODO Auto-generated constructor stub

}

Checker::~Checker() {
	// TODO Auto-generated destructor stub
}


int Checker::getRow(){
	int answer=row;
	return answer;

}
int Checker::getCol(){
	int answer=col;
	return answer;
}
void Checker::setRow(int row){
	this->row=row;
}
void Checker::setCol(int col){
	this->col=col;
}
void Checker::setChar(char letter){
	this->c=letter;
}
char Checker::getChar(){
	return c;
}
void Checker::setIsPawn(bool isP){
	this->isP=isP;
}
bool Checker::isPawn(){
	return isP;
}
bool Checker::isEmpty(){
	return isE;
}
void Checker::setIsEmpty(bool e){
	isE=e;
}
bool Checker::isRed(){
	return isE;
}
void Checker::setIsRed(bool r){
	isR=r;
}
