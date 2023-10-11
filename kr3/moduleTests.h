#pragma once

#include "Class.h"
#include "Interface.h"

void EnterMatrixFromFile(vector<vector<double>>& arrOrig, string filePath);
void CopyMatrix(vector<vector<double>>& a, vector<vector<double>>& b);
void CompleteModuleTests();
bool AreMatrixEqual(vector<vector<double>>& a, vector<vector<double>>& b);