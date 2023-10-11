#pragma once
#include "Class.h"

void Show_menu();

int Check_int();

void Add_matrix(vector<vector<double>>& Matrix);

void Sort_handler(vector<vector<double>> arr);

bool File_exists(string Filename);
bool Only_read(string Filename);
bool Is_valid_filename(const string& Filename);
bool Ñheck_empty_file(ifstream& file);