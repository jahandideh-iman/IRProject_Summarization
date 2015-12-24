#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "KMeansClusterer.h"
#include "Matrix.h"
#include "CosSim.hpp"

namespace IRProject
{
	struct ClusterInfo{

		ClusterInfo()
		{
			cluster = nullptr;
			weight  = 0;
		}

		ClusterInfo(Cluster *c, double w)
		{
			cluster = c;
			weight  = w;
		}
		Cluster *cluster;
		double weight;
	};

	struct DocInfo{

		DocInfo()
		{
			cluster = nullptr;
			weight  = 0;
		}

		DocInfo(Cluster *c, double w)
		{
			cluster = c;
			weight  = w;
		}
		Cluster *cluster;
		double weight;
	};
}

IRProject::ClusterBasedConditionalMarkovRandomWalk::ClusterBasedConditionalMarkovRandomWalk(Index *index)
{

	this->index = index;
	std::vector<int> docs;
	for(int i = 1 ; i<= index->docCount(); i++)
	{
		docs.push_back(i);
	}
	docsSetCluster = new ClusterRep(docs,*index);
}


IRProject::ClusterBasedConditionalMarkovRandomWalk::~ClusterBasedConditionalMarkovRandomWalk(void)
{
	delete docsSetCluster;
}

std::vector<std::string> IRProject::ClusterBasedConditionalMarkovRandomWalk::summarize()
{
	KMeansClusterer clusterer(index,std::sqrt(index->docCount()));
	std::vector<Cluster *> *clusters = clusterer.cluster();

	unsigned clustersCount = clusters->size();
	unsigned docsCount = index->docCount();

	std::vector<ClusterInfo> clustersInfo(clustersCount);
	Matrix<DocInfo> docsInfo(docsCount,docsCount);
	
	for( unsigned i = 0 ; i < clustersCount; i++)
	{
		clustersInfo[i].cluster = (*clusters)[i];
		clustersInfo[i].weight = computeClusterWeight((*clusters)[i]);
	}


	delete clusters;
	std::vector<std::string> senteces;
	return senteces;
}

double IRProject::ClusterBasedConditionalMarkovRandomWalk::computeClusterWeight(Cluster *cluster)
{
	lemur::cluster::CosSim s(*index);
	return s.similarity(cluster->getClusterRep(),docsSetCluster);
}
