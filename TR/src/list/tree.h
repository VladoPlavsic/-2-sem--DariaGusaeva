#pragma once

#include "../additional/values.h"

namespace linked_tree {

	struct Human {

		//���������� � ��������
		std::string m_MiddleName;
		std::string m_Name;
		std::string m_LastName;
		std::string m_Date;
		std::string m_Death;
		std::string m_Place;

		bool m_Printed;

		//�����
		Human* m_Left;
		Human* m_Right;
		Human* m_Parent;

		//�����������
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
			m_Printed = values.m_Printed;
		}
	};

	struct Tree {

		Human* m_First;
		Human* m_Current;

		//��������� �����
		Human* CheckLeft();
		//��������� ������
		Human* CheckRight();
		//�������� �������
		Human* CheckCurrent();

		//�������� �� ������������� ������� ��������
		bool CheckFirst();

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