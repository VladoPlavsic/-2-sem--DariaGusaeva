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

		//�������� �� ������������� ������� ��������
		bool CheckFirst();

		//��������� �����
		Values* CheckLeft();
		//��������� ������
		Values* CheckRight();
		//�������� �������
		Values* CheckCurrent();

		//�������� ������� ������
		void CreateFirst(const Values& value);
		//������� ������� ������ ������;
		void Root();
		//������� ������� ����� ���������
		void Left();
		//������� ������� ������ ��������� 
		void Right();
		//������� ������� ������������ ������� ��� ������� �������
		void Parent();
		//������ �������� ������� �������;
		void GetValue(const char& c);
		void ChangeName(std::string* name);
		void ChangeSurname(std::string* middleName);
		void ChangeLastName(std::string* lastName);
		void ChangeDate(std::string* date);
		void ChangeDeath(std::string* death);
		void ChangePlace(std::string* place);
		//�������� �������� ������� �������;
		void ChangeAll(const Values& human);
		//������� ����� ��������� ��� ������� �������;
		void AddLeft(const Values& human);
		//������� ������ ��������� ��� ������� �������;
		void AddRight(const Values& human);
		//�������� �� ������� ������(���������, ������������� � ������� �������);
		bool CheckIfEmpty();
		//������� ������
		void Delete();
		//����� ����� �������
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