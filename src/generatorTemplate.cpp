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
    cout << endl << "Symbol: 		" << this->wIssueSymbol << "		";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout  << this->prices[i] << "		";

    cout << endl << "Price Changes:						";

	for (unsigned int i = 0; i < prices.size()-1; i++)
		cout << this->priceChanges[i] << "		";

    cout << endl << "Trade Volumes:				";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout << this->wTradeVolume[i] << "		";

	cout << endl << "Trade Counts:				";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout << this->wTradeCount[i] << "		";

    cout << endl << "Average Change:		" << this->avChange << endl;
    cout << "% positive: 		" << this->percentPositive << endl;
    cout << "StandardDeviation:	" << this->sdChange << endl;
}

