#include "Class.h"


ISort::ISort() {
	comparisons = 0;
	permutations = 0;
}

int ISort::GetNumOfComparisons() const {
	return comparisons;
}

int ISort::GetNumOfPermutations() const {
	return permutations;
}

void ISort::printInfo() {
	cout << comparisons << endl;
	cout << permutations << endl;
}

void ISort::print(const vector<vector<double>>& arr) const {

	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "----------" << endl;
}

void ISort::Clear() {
	comparisons = 0;
	permutations = 0;
}

string BubbleSort::Name() {  //override проверяет переопределена ли функция, а final запрещает переопределять эту функцию в дальнейшем
	return "BubbleSort";
}

void BubbleSort::Sort(vector<vector<double>>& arr) {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	print(arr);

	// Сортировка четных столбцов по убыванию
	for (int col = 1; col < cols; col += 2) {
		for (int i = 0; i < rows - 1; i++) {
			for (int j = 0; j < rows - i - 1; j++) {
				if (arr[j][col] < arr[j + 1][col]) {
					// Обмен элементов
					swap(arr[j][col], arr[j + 1][col]);
					permutations++;
				}
				comparisons++;
			}
		}
	}

	/*print(arr);*/

	// Сортировка каждой строки по убыванию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols - 1; j++) {
			for (int k = 0; k < cols - j - 1; k++) {
				if (arr[i][k] < arr[i][k + 1]) {
					// Обмен элементов
					swap(arr[i][k], arr[i][k + 1]);
					permutations++;
				}
				comparisons++;
			}
		}
	}

	/*print(arr);*/
}

string SelectionSort::Name() {
	return "SelectionSort";
}

void SelectionSort::Sort(vector<vector<double>>& arr) {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию
	for (int col = 1; col < cols; col += 2) {
		for (int i = 0; i < rows - 1; i++) {
			int max_idx = i;
			for (int j = i + 1; j < rows; j++) {
				if (arr[j][col] > arr[max_idx][col]) {
					max_idx = j;
				}
				comparisons++;
			}
			if (max_idx != i) {
				// Обмен элементов
				swap(arr[i][col], arr[max_idx][col]);
				permutations++;
			}
		}
	}

	// Сортировка каждой строки по убыванию методом отбора (Selection Sort)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols - 1; j++) {
			int max_idx = j;
			for (int k = j + 1; k < cols; k++) {
				if (arr[i][k] > arr[i][max_idx]) {
					max_idx = k;
				}
				comparisons++;
			}
			if (max_idx != j) {
				// Обмен элементов
				swap(arr[i][j], arr[i][max_idx]);
				permutations++;
			}
		}
	}
}

string InsertionSort::Name() {
	return "InsertionSort";
}

void InsertionSort::Sort(vector<vector<double>>& arr) {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом вставки
	for (int col = 1; col < cols; col += 2) {
		for (int i = 1; i < rows; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (arr[j][col] < arr[j + 1][col]) {
					swap (arr[j][col], arr[j + 1][col]);
					comparisons++;
					permutations++;
				}
				else { comparisons++; break; }
			}
			
		}
	}

	// Сортировка каждой строки по убыванию методом вставки (Insertion Sort)
	for (int i = 0; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			for (int k = j - 1; k >= 0; k--) {
				if (arr[i][k] < arr[i][k + 1]) {
					swap(arr[i][k], arr[i][k + 1]);
					comparisons++;
					permutations++;
				}
				else { comparisons++; break; }
			}
			
		}
	}
}

string ShellSort::Name() {
	return "ShellSort";
}

void ShellSort::Sort(vector<vector<double>>& arr) {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом Шелла
	for (int col = 1; col < cols; col += 2) {
		for (int gap = rows / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < rows; i++) {
				double temp = arr[i][col];
				int j;
				for (j = i; j >= gap; j -= gap ) {
					if (arr[j - gap][col] < temp) {
						arr[j][col] = arr[j - gap][col];
						++permutations;
						++comparisons;
					}
					else {
						comparisons++;
						break;
					}
				}
				arr[j][col] = temp;
			}
		}
	}

	// Сортировка каждой строки по убыванию методом Шелла
	for (int i = 0; i < rows; i++) {
		for (int gap = cols / 2; gap > 0; gap /= 2) {
			for (int j = gap; j < cols; j++) {
				double temp = arr[i][j];
				int k;
				for (k = j; k >= gap ; k -= gap) {
					if (arr[i][k - gap] < temp) {
						arr[i][k] = arr[i][k - gap];
						++permutations;
						++comparisons;
					}
					else {
						comparisons++;
						break;
					}
				}
				arr[i][k] = temp;
			}
		}
	}
}

string QuickSort::Name() {
	return "QuickSort";
}

void QuickSort::QuickSortColumn(vector<vector<double>>& arr, int col, int low, int high) {
	if (low < high) {
		int pivotIdx = PartitionColumn(arr, col, low, high);
		QuickSortColumn(arr, col, low, pivotIdx - 1);
		QuickSortColumn(arr, col, pivotIdx + 1, high);
	}
}

int QuickSort::PartitionColumn(vector<vector<double>>& arr, int col, int low, int high) {
	double pivot = arr[high][col];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		comparisons++;
		if (arr[j][col] > pivot) {
			i++;
			swap(arr[i][col], arr[j][col]);
			permutations++;
		}
	}
	swap(arr[i + 1][col], arr[high][col]);
	permutations++;
	return i + 1;
}

void QuickSort::QuickSortString(vector<vector<double>>& arr, int row, int low, int high) {
	if (low < high) {
		int pivotIdx = PartitionString(arr, row, low, high);
		QuickSortString(arr, row, low, pivotIdx - 1);
		QuickSortString(arr, row, pivotIdx + 1, high);
	}
}

int QuickSort::PartitionString(vector<vector<double>>& arr, int row, int low, int high) {
	double pivot = arr[row][high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		comparisons++;					
		if (arr[row][j] > pivot) {
			i++;
			swap(arr[row][i], arr[row][j]);
			permutations++;
		}
	}
	swap(arr[row][i + 1], arr[row][high]);
	permutations++;
	return i + 1;
}

void QuickSort::Sort(vector<vector<double>>& arr) {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом быстрой сортировки 
	for (int col = 1; col < cols; col += 2) {
		QuickSortColumn(arr, col, 0, rows - 1);
	}

	// Сортировка каждой строки по убыванию методом быстрой сортировки
	for (int row = 0; row < rows; row++) {
		QuickSortString(arr, row, 0, cols - 1);
	}
}