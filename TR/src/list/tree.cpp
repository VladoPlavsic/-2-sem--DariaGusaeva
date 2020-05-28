#include "tree.h"

Tree::Tree(){};

void Tree::CreateFirst(Values human)
{
	m_First = new Human(human, nullptr, nullptr, nullptr);
	m_Current = m_First;
}

void Tree::Root()
{
	m_Current = m_First;
}

void Tree::Left()
{
	if (m_Current->m_Left != nullptr) {
		m_Current = m_Current->m_Left;
		return;
	}
	printf("Левое поддерево несуществует!\n");
}

void Tree::Right()
{
	if (m_Current->m_Right != nullptr) {
		m_Current = m_Current->m_Right;
		return;
	}
	printf("Правое поддерево несуществует!\n");
}

//сделать текущим родительскую вершину для текущей вершины(для удобства можно в способе 1 ввести третью связь – обратную связь с родительской вершиной, чтобы не искать ее по всему дереву – Трёхсвязный список);
void Tree::Parent()
{
	if (m_Current->m_Parent != nullptr) {
		m_Current = m_Current->m_Parent;
		return;
	}
	printf("Вы уже пришли к корню дерева!\n");
}

//узнать значение текущей вершины;
void Tree::GetValue()
{
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
}

void Tree::ChangeSurname(std::string* middleName)
{
	m_Current->m_MiddleName = *middleName;
}

void Tree::ChangeLastName(std::string* lastName)
{
	m_Current->m_LastName = *lastName;
}

void Tree::ChangeDate(std::string* date)
{
	m_Current->m_Date = *date;
}

void Tree::ChangeDeath(std::string* death)
{
	m_Current->m_Death = *death;
}

void Tree::ChangePlace(std::string* place)
{
	m_Current->m_Place = *place;
}

//изменить значение текущей вершины;
void Tree::ChangeAll(Values human)
{
	m_Current->m_Name = human.m_Name;
	m_Current->m_LastName = human.m_LastName;
	m_Current->m_MiddleName = human.m_MiddleName;
	m_Current->m_Date = human.m_Date;
	if (!human.m_Death.empty())
		m_Current->m_Death = human.m_Death;
	if (!human.m_Place.empty())
		m_Current->m_Place = human.m_Place;
}

//создать левое поддерево для текущей вершины;
void Tree::AddLeft(Values human)
{
	m_Current->m_Left = new Human(human, nullptr, nullptr, m_Current);
}

//создать правое поддерево для текущей вершины;
void Tree::AddRight(Values human)
{
	m_Current->m_Right = new Human(human, nullptr, nullptr, m_Current);
}

//проверка на пустоту дерева(поддерева, начинающегося с текущей вершины);
bool Tree::CheckIfEmpty()
{
	return (m_Current->m_Left != nullptr || m_Current->m_Right != nullptr) ? false : true;
}
