#pragma once

#include "../additional/values.h"

namespace array_tree {

#define MAX_ARRAY_SIZE 100

	struct Tree {

		Values** m_Values = (Values**)malloc(MAX_ARRAY_SIZE * sizeof(Values));

		Tree()
		{
			memset(m_Values, 0, MAX_ARRAY_SIZE * sizeof(Values));
		}

		~Tree()
		{
			delete[] m_Values;
		}

		unsigned int m_Current = 0;

		//проверит на существование первого элемента
		bool CheckFirst();

		//проверить левый
		Values* CheckLeft();
		//проверить правый
		Values* CheckRight();
		//Проверит текущий
		Values* CheckCurrent();

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
		void GenTree();
		void SearchGen();
	};
}