#pragma once

//inputs for the test data
class Inputs
{
	double x0, x1;
public:
	Inputs(double x0i, double x1i){
		x0 = x0i; x1 = x1i;
	}
	double getX0() { return x0; }
	double getX1(){ return x1; }
	double calculateOutput(double w0, double w1, double b) { return w0*x0+w1*x1+b; }
	~Inputs(){};
};

