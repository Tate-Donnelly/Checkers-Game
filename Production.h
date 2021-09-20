/*
 * Production.h
 *
 *  Created on: Mar 7, 2021
 *      Author: tedon
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>//strncpy
#include <stdlib.h>
#include "Board.h"
#include "Checker.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;
#ifndef PRODUCTION_H_
#define PRODUCTION_H_

class Production {
public:
	Production();
	virtual ~Production();
	bool prod(int argc, char* argv[]);
};

#endif /* PRODUCTION_H_ */
