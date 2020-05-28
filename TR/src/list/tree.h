#pragma once

#include <iostream>

struct Values
{
	std::string m_MiddleName;
	std::string m_Name;
	std::string m_LastName;
	std::string m_Date;
	std::string m_Death;
	std::string m_Place;

};

struct Human {

	//информация о человеке
	std::string m_MiddleName;
	std::string m_Name;
	std::string m_LastName;
	std::string m_Date;
	std::string m_Death;
	std::string m_Place;

	//связы
	Human* m_Left;
	Human* m_Right;
	Human* m_Parent;

	//конструктор
	Human(Values values, Human* left, Human* right, Human* parent)
	{
		m_MiddleName = values.m_MiddleName;
		m_Name = values.m_Name;
		m_LastName = values.m_LastName;
		m_Date = values.m_Date;
		if (!values.m_Death.empty())
			m_Death = values.m_Death;
		if (!values.m_Place.empty())
			m_Place = values.m_Place;
		m_Left = left;
		m_Right = right;
		m_Parent = parent;
	}

	/*
	Human()
	{
		m_MiddleName = "";
		m_Name = "";
		m_LastName = "";
		m_Date = "";
		m_Death = "";
		m_Place = "";
		m_Left = nullptr;
		m_Right = nullptr;
		m_Parent = nullptr;
	}
	*/
};

struct Tree {

	Human* m_First;
	Human* m_Current;

	Tree();

	void CreateFirst(Values value);
	void Root();
	void Left();
	void Right();
	//сделать текущим родительскую вершину для текущей вершины(для удобства можно в способе 1 ввести третью связь – обратную связь с родительской вершиной, чтобы не искать ее по всему дереву – Трёхсвязный список);
	void Parent();
	//узнать значение текущей вершины;
	void GetValue();
	void ChangeName(std::string* name);
	void ChangeSurname(std::string* middleName);
	void ChangeLastName(std::string* lastName);
	void ChangeDate(std::string* date);
	void ChangeDeath(std::string* death);
	void ChangePlace(std::string* place);
	//изменить значение текущей вершины;
	void ChangeAll(Values human);
	//создать левое поддерево для текущей вершины;
	void AddLeft(Values human);
	//создать правое поддерево для текущей вершины;
	void AddRight(Values human);
	//проверка на пустоту дерева(поддерева, начинающегося с текущей вершины);
	bool CheckIfEmpty();
};

/*
- сделать текущим (по адресу в списке или индексу в массиве) корень дерева;
*/