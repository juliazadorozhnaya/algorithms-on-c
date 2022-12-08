#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <random>
#include <cmath>

#include "solution.h"

class generator {
private:
	std::random_device rd{};
    std::mt19937 gen{rd()};
    int vertexNum, minWeight, maxWeight; 
    double dispVertexWeight, compNum, dispComp;
    double vertexDegree, dispDegree;
	std::vector<std::pair<oneJob *, std::pair<int, int>>> allJobs;
public:

	generator(int vertexNum_, int minWeight_, int maxWeight_, double dispVertexWeight_, double compNum_,
			  double dispComp_, double vertexDegree_, double dispDegree_) : vertexNum(vertexNum_), minWeight(minWeight_), 
			  maxWeight(maxWeight_), dispVertexWeight(dispVertexWeight_), compNum(compNum_),
			  dispComp(dispComp_), vertexDegree(vertexDegree_), dispDegree(dispDegree_) {
		for (size_t i = 0; i < vertexNum; i++) {
			allJobs.push_back(std::make_pair(new oneJob (distForWeight(minWeight, maxWeight, dispVertexWeight), i), std::make_pair(-1, 0)));
		}
	}

	int distForWeight(int min, int max, double disp){
		//std::random_device rd{};
	    //std::mt19937 gen{rd()};
	    std::normal_distribution<> dist{(double)(max - min) / 2, disp}; 
	    int res = std::round(dist(gen));
	    while (res < min || res > max) {
	    	res = std::round(dist(gen));
	    }
	    return res;
	}
	
	int distForComp(double mean, double disp, int max){
		//std::random_device rd{};
	    //std::mt19937 gen{rd()};
	    std::normal_distribution<> dist{mean, disp}; 
	    int res = std::round(dist(gen));
	    while (res < 0 || res > max) {
	    	res = std::round(dist(gen));
	    }
	    return res;
	}
	
	
	int distForDegree(double mean, double disp, int min){
		//std::random_device rd{};
	    //std::mt19937 gen{rd()};
	    std::normal_distribution<> dist{mean, disp}; 
	    int res = std::round(dist(gen));
	    while (res < min) {
	    	res = std::round(dist(gen));
	    }
	    return res;
	}

	void print() {
		for (size_t i = 0; i < allJobs.size(); i++) {
			std::cout << "Num: " << allJobs[i].first->getNum() << " Weight: " << allJobs[i].first->getDuration();
			std::cout << " Component " << allJobs[i].second.first << " Dependences: ";
			if (allJobs[i].first->depNum.size()) {
				for (auto j: allJobs[i].first->depNum) {
					std::cout << j << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	void compInitialize ()
	{
		int vertex = vertexNum, newCompVertexNum, j = 0;
		while (vertex > compNum) {
			newCompVertexNum = this->distForComp(compNum, dispComp, vertex);
			for (size_t i = vertexNum - vertex; i < vertexNum - vertex + newCompVertexNum; i++) {
				allJobs[i].second.first = j;
			}
			j++;
			vertex -= newCompVertexNum;
		}
		for (size_t i = vertexNum - vertex; i < vertexNum; i++) {
			allJobs[i].second.first = j;
		}
		return;
	}


	void degreeInitialize ()
	{
		int j = 0, cur = 0, k = 0, last = 0;
		while (true) {
			k = 0;
			for (size_t i = cur; i < allJobs.size(); i++) {
				if (allJobs[i].second.first == j) {
					cur++;
					k++;
				} else {
					break;
				}
			}
			//std::cout << "COMP " << j << " ELEM: " << k << " last " << last << " cur " << cur << std::endl;
			for (size_t i = last; i < cur; i++) {
				int depVertNum = distForDegree(vertexDegree, dispDegree, std::max(1, allJobs[i].second.second));
				//std::cout << "         VERT: " << i << " Degree: " << depVertNum << " DEP: " << allJobs[i].second.second << std::endl;
				allJobs[i].first->depNum = std::vector<size_t>();
				depVertNum -= allJobs[i].second.second;
				//std::cout << "              DEP: " << depVertNum << " MIN: " << i + 1 << " MAX: " << std::min((int)(i + depVertNum), cur) << std::endl;
				for (size_t ii = i + 1; ii < std::min((int)(i + depVertNum + 1), cur); ii++) {
					allJobs[i].first->depNum.push_back(allJobs[ii].first->getNum());
					allJobs[ii].second.second ++;
				}
			}
			j++;
			last = cur;
			if (cur >= allJobs.size()) {
				break;
			}
		}
		return;
	}



	std::vector<oneJob *> transform () {
		std::vector<oneJob *> res;
		int curComp = 0, from = 0;
		for (size_t i = 0; i < allJobs.size(); i++) {
			if (curComp != allJobs[i].second.first) {
				curComp = allJobs[i].second.first;
				from = i;
			}
			res.push_back(new oneJob(allJobs[i].first->getDuration(), allJobs[i].first->getNum()));
			for (size_t j = from; j < i; j++) {
				for (auto dep: allJobs[j].first->depNum) {
					if (dep == res[i]->getNum()) {
						res[i]->depNum.push_back(j);
					}
				}
			}
	
		}
		/*std::cout << "\n********************************************\n" << std::endl;
		for (size_t i = 0; i < res.size(); i++) {
			std::cout << "Num: " << res[i]->getNum() << " Weight: " << res[i]->getDuration();
			std::cout << " Dependences: ";
			if (res[i]->depNum.size()) {
				for (auto j: res[i]->depNum) {
					std::cout << j << " ";
				}
			}
			std::cout << std::endl;
	
		}*/
		return res;
	}

	void inputFormat (std::string filename) {
		std::vector<oneJob*> myAllJobs = transform();
		std::ofstream file;
	  	file.open(filename + ".txt");
	  	file << myAllJobs.size() << std::endl;
	  	
	  	for (auto job : myAllJobs) {
	  		file << job->getDuration();
	  		for (auto j: job->depNum) {
	  			file << " " << j;
	  		}
	  		file << std::endl;
	  	}
	  	return;
	}
	
	void dotFormat (std::string filename) {
		std::ofstream file;
	  	file.open(filename + ".dot");
	  	file << "digraph G {" << std::endl;
	  	file << "    graph [fontsize=24]" << std::endl;
	  	file << "    edge [fontsize=24]" << std::endl;
	 	file << "    node [fontsize=24]" << std::endl;
	  	file << "    ranksep = 1.5" << std::endl;
	  	file << "    nodesep = .25" << std::endl;
	  	for (auto job : allJobs) {
	  		file << "    " << job.first->getNum() << " -> { ";
	  		for (auto j: job.first->depNum) {
	  			file << allJobs[j].first->getNum() << " ";
	  		}
	  		file << "};" << std::endl;
	  		
	  	}
	  	file << "}" << std::endl;
	}
	
};
