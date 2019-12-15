#include "stdafx.h"
#include "TrainingDataSet.h"

using namespace std;

TrainingDataSet::TrainingDataSet(double x0i, double x1i, double yi)
{
	x0 = x0i; x1 = x1i; y = yi;
}


TrainingDataSet::~TrainingDataSet()
{
}
