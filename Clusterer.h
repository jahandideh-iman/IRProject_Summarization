#pragma once

#include "Types.h"

namespace IRProject
{
	class Clusterer
	{
	public:
		Clusterer(void);
		~Clusterer(void);

		virtual std::vector<Cluster*> *cluster() = 0; 
	};
}
