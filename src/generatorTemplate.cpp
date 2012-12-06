/*
 * generatorTemplate.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#include "generatorTemplate.h"
#include "iostream.h"

generatorTemplate::generatorTemplate(string _wIssueSymbol, double _wBaseTradePrice, double _wTradePriceChange, int _wTradeVolume, int _wBaseTradeCount, int _wTradeCountChange, int _QuotesToProduce) {
	wIssueSymbol = _wIssueSymbol;
	wBaseTradePrice = _wBaseTradePrice;
	wTradePriceChange = _wTradePriceChange;
	wTradeVolume = _wTradeVolume;
	wBaseTradeCount = _wBaseTradeCount;
	wTradeCountChange = _wTradeCountChange;
	quotesToProduce = _QuotesToProduce;
}

generatorTemplate::~generatorTemplate() {
	// TODO Auto-generated destructor stub
}

void generatorTemplate::print()
{
	  cout << this->wIssueSymbol << "		" << this->wBaseTradePrice << "		" << this->wTradePriceChange << "		" << this->wTradeVolume << "		"
			  << this->wBaseTradeCount << "		" << this->wTradeCountChange << "		" << this->quotesToProduce << endl;
}

