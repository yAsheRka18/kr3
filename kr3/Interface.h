#pragma once
#include "Class.h"

void Show_menu();
int Check_int();
string EnterFilePath();
void InputFromFile(vector<vector<double>>& arrOrig);
int EnterNum(const string& msg);
void InputFromConsole(vector<vector<double>>& arrOrig);
vector<vector<double>> AM_random();
void Save_to_file(
	string Filename, BubbleSort bs, SelectionSort ss, InsertionSort is, ShellSort shells, QuickSort qs,
	vector<vector<double>>& matrix,
	vector<vector<double>>& matrixFirst
);
void Add_matrix(vector<vector<double>>& Matrix);
void Sort_handler(vector<vector<double>> arr);
bool File_exists(string Filename);
bool Only_read(string Filename);
bool Is_valid_filename(const string& Filename);
bool Ñheck_empty_file(ifstream& file);