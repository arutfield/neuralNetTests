#include "stdafx.h"
#include "CppUnitTest.h"
#include "../neuralNet/TrainingDataSet.h"
#include "../neuralNet/Network.h"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestDataSet)
		{	
			TrainingDataSet dataSet (0.0, 0.0, 0.0);
			Assert::AreEqual(dataSet.getX0(), 0.0);
		}

		TEST_METHOD(TestReadingTrainingDataAll)
		{
			Network network;
			TrainingDataSet dataSet(0.0, 0.0, 0.0);
			
			network.readTrainingData("..\\allTData1to5.txt");
			Assert::AreEqual(network.getTrainingData().size(), (size_t) 36);
		}

		TEST_METHOD(TestReadingTrainingData)
		{
			Network network;

			network.readTrainingData("..\\allTData1to5.txt");
			TrainingDataSet tdSet = network.getTrainingData().front();
			Assert::AreEqual(tdSet.getX0(), 0.0);
			Assert::AreEqual(tdSet.getX1(), 0.0);
			Assert::AreEqual(tdSet.getY(), 1.0);
		}

		TEST_METHOD(TestCorrectConstantCalculation)
		{
			Network network;

			network.readTrainingData("..\\allTData1to5.txt");
			double * pConstants = network.setBestConstants(10000, 0.001, false);
			double constants[3];
			for (int i = 0; i < 3; i++){
				constants[i] = *(pConstants + i);
			}
			Assert::IsTrue(abs(constants[0] - 6.0) < 1e-4);
			Assert::IsTrue(abs(constants[1] - 1.0) < 1e-4);
			Assert::IsTrue(abs(constants[2] - 1.0) < 1e-4);

		}

		TEST_METHOD(TestCorrectOutput)
		{
			Network network;

			network.readTrainingData("..\\allTData1to5.txt");
			double * pConstants = network.setBestConstants(10000, 0.001, false);

			double * results = network.calculateOutputs("..\\testOutputData.txt");
			Assert::IsTrue(abs(*(results) - 759.0) < 1e-4);
		}
	};
}