#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

namespace tree{
	Values CreateValues();
	std::string GetString(const std::string& value);
	void Header();
	void Choice();
	void ProgramLoop();
}