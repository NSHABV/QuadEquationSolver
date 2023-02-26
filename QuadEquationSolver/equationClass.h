#pragma once
#include <string>

struct rootStruct
{
	int rootCount;
	double firstRoot, secondRoot;
};

class equationCl
{
public:
	equationCl(double constantCoeff, double xCoeff, double squareCoeff = 0);
	equationCl() : equationCl(0, 0, 0) {};
	
	bool initFromFile(std::string fileName);
	double calculateDeterminant();
	rootStruct getRoots();
	bool outputRootsToFile(std::string fileName);

	double getSquareXCoeff();
	double getRegXCoeff();
	double getConstantCoeff();
private:
	double m_squareXCoeff = 0;
	double m_regXCoeff = 0;
	double m_constantCoeff = 0;

	bool failureFlag = 0;
};