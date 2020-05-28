#pragma once
#include "../list/treeconsole.h"
#include <iostream>

struct File
{
	FILE* m_pFile = fopen("../informaton/example1.txt", "r");
	std::string m_Result;
	unsigned long m_Size;
	unsigned long m_Position;
	char* m_Value;

	File(FILE* pFile);
	void ToObject(Values* values);
	char* ReadLine();

	~File()
	{
		fclose(m_pFile);
	}

};