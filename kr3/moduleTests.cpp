#include "moduleTests.h"

void EnterMatrixFromFile(vector<vector<double>>& arrOrig, string filePath) {

	int m = 0, n = 0;
	ifstream inputStream(filePath.c_str());
	vector<double> subArr;
	double variable;

	inputStream >> m >> n;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			inputStream >> variable;
			subArr.push_back(variable);
		}
		arrOrig.push_back(subArr);
		subArr.clear();
	}

	inputStream.close();
};

void CopyMatrix(vector<vector<double>>& a, vector<vector<double>>& b) {
	b.clear();
	vector<double> subArr;
	for (auto i = 0; i < a.size(); i++) {
		b.push_back(a[i]);
	}
};

bool AreMatrixEqual(vector<vector<double>>& a, vector<vector<double>>& b) {
	vector<double> subArrayForA;
	vector<double> subArrayForB;
	for (auto i = 0; i < a.size(); i++) {
		subArrayForA = a[i];
		subArrayForB = b[i];
		if (subArrayForA != subArrayForB) return false;
	}
	return true;
}


void CompleteModuleTests() {
	ifstream input, result;
	string inputPaths[5] = { "A.txt", "B.txt", "C.txt", "D.txt", "E.txt" };
	string resultPaths[5] = { "A1.txt", "B1.txt", "C1.txt", "D1.txt", "E1.txt" };
	bool isTaskOkay = true;
	bool isFilesMissing = false;

	for (size_t k = 0; k < 5; k++) {
		BubbleSort a;
		SelectionSort b;
		InsertionSort c;
		ShellSort d;
		QuickSort e;
		vector<vector<double>> matrix;
		vector<vector<double>> sortedMatrix;
		vector<vector<double>> resultsMatrix;

		input.open(inputPaths[k]);
		if (!input.is_open()) {
			cout << "Ошибка при открытии файла " << inputPaths[k] << endl;
			isFilesMissing = true;
			continue;
		}
		result.open(resultPaths[k]);
		if (!result.is_open()) {
			cout << "Ошибка при открытии файла " << resultPaths[k] << endl;
			isFilesMissing = true;
			continue;
		}
		result.close();
		input.close();

		EnterMatrixFromFile(matrix, inputPaths[k]);
		CopyMatrix(matrix, sortedMatrix);
		EnterMatrixFromFile(resultsMatrix, resultPaths[k]);

		if (matrix.size() != resultsMatrix.size() or matrix[0].size() != resultsMatrix[0].size()) {
			isTaskOkay = false;
			cout << "Не совпадают размеры матрицы в файлах " << inputPaths[k] << " и " << resultPaths[k] << endl;
		}
		else {
			CopyMatrix(matrix, sortedMatrix);
			a.Sort(sortedMatrix);
			if (!AreMatrixEqual(sortedMatrix,resultsMatrix)) {
				isTaskOkay = false;
				cout << "Сортировка пузырьком работает некорректно." << endl;
			}
			CopyMatrix(matrix, sortedMatrix);
			b.Sort(sortedMatrix);
			if (!AreMatrixEqual(sortedMatrix, resultsMatrix)) {
				isTaskOkay = false;
				cout << "Сортировка выбором работает некорректно." << endl;
			}
			CopyMatrix(matrix, sortedMatrix);
			c.Sort(sortedMatrix);
			if (!AreMatrixEqual(sortedMatrix, resultsMatrix)) {
				isTaskOkay = false;
				cout << "Сортировка вставками работает некорректно." << endl;
			}
			CopyMatrix(matrix, sortedMatrix);
			d.Sort(sortedMatrix);
			if (!AreMatrixEqual(sortedMatrix, resultsMatrix)) {
				isTaskOkay = false;
				cout << "Сортировка Шелла работает некорректно." << endl;
			}
			CopyMatrix(matrix, sortedMatrix);
			e.Sort(sortedMatrix);
			if (!AreMatrixEqual(sortedMatrix, resultsMatrix)) {
				isTaskOkay = false;
				cout << "Быстрая сортировка работает некорректно." << endl;
			}
		}

		matrix.clear();
		sortedMatrix.clear();
		resultsMatrix.clear();

	}
	if (isTaskOkay && !isFilesMissing) {
		cout << "Задание работает корректно." << endl;
	}
	if (isFilesMissing) {
		cout << "Невозможно выполнить тесты, отсутсвуют файлы с данными." << endl;
	}
};