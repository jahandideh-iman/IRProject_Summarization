#include "KMeansClusterer.h"


IRProject::KMeansClusterer::~KMeansClusterer(void)
{
	delete clusterer;
}

IRProject::KMeansClusterer::KMeansClusterer(const Index *index, unsigned k)
{
	this->index = index;
	this->k = k;
	clusterer = new lemur::cluster::OfflineCluster(*index);

}

std::vector<IRProject::Cluster *> *IRProject::KMeansClusterer::cluster()
{
	std::vector<int> docs;
	for(int i = 1 ; i<= index->docCount(); i++)
		docs.push_back(i);
	return clusterer->kMeans(docs,k);
}
