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

static vector<string> symbols;
static vector<string> symbolsToCompare;

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
    vector<int> totalTrades;
	for (int p = 0; p < usableFiles; p++)
		totalTrades.push_back(0);

    for (unsigned int i = 0; i < symbolsToCompare.size(); i++)
    {
    	string wIssueSymbol = symbolsToCompare[i];
    	vector<double> prices;
    	vector<double> priceChanges;
    	double avChange;
    	double sdChange;
    	double percentPositive;
    	vector<int> tradeVolumes;
    	vector<int> tradeCounts;
    	vector<long double> tradeCountPercent;
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

    				//cout <<  "Symbol: " << snapShots[j][k].wIssueSymbol << "	Price: " <<  snapShots[j][k].wTradePrice << "	Volume: " << snapShots[j][k].wTradeVolume << "	Count:" << snapShots[j][k].wTradeCount << endl;

    				double priceChangesTotal = 0;
    				double positive = 0;
    				if (j == usableFiles-1)
    				{
    					for (int l = 0; l < usableFiles; l++)
    					{
    						if (l < usableFiles-1)
    						{
    							double tempChange = prices[l+1]-prices[l];
    							priceChanges.push_back(tempChange);
    							// following if statements check whether the change is +ive or -ive, and adjusts
    							// so they're all positive (for calculating the av change).
    							if (tempChange < 0)
        							priceChangesTotal += (tempChange * -1);
    							else
    							{
    								positive++;
    								priceChangesTotal += tempChange;
    							}
    						}
    						else
    						{
    			    			avChange = (priceChangesTotal / (usableFiles-1));
    			    			percentPositive = positive / (usableFiles-1);
    						}
    					}
    					double sdCalc = 0;
    					for (int x = 0; x < usableFiles-1; x++)
    					{
    						if (priceChanges[x] < 0)
    							priceChanges[x] = priceChanges[x] * -1;
    						double tempSdVar = priceChanges[x]-avChange;
    						if (tempSdVar < 0)
    							tempSdVar = tempSdVar *-1;
        				    tempSdVar = (tempSdVar*tempSdVar);
        				    sdCalc += tempSdVar;
    					}
    					sdChange = sqrt(sdCalc / (usableFiles-1));


    					double lowestChange = priceChanges[0];
    				    for(int i = 0; i < usableFiles-1; i++)
    				    {
    				        if(priceChanges[i] < lowestChange)
    				        lowestChange = priceChanges[i];
    				    }

    					double highestChange = priceChanges[0];
    				    for(int i = 0; i < usableFiles-1; i++)
    				    {
    				        if(priceChanges[i] > highestChange)
    				        highestChange = priceChanges[i];
    				    }

    				    double r = randfrom(lowestChange, highestChange);
    				    double s = randfrom(0, sdChange);

    				    if (positiveOrNegative(percentPositive))
    				    	nextPriceChange = ((r + avChange) / 2) + s;
    				    else
    				    	if ((((r + avChange) / 2) - s) < 0)
    				    		nextPriceChange = ((r + avChange) / 2) + s;
    				    	else
    				    		nextPriceChange = ((r + avChange) / 2) - s;

    				    upOrDown = positiveOrNegative(percentPositive);

    				    if (prices[prices.size()-1] - nextPriceChange < 0)
    				    	nextPrice = prices[prices.size()-1] + nextPriceChange;
    				    else if (upOrDown)
    				    	nextPrice = prices[prices.size()-1] + nextPriceChange;
    				    else
    				    	nextPrice = prices[prices.size()-1] - nextPriceChange;

        		        generatedSnapShot = new generatorTemplate(wIssueSymbol, prices, priceChanges, avChange, sdChange, percentPositive, tradeVolumes, tradeCounts, tradeCountPercent, nextPrice);
    				}
    				break;
    			}
    		}
        }

        cout << fixed << showpoint;
        cout << setprecision(2);

        // print before percentages calculated
        // generatedSnapShot->print();

        snapSym.push_back(generatedSnapShot);
    }

    for (unsigned int j = 0; j < snapSym.size(); j++)
    {
    	snapSym[j]->print();
    	for (int k = 0; k < usableFiles; k++){
    		totalTrades[k] += snapSym[j]->wTradeCount[k];
    	}
    }

	for (int j = 0; j < usableFiles; j++)
		cout << "Total trades for day " << j << ": " <<  totalTrades[j] << endl;

    cout << setprecision(90);

    long double count1 = 0;
    long double count2 = 0;
    long double count3 = 0;
    long double count4 = 0;
    long double count5 = 0;
    long double count6 = 0;
    long double count7 = 0;

    //vector<long double> counters;

    for (int j = 0; j < usableFiles; j++)
    {
    	for (unsigned int k = 0; k < snapSym.size(); k++){
    		long double percentage = (long double) snapSym[k]->wTradeCount[j] / (long double) totalTrades[j];
			if (j == 0)
				count1 += percentage;
			if (j == 1)
				count2 += percentage;
			if (j == 2)
				count3 += percentage;
			if (j == 3)
				count4 += percentage;
			if (j == 4)
				count5 += percentage;
			if (j == 5)
				count6 += percentage;
			if (j == 6)
				count7 += percentage;
    	}
    }


    for (int j = 0; j < usableFiles; j++){
		for (int k = 0; k < fileLengthsNormalised[j]; k++){
			//cout << "Day " << j << endl;
			//cout << snapShots[j][k].wIssueSymbol << " has "  << snapShots[j][k].wTradeCount << " trades." << endl;
			//long double percentage = (long double) snapShots[j][k].wTradeCount / (long double) totalTrades[j];
			//cout << snapShots[j][k].wTradeCount << " out of " << totalTrades[j] << " is " << percentage << endl;
			//generatedSnapShot[j].tradeCountPercent.push_back(percentage);
		}
    }

    cout << "Day 1: " << count1 << endl;
    cout << "Day 2: " << count2 << endl;
    cout << "Day 3: " << count3 << endl;
    cout << "Day 4: " << count4 << endl;
    cout << "Day 5: " << count5 << endl;
    cout << "Day 6: " << count6 << endl;
    cout << "Day 7: " << count7 << endl;



    return 0;
}
