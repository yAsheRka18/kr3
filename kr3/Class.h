#pragma once 
#include "pfu.h"

class ISort {
protected:
	int comparisons;
	int permutations;

public:
	ISort();

	virtual ~ISort() = default;

	virtual void Sort(vector<vector<double>>& arr) = 0;

	virtual string Name() = 0;

	inline int GetNumOfComparisons() const;

	inline int GetNumOfPermutations() const;

	inline void printInfo();

	void print(const vector<vector<double>>& arr) const;

	inline void Clear();
};

class BubbleSort : public ISort {
public:

	BubbleSort(): ISort();

	virtual ~BubbleSort() = default;

	virtual string Name() override final;
	
	virtual void Sort(vector<vector<double>>& arr) override final;
};

class SelectionSort : public ISort {
public:

	SelectionSort(): ISort();

	virtual ~SelectionSort() = default;

	virtual string Name() override final;

	virtual void Sort(vector<vector<double>>& arr) override final;
};

class InsertionSort : public ISort {
public:

	InsertionSort(): ISort();

	virtual ~InsertionSort() = default;

	virtual string Name() override final;

	virtual void Sort(vector<vector<double>>& arr) override final;
};

class ShellSort : public ISort {
public:

	ShellSort(): ISort();

	virtual ~ShellSort() = default;

	virtual string Name() override final;

	virtual void Sort(vector<vector<double>>& arr) override final;
};

class QuickSort : public ISort {
public:

	QuickSort(): ISort();

	virtual ~QuickSort() = default;

	virtual string Name() override final;

	void QuickSortColumn(vector<vector<double>>& arr, int col, int low, int high);
	int PartitionColumn(vector<vector<double>>& arr, int col, int low, int high);
	virtual void Sort(vector<vector<double>>& arr) override final;
};