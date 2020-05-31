#include "calculator.h"

bool Calculator(const std::string* date_root, const std::string* date_new)
{
	char yyyy_root[4];
	char yyyy_new[4];

	for (int i = 0; i < 4; i++)
	{
		yyyy_root[i] = date_root->at(i + 6);
		if (date_new->size() < 10)
			yyyy_new[i] = TODAY[i + 6];
		else
			yyyy_new[i] = date_new->at(i + 6);
	}

	if (std::stoi(yyyy_new) - std::stoi(yyyy_root) >= 70)
		return true;
	return false;
}

bool IsMoscow(const std::string* place)
{
	if (place->compare("Москва") == 0 || place->compare("Moskva") == 0 || place->compare("Moscow") == 0)
		return true;
	return false;
}