#include "filereader.h"

File::File(FILE* pFile)
	: m_pFile(pFile)
{

	fseek(pFile, 0, SEEK_END);
	m_Size = ftell(pFile);
	m_Position = 0;
	fseek(pFile, 0, SEEK_SET);  /* same as rewind(f); */

	m_Value = new char[m_Size + 1];
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

	char* line = new char[size + 1];
	unsigned int k = 0;

	for (int i = m_Position; i < m_Position + size; i++) {
		line[k] = m_Value[i];
		k++;
	}
	m_Position += size + 1;
	line[size + 1] = 0;
	return line;
}