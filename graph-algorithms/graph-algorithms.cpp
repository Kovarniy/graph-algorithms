#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <stack>

using namespace std;

string inputPuth = "input.txt";

class Graph {
private:
	vector<vector<int>> adjMatrix;
	vector<vector<int>> adjList;
	vector<int> algorithmTrace;
	// label need for check visited vertex
	vector<bool> label;
	// stack and queue help reloaded label
	queue<int> queForBfs;
	stack<int> stackForDfs;
	int _matrSize;
	int countAdjComp = 0;
	bool writeTrace = false;

	void initAdjList() {
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

	// this function print dfs trace
	void dfs(int vertexNum) {
		if (writeTrace) algorithmTrace.push_back(vertexNum);
		label[vertexNum] = true;
		for (auto iter : adjList[vertexNum])
			if (label[iter] == false) {
				stackForDfs.push(iter);
				dfs(iter);
				stackForDfs.pop();
			}
		//if (stackForDfs.empty()) lableReload();
	}

	// this function print bfs trace
	void bfs(int vertexNum) {
		if (writeTrace) algorithmTrace.push_back(vertexNum);
		label[vertexNum] = true;
		for (auto iter : adjList[vertexNum])
			if (label[iter] == false) {
				label[iter] = true;
				queForBfs.push(iter);
			}

		if (!queForBfs.empty())
		{
			// add firs queue element to buffer
			int buffer = queForBfs.front();
			// and remove it in queue
			queForBfs.pop();
			bfs(buffer);
		} /* else {
			lableReload();
		}*/	
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

		initAdjList();
		lableInit();
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

	vector<int> getBfsTrace(int vertex) {
		// Я не уверен, что это оптимальный метод очистки вектора
		if (!algorithmTrace.empty()) algorithmTrace.clear();
		writeTrace = true;
		dfs(vertex);
		writeTrace = false;
		return algorithmTrace;
	}

	vector<int> getDfsTrace(int vertex) { 
		if (!algorithmTrace.empty()) algorithmTrace.clear();
		writeTrace = true;
		bfs(vertex);
		writeTrace = false;
		return algorithmTrace;
	}

	// get count adjant compounents
	int getCountAdjComp() {	
		for (int i = 0; i < label.size(); i++) {
			if (label[i] == false) {
				bfs(i);
				countAdjComp++;
			}
		}
		if(queForBfs.empty()) {
			lableReload();
		}
		return countAdjComp;
	}

	// get optimal path 
	void getOptimalPath(int vertexA, int vertexB) {
		// TODO
	}

	bool haveLoop() {
		return 0;
	}

};

int main()
{
	Graph g1;
	g1.printMatrix();
	g1.printAdjList();	
	cout << "--------" << endl;
	cout << g1.getCountAdjComp();
	
	
}