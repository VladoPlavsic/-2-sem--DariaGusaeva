#pragma once
#include "file.h"
#include "../additional/date.h"

Values CreateValues();
std::string GetString(const std::string& value);
void Header();
void Choice();
void ProgramLoop(const char* task);