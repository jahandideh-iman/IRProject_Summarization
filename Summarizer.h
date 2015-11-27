#pragma once

#include <vector>

class Summarizer
{
public:
	Summarizer(void);
	~Summarizer(void);

	virtual std::vector<std::string> summarize() = 0;
};

