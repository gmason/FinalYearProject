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

generatorTemplate::generatorTemplate(string _wIssueSymbol, vector<double> _prices, vector<double> _priceChanges, double _avPriceChange, double _sdPriceChange, \
		double _percentPositive, std::vector<int> _wTradeVolume, int _minVol, int _maxVol, int _avVol, std::vector<double> _wTradeCount,  double _avTrades, \
		double _sdTrades, long double _tradeCountPercent, double _nextPrice, int _nextTrades) {
	wIssueSymbol = _wIssueSymbol;
	prices = _prices;
	priceChanges = _priceChanges;
	avPriceChange = _avPriceChange;
	sdPriceChange = _sdPriceChange;
	percentPositive = _percentPositive;
	wTradeVolume = _wTradeVolume;
	minVol = _minVol;
	maxVol = _maxVol;
	avVol = _avVol;
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
	minVol = 0;
	maxVol = 0;
	avVol = 0;
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

	for (unsigned int i = 0; i < priceChanges.size(); i++)
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

	for (unsigned int i = 0; i < wTradeVolume.size(); i++)
		symbolDetails << this->wTradeVolume[i] << "		";

	symbolDetails << endl << "Minimum Volume:	" << this->minVol;
	symbolDetails << endl << "Maximum Volume:	" << this->maxVol;
	symbolDetails << endl << "Average Volume:	" << this->avVol;

	symbolDetails << setprecision(65);
	symbolDetails << endl << "Trade Count %s:		" << this->tradeCountPercent << endl;

	symbolDetails << endl << endl << endl;

	symbolDetails.close();
}

void generatorTemplate::printVolumes(string filepath)
{
	ofstream volumes;
	volumes.open(filepath.c_str(), ios::out | ios::app);

	volumes << this->wIssueSymbol << "," << prices.size() << ",";
	for (unsigned int i = 0; i < prices.size(); i++)
		volumes << this->wTradeVolume[i] << ",";

	volumes << this->avVol << endl;

	volumes.close();
}

void generatorTemplate::printCsv(string filepath)
{
	ofstream csvOut;
	csvOut.open(filepath.c_str(), ios::out | ios::app);

	csvOut << this->wIssueSymbol << "," << prices.size() << ",";
	for (unsigned int i = 0; i < prices.size(); i++)
		csvOut << this->prices[i] << ",";

	for (unsigned int i = 0; i < priceChanges.size(); i++)
		csvOut << this->priceChanges[i] << ",";

	csvOut << this->avPriceChange << ","  << this->sdPriceChange << ","<< this->percentPositive << ",";

	for (unsigned int i = 0; i < wTradeVolume.size(); i++)
			csvOut << this->wTradeVolume[i] << ",";

	csvOut << this->minVol << "," << this->maxVol << "," << this->avVol << ",";

	for (unsigned int i = 0; i < wTradeCount.size(); i++)
				csvOut << this->wTradeCount[i] << ",";


	csvOut << this->avTrades << "," << this->sdTrades << ",";
	csvOut << setprecision(70);
	csvOut << this->tradeCountPercent;
	csvOut << setprecision(6);
	csvOut << "," << this->nextPrice <<  "," << this->nextTrades << endl;

	csvOut.close();
}
