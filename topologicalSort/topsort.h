#pragma once
#ifndef _IMPLEMENTATION_
#define _IMPLEMENTATION_
#define GRAPHSIZE 50
#define NUMOFSEM 8
using namespace std;

class Tnode {
private:
	string name;
	string num;
	int studytime;
	int semestem;
public:
	Tnode() {}
	Tnode(string n, string nu, int studyt, int sem) {
		name = n;  num = nu;
		studytime = studyt;  semestem = sem;
	}
	int getSem() const {
		return semestem;
	}
	void printTnode() const {
			cout << num << "\t" << name << "\t" << studytime << endl;
	}
};

struct Key {
	int key;
	Tnode* tnode;
	bool isvisited;
};

class Tsort {
private:
	int graph[GRAPHSIZE][GRAPHSIZE];
	Key kForT[GRAPHSIZE];
	int numOfSem[NUMOFSEM];
	int numOfCourse;
	stack<Key> s;
	void input();
	void TopSort(int i);
	void printCourse(Key kForT[]);
public:
	~Tsort() {}
	Tsort() {}
	void run();
};

#endif