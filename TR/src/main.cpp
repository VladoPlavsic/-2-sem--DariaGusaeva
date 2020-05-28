#define _CRT_SECURE_NO_WARNINGS
#include "list/tree.h"

Values CreateValues()
{
	Values values;
	printf("Введите имя!\n");
	std::cin >> values.m_Name;
	printf("Введите фамилию!\n");
	std::cin >> values.m_LastName;
	printf("Введите отчество!\n");
	std::cin >> values.m_MiddleName;
	printf("Введите дату рождения!\n");
	std::cin >> values.m_Date;
	printf("Введите дату смерти!\n");
	std::cin >> values.m_Death;
	printf("Введите место рождения!\n");
	std::cin >> values.m_Place;
	return values;
}

std::string GetString(const char value[10])
{
	printf("Введите %c\n", &value);
	std::string str;
	std::cin >> str;
	std::cin.clear();
	return str;
}

void Header()
{
	printf("\
	-проверка на пустоту дерева : 1\n\
	-создание пустого дерева : 2\n \
	-сделать текущим корень дерева : 3\n\
	-сделать текущим левое поддерево(от текущей вершины) : 4\n\
	-сделать текущим правое поддерево(от текущей вершины) : 5\n\
	-сделать текущим родительскую вершину для текущей вершины : 6\n\
	-узнать значение текущей вершины : 7\n\
	-изменить значение текущей вершины : 8\n\
	-создать левое поддерево для текущей вершины : 9\n\
	-создать правое поддерево для текущей вершины : A\n\
	-очистить консолу : C\n\
	-закончит : E\n\
	");
}

void Choice()
{
	printf("\
					Если хотите изменит вся значения нажмите : 0\n\
					Для измененися именм : 1\n\
					Для измененися фамилии : 2\n\
					Для измененися отчества : 3\n\
					Для измененися дати рождения : 4\n\
					Для измененися дати смерти : 5\n\
					Для измененися места рождения : 6\n\
					Сброс : E\n\
				");
}

int main()
{
	Tree *tree = new Tree();
	bool created = false;
	Header();
	unsigned char choice;
	std::cin >> choice;
	while (choice != 'E') {
		if (choice != '2' && choice != 'E' && !created)
		{
			printf("Сначала создайте дерево! №2!\n");
			scanf("%c", &choice);
			continue;
		}
		switch (choice)
		{
		case '1':
			if (tree->CheckIfEmpty())
			{
				printf("Дерево пустое\n");
				break;
			}
			printf("Дерево не пустое\n");
			break;
		case '2':
			if (!created)
			{
				{tree->CreateFirst(CreateValues()); }
				printf("Создан первый элемент\n");
				created = true;
				break;
			}
			printf("Дерево уже существует\n");
			break;
		case '3':
			tree->Parent();
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
			tree->GetValue();
			break;
		case '8':
		{
			Choice();
			char c;
			std::cin >> c;
			switch (c)
			{
			case '0':
			{
				tree->ChangeAll(CreateValues());
			}
				break;
			case '1':
				tree->ChangeName(&GetString("имя"));
				break;
			case '2':
				tree->ChangeLastName(&GetString("фамилию"));
				break;
			case '3':
				tree->ChangeSurname(&GetString("отчество"));
				break;
			case '4':
				tree->ChangeDate(&GetString("дату рожления"));
				break;
			case '5':
				tree->ChangeDeath(&GetString("дату смерти"));
				break;
			case '6':
				tree->ChangePlace(&GetString("место рождения"));
				break;
			case 'E': printf("Cброс");
				break;
			default:
				printf("Неверный ввод! Cброс");
				break;
			}
		}
			break;
		case '9':
		{
			tree->AddLeft(CreateValues());
		}
			break;
		case 'A':
		{
			tree->AddRight(CreateValues());
		}
			break;
		case 'C':
			system("CLS");
			Header();
			break;
		default:
			break;
		}
		scanf("%c", &choice);
	}


}