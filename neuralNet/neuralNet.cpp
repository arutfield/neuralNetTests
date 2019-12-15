// neuralNet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TrainingDataSet.h"
#include "Inputs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <vector>
#include <list>
#include "Network.h"
#define GetCurrentDir _getcwd

using namespace std;

// run neural net gradient descent
int _tmain(int argc, _TCHAR* argv[])
{
	int iterations = 5000;

	//first argument is number of iterations (default 5000)
	if (argc > 1){
		iterations = stoi(argv[1]);
	}

	//second argument is the size of the learning parameter (default 0.01)
	double learningParam = 0.01;
	if (argc > 2){
		learningParam = stod(argv[2]);
	}

	bool printValues = false;
	
	//third argument - view values during gradient descent (true to print, else don't)
	if (argc > 3){
		cout << argv[3] << endl;
		(_tcscmp(argv[3], "true") == 0)? printValues = true : printValues = false;
	}
	Network network;
	network.readTrainingData("..\\neuralNetData.txt");

	//find best w0, w1, b
	network.setBestConstants(iterations, learningParam, printValues);
	//calculate outputs
	network.calculateOutputs("..\\testNetData.txt");

	cout << "Press any key to exit";
	cin.get();
	return 0;
}