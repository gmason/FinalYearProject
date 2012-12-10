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
	public: double avChange;
	public: double sdChange;
	public: int percentPositive;
	public: std::vector<int> wTradeVolume;
	public: std::vector<int> wTradeCount;
	public: void print();
public:
	generatorTemplate(string, std::vector<double>, std::vector<double>, double, double, int, std::vector<int>, std::vector<int>);
	generatorTemplate();
	generatorTemplate(const generatorTemplate&);
	generatorTemplate& operator =(const generatorTemplate& a);
	virtual ~generatorTemplate();
};
#endif
