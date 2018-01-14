#include "stdafx.h"

#define TEXT "course_inf.txt"
#define LINESIZE 100
using namespace std;
void Tsort::input() {
	fstream fin;
	numOfCourse = 0;
	fin.open(TEXT);
	if (fin.fail()) {
		cout << "open failed." << endl;
		perror(TEXT);
		system("pause");
		exit(1);
	}
	for (int i = 0; i < NUMOFSEM; i++)
		fin >> numOfSem[i];
	while (!fin.eof()) {
		int inNode;
		string temp, con1, con2;
		stringstream stream;
		string tempNum, tempName;
		int tempStudytime, tempSem;
		fin >> tempNum >> tempName >> tempStudytime >> tempSem;
		getline(fin, temp);
		if (!temp.empty()) {
			stream.clear();
			stream.str("");
			temp.erase(0, 2); //delete '/t'
			if (!temp.empty()) { //if it is empty
				con1 = temp.substr(1, 2);
				temp.erase(0, 5);
				stream << con1;
				stream >> inNode;
				graph[inNode - 1][numOfCourse] = 1;
			}
		}
		if (!temp.empty()) {
			stream.clear();
			stream.str("");
			con2 = temp;
			stream << con2;
			stream >> inNode;
			graph[inNode - 1][numOfCourse] = 1;
		}
		kForT[numOfCourse].tnode = new Tnode(tempNum, tempName, tempStudytime, tempSem);
		kForT[numOfCourse].key = numOfCourse;
		kForT[numOfCourse].isvisited = 0;
		numOfCourse++;
	}
	fin.close();
}


void Tsort::TopSort(int i) {
	int m = 0;
	Key tempKforT[GRAPHSIZE];
	int count[GRAPHSIZE];
	for (int i = 0; i < numOfCourse; i++)
		count[i] = 0; //inital
	for (int i = 0; i < numOfCourse; i++)
		for (int k = 0; k < numOfCourse; k++) {
			if (graph[k][i] == 1)
				count[i]++;     //statistic indegree
		}
	for (int i = 0; i < numOfCourse; i++)
		if (count[i] == 0)
			s.push(kForT[i]);  //push nodes whose indegree = 0
	while (!s.empty()) {
		Key temp = s.top();
		s.pop();
		tempKforT[m] = temp;
		m++;
		for (int i = 0; i < numOfCourse; i++) {
			if (graph[temp.key][i] == 1) {
				count[i]--;      //for every point's indegree next to the temp is decreased 1 for this temp has been visited
				if (i != temp.key && count[i] == 0)
					s.push(kForT[i]);
			}
		}
	}
	printCourse(tempKforT);
}

void Tsort::printCourse(Key tempkForT[]) {
	int countSem = 0;
	while (countSem < NUMOFSEM) {
		int countCourse = numOfSem[countSem];
		cout << "semestem: " << countSem + 1 << endl;
		for (int i = 0; i < numOfCourse; i++)     //print the courses which have the sure sem
			if (tempkForT[i].tnode->getSem() == countSem + 1) {
				tempkForT[i].tnode->printTnode();
				tempkForT[i].isvisited = 1;
				countCourse--;
			}
		for (int i = 0; countCourse && i < numOfCourse; i++) {
			if (tempkForT[i].tnode->getSem() || tempkForT[i].isvisited) //skip the one whose sem is sure or has been visited
				continue;
			tempkForT[i].isvisited = 1;
			countCourse--;
			tempkForT[i].tnode->printTnode();
		}
		countSem++;
		cout << endl;
	}
}

void Tsort::run() {
	input();
	for (int i = 0; i < numOfCourse; i++)
		for (int k = 0; k < numOfCourse; k++)
			if (graph[i][k] != 1)
				graph[i][k] = 0;
	TopSort(0);
}