#pragma once

#include "UnitGraphConstructor.h"
#include "Types.h"

namespace IRProject
{

	class CosinSimGraphConstructor : public UnitGraphConstructor
	{
	public:
		CosinSimGraphConstructor(Index *index);
		~CosinSimGraphConstructor(void);

		virtual void constructGraph() override;

	private:
		Index *index;
	};

}