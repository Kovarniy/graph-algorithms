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
	vector<vector<int>> connectCompunents;
	vector<int> algorithmTrace;
	// label need for check visited vertex
	vector<bool> label;
	// stack and queue help reloaded label
	queue<int> queForBfs;
	stack<int> stackForDfs;
	// aka count Vertex
	int _matrSize;
	//int countAdjComp = 0;
	bool writeTrace = false;
	int countEdges = 0;
	bool isWeighted = false;

	void matrixToList() {
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

	void listToMatrix() {
		adjMatrix.resize(adjList.size(), vector<int>(adjList.size(), 0));
		for (int i = 0; i < adjList.size(); i++) {
			for (int j = 0; j < adjList[i].size(); j++) {
				int indJ = adjList[i][j];
				adjMatrix[i][indJ] = 1;
			}
		}
	}

	void lableInit() {
		label.resize(_matrSize, false);
	}

	void initCountEdge() {
		for (int i = 0; i < adjList.size(); i++)
			countEdges += adjList[i].size();
	}

	// This function returnes label to false state
	void lableReload() {
		for (int i = 0; i < label.size(); i++)
			label[i] = false;
	}

	vector<int> bufferComp;
	// this function init sum of connection compounents and it solution in vector view
	void initAnyParameters() {
		for (int i = 0; i < label.size(); i++) {
			if (label[i] == false) {
				bfs(i);
				connectCompunents.push_back(bufferComp);
				bufferComp.resize(0, 0);
				// Данный параметр можно не считать, т.к. кол-во компонент связаности - это размер массива
				// con-ionComp
				//countAdjComp++;
			}
		}
		if (queForBfs.empty()) {
			lableReload();
		}
	}

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
				// formed vector of connection compinents
				bufferComp.push_back(iter);
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
	// Graph can be intialized wich adjacency matrix or list
	Graph(vector<vector<int>> v) {
		bool isMatrix = true;
		_matrSize = v.size();

		// Check for input vector is matrix or list
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v[i].size(); j++) {
				if (v[i][j] > 1) isWeighted = true;
			}
			if (v.size() != v[i].size()) {
				isMatrix = false;
				break;
			}
		}
		
		// check matrix or list
		if (isMatrix) {
			for (int i = 0; i < v.size(); i++)
				if (v[i][i] != 0) throw exception("it matrix has loop!");
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				for (int j = 0; j < v[i].size(); j++) {
					v[i][j] -= 1;
					if (v[i][j] > v.size())
						throw exception("Adjacency list is not correct");
				}
			}
		}

		if (isMatrix) {
			adjMatrix.resize(v.size(), vector<int>(v.size(),0));
			copy(v.begin(), v.end(), adjMatrix.begin());
			// init start parametres 
			matrixToList();
		}
		else {
			adjList.resize(v.size(), vector<int>());
			for (int i = 0; i < v.size(); i++)
				for (int j = 0; j < v[i].size(); j++)
					adjList[i].push_back(v[i][j]);
			listToMatrix();
		}
		lableInit();
		initCountEdge();
		initAnyParameters();
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
		lableReload();
		// Я не уверен, что это оптимальный метод очистки вектора
		if (!algorithmTrace.empty()) algorithmTrace.clear();
		writeTrace = true;
		bfs(vertex);
		writeTrace = false;
		return algorithmTrace;
	}

	vector<int> getDfsTrace(int vertex) { 
		lableReload();
		if (!algorithmTrace.empty()) algorithmTrace.clear();
		writeTrace = true;
		dfs(vertex);
		writeTrace = false;
		return algorithmTrace;
	}

	void printConnectComp() {
		for (int i = 0; i < connectCompunents.size(); i++, cout << endl) {
			cout << "Compounents numper " << i + 1 << " has next vertices: ";
			for (int j = 0; j < connectCompunents[i].size(); j++)
				cout << connectCompunents[i][j] << " ";
		}
	}

	// get count adjant compounents
	int getCountСonnectComp() {	
		return connectCompunents.size();
	}

	vector<vector<int>> getConnectCompunents() {
		return connectCompunents;
	}

	// get optimal path 
	void getOptimalPath(int vertexA, int vertexB) {
		// TODO
	}

	int getCountEdge() {
		return countEdges;
	}

	// tree has n - 1 edges and 1 connectivity component
	// loess - its  Tree? 
	bool itsTree() {
		if (getCountEdge() == _matrSize - 1) {
			for (int i = 1; i < label.size(); i++) 
				if (label[i] == false) return false;
			return true;
		}
		return false;
	}

	bool haveLoop() {
		// TODO
		return 0;
	}

};

int main()
{

	// Task 4
	vector<vector<int>> task4({ { 2, 4, 6 },
								{ 1 },
								{ 5, 9 },
								{ 1 },
								{ 3, 9 },
								{ 1 },
								{ 8, 10 },
								{ 7, 10 , 11 },
								{ 3, 5 },
								{ 7, 8, 12 },
								{ 8, 12},
								{ 10, 11 } });
	// Task 5
	vector<vector<int>> task5({ { 0, 1, 0, 0, 0, 0, 0, 0, 0 },
								{ 1, 0, 1, 0, 0, 1, 1, 0, 0 },
								{ 0, 1, 0, 0, 0, 0, 0, 0, 0 },
								{ 0, 0, 0, 0, 1, 0, 0, 1, 1 },
								{ 0, 0, 0, 1, 0, 0, 0, 1, 0 },
								{ 0, 1, 0, 0, 0, 0, 1, 0, 0 },
								{ 0, 1, 0, 0, 0, 1, 0, 0, 0 },
								{ 0, 0, 0, 1, 1, 0, 0, 0, 1 },
								{ 0, 0, 0, 1, 0, 0, 0, 1, 0 } });

	try
	{
		Graph g4(task4);
		cout << "Graph in task 4 has " << g4.getCountСonnectComp() << " connectedness component" << endl;
		g4.printConnectComp();
		Graph g5(task5);
		cout << "Graph in task 5 has " <<g5.getCountСonnectComp() << " connectedness component" << endl;
		g5.printConnectComp();
	}
	catch (const exception & exp)
	{
		cout << exp.what() << endl;
	}
		
}