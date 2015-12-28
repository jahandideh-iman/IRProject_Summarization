#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "Matrix.h"
#include "CosSim.hpp"
#include "Types.h"

namespace IRProject
{
	
}

IRProject::ClusterBasedConditionalMarkovRandomWalk::ClusterBasedConditionalMarkovRandomWalk(double lambda, Index *index) 
	: ClusterBasedSummarizer(index)
{
	this->lambda = lambda;
}

IRProject::ClusterBasedConditionalMarkovRandomWalk::~ClusterBasedConditionalMarkovRandomWalk(void)
{

}

void IRProject::ClusterBasedConditionalMarkovRandomWalk::initialAdjacencyMatrix(Matrix &m, const std::vector<ClusterInfo> &clusters)
{
	std::vector<DocInfo> docs(docsCount+1);
	initialDocsInfo(docs, clusters);

	m.resize(docsCount+1);

	for(int i = 1 ; i<= docsCount ; i++)
	{
		m[i].resize(docsCount+1);
		ClusterRep docRepI(i,*index);
		for(int j = 1 ; j<= docsCount ; j++)
		{
			if(i == j)
				m[i][j] = 0;
			else
			{
				ClusterRep docRepJ(j,*index);
				double sim = cosSim->similarity(&docRepI, &docRepJ);
				m[i][j] = sim * (lambda* docs[i].clusterInfo->weight * docs[i].weight) + ((1-lambda) * docs[j].clusterInfo->weight * docs[j].weight );
			}
		}
	}

	normalize(m);
}

void IRProject::ClusterBasedConditionalMarkovRandomWalk::initialDocsInfo(std::vector<DocInfo> &docs, const std::vector<ClusterInfo> &clusters)
{
	for(const ClusterInfo &cInfo : clusters)
	{
		for(auto id : cInfo.cluster->getDocIds())
		{
			ClusterRep docRep(id,*index);
			docs[id].clusterInfo  = &cInfo;
			docs[id].weight = cosSim->similarity(cInfo.cluster->getClusterRep(), &docRep);
		}
	}
}

std::vector<double> IRProject::ClusterBasedConditionalMarkovRandomWalk::computeSentencesScore(Matrix &m)
{
	std::vector<double> currentDocP(docsCount+1,1);
	std::vector<double> nextDocP(docsCount+1,1);

	double beta = 0.85;
	while(true)
	{
		for(int i = 1 ; i <= docsCount; i++)
		{
			nextDocP[i] = (1 - beta) / docsCount;
			for(int j = 1 ; j <= docsCount; j++)
			{
				if(i != j)
				{
					nextDocP[i]+= beta * currentDocP[j] * m[j][i];
				}
			}
		}

		nextDocP.swap(currentDocP);

		if(isUnderThreshold(currentDocP,nextDocP,1, 0.0001))
			break;
	}

	return currentDocP;
}
