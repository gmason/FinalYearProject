/*
 * symbol.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: gtgmason
 */
// symbol descriptor

#include "symbol.h"
#include "iostream.h"

symbol::symbol(string _wIssueSymbol, double _wTradePrice, int _wTradeVolume, int _wTradeCount) {
	wIssueSymbol = _wIssueSymbol;
	wTradePrice = _wTradePrice;
	wTradeVolume = _wTradeVolume;
	wTradeCount = _wTradeCount;
}

symbol::symbol() {
	wIssueSymbol = "";
	wTradePrice = 0;
	wTradeVolume = 0;
	wTradeCount = 0;
}

symbol::~symbol() {
	// TODO Auto-generated destructor stub
}

void symbol::print()
{
	  cout << this->wIssueSymbol << "		" << this->wTradePrice << "		" << this->wTradeVolume << "		" << this->wTradeCount << endl;
}
