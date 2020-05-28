#include "list/treeconsole.h"
#include "additional/filereader.h"

void Header() {
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
	Header();
	char task;
	std::cin >> task;
	while (task != 'E') {
		if (task == '1')
			tree::ProgramLoop();
		else if (task == '2')
			NULL;
		else
			printf("Неверный ввод!");
		Header();
		std::cin >> task;
	}


}