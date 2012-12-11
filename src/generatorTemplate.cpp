/*
 * generatorTemplate.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#include "generatorTemplate.h"
#include "iostream.h"
using namespace std;

generatorTemplate::generatorTemplate(string _wIssueSymbol, vector<double> _prices, vector<double> _priceChanges, double _avChange, double _sdChange, double _percentPositive, std::vector<int> _wTradeVolume, std::vector<int> _wTradeCount) {
	wIssueSymbol = _wIssueSymbol;
	prices = _prices;
	priceChanges = _priceChanges;
	avChange = _avChange;
	sdChange = _sdChange;
	percentPositive = _percentPositive;
	wTradeVolume = _wTradeVolume;
	wTradeCount = _wTradeCount;
}

generatorTemplate::~generatorTemplate() {
	// TODO Auto-generated destructor stub
}

generatorTemplate::generatorTemplate() {
	wIssueSymbol = "";
//	prices - no constructor required for vector.
//	priceChanges - no constructor required for vector.
	avChange = 0;
	sdChange = 0;
	percentPositive = 0;
//	wTradeVolume - no constructor required for vector.
//	wTradeCount - no constructor required for vector.
}



void generatorTemplate::print()
{
	cout << "I have to code the printing..." << endl;

	cout << this->wIssueSymbol << "		" << this->prices[0] << "		" << this->priceChanges[0]
	     << "		" << this->avChange << "	" << this->sdChange << "	" << this->percentPositive
	     << "		" << this->wTradeVolume[0] << "		" << this->wTradeCount[0] << endl;
	for (unsigned int i = 1; i < prices.size(); i++)
	{
		cout << "		" << this->prices[i] << "		" << this->priceChanges[i] << "								"
				<< this->wTradeVolume[i] << "		" << this->wTradeCount[i] << endl;
	}
}

