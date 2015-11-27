#pragma once

namespace IRProject
{
	class UnitScorer
	{
	public:
		UnitScorer(void);
		virtual ~UnitScorer(void);

		virtual void computeScores() = 0;
	};
}
