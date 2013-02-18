//============================================================================
// Name        : MarketDataGenerator.cpp
// Author      : Gareth Mason
// Version     :
// Copyright   : 
// Description : Base class of marketDataGenerator project, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <list>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <cmath>
#include "symbol.h"
#include "generatorTemplate.h"
#include <ctime>
using namespace std;


static vector<string> symbols;
static vector<string> symbolsToCompare;

string subStringConverter (string startField, string line)
{
	int start, end;
	start = line.find(startField, 0);
	end = line.find(' ', start);
    string returnString = line.substr(start+startField.length(), end);

	return returnString;
}

int LengthOfFile (string filename)
{
	string line;
    int numLines = 0;

    ifstream symFile (filename.c_str());
    ofstream processedFile;

    char buf[256];
    snprintf(buf, sizeof buf, "%s%s", filename.c_str(), "_processed");
    processedFile.open(buf);

    while ( getline (symFile, line) )
    {
  	  if (string::npos != line.find("wTradePrice"))
  	  {
  	   ++numLines;
  	  }
    }
    symFile.clear();
    symFile.seekg(0);
	symFile.close();

	return numLines;
}

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

bool positiveOrNegative(double positive)
{
	double val = (double)rand() / RAND_MAX;
	bool posOrNeg;
	if (val > positive)       //  %neg
		posOrNeg = false;
	else if (val < positive)  //  %pos
		posOrNeg = true;

	return posOrNeg;
}

void FileParser (string filename, int arrLength, symbol *arr[ ]) {
  string line;
  int numLines = arrLength;

  ifstream symFile (filename.c_str());
  ofstream processedFile;

  char buf[256];
  snprintf(buf, sizeof buf, "%s%s", filename.c_str(), "_processed");
  processedFile.open(buf);

  string symFileLine [numLines];
  symbol *symbolsInFile [numLines];

  int n = 0;

  while ( getline (symFile, line) )
  {
	  if (string::npos != line.find("wTradePrice"))
	  {
		  double symPrice;
		  int symVolume, tradeCount;
		  symFileLine[n] = line;

		  // set the symbol
		  int i = line.find(".NSDQ", 0);
		  string symName = line.substr(0, i);

		  // set the trade price
		  stringstream convertPrice (subStringConverter("wTradePrice F64=", line));
		  if ( !(convertPrice >> symPrice) )
		      symPrice = 0;

		  // set the trade volume
		  stringstream convertVolume(subStringConverter("wTradeVolume U32=", line));
		  if ( !(convertVolume >> symVolume) )
			  symVolume = 0;

		  // set the trade count
		  stringstream convertCount(subStringConverter("wTradeCount U32=", line));
		  if ( !(convertCount >> tradeCount) )
			  tradeCount = 0;

		  symbolsInFile[n] = new symbol(symName, symPrice, symVolume, tradeCount);
		  processedFile << symFileLine[n] << endl;
		  n++;

	  }
  }

  for (int i = 0; i < numLines; i++)
	  arr[i] = symbolsInFile[i];

  symFile.close();
  processedFile.close();
}

// input files are standard wombat symbol files (with all fields)
// Before inputting please run the following in vi
// :%s/_^...._^/ /g
// :%s/_^...._^/ /g
// :%s/<tab>/ /g

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

double valueGenerator(vector<double> &values, int size, double sd, double av, double high, double low, double percentPos)
{
	double r = randfrom(low, high);
    double s = randfrom(0, sd);
    double generated = 0;

    if (positiveOrNegative(percentPos))
    	generated = ((r + av) / 2) + s;
    else
    	if ((((r + av) / 2) - s) < 0)
    		generated = ((r + av) / 2) + s;
    	else
    		generated = ((r + av) / 2) - s;

    return generated;
}

double valueGenerator(vector<double> &values, int size, double sd, double av, double high, double low)
{
	double r = randfrom(low, high);
    double s = randfrom(0, sd);
    double generated = 0;

    if ((((r + av) / 2) - s) < 0)
   		generated = ((r + av) / 2) + s;
   	else
    	generated = ((r + av) / 2) - s;

    return generated;
}

double lowValue(vector<double> &values, int size)
{
	double lowest;
	for(int i = 0; i < size; i++)
	{
	    if(values[i] < lowest)
	    	lowest = values[i];
	}
	return lowest;
}

double highValue(vector<double> &values, int size)
{
	double highest;
	for(int i = 0; i < size; i++)
	{
	    if(values[i] > highest)
	    	highest = values[i];
	}
	return highest;
}

double avCalculator(vector<double> &values, int size)
{
	double runningTotal = 0;
	for (int x = 0; x < size; x++)
		runningTotal += values[x];

	double average = runningTotal / (double) size;
	return average;
}

double sdCalculator(vector<double> &values, double average, int size)
{
	double sdVar;

	for (int x = 0; x < size; x++)
	{
		if (values[x] < 0)
			values[x] = values[x] * -1;
		double tempSdVar = values[x]-average;
		if (tempSdVar < 0)
			tempSdVar = tempSdVar *-1;
	    tempSdVar = (tempSdVar*tempSdVar);
	    sdVar += tempSdVar;
	}

	double standardDevation = sqrt(sdVar / (size));

	return standardDevation;
}

int main()
{
	srand ( time(NULL) );

    string dir = string("/Users/gtgmason/Documents/workspace/symfiles/sorted/puresym/");
    vector<string> files = vector<string>();
    getdir(dir,files);
    int fileLengths[files.size()];
    int fileLengthsNormalised[files.size()];
    int usableFiles = 0;
    int longestFile = 0;
    string fileNames[files.size()];

    for (unsigned int i = 0;i < files.size();i++) {
    	if (i >= 2 && files[i].find("_processed") == string::npos){
    		usableFiles++;

    		stringstream ss;
			ss << dir << files[i];
			fileNames[i] = ss.str();

			fileLengths[i] = LengthOfFile(fileNames[i].c_str());
			if (fileLengths[i] > longestFile){
				longestFile = fileLengths[i];
			}
    	}
    }

    symbol **snapShots = new symbol*[usableFiles];
    for(int i = 0; i < usableFiles; ++i) {
    	snapShots[i] = new symbol[longestFile];
    }

    int usedFiles = 0;

    for (unsigned int i = 0;i < files.size();i++) {
    	if (i >= 2 && files[i].find("_processed") == string::npos)
    	{
			symbol* temporaryFileHold[fileLengths[i]];

			FileParser(fileNames[i], fileLengths[i], temporaryFileHold);

	    	for (int j = 0; j < fileLengths[i]; j++)
	    	{
	    		snapShots[usedFiles][j].wIssueSymbol = temporaryFileHold[j]->wIssueSymbol;
	    		snapShots[usedFiles][j].wTradeCount = temporaryFileHold[j]->wTradeCount;
	    		snapShots[usedFiles][j].wTradePrice = temporaryFileHold[j]->wTradePrice;
	    		snapShots[usedFiles][j].wTradeVolume = temporaryFileHold[j]->wTradeVolume;
	    	}
	    	fileLengthsNormalised[usedFiles] = fileLengths[i];
    		usedFiles++;
    	}
    }

    int totalSyms = 0;
    for (int i = 0; i < usableFiles; i++){
    	totalSyms += fileLengthsNormalised[i];
    }

    long counter = 0;
    for (long i = 0; i < usableFiles; i++){
		for (long j = 0; j < fileLengthsNormalised[i]; j++)
		{
			counter ++;
			symbols.push_back(snapShots[i][j].wIssueSymbol);
		}
    }

    sort(symbols.begin(),symbols.end());
    for (int i = 0; i < totalSyms-(usableFiles-1); i++)
    {
		if (symbols[i] == symbols[i+(usableFiles-1)])
		{
			symbolsToCompare.push_back(symbols[i]);
		}
    }

    generatorTemplate* generatedSnapShot;
    vector<generatorTemplate*> snapSym;
    int totalTrades;

    for (unsigned int i = 0; i < symbolsToCompare.size(); i++)
    {
    	string wIssueSymbol = symbolsToCompare[i];
    	vector<double> prices;
    	vector<double> priceChanges;
    	double avPriceChange;
    	double sdPriceChange;
    	double avTradeCount;
    	double sdTradeCount;
    	double percentPositive;
    	vector<int> tradeVolumes;
    	vector<double> tradeCounts;
    	long double tradeCountPercent;
    	double nextPriceChange;
    	double nextPrice;
    	bool upOrDown;

        for (int j = 0; j < usableFiles; j++){
    		for (int k = 0; k < fileLengthsNormalised[j]; k++)
    		{
    			if (snapShots[j][k].wIssueSymbol == wIssueSymbol)
    			{
    				prices.push_back(snapShots[j][k].wTradePrice);
    				tradeVolumes.push_back(snapShots[j][k].wTradeVolume);
    				tradeCounts.push_back(snapShots[j][k].wTradeCount);
    				//tradeCountPercent.push_back(0);

    				double priceChangesTotal = 0;
    				double positive = 0;
    				if (j == usableFiles-1)
    				{
    					for (int l = 0; l < usableFiles; l++)
    					{
    						if (l < usableFiles-1)
    						{
    							double tempPriceChange = prices[l+1]-prices[l];
    							priceChanges.push_back(tempPriceChange);
    							// following if statements check whether the change is +ive or -ive, and adjusts
    							// so they're all positive (for calculating the av change).
    							if (tempPriceChange < 0)
        							priceChangesTotal += (tempPriceChange * -1);
    							else
    							{
    								positive++;
    								priceChangesTotal += tempPriceChange;
    							}
    						}
    						else
    						{
    							avPriceChange = (priceChangesTotal / (usableFiles-1));
    			    			percentPositive = positive / (usableFiles-1);
    						}
    					}

    					sdPriceChange = sdCalculator(priceChanges, avPriceChange, usableFiles-1);
    					double lowestPriceChange = lowValue(priceChanges, usableFiles-1);
    					double highestPriceChange = highValue(priceChanges, usableFiles-1);

    				    upOrDown = positiveOrNegative(percentPositive);
    					nextPriceChange = valueGenerator(prices, usableFiles-1, sdPriceChange, avPriceChange, highestPriceChange, lowestPriceChange, percentPositive);

    				    if (prices[prices.size()-1] - nextPriceChange < 0)
    				    	nextPrice = prices[prices.size()-1] + nextPriceChange;
    				    else if (upOrDown)
    				    	nextPrice = prices[prices.size()-1] + nextPriceChange;
    				    else
    				    	nextPrice = prices[prices.size()-1] - nextPriceChange;

    					avTradeCount = avCalculator(tradeCounts, usableFiles);
    					sdTradeCount = sdCalculator(tradeCounts, avTradeCount, usableFiles);
    					double lowestTradeCount = lowValue(tradeCounts, usableFiles);
    					double highestTradeCount = highValue(tradeCounts, usableFiles);

    					double nextTradeCount = valueGenerator(tradeCounts, usableFiles, sdTradeCount, avTradeCount, highestTradeCount, lowestTradeCount);
    					int nextTrades = (int) nextTradeCount;

        		        generatedSnapShot = new generatorTemplate(wIssueSymbol, prices, priceChanges, avPriceChange, sdPriceChange, percentPositive, tradeVolumes, tradeCounts, avTradeCount, sdTradeCount, tradeCountPercent, nextPrice, nextTrades);
    				}
    				break;
    			}
    		}
        }

        // print before percentages calculated
        // generatedSnapShot->print();

        snapSym.push_back(generatedSnapShot);
    }

    totalTrades = 0;
    for (unsigned int j = 0; j < snapSym.size(); j++)
    	totalTrades += snapSym[j]->nextTrades;


    long double totalTradesPredicted = 0;
   	for (unsigned int k = 0; k < snapSym.size(); k++){
    	long double percentage = (long double) snapSym[k]->nextTrades / (long double) totalTrades;
   		snapSym[k]->tradeCountPercent = percentage;
   		totalTradesPredicted += percentage;
    	snapSym[k]->print();
    }

   	cout << "The total trades: 			" << totalTrades << endl;
   	cout << "Total Trades percentage:		" << totalTradesPredicted << endl;

//    Debug for making sure all percentages add up to 1
//    cout << "Big dirty total: " << entireTotal / usableFiles << endl;

//    for (unsigned int j = 0; j < snapSym.size(); j++)
//    	snapSym[j]->print();

//    Debugging loop. Ensures all probabilities add to 1
//    for (int j = 0; j < usableFiles; j++)
//    	cout << "Day " << j << " : " << counters[j] << endl;

    return 0;
}
