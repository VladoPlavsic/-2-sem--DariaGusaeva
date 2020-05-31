#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

#include "../additional/filereader.h"
#include "../additional/calculator.h"
#include "../additional/date.h"

namespace linked_tree {

	bool Tree::CheckFirst()
	{
		return m_First == nullptr;
	}

	void Tree::CreateFirst(const Values& human)
	{
		if (m_First == nullptr) {
			m_First = new Human(human, nullptr, nullptr, nullptr);
			m_Current = m_First;
			return;
		}
		printf("��� ���������� ������!\n");

	}

	Human* Tree::CheckLeft()
	{
		return (m_Current->m_Left != nullptr) ? m_Current->m_Left : nullptr;
	}

	Human* Tree::CheckRight()
	{
		return (m_Current->m_Right != nullptr) ? m_Current->m_Right : nullptr;
	}

	Human* Tree::CheckCurrent()
	{
		return (m_Current != nullptr) ? m_Current : nullptr;
	}


	void Tree::Root()
	{
		if (m_First != nullptr) {
			m_Current = m_First;
		}
	}

	void Tree::Left()
	{
		if (m_Current->m_Left != nullptr) {
			m_Current = m_Current->m_Left;
			return;
		}
	}

	void Tree::Right()
	{
		if (m_Current->m_Right != nullptr) {
			m_Current = m_Current->m_Right;
			return;
		}
	}

	//������� ������� ������������ ������� ��� ������� �������(��� �������� ����� � ������� 1 ������ ������ ����� � �������� ����� � ������������ ��������, ����� �� ������ �� �� ����� ������ � ���������� ������);
	void Tree::Parent()
	{
		if (m_Current->m_Parent != nullptr) {
			m_Current = m_Current->m_Parent;
			return;
		}
	}

	//������ �������� ������� �������;
	void Tree::GetValue(const char& c)
	{
		if (c == 'a')
			m_Current->m_Printed = true;
		printf("���: %s\n", m_Current->m_Name.c_str());
		printf("��������: %s\n", m_Current->m_MiddleName.c_str());
		printf("�������: %s\n", m_Current->m_LastName.c_str());
		printf("���� ��������: %s\n", m_Current->m_Date.c_str());
		if (!m_Current->m_Death.empty())
			printf("���� ������: %s\n", m_Current->m_Death.c_str());
		if (!m_Current->m_Place.empty())
			printf("����� ��������: %s\n", m_Current->m_Place.c_str());
	}

	void Tree::ChangeName(std::string* name)
	{
		m_Current->m_Name = *name;
		printf("�������� �������� �����!\n");
	}

	void Tree::ChangeSurname(std::string* middleName)
	{
		m_Current->m_MiddleName = *middleName;
		printf("�������� �������� ��������!\n");
	}

	void Tree::ChangeLastName(std::string* lastName)
	{
		m_Current->m_LastName = *lastName;
		printf("�������� �������� �������!\n");
	}

	void Tree::ChangeDate(std::string* date)
	{
		m_Current->m_Date = *date;
		printf("�������� �������� ���� ��������!\n");
	}

	void Tree::ChangeDeath(std::string* death)
	{
		m_Current->m_Death = *death;
		printf("�������� �������� ���� ������!\n");
	}

	void Tree::ChangePlace(std::string* place)
	{
		m_Current->m_Place = *place;
		printf("�������� �������� ����� ��������!\n");
	}

	//�������� �������� ������� �������;
	void Tree::ChangeAll(const Values& human)
	{
		m_Current->m_Name = human.m_Name;
		m_Current->m_LastName = human.m_LastName;
		m_Current->m_MiddleName = human.m_MiddleName;
		m_Current->m_Date = human.m_Date;
		if (!human.m_Death.empty())
			m_Current->m_Death = human.m_Death;
		if (!human.m_Place.empty())
			m_Current->m_Place = human.m_Place;
		printf("�������� ��� ��������!\n");
	}

	//������� ����� ��������� ��� ������� �������;
	void Tree::AddLeft(const Values& human)
	{
		if (m_Current->m_Left == nullptr) 
		{
			m_Current->m_Left = new Human(human, nullptr, nullptr, m_Current);
			m_Current = m_Current->m_Left;
			printf("���������� ����� ���������\n");
			return;
		}
		printf("����� ��������� ��� ������ ������� ��� ����������!");
	}

	//������� ������ ��������� ��� ������� �������;
	void Tree::AddRight(const Values& human)
	{
		if (m_Current->m_Right == nullptr) 
		{
			m_Current->m_Right = new Human(human, nullptr, nullptr, m_Current);
			m_Current = m_Current->m_Right;
			printf("���������� ������ ���������\n");
			return;
		}
		printf("������ ��������� ��� ������ ������� ��� ����������!");

	}

	//�������� �� ������� ������(���������, ������������� � ������� �������);
	bool Tree::CheckIfEmpty()
	{
		return (m_Current->m_Left != nullptr || m_Current->m_Right != nullptr) ? false : true;
	}

	void Tree::LeftMost()
	{
		while (m_Current->m_Left != nullptr)
			Left();
	}

	void Tree::Delete()
	{
		Root();
		LeftMost();
		while (true) {
			while (true) {
				if (CheckRight() != nullptr)
				{
					Right();
					LeftMost();
				}
				else
					break;
			}
			Parent();
			if (CheckLeft() != nullptr)
			{
				delete m_Current->m_Left;
				m_Current->m_Left = nullptr;
			}
			else if (CheckRight() != nullptr)
			{
				delete m_Current->m_Right;
				m_Current->m_Right = nullptr;
			}
			else if (m_Current == m_First)
			{
				delete m_Current;
				m_First = nullptr;
				printf("������ ��������! \n");
				return;
			}
		}
	}

	void Tree::CreateFromFile()
	{
		FILE* pFile = fopen("src\\information\\tests.txt", "r");
		if (pFile == nullptr) {
			printf("������! �� ������ ������ ������ ����!");
			return;
		}
		File* f = new File(pFile);
		while (f->m_Position < f->m_Size) {
			Values values;
			if (!f->ToObject(&values)) {
				printf("������ � �����! ����! \n");
				continue;
			}
			if (!CheckDate(&values.m_Date) || (!CheckDate(&values.m_Death) && values.m_Death.size() > 1))
				continue;
			if (this->m_First == nullptr)
				CreateFirst(values);
			else
			{
				m_Current = m_First;
				while (true) {
					if (CompareDates(&m_Current->m_Date, &values.m_Date) && CheckRight() != nullptr)
						Right();
					else if (CompareDates(&m_Current->m_Date, &values.m_Date) && CheckRight() == nullptr)
					{
						AddRight(values);
						break;
					}
					else if (!CompareDates(&m_Current->m_Date, &values.m_Date) && CheckLeft() != nullptr)
						Left();
					else
					{
						AddLeft(values);
						break;
					}
				}
			}
		}
		fclose(pFile);
	}

	bool Tree::CompareDates(const std::string* date_root, const std::string* date_new)
	{
		char dd_root[2];
		char mm_root[2];
		char yyyy_root[4];
		char dd_new[2];
		char mm_new[2];
		char yyyy_new[4];


		for (int i = 0; i < 2; i++)
		{
			dd_root[i] = date_root->at(i);
			dd_new[i] = date_new->at(i);
		}
		for (int i = 0; i < 2; i++)
		{
			mm_root[i] = date_root->at(i + 3);
			mm_new[i] = date_new->at(i + 3);
		}
		for (int i = 0; i < 4; i++)
		{
			yyyy_root[i] = date_root->at(i + 6);
			yyyy_new[i] = date_new->at(i + 6);
		}

		try {
			if (std::stoi(yyyy_new) < std::stoi(yyyy_root))
				return false;
			else if (std::stoi(yyyy_new) > std::stoi(yyyy_root))
				return true;
			else if (std::stoi(yyyy_new) == std::stoi(yyyy_root))
			{
				if (std::stoi(mm_new) < std::stoi(mm_root))
					return false;
				else if (std::stoi(mm_new) > std::stoi(mm_root))
					return true;
				else if (std::stoi(mm_new) == std::stoi(mm_root))
				{
					if (std::stoi(dd_new) < std::stoi(dd_root))
						return false;
					else if (std::stoi(dd_new) > std::stoi(dd_root))
						return true;
					else
						return true;
				}
			}
		}
		catch (std::invalid_argument& e)
		{
			printf("������! ���� �������� ������ � ����� ��������! ���������� ��������� ������, � ������������� ���������!\n");
			return false;
		}
		return false;
	}

	bool Tree::Printed()
	{
		return m_Current->m_Printed;
	}

	void Tree::AddByKey(const Values& human)
	{
		m_Current = m_First;
		while (true) {
			if (CompareDates(&m_Current->m_Date, &human.m_Date) && CheckRight() != nullptr)
				Right();
			else if (CompareDates(&m_Current->m_Date, &human.m_Date) && CheckRight() == nullptr)
			{
				AddRight(human);
				break;
			}
			else if (!CompareDates(&m_Current->m_Date, &human.m_Date) && CheckLeft() != nullptr)
				Left();
			else
			{
				AddLeft(human);
				break;
			}
		}
	}

	void Tree::PrintByAge()
	{
		Root();
		LeftMost();
		GetValue('a');
		while (true)
		{
			if (m_Current->m_Right != nullptr && !CheckRight()->m_Printed)
			{
				Right();
				LeftMost();
				GetValue('a');
			}
			else {
				Parent();
				if (Printed())
				{
					if (m_Current == m_First && (CheckRight() == nullptr || CheckRight()->m_Printed))
						break;
					continue;
				}
				GetValue('a');
			}
		}
		ResetPrint();
	}

	void Tree::ResetPrint()
	{
		Root();
		LeftMost();
		m_Current->m_Printed = false;
		while (true)
		{
			if (m_Current->m_Right != nullptr && CheckRight()->m_Printed)
			{
				Right();
				LeftMost();
				m_Current->m_Printed = false;
			}
			else {
				Parent();
				if (!Printed())
				{
					if (m_Current == m_First && (CheckRight() == nullptr || !CheckRight()->m_Printed))
						return;
					continue;
				}
				m_Current->m_Printed = false;
			}
		}
	}

	void Tree::PrintRoot()
	{
		Root();
		GetValue('a');
		while (true) {
			while (CheckLeft() != nullptr && !CheckLeft()->m_Printed)
			{
				Left();
				GetValue('a');
			}
			if (CheckLeft() == nullptr && (CheckRight() == nullptr || !CheckRight()->m_Printed))
				printf("**\n");
			if (CheckRight() != nullptr && !CheckRight()->m_Printed)
			{
				Right();
				GetValue('a');
				continue;
			}
			if (CheckRight() == nullptr)
				printf("**\n");
			Parent();
			if (m_Current == m_First && CheckRight() == nullptr && CheckLeft() == nullptr)
				break;
			else if (m_Current == m_First && CheckRight() == nullptr && CheckLeft() != nullptr)
			{
				if (CheckLeft()->m_Printed)
					break;
				else
					continue;
			}
			else if (m_Current == m_First && CheckRight() != nullptr && CheckLeft() != nullptr)
			{
				if (CheckRight()->m_Printed)
					break;
			}
		}
		ResetPrint();
	}

	void Tree::GenTree()
	{
		FILE* pFile = fopen("src\\information\\example2.txt", "r");
		if (pFile == nullptr) {
			printf("������! �� ������ ������ ������ ����!");
			return;
		}
		File* f = new File(pFile);
		bool check = true;
		while (f->m_Position < f->m_Size) {
			Values values;
			if (m_First == nullptr)
			{
				f->GenTree(&values);
				CreateFirst(values);
			}
			else {
				check = f->GenTree(&values);
				if (check && CheckLeft() == nullptr)
				{
					AddLeft(values);
					continue;
				}
				else
				{
					if (!check && CheckLeft() == nullptr)
						check = f->GenTree(&values);
					if (check)
					{
						AddRight(values);
						continue;
					}
					else
					{
						Parent();
						while ((CheckLeft() != nullptr && CheckRight() != nullptr) && m_Current != m_First)
							Parent();
					}
				}
			}
		}
		fclose(pFile);
	}

	void Tree::SearchGen()
	{
		Root();
		if (Calculator(&m_Current->m_Date, &m_Current->m_Death) && IsMoscow(&m_Current->m_Place))
			GetValue('a');
		else
			m_Current->m_Printed = true;
		while (true) {
			while (CheckLeft() != nullptr && !CheckLeft()->m_Printed)
			{
				Left();
				if (Calculator(&m_Current->m_Date, &m_Current->m_Death) && IsMoscow(&m_Current->m_Place))
					GetValue('a');
				else
					m_Current->m_Printed = true;
			}
			if (CheckRight() != nullptr && !CheckRight()->m_Printed)
			{
				Right();
				if (Calculator(&m_Current->m_Date, &m_Current->m_Death) && IsMoscow(&m_Current->m_Place))
					GetValue('a');
				else
					m_Current->m_Printed = true;
				continue;
			}
			Parent();
			if (m_Current == m_First && CheckRight() == nullptr && CheckLeft() == nullptr)
				break;
			else if (m_Current == m_First && CheckRight() == nullptr && CheckLeft() != nullptr)
			{
				if (CheckLeft()->m_Printed)
					break;
				else
					continue;
			}
			else if (m_Current == m_First && CheckRight() != nullptr && CheckLeft() != nullptr)
			{
				if (CheckRight()->m_Printed)
					break;
			}
		}
		ResetPrint();
	}

}