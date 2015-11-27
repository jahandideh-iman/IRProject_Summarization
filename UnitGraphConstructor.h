#pragma once

namespace IRProject
{
	class UnitGraphConstructor
	{
	public:
		UnitGraphConstructor(void);
		virtual ~UnitGraphConstructor(void);

		virtual void constructGraph() = 0;
	};
}
