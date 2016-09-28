#include "studentController.h"

#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	cout << "Anh Nguyen Viet - 1st Week Pratices\n";
	cout << "-----------------------------------\n\n";

	int n = 0;

	while(n < 32){
		cout << "\n\n	---MENU---\n";
		cout << " 1-add new student records\n";
		cout << " 2-show all student records\n";
		cout << " 3-update a student info\n";
		cout << " 4-delete a student record\n";
		cout << " 5-search for records\n";
		cout << " 6-do statistics\n";
		cout << " 0-exit program\n\n";

		int fearture;
		cout << "your choice: ";
		cin >> fearture;

		switch(fearture){
			case 1:
				cout << "\nnumber of records to add: ";
				cin >> n;
				add(n);
				break;
			case 2:
				show();
				break;
			case 3:
				update();
				break;
			case 4:
				del();
				break;
			case 5:
				search();
				break;
			case 6:
				stat();
				break;
			case 0:
				cout << "will now exit program..";
				remove("student_search_result.txt");
				exit(0);
			default:
				cout << "invalid parameter. please choose one of following parameters..\n";
		}
	}

	getch();
	return 0;
}