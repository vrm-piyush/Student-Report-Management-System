#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<Windows.h>

using namespace std;

/*	CLASS USED IN PROJECT	*/

class student
{
private:
	int rollno;
	char name[50];
	double p_marks, c_marks, m_marks, e_marks, cs_marks;
	double percentage;
	char grade;
	void calculate();	//function to calculate grade
public:
	void getdata();		//function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retrollno() const;
}; //class ends here


void student::calculate()
{
	percentage = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
	if (percentage >= 90)
		grade = 'A';
	else if (percentage >= 80 && percentage < 90)
		grade = 'B';
	else if (percentage >= 70 && percentage < 80)
		grade = 'C';
	else if (percentage >= 65 && percentage < 70)
		grade = 'D';
	else if (percentage >= 35 && percentage < 65)
		grade = 'E';
	else
		grade = 'F';
}

void student::getdata()
{
	cout << "\n\tEnter The roll number of student:\t";
	cin >> rollno;
	cout << "\n\n\tEnter The Name of student:\t";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\tEnter The marks in Physics out of 100:\t";
	cin >> p_marks;
	cout << "\n\tEnter The marks in Chemistry out of 100:\t";
	cin >> c_marks;
	cout << "\n\tEnter The marks in Maths out of 100:\t";
	cin >> m_marks;
	cout << "\n\tEnter The marks in English out of 100:\t";
	cin >> e_marks;
	cout << "\n\tEnter The marks in Computer Science out of 100:\t";
	cin >> cs_marks;
	calculate();
}

void student::showdata() const
{
	cout << "\n\tRoll number of student:\t\t" << rollno;
	cout << "\n\tName of student:\t\t" << name;
	cout << "\n\tMarks in Physics:\t\t" << p_marks;
	cout << "\n\tMarks in Chemistry:\t\t" << c_marks;
	cout << "\n\tMarks in Maths:\t\t\t" << m_marks;
	cout << "\n\tMarks in English:\t\t" << e_marks;
	cout << "\n\tMarks in Computer Science:\t" << cs_marks;
	cout << "\n\tPercentage(%):\t\t\t" << percentage;
	cout << "\n\tGrade of student:\t\t" << grade;
}

void student::show_tabular() const
{
	cout << "\t  " << rollno << setw(9) << " " << name << setw(12) << p_marks << setw(8) << c_marks << setw(10) << m_marks << setw(9)
		<< e_marks << setw(10) << cs_marks << setw(8) << percentage << setw(6) << grade << endl;
}

int  student::retrollno() const
{
	return rollno;
}


/*	function declaration	*/

void write_student();		//write the record in binary file
void display_all();			//read all records from binary file
void display_sp(int);		//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();		//display all records in tabular format from binary file
void result();				//display result menu
void intro();				//display welcome screen
void entry_menu();			//display entry menu on screen



/*    	THE MAIN FUNCTION OF PROGRAM	*/

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char ch;
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		system("COLOR 70");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t\t01. RESULT";
		cout << "\n\n\t\t02. ENTRY/EDIT";
		cout << "\n\n\t\t03. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3):\t";
		cin >> ch;
		switch (ch)
		{
		case '1': result();
			break;
		case '2': entry_menu();
			break;
		case '3':
			break;
		default:cout << "\a";
		}
	} while (ch != '3');
	return 0;
}

/*		function to write in file		*/

void write_student()
{
	system("COLOR 7C");
	student st;
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);
	cout << "\n\n\t\tSTUDENT DETAILS";
	st.getdata();
	outFile.write(reinterpret_cast<char*> (&st), sizeof(student));
	outFile.close();
	cout << "\n\n\n\tStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}

/*		function to read all records from file		*/    	

void display_all()
{
	system("COLOR 7C");
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "\n\tFile could not be open !! Press any Key...\t";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read(reinterpret_cast<char*> (&st), sizeof(student)))
	{
		st.showdata();
		cout << "\n\n\t====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

/*		function to read specific record from file		*/    	

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "\n\tFile could not be open !! Press any Key...\t";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while (inFile.read(reinterpret_cast<char*> (&st), sizeof(student)))
	{
		if (st.retrollno() == n)
		{
			st.showdata();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\n\tNo Record found!!";
	cin.ignore();
	cin.get();
}

/*		function to modify record of file		*/    	

void modify_student(int n)
{
	system("COLOR 71");
	bool found = false;
	student st;
	fstream File;
	File.open("student.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "\n\tFile could not be open !! Press any Key...\t";
		cin.ignore();
		cin.get();
		return;
	}
	while (!File.eof() && found == false)
	{

		File.read(reinterpret_cast<char*> (&st), sizeof(student));
		if (st.retrollno() == n)
		{
			cout << "\n\n\t\tCurrent Details\n";
			st.showdata();
			cout << "\n\n\t\tNew Details" << endl;
			st.getdata();
			int pos = (-1) * static_cast<int>(sizeof(st));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&st), sizeof(student));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}

/*		function to delete record of file		*/    	

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "\n\tFile could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&st), sizeof(student)))
	{
		if (st.retrollno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

/*		function to display all students grade report		*/    	

void class_result()
{
	student st;
	system("COLOR 8E");
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "\t=================================================================================================\n";
	cout << "\t R.No		Name            Phy    Chem	 Maths     Eng      CS	    %age    Grade" << endl;
	cout << "\t=================================================================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

/*		function to display result menu		*/    	

void result()
{
	char ch;
	int rno;
	system("cls");
	system("COLOR 03");
	cout << "\n\n\n\t\tRESULT MENU";
	cout << "\n\n\n\t1. Class Result";
	cout << "\n\n\t2. Student Report Card";
	cout << "\n\n\t3. Back to Main Menu";
	cout << "\n\n\n\tEnter Choice (1/2/3)? ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':	class_result(); 
		result();
	case '2':	system("COLOR F9");
		cout << "\n\n\t\tSTUDENT REPORT CARD" << endl;
		cout << "\n\n\tEnter Roll Number Of Student : ";
		cin >> rno;
		display_sp(rno); 
		result();
	case '3':	break;
	default:	
		cout << "\a";
	}
}

/*		INTRODUCTION FUNCTION		*/    	

void intro()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	cout << "\n\n\n\t\tSTUDENT REPORT MANAGEMENT";
	SetConsoleTextAttribute(h, 14);
	cout << "\n\n\n\tPress any key to enter!";
	cin.get();
}

/*		ENTRY / EDIT MENU FUNCTION		 */    	

void entry_menu()
{
	system("COLOR 0D");
	char ch;
	int num;
	system("cls");
	cout << "\n\n\n\t\tENTRY MENU";
	cout << "\n\n\t1.Create Student Record";
	cout << "\n\n\t2.Display All Students Records";
	cout << "\n\n\t3.Search Student Record ";
	cout << "\n\n\t4.Modify Student Record";
	cout << "\n\n\t5.Delete Student Record";
	cout << "\n\n\t6.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-6) ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
		case '1':	write_student(); 
					entry_menu();
		case '2':	display_all(); 
					entry_menu();
		case '3':	system("COLOR 71");
			cout << "\n\n\t\tRECORD SEARCH\n" << "\n\n\tPlease Enter The roll number ";
			cin >> num;
			display_sp(num); 
			break;
		case '4':	system("COLOR 71");
			cout << "\n\n\t\tUPDATE RECORD\n" << "\n\n\tPlease Enter The roll number ";
			cin >> num;
			modify_student(num); 
			break;
		case '5':system("COLOR F3");
			cout << "\n\n\t\tDELETE RECORD\n" << "\n\n\tPlease Enter The roll number ";
			cin >> num;
			delete_student(num); 
			break;
		case '6':	break;
	default:	
		cout << "\a"; 
		entry_menu();
	}
}