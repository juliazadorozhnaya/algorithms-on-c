#pragma once
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>

#include "solution.h"
#include "mutation.h"
#include "temperature.h"

class mainAlgorithm
{

private:
	solution* curSol, *bestSol;
	temperature* temp;
	mutation* curMutation;
	int globOutMaxIter = 10, globInMaxIter = 10;
	double bestCriterion, curCriterion;
 	int step;

public:
	mainAlgorithm(solution* initSol, temperature * initTemp, mutation* initMutation, solution * best = nullptr, int step_ = -1): step(step_){
		curMutation = initMutation->copyOfObj();
		curSol = initSol->copyOfObj();
		if (best == nullptr) {
			bestSol = initSol->copyOfObj();
			
		} else {
			bestSol = best->copyOfObj();
		}
		temp = initTemp->copyOfObj();
	} 
	
	~mainAlgorithm() {
		delete curSol;
		delete bestSol;
		delete temp;
		delete curMutation;
	}

	solution* mainCycle (std::string filename = "currentSolution.txt")
	{
		std::ofstream file;
  		int curStep = 0;
		if (step != -1) {	
			file.open(filename);
  			
		}

		int inMaxIter = globInMaxIter, outMaxIter = globOutMaxIter;
		curCriterion = curSol->getCriterion();
		bestCriterion = bestSol->getCriterion();
		
		
		while (outMaxIter--)
		{
			while (inMaxIter--)
			{
				solution * newSol = curMutation->mutate(curSol->copyOfObj());
				double newCriterion = newSol->getCriterion();
				
				if (newCriterion < bestCriterion)
				{
					delete bestSol;
					bestSol = newSol->copyOfObj();
					bestCriterion = newCriterion;
					outMaxIter = globOutMaxIter;
				} 
				int diff = newCriterion - curCriterion;
				if (diff <= 0)
				{
					delete curSol;
					curSol = newSol->copyOfObj();
					curCriterion = newCriterion;					
				} else {
					double probOfChange = getRandom<double>(0.0, 1.0);
					if (probOfChange < exp(-diff / temp->getTemp()))
					{
				 		delete curSol;
				 		curSol = newSol->copyOfObj();
				 		curCriterion = newCriterion;					
					}	
				}
				if (step != -1) {
					curStep++;
					if (curStep == step) {
						file.open(filename, std::ios::app);
						file << "BEST SOLUTION" << std::endl;
						file.close();
						bestSol->printNumFile(filename);
						file.open(filename, std::ios::app);
						file << "BEST CRITERION: " << bestCriterion << std::endl << std::endl;
						file << "CURRENT SOLUTION" << std::endl;
						file.close();
						curSol->printNumFile(filename);
						file.open(filename, std::ios::app);
						file << "CURRENT CRITERION: " << curCriterion << std::endl << std::endl << std::endl << std::endl;
						file.close();
						curStep = 0;	
					}
				}
					 
			}
			temp->decreaseTemp();
			inMaxIter = globInMaxIter;
		}
		return bestSol;
	}
};