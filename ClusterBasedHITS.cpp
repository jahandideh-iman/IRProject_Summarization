#include "ClusterBasedHITS.h"
#include "CosSim.hpp"

IRProject::ClusterBasedHITS::ClusterBasedHITS(Index *index) 
	: ClusterBasedSummarizer(index)
{
}


IRProject::ClusterBasedHITS::~ClusterBasedHITS(void)
{
}

void IRProject::ClusterBasedHITS::initialAdjacencyMatrix(Matrix &m,const std::vector<ClusterInfo> &clusters)
{
	int clustersCount = clusters.size();
	m.resize(docsCount+1);

	for(int i = 1 ; i<=docsCount; i++)
	{
		m[i].resize(clustersCount);
		ClusterRep docRep(i,*index);
		for(int j = 0 ; j < clustersCount; j++)
		{
			m[i][j] = cosSim->similarity(&docRep, clusters[j].cluster->getClusterRep());
		}
	}
}

std::vector<double> IRProject::ClusterBasedHITS::computeSentencesScore(Matrix &m)
{
	int clustersCount = m[1].size();

	std::vector<double> currentAuthScore(docsCount+1,1);
	std::vector<double> nextAuthScore(docsCount+1,1);
	std::vector<double> currentHubScore(clustersCount,1);
	std::vector<double> nextHubScore(clustersCount,1);

	while(true)
	{
		for(int d = 1 ; d<= docsCount; d++)
		{
			nextAuthScore[d] = 0;
			for(int c = 0 ; c < clustersCount ; c++)
			{
				nextAuthScore[d] += m[d][c] * currentHubScore[c];
			}
		}

		for(int c = 0 ; c< clustersCount; c++)
		{
			nextHubScore[c] = 0;
			for(int d = 1 ; d <= docsCount ; d++)
			{
				nextHubScore[c] += m[d][c] * currentAuthScore[d];
			}
		}

		nextAuthScore.swap(currentAuthScore);
		nextHubScore.swap(currentHubScore);

		normalize(currentAuthScore,1);
		normalize(currentHubScore,0);

		if(isUnderThreshold(nextAuthScore, currentAuthScore, 1, 0.0001)
			&& isUnderThreshold(nextHubScore, currentHubScore, 0, 0.0001))
			break;
	}

	return currentAuthScore;
}
