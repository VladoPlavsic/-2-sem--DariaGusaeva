#define _CRT_SECURE_NO_WARNINGS
#include "file.h"

Writer::Writer()
{
	m_pFile = fopen("src\\information\\log.txt", "a+");
}

void Writer::Print(array_tree::Tree* tree)
{
	if (tree->CheckFirst())
		return;
	tree->Root();
	Write(tree);
	while (true) {
		while (tree->CheckLeft() != nullptr && !tree->CheckLeft()->m_Printed)
		{
			tree->Left();
			Write(tree);

		}
		if (tree->CheckLeft() == nullptr && (tree->CheckRight() == nullptr || !tree->CheckRight()->m_Printed))
			fwrite("**\n", sizeof(char), 3, m_pFile);
		if (tree->CheckRight() != nullptr && !tree->CheckRight()->m_Printed)
		{
			tree->Right();
			Write(tree);
			continue;
		}
		if (tree->CheckRight() == nullptr)
			fwrite("**\n", sizeof(char), 3, m_pFile);
		tree->Parent();
		if (tree->CheckCurrent() == tree->m_Values[0] && tree->CheckRight() == nullptr && tree->CheckLeft() == nullptr)
			break;
		else if (tree->CheckCurrent() == tree->m_Values[0] && tree->CheckRight() == nullptr && tree->CheckLeft() != nullptr)
		{
			if (tree->CheckLeft()->m_Printed)
				break;
			else
				continue;
		}
		else if (tree->CheckCurrent() == tree->m_Values[0] && tree->CheckRight() != nullptr && tree->CheckLeft() == nullptr)
		{
			if (tree->CheckRight()->m_Printed)
				break;
		}
		else if (tree->CheckCurrent() == tree->m_Values[0] && tree->CheckRight() != nullptr && tree->CheckLeft() != nullptr)
		{
			if (tree->CheckRight()->m_Printed && tree->CheckLeft()->m_Printed)
				break;
		}
	}
	tree->ResetPrint();
}

void Writer::Print(linked_tree::Tree* tree)
{
	if (tree->CheckFirst())
		return;
	tree->Root();
	Write(tree);
	if (tree->CheckIfEmpty())
		return;
	while (true) {
		while (tree->CheckLeft() != nullptr && !tree->CheckLeft()->m_Printed)
		{
			tree->Left();
			Write(tree);

		}
		if (tree->CheckLeft() == nullptr && (tree->CheckRight() == nullptr || !tree->CheckRight()->m_Printed))
			fwrite("**\n", sizeof(char), 3, m_pFile);
		if (tree->CheckRight() != nullptr && !tree->CheckRight()->m_Printed)
		{
			tree->Right();
			Write(tree);
			continue;
		}
		if (tree->CheckRight() == nullptr)
			fwrite("**\n", sizeof(char), 3,m_pFile);
		tree->Parent();
		if (tree->m_Current == tree->m_First && tree->CheckRight() == nullptr && tree->CheckLeft() == nullptr)
			break;
		else if (tree->m_Current == tree->m_First && tree->CheckRight() == nullptr && tree->CheckLeft() != nullptr)
		{
			if (tree->CheckLeft()->m_Printed)
				break;
			else
				continue;
		}
		else if (tree->m_Current == tree->m_First && tree->CheckRight() != nullptr && tree->CheckLeft() == nullptr)
		{
			if (tree->CheckRight()->m_Printed)
				break;
		}
		else if (tree->m_Current == tree->m_First && tree->CheckRight() != nullptr && tree->CheckLeft() != nullptr)
		{
			if (tree->CheckRight()->m_Printed && tree->CheckLeft()->m_Printed)
				break;
		}
	}
	tree->ResetPrint();
}

template <class T>
void Writer::Write(T tree)
{	
	fprintf(m_pFile, "%s\n", tree->CheckCurrent()->m_Name.c_str());
	fprintf(m_pFile, "%s\n", tree->CheckCurrent()->m_LastName.c_str());
	fprintf(m_pFile, "%s\n", tree->CheckCurrent()->m_Date.c_str());
	fprintf(m_pFile, "%s\n", tree->CheckCurrent()->m_Death.c_str());
	fprintf(m_pFile, "%s\n", tree->CheckCurrent()->m_Place.c_str());
	tree->CheckCurrent()->m_Printed = true;
}