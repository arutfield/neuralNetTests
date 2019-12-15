#include <stdio.h>
#include <list>
#include "TrainingDataSet.h"

#pragma once
class NeuralNetwork
{
	double w[2];
	double b;
	list<TrainingDataSet> trainingData;
public:
	NeuralNetwork();
	double *getConstants() { return w; }
	void readTrainingData(string fileName);
	~NeuralNetwork();
};

