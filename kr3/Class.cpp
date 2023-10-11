#include "pfu.h"
#include "Class.h"


ISort::ISort() {
	comparisons = 0;
	permutations = 0;
}

inline int ISort::GetNumOfComparisons() const {
	return comparisons;
}

inline int ISort::GetNumOfPermutations() const {
	return permutations;
}

inline void ISort::printInfo() {
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

inline void ISort::Clear() {
	comparisons = 0; 
	permutations = 0;
}

virtual string BubbleSort::Name() override final {  //override проверяет переопределена ли функция, а final запрещает переопределять эту функцию в дальнейшем
	return "BubbleSort";
}

virtual void BubbleSort::Sort(vector<vector<double>>& arr) override final {
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

virtual string SelectionSort::Name() override final {
	return "SelectionSort";
}

virtual void SelectionSort::Sort(vector<vector<double>>& arr) override final {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию
	for (int col = 1; col < cols; col += 2) {
		for (int i = 0; i < rows - 1; i++) {
			int max_idx = i;
			for (int j = i + 1; j < rows; j++) {
				comparisons++;
				if (arr[j][col] > arr[max_idx][col]) {
					max_idx = j;
				}
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
				comparisons++;
				if (arr[i][k] > arr[i][max_idx]) {
					max_idx = k;
				}
			}
			if (max_idx != j) {
				// Обмен элементов
				swap(arr[i][j], arr[i][max_idx]);
				permutations++;
			}
		}
	}
}

virtual string InsertionSort::Name() override final {
	return "InsertionSort";
}

virtual void InsertionSort::Sort(vector<vector<double>>& arr) override final {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом вставки
	for (int col = 1; col < coInsertionSort::ls; col += 2) {
		for (int i = 1; i < rows; i++) {
			double key = arr[i][col];
			int j = i - 1;
			while (j >= 0 && arr[j][col] < key) {
				arr[j + 1][col] = arr[j][col];
				j--;
				comparisons++;
				permutations++;
			}
			arr[j + 1][col] = key;
		}
	}

	// Сортировка каждой строки по убыванию методом вставки (Insertion Sort)
	for (int i = 0; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			double key = arr[i][j];
			int k = j - 1;
			while (k >= 0 && arr[i][k] < key) {
				arr[i][k + 1] = arr[i][k];
				k--;
				comparisons++;
				permutations++;
			}
			arr[i][k + 1] = key;
		}
	}
}

virtual string ShellSort::Name() override final {
	return "ShellSort";
}

virtual void ShellSort::Sort(vector<vector<double>>& arr) override final {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом Шелла
	for (int col = 1; col < cols; col += 2) {
		for (int gap = rows / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < rows; i++) {
				double temp = arr[i][col];
				int j;
				for (j = i; j >= gap && arr[j - gap][col] < temp; j -= gap) {
					arr[j][col] = arr[j - gap][col];
					comparisons++;
					permutations++;
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
				for (k = j; k >= gap && arr[i][k - gap] < temp; k -= gap) {
					arr[i][k] = arr[i][k - gap];
					comparisons++;
					permutations++;
				}
				arr[i][k] = temp;
			}
		}
	}
}

virtual string QuickSort::Name() override final {
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
		if (arr[j][col] >= pivot) {
			i++;
			swap(arr[i][col], arr[j][col]);
			permutations++;
		}
	}
	swap(arr[i + 1][col], arr[high][col]);
	permutations++;
	return i + 1;
}

virtual void QuickSort::Sort(vector<vector<double>>& arr) override final {
	int rows = (int)arr.size();
	int cols = (int)arr[0].size();

	// Сортировка четных столбцов по убыванию методом быстрой сортировки
	for (int col = 1; col < cols; col += 2) {
		QuickSortColumn(arr, col, 0, rows - 1);
	}

	// Сортировка каждой строки по убыванию методом быстрой сортировки
	for (int i = 0; i < rows; i++) {
		sort(arr[i].rbegin(), arr[i].rend());
	}
}