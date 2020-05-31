#include "date.h"

#define CURRENT_YEAR 2020

bool CheckDate(const std::string* date)
{
	if (date->size() < 10 || date->size() > 11)
		return false;
	try
	{
		if (std::stoi(&date->at(0)) > 31 || std::stoi(&date->at(3)) > 12 || std::stoi(&date->at(6)) > CURRENT_YEAR)
			return false;
	}
	catch (std::invalid_argument& e) { return false; }


	return true;
}
