#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string inputPuth = "input.txt";

class Graph {
private:
	vector<vector<int>> adjMatrix;
	vector<vector<int>> adjList;
	vector<bool> label;
	int _matrSize;

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

	void lableInit() {
		label.resize(_matrSize, false);
	}
	// This function returnes label to false state
	void lableReload() {
		for (int i = 0; i < label.size(); i++)
			label[i] = false;
	}

public:
	// TODO: сделать возможность ввода данных из текстового файла и с клавиатуры
	Graph() {
		ifstream fin;
		fin.open(inputPuth);
		fin >> _matrSize;

		adjMatrix.resize(_matrSize, vector<int>(_matrSize));

		for (int i = 0; i < _matrSize; i++)
			for (int j = 0; j < _matrSize; j++)
				fin >> adjMatrix[i][j];

		createAdjList();
		lableInit();
	}

	~Graph() {
		cout << "Goodbye!" << endl;
		// Distructure for vector. Is it necessary? 
		//delete[] label;
	}

	void printMatrix() {
		for (int i = 0; i < _matrSize; i++, cout << endl)
			for (int j = 0; j < _matrSize; j++)
				cout << adjMatrix[i][j];
	}

	void printAdjList() {
		for (int i = 0; i < _matrSize; i++, cout << endl)
			for (int j = 0; j < adjList[i].size(); j++)
				cout << adjList[i][j];
	}

	// this function print dfs trace
	void dfs(int vertexNum) {
		cout << vertexNum << " ";
		label[vertexNum] = true;
		for (auto iter : adjList[vertexNum])
			if (label[iter] == false) dfs(iter);
	}

};

int main()
{
	Graph g1;
	g1.printMatrix();
	g1.printAdjList();
	g1.dfs(1); 
	vector<bool> v;
	v.resize(4, false);
}