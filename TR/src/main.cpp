#include "logging/console.h"
#include "additional/filereader.h"
#include <windows.h>

void MainHeader() {
	printf("=====================================================\n"
		   "Здравствуйте! Пожалуйстя выберите задание!\n"
		   "«Бинарное дерево»:\n"
		   "1) на основе ссылочного типа «Нелинейный связный список»\n"
		   "2) на основе динамического массива\n"
		   "E) чтобы закончит программу \n"
		   "=====================================================\n");
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);

	MainHeader();
	char task;
	std::cin >> task;
	while (task != 'E') {
		if (task == '1')
			ProgramLoop(&task);
		else if (task == '2')
			ProgramLoop(&task);
		else
			printf("Неверный ввод!");
		MainHeader();
		std::cin >> task;
	}
}