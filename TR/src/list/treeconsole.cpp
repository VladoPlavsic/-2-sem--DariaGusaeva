#include "treeconsole.h"

namespace tree {
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

	std::string GetString(const std::string& value)
	{
		printf("Введите %s\n", value.c_str());
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
			"-добавить один элемент, со значениями введенными в интерактивном режиме (с клавиатуры) в упорядоченное дерево по ключу : N\n"
			"-вывод от самого старшего до самого младшего : O\n"
			"-вывести дерево левое-корень-правое : L\n"
			"-вывести дерево корень-левое-правое : P\n"
			//Реализовать
			"-создать неупорядоченное бинарное дерево : B\n"
			//-----------//
			"-очистить консолу : C\n"
			"-закончит : E\n");
	}

	void Choice()
	{
		printf("Если хотите изменит вся значения нажмите : 0\n"
			"Для измененися именм : 1\n"
			"Для измененися фамилии : 2\n"
			"Для измененися отчества : 3\n"
			"Для измененися дати рождения : 4\n"
			"Для измененися дати смерти : 5\n"
			"Для измененися места рождения : 6\n"
			"Сброс : E\n");
	}

	void ProgramLoop()
	{
		Tree* tree = new Tree();
		bool created = false;
		Header();
		unsigned char choice;
		std::cin >> choice;
		while (choice != 'E') {
			if (choice != '2' && choice != 'E' && choice != 'U' && tree->m_First == nullptr)
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
				break;
			case '2':
				if (tree->m_First == nullptr)
				{
					{tree->CreateFirst(CreateValues()); }
					printf("Создан первый элемент\n");
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
				{tree->AddLeft(CreateValues()); }
				break;
			case 'A':
				{tree->AddRight(CreateValues()); }
				break;
			case 'D':
				tree->Delete();
				break;
			case 'U':
				tree->CreateFromFile();
				break;
			case 'N':
				{tree->AddByKey(CreateValues()); }
				break;
			case 'O':
				tree->PrintByAge();
				break;
			case 'L':
				tree->PrintByAge();
				break;
			case 'P':
				tree->PrintRoot();
				break;
			case 'C':
				system("CLS");
				Header();
				break;
			default:
				break;
			}
			scanf(" %c", &choice);
		}

	}
}