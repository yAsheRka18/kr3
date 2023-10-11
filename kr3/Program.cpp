#include "Program.h"
#include "Interface.h"
#include "moduleTests.h"


enum Menu { Start__Delete_ = 1, MT_ = 2, Exit_ = 0 };

int Program() {
	setlocale(LC_ALL, "ru");
	system("chcp 1251");
	bool _exit = false;
	int User_choise = NULL;
	vector<vector<double>> matrix;

	do
	{
		system("pause");
		system("cls");

		Show_menu();

		User_choise = Check_int();

		switch (User_choise)
		{
		case Start__Delete_:
		{
			Add_matrix (matrix);
			if (matrix.size() != 0) Sort_handler(matrix);
			break;

		}
		case MT_:
		{
			CompleteModuleTests();
			break;
		}

		case Exit_:
		{
			_exit = true;
			break;
		}
		default: { cout << "ќшибка: вы выбрали несуществующий пункт меню! ѕвторите ввод. " << endl; system("pause"); break; }
		}
	} while (!_exit);
	return 0;
}
