#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

struct  stde {
	char	*name;
	int id;
};
int main()
{

struct stde stud;
vector<struct stde> s;
	stud.name = "karl";
	stud.id = 1;
	s.push_back(stud);
	stud.name = "kate";
	stud.id = 2;
	s.push_back(stud);
	cout << s[0].name << endl;
}
