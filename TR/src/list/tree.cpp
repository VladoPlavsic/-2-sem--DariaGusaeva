#include "../additional/filereader.h"

void Tree::CreateFirst(const Values& human)
{
	m_First = new Human(human, nullptr, nullptr, nullptr);
	m_Current = m_First;
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

//сделать текущим родительскую вершину для текущей вершины(для удобства можно в способе 1 ввести третью связь – обратную связь с родительской вершиной, чтобы не искать ее по всему дереву – Трёхсвязный список);
void Tree::Parent()
{
	if (m_Current->m_Parent != nullptr) {
		m_Current = m_Current->m_Parent;
		return;
	}
}

//узнать значение текущей вершины;
void Tree::GetValue(const char& c)
{
	if(c == 'a')
		m_Current->m_Printed = true;
	printf("Имя: %s\n", m_Current->m_Name.c_str());
	printf("Отчество: %s\n", m_Current->m_MiddleName.c_str());
	printf("Фамилия: %s\n", m_Current->m_LastName.c_str());
	printf("Дата рождения: %s\n", m_Current->m_Date.c_str());
	if (!m_Current->m_Death.empty())
		printf("Дата смерти: %s\n", m_Current->m_Death.c_str());
	if (!m_Current->m_Place.empty())
		printf("Место рождения: %s\n", m_Current->m_Place.c_str());
}

void Tree::ChangeName(std::string* name)
{
	m_Current->m_Name = *name;
	printf("Изменено значение имени!\n");
}

void Tree::ChangeSurname(std::string* middleName)
{
	m_Current->m_MiddleName = *middleName;
	printf("Изменено значение отчества!\n");
}

void Tree::ChangeLastName(std::string* lastName)
{
	m_Current->m_LastName = *lastName;
	printf("Изменено значение фамилии!\n");
}

void Tree::ChangeDate(std::string* date)
{
	m_Current->m_Date = *date;
	printf("Изменено значение дати рождения!\n");
}

void Tree::ChangeDeath(std::string* death)
{
	m_Current->m_Death = *death;
	printf("Изменено значение дати смерти!\n");
}

void Tree::ChangePlace(std::string* place)
{
	m_Current->m_Place = *place;
	printf("Изменено значение места рождения!\n");
}

//изменить значение текущей вершины;
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
	printf("Изменени все значения!\n");
}

//создать левое поддерево для текущей вершины;
void Tree::AddLeft(const Values& human)
{
	if (m_Current->m_Left == nullptr) {
		m_Current->m_Left = new Human(human, nullptr, nullptr, m_Current);
		m_Current = m_Current->m_Left;
		printf("Добавленно левое поддерево\n");
		return;
	}
	printf("Левое поддерево для данной вершини уже существует!");
}

//создать правое поддерево для текущей вершины;
void Tree::AddRight(const Values& human)
{
	if (m_Current->m_Right == nullptr) {
		m_Current->m_Right = new Human(human, nullptr, nullptr, m_Current);
		m_Current = m_Current->m_Right;
		printf("Добавленно правое поддерево\n");
		return;
	}
	printf("Правое поддерево для данной вершини уже существует!");

}

//проверка на пустоту дерева(поддерева, начинающегося с текущей вершины);
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
			if (m_Current->m_Right != nullptr)
			{
				Right();
				LeftMost();
			}
			else
				break;
		}
		Parent();
		if (m_Current->m_Left != nullptr)
		{
			delete m_Current->m_Left;
			m_Current->m_Left = nullptr;
		}
		else if (m_Current->m_Right != nullptr)
		{
			delete m_Current->m_Right;
			m_Current->m_Right = nullptr;
		}
		else if (m_Current == m_First)
		{
			delete m_Current;
			m_First = nullptr;
			printf("Дерево удаленно!");
			return;
		}
	}
}

void Tree::CreateFromFile()
{
	FILE* pFile = fopen("src\\information\\example1.txt", "r");
	File* f = new File(pFile);
	while (f->m_Position < f->m_Size) {
		Values values;
		f->ToObject(&values);
		if (this->m_First == nullptr)
			CreateFirst(values);
		else
		{
			m_Current = m_First;
			while (true) {
				if (CompareDates(&m_Current->m_Date, &values.m_Date) && m_Current->m_Right != nullptr)
					Right();
				else if (CompareDates(&m_Current->m_Date, &values.m_Date) && m_Current->m_Right == nullptr)
				{
					AddRight(values);
					break;
				}
				else if (!CompareDates(&m_Current->m_Date, &values.m_Date) && m_Current->m_Left != nullptr)
					Left();
				else
				{
					AddLeft(values);
					break;
				}
			}
		}
	}

}

bool Tree::CompareDates(const std::string* date_root, const std::string* date_new)
{
	const char* dd_root[2];
	const char* mm_root[2];
	const char* yyyy_root[4];
	const char* dd_new[2];
	const char* mm_new[2];
	const char* yyyy_new[4];


	for (int i = 0; i < 2; i++)
	{
		dd_root[i] = &date_root->at(i);
		dd_new[i] = &date_new->at(i);
	}
	for (int i = 0; i < 2; i++)
	{
		mm_root[i] = &date_root->at(i + 3);
		mm_new[i] = &date_new->at(i + 3);
	}
	for (int i = 0; i < 4; i++)
	{
		yyyy_root[i] = &date_root->at(i + 6);
		yyyy_new[i] = &date_new->at(i + 6);
	}

	if (std::stoi(*yyyy_new) < std::stoi(*yyyy_root))
		return false;
	else if (std::stoi(*yyyy_new) > std::stoi(*yyyy_root))
		return true;
	else if (std::stoi(*yyyy_new) == std::stoi(*yyyy_root))
	{
		if (std::stoi(*mm_new) < std::stoi(*mm_root))
			return false;
		else if (std::stoi(*mm_new) > std::stoi(*mm_root))
			return true;
		else if (std::stoi(*mm_new) == std::stoi(*mm_root))
		{
			if (std::stoi(*dd_new) < std::stoi(*dd_root))
				return false;
			else if (std::stoi(*dd_new) > std::stoi(*dd_root))
				return true;
			else
				return true;
		}
	}

}

bool Tree::Printed()
{
	return m_Current->m_Printed;
}

void Tree::AddByKey(const Values& human)
{
	m_Current = m_First;
	while (true) {
		if (CompareDates(&m_Current->m_Date, &human.m_Date) && m_Current->m_Right != nullptr)
			Right();
		else if (CompareDates(&m_Current->m_Date, &human.m_Date) && m_Current->m_Right == nullptr)
		{
			AddRight(human);
			break;
		}
		else if (!CompareDates(&m_Current->m_Date, &human.m_Date) && m_Current->m_Left != nullptr)
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
		if (m_Current->m_Right != nullptr && !m_Current->m_Right->m_Printed)
		{
			Right();
			LeftMost();
			GetValue('a');
		}
		else {
			Parent();
			if (Printed())
			{
				if (m_Current == m_First && (m_Current->m_Right == nullptr || m_Current->m_Right->m_Printed))
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
		if (m_Current->m_Right != nullptr && m_Current->m_Right->m_Printed)
		{
			Right();
			LeftMost();
			m_Current->m_Printed = false;
		}
		else {
			Parent();
			if (!Printed())
			{
				if (m_Current == m_First && (m_Current->m_Right == nullptr || !m_Current->m_Right->m_Printed))
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
		while (m_Current->m_Left != nullptr && !m_Current->m_Left->m_Printed)
		{
			Left();
			GetValue('a');
		}
		if(m_Current->m_Left == nullptr && (m_Current->m_Right == nullptr || !m_Current->m_Right->m_Printed))
			printf("**\n");
		if (m_Current->m_Right != nullptr && !m_Current->m_Right->m_Printed)
		{
			Right();
			GetValue('a');
			continue;
		}
		if(m_Current->m_Right == nullptr)
			printf("**\n");
		Parent();
		if (m_Current == m_First && m_Current->m_Right->m_Printed)
			break;
	}
	ResetPrint();
}