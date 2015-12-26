#include "MinimumDominatingSetSummarizer.h"
#include "CosSim.hpp"
#include "ClusterRep.hpp"


IRProject::MinimumDominatingSetSummarizer::MinimumDominatingSetSummarizer(double lambda, Index *index)
{
	this->index = index;
	this->lambda = lambda;
}


IRProject::MinimumDominatingSetSummarizer::~MinimumDominatingSetSummarizer(void)
{
}

std::vector<int> IRProject::MinimumDominatingSetSummarizer::summarize()
{
	vector<set<int>> adjList = getAdjacencyGraph();
	vector<bool> flags;

	for(int i = 0 ; i< adjList.size(); i++)
		flags.push_back(false);

	vector<int> res;

	while(1) {
		int mx_size = 0;
		int index = -1;
		for(int i = 0; i < adjList.size(); i++) {
			if(flags[i] == false && adjList[i].size() >= mx_size) {
				index = i;
				mx_size = adjList[i].size();
			}
		}
		if(index == -1) {
			break;
		} else {
			res.push_back(index+1);
			for(int i = 0; i < adjList.size(); i++) {
				if(adjList[i].find(index) != adjList[i].end())
					flags[i] = true;
					//adjList[i].erase(index);
			}
			flags[index] = true;
		}
	}
	return res;
}

vector<set<int>> IRProject::MinimumDominatingSetSummarizer::getAdjacencyGraph()
{
	lemur::cluster::CosSim s(*index);
	int docCount = index->docCount();

	vector<set<int>> graph;
	graph.resize(docCount);

	for(int i = 0 ; i< docCount ; i++)
	{
		lemur::cluster::ClusterRep doci(i+1,*index);
		for(int j = 0 ; j< docCount ; j++)
		{
			if(i != j)
			{
				lemur::cluster::ClusterRep docj(j+1,*index);
				if(s.similarity(&doci,&docj) >= lambda)
					graph[i].emplace(j);

				//std::cout<<s.similarity(&doci,&docj)<< std::endl;
			}
		}
	}
	return graph;
}
