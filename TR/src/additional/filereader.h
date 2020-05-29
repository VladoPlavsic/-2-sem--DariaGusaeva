#pragma once
#include "../logging/console.h"
#include <iostream>

struct File
{
	FILE* m_pFile;
	std::string m_Result;
	unsigned long m_Size;
	unsigned long m_Position;
	char* m_Value;

	File(FILE* pFile);
	void ToObject(Values* values);
	char* ReadLine();
	bool GenTree(Values* values);

	~File()
	{
		fclose(m_pFile);
	}

};