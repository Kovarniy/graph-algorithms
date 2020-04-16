#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string inputPuth = "input.txt";
vector<bool> lable;

class Graph {
private: 
	vector<vector<int>> adjMatrix;
	vector<vector<int>> adjList;
	int _matrSize;
	ifstream fin;

public:

	Graph(int matrSize) {
		_matrSize = matrSize;

		fin.open(inputPuth);
		for (int i = 0; i < _matrSize; i++)
			for (int j = 0; j < _matrSize; j++)
				fin >> adjMatrix[i][j];
	}

	void createAdjList() {
		adjList.resize(_matrSize, vector<int>());
		for (int i = 0; i < _matrSize; i++) {
			// j = i + 1; - небольшая оптимизация, для того чтобы обохоидть только верхнюю часть матрицы
			for (int j = i + 1; j < _matrSize; j++) {
				if (adjMatrix[i][j] > 0) {
					adjList[i].push_back(j);
					adjList[j].push_back(i);
				}
			}
		}
	}


};


// TODO: продумать структуру фунуций. Нужно ли передвать размер? т.к. мы работает с вектором, а не массивом
// Нужно ли делать шаблонные функции? 
void printMatrix (int matrSize, vector<vector<int>> matrix) {
	for (int i = 0; i < matrSize; i++, cout << endl)
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j];
}

vector<vector<int>> createAdjList (int matrSize, vector<vector<int>> matrix) {
	vector<vector<int>> adjList(matrSize, vector<int>());
	for (int i = 0; i < matrSize; i++) {
		// j = i + 1; - небольшая оптимизация, для того чтобы обохоидть только верхнюю часть матрицы
		for (int j = i + 1; j < matrSize; j++) {
			if (matrix[i][j] > 0)
			{
				adjList[i].push_back(j);
				adjList[j].push_back(i);
			}
		}
	}
	return adjList;
}

// adjList - список смежности
void dfs (int vertexNum, vector<vector<int>> adjList) {
	cout << vertexNum << " ";
	lable[vertexNum] = true;
	for (auto iter : adjList[vertexNum])
		if (lable[iter] == false) dfs(iter, adjList);
		
}

int main ()
{
/*
	ifstream fin;
	fin.open(inputPuth);
	int matrSize;
	
	fin >> matrSize;
	vector<vector<int>> G(matrSize, vector<int>(matrSize));
	lable.resize(matrSize, false);
	
	for (int i = 0; i < matrSize; i++)
		for (int j = 0; j < matrSize; j++)
			fin >> G[i][j];
	
	printMatrix(matrSize, G);
	vector<vector<int>> adjList = createAdjList(matrSize, G);
	printMatrix(matrSize, adjList);
	dfs(0, adjList);
*/

	Graph g(1);

}

