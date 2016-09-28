#include "studentController.h"
#include "studentIO.h"
#include "student.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>									//exit, EXIT_FAILURE

#define MAXSTD 32
#define MAXPATH 255

using namespace std;

bool checkID(string s, int i, Student st[])
{
	bool flag = true;
	int j;

	for(j = 1; j <= i-1; j++){
		if(st[j].getID().compare(s) == 0){
			flag = false;
		}
	}

	if(flag == false){
		cout << "\n\n hmm.. :-(\n it seem like the student id you've entered is already in the record list\n please try another\n\n";
	}

	return flag;
	
	//bool flag = true;
	//Student savedSt;
	//ifstream inFile;

	//inFile.open("studentdb.txt", ios::in/*|ios::binary*/);
	//while(inFile.read(reinterpret_cast<char *> (&savedSt), sizeof(Student))) {
	//	if(s.compare(savedSt.getID()) == 0)
	//	{
	//		flag = false;
	//	}
	//}
	//inFile.close();

	//if(flag == false){
	//	cout << "\n\n hmm.. :-(\n it seems like the student id you've entered is already in the record list\n please try another\n\n";
	//}
	//return flag;
}

void addFK(int n)
{
	Student st[MAXSTD];
	ofstream outFile;
	outFile.open("studentdb.txt",ios::out|ios::binary);

	int i;
	for(i = 1; i <= n; i++){
		cout << "\nstudent number " << i << "\n----------------\n\n";
		//Student st;
		st[i].importStd();
		/*while(!checkID(st[i].getID())) {
			cout << "\nstudent number " << i << "\n----------------\n\n";
			st.importStd();
		}*/
		while(!checkID(st[i].getID(), i, st)) {
			cout << "\nstudent number " << i << "\n----------------\n";
			st[i].importStd();
		}
		outFile.write(reinterpret_cast<char *> (&st[i]), sizeof(Student));
	}
	outFile.close();
	cout << "\n\nstudent record has been created successfully\n";
}

void addFF(int n)
{
	//cout << "\n!this feature is currently unavailable.\nplease try again after payment!\n\n";
	Student st;
	int i;
	fstream inFile;
	fstream outFile;

	inFile.open("studentIN.txt",ios::binary|ios::in/*|ios::out*/);
	if(!inFile)
	{
		cout << "file 'studentIN.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	outFile.open("studentdb.txt",ios::binary/*|ios::in*/|ios::out);
	if(!outFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	
	for(i = 1; i <= n; i++){
		inFile.read(reinterpret_cast<char *> (&st), sizeof(Student));
		outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
	}
	outFile.close();
	inFile.close();
	cout << "\n" << n << " students successfully imported from studentin.txt to studentdb.txt\n";
	cin.get();
}

void add(int n)
{
	char addOpt;

	cout << "press 'k' to add records from keyboard or 'f' to add from file: ";
	cin >> addOpt;

	switch(addOpt) {
		case 'k':
			addFK(n);
			break;
		case 'f':
			addFF(n);
			break;
		default:
			cout << "\ninvalid parameter. please choose [k/f] to add record from keyboard/file..\n";
	}

	cout << "press any key to continue..\n";
	cin.get();
}

void show()
{
	Student st;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile){
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\t---show all records---\n\n";
	int stdnumber = 1;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student))) {
		cout << "student number " << stdnumber << "\n----------------\n\n";
		st.exportStd();
		cout << "\n";
		stdnumber++;
	}
	inFile.close();
	cin.get();
}

void update()
{
	bool found=false;
	Student st;
	fstream File;
	File.open("studentdb.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}

	string s;
	cout << "\nenter the id you want to update info: ";
	fflush(stdin);
	getline(cin,s);
	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		if(st.getID().compare(s) == 0)
		{
			st.exportStd();
			cout<<"\n\nupdate student's info\n";
			st.importStd();
			int pos=(-1)*static_cast<int>(sizeof(st));					//cast<int>? if id is string? cast<char>?
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&st), sizeof(Student));
			cout<<"\n\t record has been succuessfully upadated";
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout << "\nrecord not found\n";
	cin.ignore();
	cin.get();
}

void del()
{
	bool found=false;
	Student st;
	fstream inFile;
	inFile.open("studentdb.txt",ios::binary|ios::in|ios::out);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}

	string s;
	cout << "\nenter the id you want to delete: ";
	fflush(stdin);
	getline(cin,s);
	while(!inFile.eof() && found == false)
	{

		inFile.read(reinterpret_cast<char *> (&st), sizeof(Student));
		if(st.getID().compare(s) == 0)
		{
			st.exportStd();
			cout<<"\n\ndo you really delete this student record? [Y/n] ";
			char confirm;
			cin >> confirm;
			if(confirm == 'Y' || confirm == 'y') {
				ofstream outFile;
				outFile.open("temporary.txt",ios::out);
				inFile.seekg(0,ios::beg);
				while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
				{
					if(st.getID().compare(s) != 0)
					{
						outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
					}
				}
				outFile.close();
				inFile.close();
				remove("studentdb.txt");
				rename("temporary.txt", "studentdb.txt");
				cout<<"\n\n\t record has been successfully deleted!";
				cin.get();
			}
			found = true;
		}
	}
	if(found == false)
		cout<<"\nrecord not found\n";
	cin.ignore();
	cin.get();
}

void swap(Student &st1, Student &st2){
	Student temp;
	memcpy(&temp, &st1, sizeof(Student));
	memcpy(&st1, &st2, sizeof(Student));
	memcpy(&st2, &temp, sizeof(Student));
}

void sortID(int n, Student st[]){
	for(int i = 1; i <= n; i++){
		for(int j = i+1; j <= n; j++){
			if(st[i].getID() > st[j].getID()){
				swap(st[i], st[j]);
			}
		}
	}
}

void sortTotal(int n, Student st[]){
	for(int i = 1; i <= n; i++){
		for(int j = i+1; j <= n; j++){
			if(st[i].getTotal() > st[j].getTotal()){
				swap(st[i], st[j]);
			}
		}
	}
}

void sortName(int n, Student st[]){
	for(int i = 1; i <= n; i++){
		for(int j = i+1; j <= n; j++){
			if(st[i].getName() > st[j].getName()){
				swap(st[i], st[j]);
			}
		}
	}
}

void sort(int resultcount, Student result[]){
	int sw;
	cout << "1-sort by id | 2-sort by name | 3-sort by total of point\n";
	cout << "your choice: ";
	cin >> sw;
	cout << endl;
	switch(sw) {
			   case 1:
				   sortID(resultcount, result);
				   for(int i = 1; i <= resultcount; i++){
					   result[i].exportStd();
				   }
				   break;
			   case 2:
				   sortName(resultcount, result);
				   for(int i = 1; i <= resultcount; i++){
					   result[i].exportStd();
				   }
				   break;
			   case 3:
				   sortTotal(resultcount, result);
				   for(int i = 1; i <= resultcount; i++){
					   result[i].exportStd();
				   }
				   break;
	}
}

void searchID()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	string s;
	cout << "\nenter the id you want to search: ";
	fflush(stdin);
	getline(cin,s);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getID().compare(s) == 0)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\nrecord not found\n";
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
	cin.ignore();
	cin.get();
}

void searchName()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	string s;
	cout<<"\nenter the name you want to search: ";
	fflush(stdin);
	getline(cin,s);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getName().compare(s) == 0)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag == false){
		cout << "\nrecord not found\n";
	}
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
}

void searchMath()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	float x;
	cout << "\nenter math point you want to search: ";
	cin >> x;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getMath() == x)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\nrecord not found\n";
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
	cin.ignore();
	cin.get();
}

void searchPhysics()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	float x;
	cout << "\nenter physics point you want to search: ";
	cin >> x;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getPhys() == x)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\nrecord not found\n";
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
	cin.ignore();
	cin.get();
}

void searchChemistry()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	float x;
	cout << "\nenter chemistry point you want to search: ";
	cin >> x;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getChem() == x)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\nrecord not found\n";
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
	cin.ignore();
	cin.get();
}

void searchTotal()
{
	Student st;
	Student result[MAXSTD];
	int resultcount = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile)
	{
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	float x;
	cout << "\nenter point at total you want to search: ";
	cin >> x;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getTotal() == x)
		{
			resultcount++;
			memcpy(&result[resultcount], &st, sizeof(Student));
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\nrecord not found\n";
	else{
		sort(resultcount, result);
		char confirmExp;
		cout << "\ndo you want to export searching result to file? [Y/n] ";
		cin >> confirmExp;
		if(confirmExp == 'Y' || confirmExp == 'y') {
			writeFile(resultcount, result);
			cout << "searching results have been successfully saved to student_search_result.txt\n";
		}
	}
	cin.ignore();
	cin.get();
}

void search()
{
		char searchOpt;
		cout << "\npress: 'i' to search with student id\n";
		cout << "       'n' to search with student name\n";
		cout << "       'm' to search with math point\n";
		cout << "       'p' to search with physics point\n";
		cout << "       'c' to search with chemistry point\n";
		cout << "       't' to search with point at total\n";
		cout << "your choice: ";
		cin >> searchOpt;

		switch(searchOpt){
			case 'i':
				searchID();
				break;
			case 'n':
				searchName();
				break;
			case 'm':
				searchMath();
				break;
			case 'p':
				searchPhysics();
				break;
			case 'c':
				searchChemistry();
				break;
			case 't':
				searchTotal();
				break;
			default:
				cout << "\ninvalid parameter. please choose [i/n/m/p/c/t] to search.. ";
		}
}

void stat()
{
	Student st;
	int c15 = 0, c20 = 0, c25 = 0, c30 = 0;
	ifstream inFile;
	inFile.open("studentdb.txt", ios::in|ios::binary);
	if(!inFile){
		cout << "file 'studentdb.txt' could not be open. press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\t\t---statistics---\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student))) {
		if(st.getTotal() < 15)
			c15++;
		if(st.getTotal() >=15 && st.getTotal() < 20)
			c20++;
		if(st.getTotal() >=20 && st.getTotal() < 25)
			c25++;
		if(st.getTotal() >=25)
			c30++;
	}
	inFile.close();

	cout << "\nnumber of students whose total point is under 15: " << c15;
	cout << "\nnumber of students whose total point is between 15 and 20: " << c20;
	cout << "\nnumber of students whose total point is between 20 and 25: " << c25;
	cout << "\nnumber of students whose total point is higher than 25: " << c30 << endl << endl;
	//cin.ignore();
	cin.get();
}