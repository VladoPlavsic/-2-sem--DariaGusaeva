#include "array.h"

#include "../additional/filereader.h"
#include "../additional/calculator.h"
#include "../additional/date.h"

namespace array_tree {

	bool Tree::CheckFirst()
	{
		return m_Values[0] == nullptr;
	}

	void Tree::CreateFirst(const Values& human)
	{
		if (m_Values[0] == nullptr) {
			m_Values[0] = new Values(human);
			m_Current = 0;
			return;
		}
		printf("Уже существует корень!\n");
	}

	void Tree::Root()
	{
		if (m_Values[0] != nullptr) {
			m_Current = 0;
		}
	}

	Values* Tree::CheckLeft()
	{
		return (m_Values[m_Current * 2 + 1] != nullptr) ? m_Values[m_Current * 2 + 1] : nullptr;
	}

	Values* Tree::CheckRight()
	{
		return (m_Values[m_Current * 2 + 2] != nullptr) ? m_Values[m_Current * 2 + 2] : nullptr;
	}

	Values* Tree::CheckCurrent()
	{
		return (m_Values[m_Current] != nullptr) ? m_Values[m_Current] : nullptr;
	}

	void Tree::Left()
	{
		m_Current = CheckLeft() != nullptr ? (m_Current * 2) + 1 : m_Current;
	}

	void Tree::Right()
	{
		m_Current = CheckRight() != nullptr ? (m_Current * 2) + 2 : m_Current;
	}

	//сделать текущим родительскую вершину для текущей вершины(для удобства можно в способе 1 ввести третью связь – обратную связь с родительской вершиной, чтобы не искать ее по всему дереву – Трёхсвязный список);
	void Tree::Parent()
	{
		if (m_Current != 0)
			m_Current = m_Current % 2 == 0 ? (m_Current - 2) / 2 : (m_Current - 1) / 2;
		else
			m_Current = 0;
	}

	//узнать значение текущей вершины;
	void Tree::GetValue(const char& c)
	{
		if (c == 'a')
			CheckCurrent()->m_Printed = true;
		printf("Имя: %s\n", m_Values[m_Current]->m_Name.c_str());
		printf("Отчество: %s\n", m_Values[m_Current]->m_MiddleName.c_str());
		printf("Фамилия: %s\n", m_Values[m_Current]->m_LastName.c_str());
		printf("Дата рождения: %s\n", m_Values[m_Current]->m_Date.c_str());
		if (!m_Values[m_Current]->m_Death.empty())
			printf("Дата смерти: %s\n", m_Values[m_Current]->m_Death.c_str());
		if (!m_Values[m_Current]->m_Place.empty())
			printf("Место рождения: %s\n", m_Values[m_Current]->m_Place.c_str());
	}

	void Tree::ChangeName(std::string* name)
	{
		m_Values[m_Current]->m_Name = *name;
		printf("Изменено значение имени!\n");
	}

	void Tree::ChangeSurname(std::string* middleName)
	{
		m_Values[m_Current]->m_MiddleName = *middleName;
		printf("Изменено значение отчества!\n");
	}

	void Tree::ChangeLastName(std::string* lastName)
	{
		m_Values[m_Current]->m_LastName = *lastName;
		printf("Изменено значение фамилии!\n");
	}

	void Tree::ChangeDate(std::string* date)
	{
		m_Values[m_Current]->m_Date = *date;
		printf("Изменено значение дати рождения!\n");
	}

	void Tree::ChangeDeath(std::string* death)
	{
		m_Values[m_Current]->m_Death = *death;
		printf("Изменено значение дати смерти!\n");
	}

	void Tree::ChangePlace(std::string* place)
	{
		m_Values[m_Current]->m_Place = *place;
		printf("Изменено значение места рождения!\n");
	}

	//изменить значение текущей вершины;
	void Tree::ChangeAll(const Values& human)
	{
		m_Values[m_Current]->m_Name = human.m_Name;
		m_Values[m_Current]->m_LastName = human.m_LastName;
		m_Values[m_Current]->m_MiddleName = human.m_MiddleName;
		m_Values[m_Current]->m_Date = human.m_Date;
		if (!human.m_Death.empty())
			m_Values[m_Current]->m_Death = human.m_Death;
		if (!human.m_Place.empty())
			m_Values[m_Current]->m_Place = human.m_Place;
		printf("Изменени все значения!\n");
	}

	//создать левое поддерево для текущей вершины;
	void Tree::AddLeft(const Values& human)
	{
		if (CheckLeft() == nullptr) 
		{
			m_Values[m_Current * 2 + 1] = new Values(human);
			Left();
			printf("Добавленно левое поддерево\n");
			return;
		}
		printf("Левое поддерево для данной вершины уже существует!");
	}

	//создать правое поддерево для текущей вершины;
	void Tree::AddRight(const Values& human)
	{
		if (CheckRight() == nullptr) 
		{
			m_Values[m_Current * 2 + 2] = new Values(human);
			Right();
			printf("Добавленно правое поддерево\n");
			return;
		}
		printf("Правое поддерево для данной вершины уже существует!");

	}

	//проверка на пустоту дерева(поддерева, начинающегося с текущей вершины);
	bool Tree::CheckIfEmpty()
	{
		return (CheckLeft() != nullptr || CheckRight() != nullptr) ? false : true;
	}

	void Tree::LeftMost()
	{
		while (m_Values[m_Current * 2 + 1] != nullptr)
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
				delete CheckLeft();
				m_Values[m_Current * 2 + 1] = nullptr;
			}
			else if (CheckRight() != nullptr)
			{
				delete CheckRight();
				m_Values[m_Current * 2 + 2] = nullptr;
			}
			else if (m_Current == 0)
			{
				delete m_Values[0];
				m_Values[0] = nullptr;
				printf("Дерево удаленно! \n");
				return;
			}
		}
	}

	void Tree::CreateFromFile()
	{
		FILE* pFile = fopen("src\\information\\example1.txt", "r");
		if (pFile == nullptr) {
			printf("Ошибка! Не смогли открыт данный файл! \n");
			return;
		}
		File* f = new File(pFile);
		while (f->m_Position < f->m_Size) {
			Values values;
			if (!f->ToObject(&values)) {
				printf("Ошибка в файле! Дата! \n");
				continue;
			}
			if (!CheckDate(&values.m_Date) || (!CheckDate(&values.m_Death) && values.m_Death.size() > 1))
				continue;
			if (m_Values[0] == nullptr)
				CreateFirst(values);
			else
			{
				m_Current = 0;
				while (true) {
					if (CompareDates(&m_Values[m_Current]->m_Date, &values.m_Date) && CheckRight() != nullptr)
						Right();
					else if (CompareDates(&m_Values[m_Current]->m_Date, &values.m_Date) && CheckRight() == nullptr)
					{
						AddRight(values);
						break;
					}
					else if (!CompareDates(&m_Values[m_Current]->m_Date, &values.m_Date) && CheckLeft() != nullptr)
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
		return false;
	}

	bool Tree::Printed()
	{
		return CheckCurrent()->m_Printed;
	}

	void Tree::AddByKey(const Values& human)
	{
		m_Current = 0;
		while (true) {
			if (CompareDates(&CheckCurrent()->m_Date, &human.m_Date) && CheckRight() != nullptr)
				Right();
			else if (CompareDates(&CheckCurrent()->m_Date, &human.m_Date) && CheckRight() == nullptr)
			{
				AddRight(human);
				break;
			}
			else if (!CompareDates(&CheckCurrent()->m_Date, &human.m_Date) && CheckLeft() != nullptr)
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
			if (CheckRight() != nullptr && !CheckRight()->m_Printed)
			{
				Right();
				LeftMost();
				GetValue('a');
			}
			else {
				Parent();
				if (Printed())
				{
					if (m_Current == 0 && (CheckRight() == nullptr || CheckRight()->m_Printed))
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
		CheckCurrent()->m_Printed = false;
		while (true)
		{
			if (CheckRight() != nullptr && CheckRight()->m_Printed)
			{
				Right();
				LeftMost();
				CheckCurrent()->m_Printed = false;
			}
			else {
				Parent();
				if (!Printed())
				{
					if (m_Current == 0 && (CheckRight() == nullptr || !CheckRight()->m_Printed))
						return;
					continue;
				}
				CheckCurrent()->m_Printed = false;
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
			if (m_Current == 0 && CheckRight() == nullptr && CheckLeft() == nullptr)
				break;
			else if (m_Current == 0 && CheckRight() == nullptr && CheckLeft() != nullptr)
			{
				if (CheckLeft()->m_Printed)
					break;
				else
					continue;
			}
			else if (m_Current == 0 && CheckRight() != nullptr && CheckLeft() != nullptr)
			{
				if (CheckRight()->m_Printed)
					break;
			}
		}
		ResetPrint();
	}

	void Tree::GenTree()
	{
		if (!CheckFirst())
		{
			printf("Ошибка! Дерево уже существует, пожалуйста удалите его! \n");
			return;
		}

		FILE* pFile = fopen("src\\information\\example2.txt", "r");
		if (pFile == nullptr) {
			printf("Ошибка! Не смогли открыт данный файл! \n");
			return;
		}
		File* f = new File(pFile);
		bool check = true;
		while (f->m_Position < f->m_Size) {
			Values values;
			if (CheckFirst())
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
						while ((CheckLeft() != nullptr && CheckRight() != nullptr) && m_Current != 0)
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
		if (Calculator(&CheckCurrent()->m_Date, &CheckCurrent()->m_Death) && IsMoscow(&CheckCurrent()->m_Place))
			GetValue('a');
		else
			CheckCurrent()->m_Printed = true;
		while (true) {
			while (CheckLeft() != nullptr && !CheckLeft()->m_Printed)
			{
				Left();
				if (Calculator(&CheckCurrent()->m_Date, &CheckCurrent()->m_Death) && IsMoscow(&CheckCurrent()->m_Place))
					GetValue('a');
				else
					CheckCurrent()->m_Printed = true;
			}
			if (CheckRight() != nullptr && !CheckRight()->m_Printed)
			{
				Right();
				if (Calculator(&CheckCurrent()->m_Date, &CheckCurrent()->m_Death) && IsMoscow(&CheckCurrent()->m_Place))
					GetValue('a');
				else
					CheckCurrent()->m_Printed = true;
				continue;
			}
			Parent();
			if (m_Current == 0 && CheckRight() == nullptr && CheckLeft() == nullptr)
				break;
			else if (m_Current == 0 && CheckRight() == nullptr && CheckLeft() != nullptr)
			{
				if (CheckLeft()->m_Printed)
					break;
				else
					continue;
			}
			else if (m_Current == 0 && CheckRight() != nullptr && CheckLeft() != nullptr)
			{
				if (CheckRight()->m_Printed)
					break;
			}
		}
		ResetPrint();
	}
}
