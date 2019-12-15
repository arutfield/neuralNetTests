#include "stdafx.h"
#include "Network.h"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;


Network::Network()
{
	//initialize network with empty weights and biases
	for (int i = 0; i < sizeof(w) / 8.0; i++){
		w[i] = 0;
	}
	b = 0;
}


Network::~Network()
{
}

// read in the training data from a file and store it in trainingData
void Network::readTrainingData(string fileName){
	ifstream file(fileName);
	string str;
	while (getline(file, str)){
		string array[3];
		size_t pos = 0, found;
		int i = 0;
		while (i<3){
			found = str.find_first_of(' ', pos);
			array[i] = str.substr(pos, found - pos);
			pos = found + 1;
			i++;
		}
		TrainingDataSet newData(stod(array[0]), stod(array[1]), stod(array[2]));
		trainingData.push_back(newData);
	}
}

//calculate the best constants based on the training set
double * Network::setBestConstants(int iterations, double learningParam, bool printValues){
		for (int i = 0; i < iterations; i++){
			double* pdResults = getCostDerivatives();
			double dResults[3];
			dResults[0] = *pdResults;
			dResults[1] = *(pdResults + 1);
			dResults[2] = *(pdResults + 2);
			for (int i = 0; i < sizeof(w) / 8.0; i++){
				w[i] = w[i] - learningParam*dResults[i];
			}
			b = b - learningParam*dResults[2];
			if (printValues){
				cout << "w0: " << w[0] << ", w1: " << w[1] << ", b: " << b << endl;
			}
		}
		double results[3];
		int i;
		for (i = 0; i < sizeof(w) / 8.0; i++){
			results[i] = w[i];
		}
		results[i] = b;
		return results;
}

// find derivatives for gradient descent
double * Network::getCostDerivatives(){
	//find dw0
	double cFunction[3];
	double increment = 0.1;
	double w0 = w[0];
	double w1 = w[1];

	//find dw0
	for (int i = 0; i < 3.0; i++){
		double w0Temp = w0 + ((double)(i - 1))*increment;
		double wArray[] = { w0Temp, w1 };
		cFunction[i] = getCostFunction(wArray, b);
	}
	double dw0 = 0.5*((cFunction[1] - cFunction[0]) / increment + (cFunction[2] - cFunction[1]) / increment);

	//find dw1
	for (int i = 0; i < 3.0; i++){
		double w1Temp = w1 + ((double)(i - 1))*increment;
		double wArray[] = { w0, w1Temp };
		cFunction[i] = getCostFunction(wArray, b);
	}
	double dw1 = 0.5*((cFunction[1] - cFunction[0]) / increment + (cFunction[2] - cFunction[1]) / increment);

	//find db
	for (int i = 0; i < 3.0; i++){
		double bTemp = b + ((double)(i - 1))*increment;
		cFunction[i] = getCostFunction(w, bTemp);
	}
	double db = 0.5*((cFunction[1] - cFunction[0]) / increment + (cFunction[2] - cFunction[1]) / increment);
	double results[3] = { dw0, dw1, db };
	return results;
}

//calculate cost function based on current weights and bias
double Network::getCostFunction(double w[], double b){
	double costFunction = 0;
	for (TrainingDataSet currentData : trainingData){
		double yx = currentData.getY();
		double a = w[0] * currentData.getX0() + w[1] * currentData.getX1() + b;
		costFunction = costFunction + getMagnitude(&yx, &a);
	}
	costFunction = 0.25 * costFunction;

	return costFunction;
}

//get magnitude of two arrays
double Network::getMagnitude(double yArray[], double aArray[]){
	double sumVector[(unsigned int)(sizeof(*yArray) / 8.0)];
	for (int i = 0; i < sizeof(*yArray) / 8.0; i++){
		sumVector[i] = yArray[i] - aArray[i];
	}
	//sum the squares
	double sum = 0;
	for (int i = 0; i < sizeof(sumVector) / 8.0; i++){
		sum = sum + pow(sumVector[i], 2);
	}
	return pow(sum, 0.5);
}

//take in test data and output results
double * Network::calculateOutputs(string fileName){
	list<Inputs> inputs = readTestData(fileName);
	const int length = (const int) inputs.size();
	double * outputs = new double[length];
	int i = 0;
	for (Inputs input : inputs){
		cout << "Inputs: " << input.getX0() << ", " << input.getX1() << endl;
		outputs[i] = input.calculateOutput(w[0], w[1], b);
		cout << "Output: " << outputs[i] << endl << endl;
		i++;
	}
	return outputs;
}

list<Inputs> Network::readTestData(string fileName){
	ifstream file(fileName);
	string str;
	list<Inputs> inputList;
	while (getline(file, str)){
		string array[2];
		size_t pos = 0, found;
		int i = 0;
		while (i<2){
			found = str.find_first_of(' ', pos);
			array[i] = str.substr(pos, found - pos);
			pos = found + 1;
			i++;
		}
		Inputs newInput(stod(array[0]), stod(array[1]));
		inputList.push_back(newInput);
	}
	return inputList;
}