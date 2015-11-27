#pragma once

#include <vector>

namespace IRProject
{
	class UnitExtractor
	{
	public:
		UnitExtractor(void);
		virtual ~UnitExtractor(void);

		virtual std::vector<std::string> extractUnits() = 0;
	};
}
