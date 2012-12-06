/*
 * symbol.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: gtgmason
 */

#include "symbol.h"
#include "iostream.h"

symbol::symbol(string _wIssueSymbol, double _wTradePrice, int _wTradeVolume, int _wTradeCount) {
	wIssueSymbol = _wIssueSymbol;
	wTradePrice = _wTradePrice;
	wTradeVolume = _wTradeVolume;
	wTradeCount = _wTradeCount;
}

symbol::~symbol() {
	// TODO Auto-generated destructor stub
}

void symbol::print()
{
	  cout << this->wIssueSymbol << "		" << this->wTradePrice << "		" << this->wTradeVolume << "		" << this->wTradeCount << endl;
}
