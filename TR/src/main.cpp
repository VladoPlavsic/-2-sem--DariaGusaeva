#include "logging/console.h"
#include "additional/filereader.h"
#include <windows.h>

void MainHeader() {
	printf("=====================================================\n"
		   "������������! ���������� �������� �������!\n"
		   "��������� ������:\n"
		   "1) �� ������ ���������� ���� ����������� ������� ������\n"
		   "2) �� ������ ������������� �������\n"
		   "E) ����� �������� ��������� \n"
		   "=====================================================\n");
}

int main()
{
	setlocale(LC_ALL, "Russian");

	MainHeader();
	char task;
	std::cin >> task;
	while (task != 'E') {
		if (task == '1')
			ProgramLoop(&task);
		else if (task == '2')
			ProgramLoop(&task);
		else
			printf("�������� ����! \n");
		MainHeader();
		std::cin >> task;
	}
}