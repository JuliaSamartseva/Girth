// DetectGraphCycles.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <queue>

struct Node {
	int data;
	Node* next;
	Node (int data)
	{
		this->data = data;
		this->next = NULL;
	}
};

struct AdjacencyList {
	Node** head;

	AdjacencyList(int vertices) {
		head = new Node*[vertices];
		for (int i = 0; i < vertices; i++) head[i] = NULL;
	}

	void Add(int source, int destination){
		if (head[source] == NULL) head[source] = new Node(destination);
		else {
			Node* temp = head[source];
			head[source] = new Node(destination);
			head[source]->next = temp;
		}
	}
};

struct Set {
	Node* head = NULL;

	void insert(int data) {

		Node* element = new Node(data);
		if (head == NULL) head = element;
		else {
			element->next = head;
			head = element;
		}
	}

	bool contains(int data) {
		Node* x = head;
		while (x->next != NULL) {
			if (x->data == data) return true;
			x = x->next;
		}
		if (x->data == data) return true;
		return false;
	}

	void clean() {
		Node* current = head;
		Node* next;
		while (current != NULL) {
			next = current->next;
			free(current);
			current = next;
		}
	}

};

struct Graph {
	int Vertices;
	AdjacencyList* list = NULL;

	Graph (int v) //ask
	{
		Vertices = v;
		list = new AdjacencyList(Vertices);
		std::fstream file;
		std::string filename;
		int source, destination, number;

		filename = "file3.txt";
		file.open(filename.c_str());

		if (file.is_open()) {
			int i = 1;
			while ((file >> number)) {
				if (i == 1) {
					source = number;
					i++;
				}
				else {
					destination = number;
					AddEdge(source, destination);
					AddEdge(destination, source);
					i = 1;
				}
			}
		}
		file.close();
	}


	void AddEdge(int source, int destination) {
		list->Add(source, destination);
	}

	int Girth() {
		int result = 100;

		for (int i = 0; i < Vertices; i++) {
			bool* visited = new bool[Vertices];
			int* height = new int[Vertices];
			int* parent = new int[Vertices];
			for (int i = 0; i < Vertices; i++) {
				visited[i] = false;
				height[i] = 0;
				parent[i] = NULL;
			}
			Set S;
			S.clean();
			std::queue<int> q;
			while (!q.empty()) q.pop();
			visited[i] = true;
			q.push(i);
			// BFS
			while (!q.empty()) {
				int s = q.front();
				S.insert(s);
				q.pop();
				//for each Node adjacent to n
				Node* x = list->head[s];
				while (x != NULL) {
					if ((parent[s] != x->data)) {
						if (!S.contains(x->data)) {
							parent[x->data] = s;
							height[x->data] = height[s] + 1;
							q.push(x->data);
							S.insert(x->data);
						}
						else {
							int res = height[x->data] + height[s] + 1;
							if (res < result) result = res;
						}
					}
					x = x->next;
				}
			}
		}
		return result;
	}
};



int main()
{
	Graph* q = new Graph(10);
	std::cout << q->Girth();
}

