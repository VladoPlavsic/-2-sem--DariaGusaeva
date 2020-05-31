#pragma once

#include <iostream>

#include "../array/array.h"
#include "../list/tree.h"

struct Writer
{
	FILE* m_pFile;

	Writer();
	void Print(array_tree::Tree* tree);
	void Print(linked_tree::Tree* tree);

	template <class T>
	void Write(T tree);

	~Writer()
	{
		fclose(m_pFile);
	}
};