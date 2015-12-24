#include "CosinSimGraphConstructor.h"
#include "CosSim.hpp"
#include "ClusterRep.hpp"

IRProject::CosinSimGraphConstructor::CosinSimGraphConstructor(Index *index)
{
	this->index = index;
}


IRProject::CosinSimGraphConstructor::~CosinSimGraphConstructor(void)
{
}

void IRProject::CosinSimGraphConstructor::constructGraph()
{
	lemur::cluster::CosSim s(*index);
	int docCount = index->docCount();
	double **m = new double *[docCount];
	for(int i = 0 ; i< docCount ; i++)
	{
		m[i] = new double[docCount];
	}

	for(int i = 0 ; i< docCount ; i++)
	{
		lemur::cluster::ClusterRep doci(i+1,*index);
		for(int j = 0 ; j< docCount ; j++)
		{
			if(i == j)
				m[i][j] = 0;
			else
			{
				lemur::cluster::ClusterRep docj(j+1,*index);
				m[i][j] = s.similarity(&doci,&docj);

			}
			std::cout<< m[i][j] << std::endl;
		}
	}

	for(int i = 0 ; i< docCount ; i++)
		delete [] m[i];
	delete []m;
}
