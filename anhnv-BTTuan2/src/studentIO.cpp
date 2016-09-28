#include "studentIO.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>

using namespace std;

void writeFile(int n, Student st[]){
	fstream f;
	int i;

	f.open("student_search_result.txt", ios::out/*ios::app*/);
	f << setw(6) << "id" << setw(30) << "name" << setw(30) << "address" << setw(9) << "sex" << setw(9) << "math" << setw(12) << "physics" << setw(16) << "chemistry\n\n";
	for(i = 1; i <= n; i++){
		f << setw(6) << st[i].getID()<< setw(30) << st[i].getName( )<< setw(30) << st[i].getAdd() << setw(9) << st[i].getSex() << setw(9) << st[i].getMath() << setw(12) << st[i].getPhys() << setw(14) << st[i].getChem() << endl;
	}
	f.close();
}

void readFile(Student st[])
{
	fstream f;
	f.open("studentin.txt", ios::in);
	int i = 1;

	while(!f.eof()) {
		cout << "\nstudent number " << i << "\n----------------\n";
		//st[i].exportStd();
		cout << "id: "; f >> st[i].id; cout << st[i].id << endl;
		cout << "name: "; f >> st[i].name; cout << st[i].name << endl;
		cout << "address: "; f >> st[i].address; cout << st[i].address << endl;
		cout << "sex: "; f >> st[i].sex;
		if(st[i].sex.compare("m") == 0)
			cout << "male\n";
		else
			cout << "female\n";
		cout << "math: "; f >> st[i].math; cout << st[i].math << endl;
		cout << "physics: "; f >> st[i].phys; cout << st[i].phys << endl;
		cout << "chemistry: "; f >> st[i].chem; cout << st[i].chem << endl << endl;
		i++;
	}

	f.close();
}