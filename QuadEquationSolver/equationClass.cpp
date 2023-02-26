#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "equationClass.h"

equationCl::equationCl(double constantCoeff, double xCoeff, double squareCoeff)
{
    m_constantCoeff = constantCoeff;
    m_regXCoeff = xCoeff;
    m_squareXCoeff = squareCoeff;
}

bool equationCl::initFromFile(std::string fileName)
{
    std::ifstream extractionFile(fileName);
    std::string readLine;
    std::vector<std::string> extractedVec;
    if (!extractionFile.is_open())
    {
        std::cout << "Failed to open file " + fileName + "\n";
        failureFlag = 1;
        return false;
    }

    while (std::getline(extractionFile, readLine, ' '))
        extractedVec.push_back(readLine);

    extractionFile.close();

    auto vecSize = extractedVec.size();
    switch (vecSize)
    {
    case 2:
        m_constantCoeff = std::stod(extractedVec.at(1));
        m_regXCoeff = std::stod(extractedVec.at(0));
        m_squareXCoeff = 0;
        failureFlag = 0;
        return true;
    case 3:
        m_constantCoeff = std::stod(extractedVec.at(2));
        m_regXCoeff = std::stod(extractedVec.at(1));
        m_squareXCoeff = std::stod(extractedVec.at(0));
        failureFlag = 0;
        return true;
    default:
        std::cout << "Input parameters inconclusive.\n";
        m_constantCoeff = 0;
        m_regXCoeff = 0;
        m_squareXCoeff = 0;

        failureFlag = 1;
        return false;
    }
}

double equationCl::calculateDeterminant()
{
    if (!m_squareXCoeff == 0 && failureFlag == 0)
    {
        double det = std::sqrt(m_regXCoeff * m_regXCoeff - 4 * m_squareXCoeff * m_constantCoeff);
        return det;
    }
    else
        return 0;
}

rootStruct equationCl::getRoots()
{
    rootStruct calcedRoots;

    float det = calculateDeterminant();
    if (det < 0 || failureFlag == 1)
    {
        std::cout << "Equation cannot be solved for real roots.\n";
        calcedRoots.rootCount = 0;
        return calcedRoots;
    }

    if (m_squareXCoeff != 0)
    {
        float det = calculateDeterminant();
        if (det == 0)
        {
            calcedRoots.rootCount = 1;
            calcedRoots.firstRoot = -1 * m_regXCoeff * 0.5 / m_squareXCoeff;
            return calcedRoots;
        }
        else
        {
            calcedRoots.rootCount = 2;
            calcedRoots.firstRoot =  (-1 * m_regXCoeff + det) * 0.5 / m_squareXCoeff;
            calcedRoots.secondRoot = (-1 * m_regXCoeff - det) * 0.5 / m_squareXCoeff;
            return calcedRoots;
        }
    }
    else if (m_regXCoeff != 0)
    {
        calcedRoots.rootCount = 1;
        calcedRoots.firstRoot = -1 * m_constantCoeff / m_regXCoeff;
        return calcedRoots;
    }
    else    
    {
        std::cout << "Equation cannot be solved due to lack of coefficients.\n";
        calcedRoots.rootCount = 0;
        return calcedRoots;
    }
}

bool equationCl::outputRootsToFile(std::string fileName)
{
    if (failureFlag == 1)
    {
        std::cout << "Incorrectly initialized equation - impossible to solve.\n";
        return 0;
    }
       
    rootStruct calcedRoots = getRoots();

    std::ofstream writeFile(fileName, std::ofstream::trunc);
    if (!writeFile.is_open())
    {
        std::cout << "Failed to open file " + fileName + "\n";
        return false;
    }

    switch (calcedRoots.rootCount)
    {
    case 1:
        writeFile << calcedRoots.firstRoot;
        writeFile.close();
        return true;
    case 2:
        writeFile << std::to_string(calcedRoots.firstRoot);
        writeFile << " ";
        writeFile << std::to_string(calcedRoots.secondRoot);
        writeFile.close();
        return true;
    default:
        writeFile << "No roots.";
        writeFile.close();
        return true;
    }
}

double equationCl::getSquareXCoeff()
{
    return m_squareXCoeff;
}

double equationCl::getRegXCoeff()
{
    return m_regXCoeff;
}

double equationCl::getConstantCoeff()
{
    return m_constantCoeff;
}