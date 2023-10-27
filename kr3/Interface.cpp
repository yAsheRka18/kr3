#include "Class.h"
#include "Interface.h"
#include "pfu.h"

enum _set { Manual_ = 1, From_file_ = 2, Random_, Exit_ = 0 };
enum _choise { Yes_ = 1, No_ = 2 };
enum _bool { True_ = 1, False_ = 2 };
enum _mode { Add_ = 1, Delete_and_add_ = 2 };

void Show_menu()
{
	cout << ">> Контрольная работа №3. Вариант №22Выполнена студентом 425 группы Роевой Алёны." << endl
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl
		<< "Необходимо составить программу для сортировки массива данных методами: " << endl
		<< "Пузырьковой, отбора, вставки, Шелла и быстрой сортировки. " << endl
		<< "Вывести на экран  неупорядоченный(один раз) и упорядоченные(для каждого из методов) массивы  данных." << endl << endl
		<< "Составить сравнительную таблицу эффективности методов, в которой  необходимо указать число сравнений и перестановок переменных в каждом  методе сортировки." << endl
		<< "Неупорядоченная матрица из N строк и M столбцов задается и заполняется  один раз(с клавиатуры, из файла или случайными числами), далее она  используется для каждого из методов сортировки." << endl
		<< "Упорядочить каждый четный столбец по убыванию, затем каждую строку по убыванию." << endl
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl
		<< endl
		<< ">> Выберете один из ниже указанных пунктов меню:" << endl
		<< ">> 1 - Начать работу программы." << endl
		<< ">> 2 - Провести модульные тесты." << endl
		<< ">> 0 - Заврешить работу программы" << endl;
}

int Check_int()
{
	int Input = 0;
	cin >> Input;
	while (cin.fail())
	{
		cout << "Некорректный ввод. Повторите попытку >>" << endl;
		cin.clear();
		cin.ignore(numeric_limits <streamsize>::max(), '\n');   //!!!
		cout << "Максимальное значение" << numeric_limits<streamsize>::max() << endl;
		cin >> Input;	
	}
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
	return Input;
}

string EnterFilePath()
{
    string Input;
    while (true)
    {
        getline(cin, Input);
        regex Pattern_the_empoty_input("(\\s*)");    // для поиска пустых строк или строк, состоящих только из пробелов (пустых символов)


        if (regex_match(Input, Pattern_the_empoty_input) == false)
        {
            regex Pattern_the_correct_symble("^[а-яА-ЯёЁa-zA-Z0-9/:._\\\\]+$");

            if (regex_match(Input, Pattern_the_correct_symble) == true)
            {
                regex Pattern_of_allowed_names("\\b(con|aux|prn|com|lpt|nul|Con|Aux|Prn|Com|Lpt|Nul|cOn|aUx|pRn|cOm|lPt|nUl|coN|auX|lpT|prN|coM|nuL|COn|AUx|PRn|COm|LPt|NUl|CoN|AuX|PrN|CoM|LpT|NuL|cON|aUX|pRN|cOM|lPT|nUL|CON|AUX|PRN|COM|LPT|NUL)\\b((\\.)*(\\w)*)*");

                if (regex_match(Input, Pattern_of_allowed_names) == false) return Input;

                else cout << "Ошибка: вы ввели зарезервированное имя. Повторите попытку ввода." << endl;
            }

            else cout << "Ошибка: вы ввели запрещенный символ. Повторите попытку ввода." << endl;
        }

        else  cout << "Ошибка: вы оставили ввод пустым. Повторите попытку ввода." << endl;
    }
}

void InputFromFile(vector<vector<double>>& arrOrig) {
    int m = 0, n = 0;

    vector<double> subArr;
    double variable;
	while (true) {
		string filePath = " ";
		filePath = EnterFilePath();
		ifstream inputStream(filePath.c_str());

		if (!inputStream.is_open() || Is_valid_filename(filePath) || !File_exists(filePath)) {
			cout << "Ошибка файла. Попробуйте снова." << endl;
			continue;
		}

            if (!(inputStream >> m || m < 1)) {
                cout << "Неверные данные из файла( некорректные данные 'rows' ) " << endl;
                continue;
            }
            if (!(inputStream >> n || n < 2)) {
                cout << "Неверные данные из файла( некорректные данные 'collums' ) " << endl;
                continue;
            }

            for (auto i = 0; i < m; ++i) {
                for (auto j = 0; j < n; ++j) {
                    if (inputStream >> variable) {
                        subArr.push_back(variable);
                    }
                    else {
                        cout << "Неверные данные из файла( некорректные значения матрицы ) " << endl;
                        arrOrig.clear();
                        continue;
                    }
                }
                arrOrig.push_back(subArr);
                subArr.clear();
            }

            inputStream.close();
            break;
    }
}


int EnterNum(const string& msg) {
	int item{};

	while (cout << msg && !(cin >> item)) {
		cin.clear();
		cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cout << endl << "Неправильный ввод. Попробуйте снова" << endl;
	}

	return item;
}

void InputFromConsole(vector<vector<double>>& arrOrig) {
	int m = 0, n = 0;

	vector<double> subArr;
	double variable;

	while (m <= 0) m = EnterNum("Введите количество строк ( rows > 0 ): ");
	while (n <= 1) n = EnterNum("Введите количество столбцов ( collums > 1 ): ");


	for (auto i = 0; i < m; ++i) {
		for (auto j = 0; j < n; ++j) {
			variable = EnterNum("arr[" + to_string(i + 1) + "][" + to_string(j + 1) + "] = ");
			subArr.push_back(variable);
		}
		arrOrig.push_back(subArr);
		subArr.clear();
	}
}



bool File_exists(string Filename)
{
	if (!_access(Filename.c_str(), 0)) return true; //проверка файла по заданному пути
	else return false;
}

bool Only_read(string Filename)
{
	if (_access(Filename.c_str(), 2)) return true; //проверка доступности файла 
	else return false;
}


bool Is_valid_filename(const string& Filename)
{
	regex pattern(".+\\.txt$"); //проверка имени файла на соответсвие шаблону 
	return !regex_match(Filename, pattern);
}


vector<vector<double>> AM_random()
{
	int Rows = NULL;
	int Columns = NULL;

	cout << "Введите количество строк матрицы: ";
	Rows = Check_int();
	while (Rows < 1)
	{
		cout << "Количество строк не может быть меньше единицы. Попробуйте ввести другое число." << endl;
		Rows = Check_int();
	}
	cout << "Введите количество столбцов матрицы: ";
	Columns = Check_int();
	while (Columns < 1)
	{
		cout << "Количество столбцов не может быть меньше единицы. Попробуйте ввести другое число." << endl;
		Columns = Check_int();
	}

	vector<vector<double>> matr;
	vector<double> submatr;

	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
			submatr.push_back(-100 + rand() % 201);
		}
		matr.push_back(submatr);
		submatr.clear();
	}

	return matr;
}

void Save_to_file(
	string Filename, BubbleSort bs, SelectionSort ss, InsertionSort is, ShellSort shells, QuickSort qs,
	vector<vector<double>>& matrix,
	vector<vector<double>>& matrixFirst
)
{
	ofstream file;
	bool _exit = false;
	system("cls");

	cout << "Выберите способ сохранения:" << endl << "1 - Записать данные в конец файла." << endl << "2 - Удалить данные из файла и записать." << endl;

	int User_choise = Check_int();
	do
	{
		switch (User_choise)
		{
		case Add_:
		{
			file.open(Filename, ios::app); //открывает файл для записи в конец файла
			_exit = true;
			break;
		}
		case Delete_and_add_:
		{
			file.open(Filename, ios::trunc);  //удаляет содержимое файла, если оно существует 
			_exit = true;
			break;
		}
		default: { cout << "Ошибка: вы выбрали несуществующий пункт меню! Пвторите ввод. " << endl; system("pause"); break; }
		}
	} while (!_exit);
	
	int numRows = matrixFirst.size();
	int numCols = matrixFirst[0].size();
	file << "Матрица отсортированная :" << '\n';
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			file << matrixFirst[i][j] << " ";
		}
		file << endl; // Переходим на новую строку после каждой строки матрицы
	}
	file << "-------------" << endl;
	numRows = matrix.size();
	numCols = matrix[0].size();
	file << "Матрица отсортированная :" << '\n';
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			file << matrix[i][j] << " ";
		}
		file << endl; // Переходим на новую строку после каждой строки матрицы
	}
	file << "Сравнительная таблица" << '\n' << "Вид сортировки\t\tКол-во сравнений\tКол-во перестановок" << '\n'
		<< "Сортировка пузырьком\t" << bs.GetNumOfComparisons() << "\t\t\t" << bs.GetNumOfPermutations() << '\n'
		<< "Сортировка выбором\t" << ss.GetNumOfComparisons() << "\t\t\t" << ss.GetNumOfPermutations() << '\n'
		<< "Сортировка вставками\t" << is.GetNumOfComparisons() << "\t\t\t" << is.GetNumOfPermutations() << '\n'
		<< "Сортировка Шелла\t" << shells.GetNumOfComparisons() << "\t\t\t" << shells.GetNumOfPermutations() << '\n'
		<< "Сортировка быстрая\t" << qs.GetNumOfComparisons() << "\t\t\t" << qs.GetNumOfPermutations() << '\n';
	file.close();
}

void Add_matrix(vector<vector<double>>& Matrix)
{
	bool _exit = false;
	int User_choise = NULL;

	do
	{
		system("cls");
		cout << "Выберите способ ввода информации: " << endl
			<< "1 - Вручную. " << endl
			<< "2 - Взять информацию с файла." << endl
			<< "3 - Заполнить матрицу случайными числами диапозоном от -100 до 100. " << endl;
		User_choise = Check_int();

		switch (User_choise)
		{
		case Manual_:
		{
			InputFromConsole(Matrix);
			_exit = true;
			break;
		}

		case From_file_:
		{
			ifstream Input_file;

			cout << "Введите путь к файлу" << endl;
			InputFromFile(Matrix);
			Input_file.close();

			_exit = true;

			break;
		}

		case Random_:
		{
			Matrix = AM_random();
			_exit = true;
			break;
		}

		case Exit_: {_exit = true; break; }

		default: { cout << "Ошибка: вы выбрали несуществующий пункт меню! Пвторите ввод. " << endl; system("pause"); break; }
		}
	} while (!_exit);
}

void Sort_handler(vector<vector<double>> arr) {
	vector<vector<double>> first = arr;
	vector<vector<double>> last;
	BubbleSort bs;
	SelectionSort ss;
	InsertionSort is;
	ShellSort shells;
	QuickSort qs;

	bs.Sort(first);
	cout << "--	--	--	--Cортировка пузырьком-	--	--	--" << endl << endl;
	bs.print(first);

	last = first;
	first = arr;

	ss.Sort(first);
	cout << "--	--	--	--Cортировка отбором--	--	--	--" << endl << endl;
	bs.print(first);
	if (last != first) { cout << "Error" << endl; return; }
	last = first;

	first = arr;

	is.Sort(first);
	cout << "--	--	--	--Cортировка вставкой--	--	--	--" << endl << endl;
	bs.print(first);
	if (last != first) { cout << "Error" << endl; return; }
	last = first;

	first = arr;

	shells.Sort(first);
	cout << "--	--	--	--Cортировка Шелла--	--	--	--" << endl << endl;
	bs.print(first);
	if (last != first) { cout << "Error" << endl; return; }
	last = first;

	first = arr;

	qs.Sort(first);
	cout << "--	--	--	--Быстрая сортировка--	--	--	--" << endl << endl;
	bs.print(first);
	if (last != first) { cout << "Error" << endl; return; }
	last = first;

	first = arr;

	stringstream outputStream;

	outputStream << setw(16) << "Name of sorting"
		<< setw(5) << " | "
		<< setw(16) << "Num of compares"
		<< setw(5) << " | "
		<< setw(16) << "Num of swaps"
		<< setw(5) << " | " << endl;

	outputStream << setw(16) << bs.Name()
		<< setw(5) << " | "
		<< setw(16) << bs.GetNumOfComparisons()
		<< setw(5) << " | "
		<< setw(16) << bs.GetNumOfPermutations()
		<< setw(5) << " | " << endl;

	outputStream << setw(16) << ss.Name()
		<< setw(5) << " | "
		<< setw(16) << ss.GetNumOfComparisons()
		<< setw(5) << " | "
		<< setw(16) << ss.GetNumOfPermutations()
		<< setw(5) << " | " << endl;

	outputStream << setw(16) << is.Name()
		<< setw(5) << " | "
		<< setw(16) << is.GetNumOfComparisons()
		<< setw(5) << " | "
		<< setw(16) << is.GetNumOfPermutations()
		<< setw(5) << " | " << endl;
	 
	outputStream << setw(16) << shells.Name()
		<< setw(5) << " | "
		<< setw(16) << shells.GetNumOfComparisons()
		<< setw(5) << " | "
		<< setw(16) << shells.GetNumOfPermutations()
		<< setw(5) << " | " << endl;

	outputStream << setw(16) << qs.Name()
		<< setw(5) << " | "
		<< setw(16) << qs.GetNumOfComparisons()
		<< setw(5) << " | "
		<< setw(16) << qs.GetNumOfPermutations()
		<< setw(5) << " | " << endl;

	cout << outputStream.str();

	cout << "Сохранить результаты?" << endl
		<< "1 - Да " << endl
		<< "2 - Нет " << endl;
	int Users_choise = Check_int();
	switch (Users_choise)
	{
	case Yes_:
	{
		ofstream file;
		string Filename;
		bool Filename_correct = false;
		do
		{
			system("cls");

			cout << "Введите путь к файлу. " << endl;
			Filename = EnterFilePath();


			if (Is_valid_filename(Filename))
			{
				cout << "Ошибка: неверный формат пути файла! Повторите попытку ввода." << endl;
				system("pause");
				continue;
			}


			if (!File_exists(Filename))
			{
				int Creat_the_new_file = NULL;
				bool Choise_entered = false;
				do
				{
					cout << "Внимание: файла не существует! Желаете создать новый файл с данным именем?" << endl << "1 - Да." << endl << "2 - Нет." << endl;
					Creat_the_new_file = Check_int();

					if (Creat_the_new_file == True_) { file.open(Filename); file.close(); Choise_entered = true; }

					else if (Creat_the_new_file == False_) Choise_entered = true;

					else { cout << "Ошибка: некорректной ввод! Повторите попытку ввода." << endl; system("pause"); }
				} while (!Choise_entered);

				if (Creat_the_new_file == False_) continue;
			}

			if (Only_read(Filename))
			{
				cout << "Ошибка: файл доступен только для чтения. Выберите другой файл." << endl;
				system("pause");
				continue;
			}

			Filename_correct = true;

		} while (!Filename_correct);

		Save_to_file(Filename, bs, ss, is, shells, qs, last, arr);
		last = first;
		break;
	}
	case No_: break;

	default: { cout << "Ошибка: вы выбрали несуществующий пункт меню! Пвторите ввод. " << endl; system("pause"); break; }
	}
}
