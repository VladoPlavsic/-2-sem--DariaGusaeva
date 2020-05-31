#define _CRT_SECURE_NO_WARNINGS
#include "filereader.h"

File::File(FILE* pFile)
	: m_pFile(pFile)
{
	fseek(pFile, 0, SEEK_END);
	m_Size = ftell(pFile);
	m_Position = 0;
	fseek(pFile, 0, SEEK_SET);

	m_Value = new char[m_Size];
	memset(m_Value, 0, m_Size * (sizeof m_Value[0]));
	fread(m_Value, 1, m_Size, pFile);
}

bool File::ToObject(Values* values)
{
	values->m_Name = ReadLine();
	values->m_MiddleName = ReadLine();
	values->m_LastName = ReadLine();
	values->m_Date = ReadLine();
	if (!CheckDate(&values->m_Date))
	{
		ReadLine();
		ReadLine();
		return false;
	}
	values->m_Death = ReadLine();
	if (!CheckDate(&values->m_Death) && values->m_Death.size() > 1) {
		ReadLine();
		return false;
	}
	values->m_Place = ReadLine();
	return true;
}

char* File::ReadLine()
{
	unsigned int size = 0;
	while (m_Value[m_Position + size] != '\n' && feof(m_pFile) != 0)
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