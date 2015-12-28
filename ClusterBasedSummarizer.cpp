#include "ClusterBasedSummarizer.h"
#include "KMeansClusterer.h"

IRProject::ClusterBasedSummarizer::ClusterBasedSummarizer(Index *index)
{
	this->index = index;
	std::vector<int> docs;
	for(int i = 1 ; i<= index->docCount(); i++)
	{
		docs.push_back(i);
	}
	setCluster = new ClusterRep(docs,*index);

	cosSim = new CosSim(*index);

	docsCount = index->docCount();
}


IRProject::ClusterBasedSummarizer::~ClusterBasedSummarizer(void)
{
	delete cosSim;
}

std::vector<IRProject::ClusterInfo> IRProject::ClusterBasedSummarizer::detectClusters()
{
	KMeansClusterer clusterer(index,std::sqrt(index->docCount()));
	std::vector<Cluster *> *clusters = clusterer.cluster();

	unsigned clustersCount = clusters->size();


	std::vector<ClusterInfo> clustersInfo(clustersCount);

	for( unsigned i = 0 ; i < clustersCount; i++)
	{
		clustersInfo[i].cluster = (*clusters)[i];
		clustersInfo[i].weight = computeClusterWeight((*clusters)[i]);
	}

	delete clusters;

	return clustersInfo;
}

double IRProject::ClusterBasedSummarizer::computeClusterWeight(Cluster *cluster)
{
	lemur::cluster::CosSim s(*index);
	return s.similarity(cluster->getClusterRep(),setCluster);
}

std::vector<int> IRProject::ClusterBasedSummarizer::selectMaximumDoc(const std::vector<double> &finalScore)
{
	std::vector<int> res;

	double maxScore = 0;
	int maxIndex = 0;
	for(int d = 1 ; d <= docsCount; d++)
	{
		if(finalScore[d]> maxScore)
		{
			maxScore = finalScore[d];
			maxIndex = d;
		}
	}
	res.push_back(maxIndex);
	return res;
}

void IRProject::ClusterBasedSummarizer::normalize(Matrix &m)
{
	for(int i = 1 ; i<= docsCount ; i++)
	{
		double sum = 0;
		for(int j = 1 ; j<= docsCount ; j++)
		{
			sum += m[i][j];
		}

		if(sum == 0) // TODO: normalize for zero row
		{
			printf("%d \n", i);
			printf("!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!! \n");
			
		}

		for(int j = 1 ; j<= docsCount ; j++)
		{
			m[i][j] = m[i][j] / sum;
			//printf("m[%d][%d] = %f \n",i,j,m[i][j]);
		}
	}
}

void IRProject::ClusterBasedSummarizer::normalize(std::vector<double> &vector, unsigned startIndex)
{
	double sum = 0;
	for(unsigned i = startIndex ; i < vector.size() ; i++)
	{
		sum+= vector[i];
	}
	for(unsigned i = startIndex ; i < vector.size() ; i++)
	{
		vector[i] = vector[i]/sum;
	}
}

bool IRProject::ClusterBasedSummarizer::isUnderThreshold(std::vector<double> &v1, std::vector<double> &v2, unsigned startIndex, double threshold)
{
	if(v1.size() != v2.size())
		return false;

	for(unsigned i = startIndex ; i < v1.size(); i++)
	{
		if(abs(v1[i] - v2[i]) > threshold )
			return false;
	}

	return true;
}

std::vector<int> IRProject::ClusterBasedSummarizer::summarize()
{
	std::vector<ClusterInfo> clusters = detectClusters();

	Matrix adjacencyMatrix;
	initialAdjacencyMatrix(adjacencyMatrix, clusters);

	std::vector<double> finalScore = computeSentencesScore(adjacencyMatrix);

	return selectDocs(finalScore);
}

std::vector<int> IRProject::ClusterBasedSummarizer::selectDocs(const std::vector<double> &finalScore)
{
	std::vector<double> affiniyRank(finalScore);
	std::vector<int> res;
	std::vector<bool> isSelectedFlag(finalScore.size(), false);

	Matrix similarityMatrix;
	initialSimilarityMatrix(similarityMatrix);

	while (res.size() != docsCount)
	{
		int selectedIndex = findMaxIndex(affiniyRank, isSelectedFlag);
		res.push_back(selectedIndex);
		isSelectedFlag[selectedIndex] = true;
		for(int i = 1; i < finalScore.size(); i++)
		{
			affiniyRank[i] -= similarityMatrix[selectedIndex][i] * finalScore[selectedIndex];
		}
	}

	return res;
}

int IRProject::ClusterBasedSummarizer::findMaxIndex(const std::vector<double> &scores, const std::vector<bool> &isSelectedFlags)
{
	double maxScore = -DBL_MAX;
	int maxIndex = 0;
	for(int d = 1 ; d < scores.size(); d++)
	{
		if(isSelectedFlags[d] == false && scores[d]> maxScore)
		{
			maxScore = scores[d];
			maxIndex = d;
		}
	}
	return maxIndex;
}

void IRProject::ClusterBasedSummarizer::initialSimilarityMatrix(Matrix &similarityMatrix)
{
	similarityMatrix.resize(docsCount+1);

	for(int i = 1 ; i<= docsCount ; i++)
	{
		similarityMatrix[i].resize(docsCount+1);
		ClusterRep docRepI(i,*index);
		for(int j = 1 ; j<= docsCount ; j++)
		{
			if(i == j)
				similarityMatrix[i][j] = 0;
			else
			{
				ClusterRep docRepJ(j,*index);
				similarityMatrix[i][j] = cosSim->similarity(&docRepI, &docRepJ);
			}
		}
	}

	normalize(similarityMatrix);
}
