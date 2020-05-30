#define _CRT_SECURE_NO_WARNINGS
#include "filereader.h"

File::File(FILE* pFile)
	: m_pFile(pFile)
{

	fseek(pFile, 0, SEEK_END);
	m_Size = ftell(pFile);
	m_Position = 0;
	fseek(pFile, 0, SEEK_SET);

	m_Value = new char[m_Size + 1];
	memset(m_Value, 0, m_Size * (sizeof m_Value[0]));
	fread(m_Value, 1, m_Size, pFile);
}

void File::ToObject(Values* values)
{
	values->m_Name = ReadLine();
	values->m_MiddleName = ReadLine();
	values->m_LastName = ReadLine();
	values->m_Date = ReadLine();
	values->m_Death = ReadLine();
	values->m_Place = ReadLine();
}

char* File::ReadLine()
{
	unsigned int size = 0;
	while (m_Value[m_Position + size] != '\n')
	{
		size++;
	}

	char* line = new char[size];
	unsigned int k = 0;

	for (unsigned int i = m_Position; i < m_Position + size; i++) {
		line[k] = m_Value[i];
		k++;
	}
	m_Position += size + 1;
	line[size] = 0;
	return line;
}

bool File::GenTree(Values* values)
{

	values->m_Name = ReadLine();
	if (values->m_Name == "**" || feof(m_pFile) == 0)
	{
		return false;
	}
	values->m_MiddleName = ReadLine();
	values->m_LastName = ReadLine();
	values->m_Date = ReadLine();
	values->m_Death = ReadLine();
	values->m_Place = ReadLine();
	return true;
}