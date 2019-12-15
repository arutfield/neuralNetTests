#pragma once
#include "TrainingDataSet.h"
#include "Inputs.h"
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Network
{
	double w[2], b;
	list<TrainingDataSet> trainingData;

public:
	Network();
	void readTrainingData(string fileName);
	list<TrainingDataSet> getTrainingData(){ return trainingData; }
	double * setBestConstants(int iterations, double learningParam, bool printValues);
	double * calculateOutputs(string fileName);
	~Network();

private:
	double * getCostDerivatives();
	list<Inputs> readTestData(string fileName);
	double getCostFunction(double w[], double b);
	double getMagnitude(double yArray[], double aArray[]);
};
