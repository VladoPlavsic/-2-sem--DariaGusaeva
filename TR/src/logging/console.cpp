#define _CRT_SECURE_NO_WARNINGS
#include "console.h"

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
	while (!CheckDate(&values.m_Date))
	{
		printf("Пожалуйста введите верную дуту! \n");
		std::cin.clear();
		std::cin >> values.m_Date;
	}
	printf("Введите дату смерти!\n");
	std::cin >> values.m_Death;
	if (values.m_Death.size() > 1) {
		while (!CheckDate(&values.m_Death))
		{
			printf("Пожалуйста введите верную дуту! \n");
			std::cin.clear();
			std::cin >> values.m_Death;
			if (values.m_Death.size() <= 1)
				break;
		}
	}
	printf("Введите место рождения!\n");
	std::cin >> values.m_Place;
	return values;
}

std::string GetString(const std::string& value)
{
	printf("Введите %s", value.c_str());
	std::string str;
	std::cin >> str;
	std::cin.clear();
	return str;
}

void Header()
{
	printf("-проверка на пустоту дерева : 1\n"
		"-создание пустого дерева : 2\n"
		"-сделать текущим корень дерева : 3\n"
		"-сделать текущим левое поддерево(от текущей вершины) : 4\n"
		"-сделать текущим правое поддерево(от текущей вершины) : 5\n"
		"-сделать текущим родительскую вершину для текущей вершины : 6\n"
		"-узнать значение текущей вершины : 7\n"
		"-изменить значение текущей вершины : 8\n"
		"-создать левое поддерево для текущей вершины : 9\n"
		"-создать правое поддерево для текущей вершины : A\n"
		"-удалить дерево : D\n"
		"-создать упорядоченное по ключу : U\n"
		"-добавить один элемент, со значениями введенными в интерактивном режиме в упорядоченное дерево по ключу : N\n"
		"-вывод от самого старшего до самого младшего : O\n"
		"-вывести дерево левое-корень-правое : L\n"
		"-вывести дерево корень-левое-правое : P\n"
		"-создать неупорядоченное бинарное дерево : B\n"
		"-найти всех предков, кто родился в Москве. прожил не менее 70 лет : F\n"
		"-очистить консоль : C\n"
		"-закончить : E\n");
}

void Choice()
{
	printf("Если хотите изменить все значения нажмите : 0\n"
		"Для изменения имени : 1\n"
		"Для изменения фамилии : 2\n"
		"Для изменения отчества : 3\n"
		"Для изменения даты рождения : 4\n"
		"Для изменения даты смерти : 5\n"
		"Для изменения места рождения : 6\n"
		"Сброс : E\n");
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
			printf("Сначала создайте корень дерева! №2!\n");
			scanf(" %c", &choice);
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
			w->Print(tree);
			break;
		case '2':
			if (tree->CheckFirst())
			{
				{tree->CreateFirst(CreateValues()); }
				printf("Создан первый элемент\n");
				w->Print(tree);
				break;
			}
			printf("Корень уже существует\n");
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
				tree->ChangeName(&GetString("имя \n"));
				break;
			case '2':
				tree->ChangeLastName(&GetString("фамилию \n"));
				break;
			case '3':
				tree->ChangeSurname(&GetString("отчество \n"));
				break;
			case '4':
				tree->ChangeDate(&GetString("дату рождения \n"));
				break;
			case '5':
				tree->ChangeDeath(&GetString("дату смерти \n"));
				break;
			case '6':
				tree->ChangePlace(&GetString("место рождения \n"));
				break;
			case 'E': printf("Сброс \n");
				break;
			default:
				printf("Неверный ввод! Сброс \n");
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