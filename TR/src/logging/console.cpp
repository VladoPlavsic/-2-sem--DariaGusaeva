#define _CRT_SECURE_NO_WARNINGS
#include "console.h"

Values CreateValues()
{
	Values values;
	printf("������� ���!\n");
	std::cin >> values.m_Name;
	printf("������� �������!\n");
	std::cin >> values.m_LastName;
	printf("������� ��������!\n");
	std::cin >> values.m_MiddleName;
	printf("������� ���� ��������!\n");
	std::cin >> values.m_Date;
	while (!CheckDate(&values.m_Date))
	{
		printf("���������� ������� ������ ����! \n");
		std::cin.clear();
		std::cin >> values.m_Date;
	}
	printf("������� ���� ������!\n");
	std::cin >> values.m_Death;
	if (values.m_Death.size() > 1) {
		while (!CheckDate(&values.m_Death))
		{
			printf("���������� ������� ������ ����! \n");
			std::cin.clear();
			std::cin >> values.m_Death;
			if (values.m_Death.size() <= 1)
				break;
		}
	}
	printf("������� ����� ��������!\n");
	std::cin >> values.m_Place;
	return values;
}

std::string GetString(const std::string& value)
{
	printf("������� %s", value.c_str());
	std::string str;
	std::cin >> str;
	std::cin.clear();
	return str;
}

void Header()
{
	printf("-�������� �� ������� ������ : 1\n"
		"-�������� ������� ������ : 2\n"
		"-������� ������� ������ ������ : 3\n"
		"-������� ������� ����� ���������(�� ������� �������) : 4\n"
		"-������� ������� ������ ���������(�� ������� �������) : 5\n"
		"-������� ������� ������������ ������� ��� ������� ������� : 6\n"
		"-������ �������� ������� ������� : 7\n"
		"-�������� �������� ������� ������� : 8\n"
		"-������� ����� ��������� ��� ������� ������� : 9\n"
		"-������� ������ ��������� ��� ������� ������� : A\n"
		"-������� ������ : D\n"
		"-������� ������������� �� ����� : U\n"
		"-�������� ���� �������, �� ���������� ���������� � ������������� ������ � ������������� ������ �� ����� : N\n"
		"-����� �� ������ �������� �� ������ �������� : O\n"
		"-������� ������ �����-������-������ : L\n"
		"-������� ������ ������-�����-������ : P\n"
		"-������� ��������������� �������� ������ : B\n"
		"-����� ���� �������, ��� ������� � ������. ������ �� ����� 70 ��� : F\n"
		"-�������� ������� : C\n"
		"-��������� : E\n");
}

void Choice()
{
	printf("���� ������ �������� ��� �������� ������� : 0\n"
		"��� ��������� ����� : 1\n"
		"��� ��������� ������� : 2\n"
		"��� ��������� �������� : 3\n"
		"��� ��������� ���� �������� : 4\n"
		"��� ��������� ���� ������ : 5\n"
		"��� ��������� ����� �������� : 6\n"
		"����� : E\n");
}

template<typename T>
void Loop(T tree)
{
	bool created = false;
	Header();
	Writer* w = new Writer();
	unsigned char choice;
	std::cin >> choice;
	while (choice != 'E') {
		if (choice != '2' && choice != 'E' && choice != 'U'  && choice != 'B' && tree->CheckFirst())
		{
			printf("������� �������� ������ ������! �2!\n");
			scanf(" %c", &choice);
			continue;
		}
		switch (choice)
		{
		case '1':
			if (tree->CheckIfEmpty())
			{
				printf("������ ������\n");
				break;
			}
			printf("������ �� ������\n");
			w->Print(tree);
			break;
		case '2':
			if (tree->CheckFirst())
			{
				{tree->CreateFirst(CreateValues()); }
				printf("������ ������ �������\n");
				w->Print(tree);
				break;
			}
			printf("������ ��� ����������\n");
			break;
		case '3':
			tree->Root();
			break;
		case '4':
			tree->Left();
			break;
		case '5':
			tree->Right();
			break;
		case '6':
			tree->Parent();
			break;
		case '7':
			tree->GetValue('n');
			break;
		case '8':
		{
			Choice();
			char c;
			std::cin >> c;
			switch (c)
			{
			case '0':
			{tree->ChangeAll(CreateValues()); }
			break;
			case '1':
				tree->ChangeName(&GetString("��� \n"));
				break;
			case '2':
				tree->ChangeLastName(&GetString("������� \n"));
				break;
			case '3':
				tree->ChangeSurname(&GetString("�������� \n"));
				break;
			case '4':
				tree->ChangeDate(&GetString("���� �������� \n"));
				break;
			case '5':
				tree->ChangeDeath(&GetString("���� ������ \n"));
				break;
			case '6':
				tree->ChangePlace(&GetString("����� �������� \n"));
				break;
			case 'E': printf("����� \n");
				break;
			default:
				printf("�������� ����! ����� \n");
				break;
			}
		}
			w->Print(tree);
			break;
		case '9':
			{tree->AddLeft(CreateValues()); }
			w->Print(tree);
			break;
		case 'A':
			{tree->AddRight(CreateValues()); }
			w->Print(tree);
			break;
		case 'D':
			tree->Delete();
			break;
		case 'U':
			tree->CreateFromFile();
			w->Print(tree);
			break;
		case 'N':
		{tree->AddByKey(CreateValues()); }
			w->Print(tree);
		break;
		case 'O':
			tree->PrintByAge();
			w->Print(tree);
			break;
		case 'L':
			tree->PrintByAge();
			w->Print(tree);
			break;
		case 'P':
			tree->PrintRoot();
			w->Print(tree);
			break;
		case 'B':
			tree->GenTree();
			w->Print(tree);
			break;
		case 'F':
			tree->SearchGen();
			break;
		case 'C':
			system("CLS");
			Header();
			w->Print(tree);
			break;
		default:
			break;
		}
		scanf(" %c", &choice);
	}
}

void ProgramLoop(const char* task)
{
	if (*task == '1')
	{
		linked_tree::Tree* tree = new linked_tree::Tree();
		Loop(tree);
	}
	else if(*task == '2')
	{
		array_tree::Tree* tree = new array_tree::Tree();
		Loop(tree);
	}
}