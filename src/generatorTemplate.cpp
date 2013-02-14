/*
 * generatorTemplate.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#include "generatorTemplate.h"
#include "iostream.h"
#include <iomanip>
using namespace std;

generatorTemplate::generatorTemplate(string _wIssueSymbol, vector<double> _prices, vector<double> _priceChanges, double _avPriceChange, double _sdPriceChange, double _percentPositive, std::vector<int> _wTradeVolume, std::vector<double> _wTradeCount, std::vector<long double> _tradeCountPercent, double _nextPrice) {
	wIssueSymbol = _wIssueSymbol;
	prices = _prices;
	priceChanges = _priceChanges;
	avPriceChange = _avPriceChange;
	sdPriceChange = _sdPriceChange;
	percentPositive = _percentPositive;
	wTradeVolume = _wTradeVolume;
	wTradeCount = _wTradeCount;
	tradeCountPercent = _tradeCountPercent;
	nextPrice = _nextPrice;
}

generatorTemplate::~generatorTemplate() {
	// TODO Auto-generated destructor stub
}

generatorTemplate::generatorTemplate() {
	wIssueSymbol = "";
//	prices - no constructor required for vector.
//	priceChanges - no constructor required for vector.
	avPriceChange = 0;
	sdPriceChange = 0;
	percentPositive = 0;
//	wTradeVolume - no constructor required for vector.
//	wTradeCount - no constructor required for vector.
//	tradeCountPercent - no constructor required for vector.
	nextPrice = 0;
}



void generatorTemplate::print()
{
    cout << fixed << showpoint;
	cout << setprecision(2);
	cout << "Symbol: 		" << this->wIssueSymbol << endl;
	cout << "Day:			";
	for (unsigned int i = 0; i < prices.size(); i++)
	{
		if (i == prices.size()-1)
			cout <<  i+1 << "			" << "Predicted";
		else
			cout << i+1 << "		";
	}

	cout << endl << "Prices: 		";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout  << this->prices[i] << "		";

	cout << "	" << this->nextPrice;

    cout << endl << "Price Changes:				";

	for (unsigned int i = 0; i < prices.size()-1; i++)
		cout << this->priceChanges[i] << "		";

    cout << endl << "Av Price Change:	" << this->avPriceChange << endl;
    cout << "% positive: 		" << this->percentPositive << endl;
    cout << "Sd Price Change:	" << this->sdPriceChange << endl;

	cout << "Trade Counts:		";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout << this->wTradeCount[i] << "		";

    cout << endl << "Trade Volumes:		";

	for (unsigned int i = 0; i < prices.size(); i++)
		cout << this->wTradeVolume[i] << "		";

	//cout << setprecision(65);
	//cout << endl << "Trade Count %s:		" << endl;

	//for (unsigned int i = 0; i < prices.size(); i++)
	//	cout << this->tradeCountPercent[i] << "		" << endl;

	cout << endl << endl;
}

