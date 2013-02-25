/*
 * generatorTemplate.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#include "generatorTemplate.h"
#include "iostream.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

generatorTemplate::generatorTemplate(string _wIssueSymbol, vector<double> _prices, vector<double> _priceChanges, double _avPriceChange, double _sdPriceChange, double _percentPositive, std::vector<int> _wTradeVolume, int _minVol, int _maxVol, std::vector<double> _wTradeCount,  double _avTrades, double _sdTrades, long double _tradeCountPercent, double _nextPrice, int _nextTrades) {
	wIssueSymbol = _wIssueSymbol;
	prices = _prices;
	priceChanges = _priceChanges;
	avPriceChange = _avPriceChange;
	sdPriceChange = _sdPriceChange;
	percentPositive = _percentPositive;
	wTradeVolume = _wTradeVolume;
	minVol = _minVol;
	maxVol = _maxVol;
	wTradeCount = _wTradeCount;
	avTrades = _avTrades;
	sdTrades = _sdTrades;
	tradeCountPercent = _tradeCountPercent;
	nextPrice = _nextPrice;
	nextTrades = _nextTrades;
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
	avTrades = 0;
	sdTrades = 0;
	tradeCountPercent = 0;
	nextPrice = 0;
	nextTrades = 0;
}

void generatorTemplate::print(string filepath)
{
	ofstream symbolDetails;
   	symbolDetails.open(filepath.c_str(), ios::out | ios::app);

   	symbolDetails << fixed << showpoint;
   	symbolDetails << setprecision(2);
   	symbolDetails << "Symbol: 		" << this->wIssueSymbol << endl;
   	symbolDetails << "Day:			";
	for (unsigned int i = 0; i < prices.size(); i++)
	{
		if (i == prices.size()-1)
			symbolDetails <<  i+1 << "			" << "Predicted";
		else
			symbolDetails << i+1 << "		";
	}

	symbolDetails << endl << "Prices: 		";

	for (unsigned int i = 0; i < prices.size(); i++)
		symbolDetails  << this->prices[i] << "		";

	symbolDetails << "	" << this->nextPrice;

	symbolDetails << endl << "Price Changes:				";

	for (unsigned int i = 0; i < prices.size()-1; i++)
		symbolDetails << this->priceChanges[i] << "		";

	symbolDetails << endl << "Av Price Change:	" << this->avPriceChange << endl;
	symbolDetails << "% positive: 		" << this->percentPositive << endl;
	symbolDetails << "Sd Price Change:	" << this->sdPriceChange << endl;

	symbolDetails << "Trade Counts:		";

	for (unsigned int i = 0; i < wTradeCount.size(); i++)
		symbolDetails << (int) this->wTradeCount[i] << "		";

	symbolDetails << "	" << this->nextTrades;

	symbolDetails << endl << "Av Trades: 		" << this->avTrades << endl;
	symbolDetails << "Sd Trades:		" << this->sdTrades;

	symbolDetails << endl << "Trade Volumes:		";

	for (unsigned int i = 0; i < prices.size(); i++)
		symbolDetails << this->wTradeVolume[i] << "		";

	symbolDetails << endl << "Minimum Volume:	" << this->minVol;
	symbolDetails << endl << "Maximum Volume:	" << this->maxVol;

	symbolDetails << setprecision(65);
	symbolDetails << endl << "Trade Count %s:		" << this->tradeCountPercent << endl;

	symbolDetails << endl << endl << endl;

	symbolDetails.close();
}

