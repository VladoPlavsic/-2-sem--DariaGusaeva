#pragma once

#include <iostream>
#include <string>

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

	bool m_Printed = false;

	//связы
	Human* m_Left;
	Human* m_Right;
	Human* m_Parent;

	//конструктор
	Human(const Values& values, Human* left, Human* right, Human* parent)
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

};

struct Tree {

	Human* m_First;
	Human* m_Current;

	//создание пустого дерева
	void CreateFirst(const Values& value);
	//сделать текущим корень дерева;
	void Root();
	//сделать текущим левое поддерево
	void Left();
	//сделать текущим правое поддерево 
	void Right();
	//сделать текущим родительскую вершину для текущей вершины
	void Parent();
	//узнать значение текущей вершины;
	void GetValue(const char& c);
	void ChangeName(std::string* name);
	void ChangeSurname(std::string* middleName);
	void ChangeLastName(std::string* lastName);
	void ChangeDate(std::string* date);
	void ChangeDeath(std::string* death);
	void ChangePlace(std::string* place);
	//изменить значение текущей вершины;
	void ChangeAll(const Values& human);
	//создать левое поддерево для текущей вершины;
	void AddLeft(const Values& human);
	//создать правое поддерево для текущей вершины;
	void AddRight(const Values& human);
	//проверка на пустоту дерева(поддерева, начинающегося с текущей вершины);
	bool CheckIfEmpty();
	//Удалить дерево
	void Delete();
	//Самый левый элемент
	void LeftMost();
	void CreateFromFile();
	bool CompareDates(const std::string* date_root, const std::string* date_new);
	void AddByKey(const Values& human);
	void PrintByAge();
	bool Printed();
	void PrintRoot();
	void ResetPrint();
};
