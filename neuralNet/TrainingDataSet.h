#pragma once

//one set of training data (2 X values, 1 y value) 
class TrainingDataSet
{
	double x0, x1, y;
public:
	TrainingDataSet(double, double, double);
	double getX0() { return x0; }
	double getX1(){ return x1; }
	double getY() { return y; }
	~TrainingDataSet();
};

