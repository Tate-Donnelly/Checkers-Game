/*
 * Tests.cpp
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */

#include "Tests.h"

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests:: tests(){
	bool answer=true;
	bool ok1=testInitBoard();
	bool ok2=testDoesPieceExist();
	bool ok3=testGetPiece();
	bool ok4=testMoveUpwards();
	bool ok5=testMoveDownwards();
	bool ok6=testJumpUpwards();
	bool ok7=testJumpDownwards();
	bool ok8=testCheckMove();
	bool ok9=testCanMove();
	bool ok10=testCanJump();
	bool ok11=testChoosePossibleMoves();
	bool ok12=testCheckMove2();
	bool ok13=testCanMove2();
	bool ok14=testCanMove3();
	bool ok15=testSetAndGet();
	bool ok16=testJumpDownwards2();
	bool ok17=testMustJump();
	answer=ok1&&ok2&&ok3&&ok4&&ok5&&ok6&&ok7&&ok8&&ok9&&ok10&&ok11&&ok12&&ok13&&ok14&&ok15&&ok16&&ok17;
	return answer;
}


bool Tests::testInitBoard(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	int row=3;
	int col=3;
	Checker** thatCellP = board + row*8 + col;
	Checker* x=*thatCellP;
	bool ok=(x->getChar()=='B')&&!(x->isEmpty())&&!(x->isPawn())&&(x->getRow()==row)&&(x->getCol()==col);
	if(ok){
		answer=true;
		printf("testInitBoard passed\n");
	}else{
		printf("testInitBoard failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testDoesPieceExist(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	bool ok=!(game->doesPieceExist(board, 0, 0, true))&&game->doesPieceExist(board, 3, 3, false);
	if(ok){
		answer=true;
		printf("testDoesPieceExist passed\n");
	}else{
		printf("testDoesPieceExist failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testGetPiece(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* x=game->getPiece(board, 3, 3);
	bool ok=ok=(x->getChar()=='B')&&!(x->isEmpty())&&!(x->isPawn())&&(x->getRow()==3)&&(x->getCol()==3);
	if(ok){
		answer=true;
		printf("testGetPiece passed\n");
	}else{
		printf("testGetPiece failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testMoveUpwards(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* b=game->getPiece(board, 2, 2);
	Checker* bTR=game->getPiece(board, 1, 3);
	Checker* bTL=game->getPiece(board, 1, 1);
	bool right=game->moveUpwards(board, b, bTR);
	bool left=game->moveUpwards(board, b, bTL);
	Checker* r=game->getPiece(board, 2, 4);
	Checker* rR=game->getPiece(board, 1, 5);
	bool rUp=game->moveUpwards(board, r, rR);
	Checker* rk=game->getPiece(board, 6, 5);
	Checker* rkR=game->getPiece(board, 5, 6);
	Checker* rkL=game->getPiece(board, 5, 4);
	bool rkUpR=game->moveUpwards(board, rk, rkR);
	bool rkUpL=game->moveUpwards(board, rk, rkL);
	bool ok =right && left && rkUpR && rkUpL &&!(rUp);
	if(ok){
		answer=true;
		printf("testMoveUpwards passed\n");
	}else{
		printf("testMoveUpwards failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testMoveDownwards(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* B=game->getPiece(board, 3, 3);
	Checker* BR=game->getPiece(board, 4, 4);
	Checker* BL=game->getPiece(board, 4, 2);
	bool left=game->moveDownwards(board, B, BL);
	bool right=game->moveDownwards(board, B, BR);
	Checker* b=game->getPiece(board, 2, 2);
	Checker* bl=game->getPiece(board, 3, 1);
	bool bDown=game->moveDownwards(board, b, bl);
	Checker* r=game->getPiece(board, 2, 4);
	Checker* rR=game->getPiece(board, 3, 5);
	bool rDown=game->moveDownwards(board, r, rR);
	Checker* R=game->getPiece(board, 6, 5);
	Checker* RR=game->getPiece(board, 7, 6);
	Checker* RL=game->getPiece(board, 7, 4);
	bool RDR=game->moveDownwards(board, R, RR);
	//printf("RDL:\n");
	bool RDL=game->moveDownwards(board, R, RL);
	/*printf("Left: %d\n", !left);
	printf("Right: %d\n", right);
	printf("Bdown: %d\n", !bDown);
	printf("Rdown: %d\n", rDown);
	printf("RDR: %d\n", RDR);
	printf("RDL: %d\n", RDL);*/
	bool ok= RDL && right && !left && !(bDown) && rDown && RDR;
	if(ok){
		answer=true;
		printf("testMoveDownwards passed\n");
	}else{
		printf("testMoveDownwards failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testJumpUpwards(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* B=game->getPiece(board, 3, 3);
	Checker* Br=game->getPiece(board, 1, 5);
	Checker* Bb=game->getPiece(board, 1, 1);
	bool right=game->jumpUpwardsR(board, B, Br);
	bool left=game->jumpUpwardsL(board, B, Bb);
	bool ok=!(left)&&right;
	if(ok){
		answer=true;
		printf("testJumpUpwards passed\n");
	}else{
		printf("testJumpUpwards failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testJumpDownwards(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* B=game->getPiece(board, 3, 3);
	Checker* Bl=game->getPiece(board, 5, 1);
	Checker* Br=game->getPiece(board, 5, 5);
	//printf("Color: %d:\n", B->isRed());
	//printf("LEFT:\n");
	bool left=game->jumpDownwardsL(board, B, Bl);
	//printf("%d",left);
	//printf("\nRIGHT:\n");
	bool right=game->jumpDownwardsR(board, B, Br);
	//printf("%d\n",right);
	Checker* r=game->getPiece(board, 0, 3);
	Checker* rl=game->getPiece(board, 1, 2);
	Checker* rr=game->getPiece(board, 1, 4);
	bool left2=game->jumpDownwardsL(board, r, rl);
	bool right2=game->jumpDownwardsR(board, r, rr);
	/*printf("Left: %d\n", left);
	printf("Right: %d\n", !right);
	printf("Left2: %d\n", !left2);
	printf("Right2: %d\n", !right2);*/
	bool ok=left && !left2 && !right2 && !right;
	if(ok){
		answer=true;
		printf("testJumpDownwards passed\n");
	}else{
		printf("testJumpDownwards failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCheckMove(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "inputTest.txt");
	Checker* R=game->getPiece(board, 4, 2);
	Checker* r=game->getPiece(board, 2, 4);
	bool Rr=game->checkMove(board, R, r);
	Checker* empty=game->getPiece(board, 6, 0);
	bool Rempty=game->checkMove(board, R, empty);
	Checker* B=game->getPiece(board, 3, 3);
	Checker* Br=game->getPiece(board, 1, 5);
	Checker* Bb=game->getPiece(board, 1, 1);
	Checker* r2=game->getPiece(board, 2, 4);
	Checker* rR=game->getPiece(board, 3, 5);
	bool rDown=game->moveDownwards(board, r2, rR);
	Checker* b=game->getPiece(board, 2, 2);
	Checker* bTR=game->getPiece(board, 1, 3);
	Checker* bTL=game->getPiece(board, 1, 1);
	bool right2=game->moveUpwards(board, b, bTR);
	bool left2=game->moveUpwards(board, b, bTL);
	Checker* r03=game->getPiece(board, 0, 3);
	Checker* r14=game->getPiece(board, 1, 4);
	Checker* r12=game->getPiece(board, 1, 2);
	bool row0=game->checkMove(board, r03, r14) && game->checkMove(board, r03, r12);
	Checker* r20=game->getPiece(board, 2, 0);
	Checker* r31=game->getPiece(board, 3, 1);
	Checker* r11=game->getPiece(board, 1, 1);
	bool col0= game->checkMove(board, r20, r31) && !(game->checkMove(board, r20, r11));
	Checker* r40=game->getPiece(board, 4, 0);
	Checker* r51=game->getPiece(board, 5, 1);
	bool col0R= game->checkMove(board, r40, r31) && (game->checkMove(board, r40, r51));
	Checker* r37=game->getPiece(board, 3, 7);
	Checker* r26=game->getPiece(board, 2, 6);
	Checker* r46=game->getPiece(board, 4, 6);
	bool col7R= game->checkMove(board, r37, r26) && (game->checkMove(board, r37, r46));
	Checker* r57=game->getPiece(board, 5, 7);
	Checker* r66=game->getPiece(board, 6, 6);
	bool col7= game->checkMove(board, r57, r66) && !(game->checkMove(board, r57, r46));
	Checker* r73=game->getPiece(board, 7, 3);
	Checker* r62=game->getPiece(board, 6, 2);
	Checker* r64=game->getPiece(board, 6, 4);
	bool row7= game->checkMove(board, r73, r62) && (game->checkMove(board, r73, r64));

	bool sides=row0 && col0 && col7R&& col0R;
	bool Not=Rr && Rempty && left ;
	bool ok=right && rDown && right2 &&left2 && sides && !Not;
	if(ok){
		answer=true;
		printf("testCheckMove passed\n");
	}else{
		printf("testCheckMove failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCanMove(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "canMove.txt");
	Checker* R=game->getPiece(board, 3, 1);
	bool canRMove=game->canMove(board, R);
	//printf("R: %d\n", canRMove);

	Checker* RowZero=game->getPiece(board, 0, 5);
	Checker* RowSeven=game->getPiece(board, 7, 3);
	Checker* ColZero=game->getPiece(board, 5, 0);
	Checker* ColZeror=game->getPiece(board, 4, 0);
	Checker* ColZeror1=game->getPiece(board, 5, 1);
	//printf("Check Move: %d\n", game->checkMove(board, ColZeror, ColZeror1));
	Checker* cornerB=game->getPiece(board, 0, 0);
	Checker* cornerb=game->getPiece(board, 7, 0);
	Checker* cornerr=game->getPiece(board, 0, 7);
	Checker* cornerR=game->getPiece(board, 7, 7);

	bool row0=game->canMove(board, RowZero);
	//printf("\nRow 0: %d\n", row0);
	bool row7=game->canMove(board, RowSeven);
	//printf("Row 7: %d\n", row7);

	Checker* ColSeven=game->getPiece(board, 3, 7);
	bool col7=game->canMove(board, ColSeven); //ERROR
	//printf("Col 7: %d\n", col7);
	//printf("Char: %c \n", ColSeven->getChar());
	bool col0=game->canMove(board, ColZero);
	Checker* up=game->getPiece(board, 4, 1);
	bool col0Up=game->moveUpwards(board, ColZero, up);
	//printf("Col 0: %d\n", col0);
	//printf("Col 0 Up: %d\n", col0Up);
	bool canCornerBMove=game->canMove(board, cornerB);
	//printf("Corner B: %d\n", canCornerBMove);
	bool canCornerbMove=game->canMove(board, cornerb);
	//printf("Corner b: %d\n", canCornerbMove);
	bool canCornerrMove=game->canMove(board, cornerr);
	//printf("Corner r: %d\n", canCornerrMove);
	bool canCornerRMove=game->canMove(board, cornerR);
	//printf("Corner R: %d\n", canCornerRMove);
	int movablePieces=14;
	bool movable=false;
	int DMP=0;
	Checker* temp =new Checker();
	for(int row=0; row<8; row++){
		for(int col=0; col<8; col++){
			Checker** thatCellP = board + row*8 + col;
			Checker* temp=*thatCellP;
			if(game->doesPieceExist(board, row, col, false)){
				if(game->canMove(board, temp)){
					DMP++;

				}else{
					;
				}
			}
		}
	}
	printf("DMP: %d\n", DMP);
	bool movableBool=DMP==movablePieces;
	bool corners=canCornerBMove && canCornerbMove && canCornerrMove && canCornerRMove;
	printf("\nCorners: %d\n", corners);
	bool sides=row0&&row7 && col0 && col7;
	printf("Sides: %d\n", sides);

	answer = !(canRMove)&& sides && corners && movableBool;
	if(answer){
		printf("testCanMove passed\n");
	}else{
		printf("testCanMove failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCanMove2(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "canMove2.txt");
	Checker* r11=game->getPiece(board, 1, 1);
	Checker* b22=game->getPiece(board, 2, 2);
	Checker* r13=game->getPiece(board, 1, 3);
	bool R11B=game->canMove(board, r11);
	bool R13B=game->canMove(board, r13);
	bool B22=game->canMove(board, b22);
	/*printf("Can Move - R11: %d\n",R11B);
	printf("Can Move - R13: %d\n",R13B);
	printf("Can Move - B22: %d\n",B22);*/
	bool pawnJumps=R11B && R13B;
	answer=pawnJumps;
	if(answer){
		printf("testCanMove2 passed\n");
	}else{
		printf("testCanMove2 failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCanMove3(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "canMove2.txt");
	Checker* B25=game->getPiece(board, 2, 5);
	Checker* B53=game->getPiece(board, 5, 3);
	Checker* b22=game->getPiece(board, 2, 2);
	Checker* e00=game->getPiece(board, 0, 0);
	Checker* e04=game->getPiece(board, 0, 4);
	Checker* e31=game->getPiece(board, 3, 1);
	Checker* e33=game->getPiece(board, 3, 3);
	bool B22=game->canMove(board, b22);
	bool B25B=game->canMove(board, B25);
	bool B53B=game->canMove(board, B53);
	/*printf("B22->E00: %d\n",game->checkMove(board, b22, e00));
	printf("B22->E04: %d\n",game->checkMove(board, b22, e04));
	printf("B22->E31: %d\n",!game->checkMove(board, b22, e31));
	printf("B22->E33: %d\n",!game->checkMove(board, b22, e33));*/
	//printf("Can Move - R13: %d\n",R13B);
	/*printf("Can Move - B22: %d\n",B22);
	printf("Can Move - B25: %d\n",!B25B);
	printf("Can Move - B53: %d\n",B53B);*/
	bool pawnJumps=B22 && B53B && !B25B;
	answer=pawnJumps;
	if(answer){
		printf("testCanMove3 passed\n");
	}else{
		printf("testCanMove3 failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCanJump(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "canJump.txt");
	Checker* B=game->getPiece(board, 4, 1);
	Checker* R=game->getPiece(board, 3, 1);
	Checker* R2=game->getPiece(board, 5, 3);
	Checker* rR7=game->getPiece(board, 7, 1);
	Checker* rR0=game->getPiece(board, 0, 6);
	Checker* bC7=game->getPiece(board, 6, 7);
	Checker* bC0=game->getPiece(board, 6, 0);
	bool canBJump=game->canJump(board, B);
	bool canRJump=game->canJump(board, R);
	bool canR2Jump=game->canJump(board, R2);
	bool row0=game->canJump(board, rR0);
	bool row7=game->canJump(board, rR7);
	bool col0=game->canJump(board, rR7);
	bool col7=game->canJump(board, rR7);


	bool sides= (!row7) && (!row0) && (!col7) && (!col0);
	answer = canR2Jump && !(canBJump) && sides && !(canRJump);
	if(answer){
		printf("testCanJump passed\n");
	}else{
		printf("testCanJump failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testChoosePossibleMoves(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "possibleMoves.txt");
	Checker* r=game->getPiece(board, 2, 3);
	Checker* rul=game->getPiece(board, 0, 1);
	Checker* rur=game->getPiece(board, 0, 5);
	Checker* rl=game->getPiece(board, 4, 1);
	Checker* rr=game->getPiece(board, 4, 5);
	Checker* pr1=game->choosePossibleMove(board, r);
	/*printf("(%d,%d)\n", pr1->getRow(), pr1->getCol());
	printf("RR: %d\n", pr1!=rr);
	printf("RL: %d\n", pr1!=rl);
	printf("RUR: %d\n", pr1!=rur);
	printf("RUL: %d\n", pr1!=rul);*/
	bool headache=pr1!=rr && pr1!=rur && pr1!=rul && pr1!=rl;
	answer=headache;
	if(answer){
		printf("testChoosePossibleMoves passed\n");
	}else{
		printf("testChoosePossibleMoves failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testCheckMove2(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "input.txt");
	Checker* r1=game->getPiece(board, 2, 1);
	bool R1=game->canMove(board, r1);
	Checker* r2=game->getPiece(board, 2, 3);
	bool R2=game->canMove(board, r1);
	Checker* r4=game->getPiece(board, 2, 5);
	bool R3=game->canMove(board, r1);
	Checker* r5=game->getPiece(board, 2, 7);
	bool R4=game->canMove(board, r1);
	bool ok= R1 && R2 && R3 && R4;
	if(ok){
		answer=true;
		printf("testCheckMove2 passed\n");
	}else{
		printf("testCheckMove2 failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testSetAndGet(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	Checker* x=new Checker();
	x->setCol(0);
	x->setRow(0);
	x->setChar('B');
	answer= (x->getCol()==0) && (x->getRow()==0) && (x->getChar()=='B');
	if(answer){
		printf("testSetCol passed\n");
	}else{
		printf("testSetCol failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testJumpDownwards2(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "input.txt");
	Checker* r=game->getPiece(board, 1, 2);
	Checker* space=game->getPiece(board, 3, 0);
	Checker* space2=game->getPiece(board, 3, 4);
	answer=!(game->checkMove(board, r, space) && game->checkMove(board, r, space2) && game->jumpDownwardsL(board, r, space) && game->jumpDownwardsR(board, r, space2));
	if(answer){
		printf("testJumpDownwards2 passed\n");
	}else{
		printf("testJumpDownwards2 failed\n");
	}
	free(game);
	free(board);
	return answer;
}
bool Tests::testMustJump(){
	bool answer=false;
	Checker** board=(Checker**)malloc(8*8*sizeof(Checker*));
	Board* game=new Board();
	game->initBoard(board, "rHasToJump.txt");
	Checker* r00=game->getPiece(board, 0, 0);
	Checker* r07=game->getPiece(board, 0, 7);
	Checker* r70=game->getPiece(board, 7, 0);
	Checker* r77=game->getPiece(board, 7, 7);
	Checker* x=new Checker();
	int counter=0;
	for(int row = 0; row<8; row++)
	{
		for(int col = 0; col<8; col++)
		{
			Checker** thatCellP = board + row*8 + col;
			Checker* x=*thatCellP;
			if((x->getChar()=='R'||x->getChar()=='r') && game->canMove(board, x)){
				counter++;
			}
		}
	}
	Checker* e22=game->getPiece(board, 2, 2);
	bool test=game->jumpDownwardsR(board, r00, e22);
	//printf("Check Move (0,0): %d\n", test);

	//printf("Counter: %d\n", counter);
	bool ok1=game->canMove(board, r00);
	//printf("Can Move (0,0): %d\n", ok1);
	bool ok2=game->canMove(board, r07);
	//printf("Can Move (0,7): %d\n", ok2);
	bool ok3=game->canMove(board, r70);
	//printf("Can Move (7,0): %d\n", ok3);
	bool ok4=game->canMove(board, r77);
	//printf("Can Move (7,7): %d\n", ok4);
	answer=(counter==4) && ok1 && ok2 && ok3 && ok4;

	if(answer){
		printf("testMustJump passed\n");
	}else{
		printf("testMustJump failed\n");
	}
	free(game);
	free(board);
	return answer;
}
