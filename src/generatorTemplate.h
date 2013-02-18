/*
 * generatorTemplate.h
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#ifndef GENERATORTEMPLATE_H_
#define GENERATORTEMPLATE_H_
#include <string>
#include <vector>
using std::string;
using std::vector;

class generatorTemplate {
	public: string wIssueSymbol;
	public: std::vector<double> prices;
	public: std::vector<double> priceChanges;
	public: double avPriceChange;
	public: double sdPriceChange;
	public: double percentPositive;
	public: std::vector<int> wTradeVolume;
	public: std::vector<double> wTradeCount;
	public: double avTrades;
	public: double sdTrades;
	public: std::vector<long double> tradeCountPercent;
	public: double nextPrice;
	public: int nextTrades;
	public: void print();
public:
	generatorTemplate(string, std::vector<double>, std::vector<double>, double, double, double, std::vector<int>, std::vector<double>, double, double, std::vector<long double>, double, int);
	generatorTemplate();
	generatorTemplate(const generatorTemplate&);
	generatorTemplate& operator =(const generatorTemplate& a);
	virtual ~generatorTemplate();
};
#endif
