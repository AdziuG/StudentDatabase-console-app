#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//here we will create Student Class

class Student
{
private:
	char student_name[50];
	int roll_no;
	int social_studies_marks, statistics_marks, maths_marks, english_marks, computer_marks;
	double student_percentage;
	char student_grade;
	bool flag;
	void calculate_grade();

public:
	Student();
	void getdata();
	void check_duplicate_in_file();
	void showdata();
	void tabular_display(); // display results for all students
	int get_student_roll_no(); // returns roll number of the current student
	void show_student_record(int); // display record of student with specific roll number
	void write_record_in_file(); // write user input to student.dat
	
	
}; //shows the end of class

Student::Student()
{
	// create student.dat
	ofstream outfile("student.dat", ios::binary | ios::app); // creating ofstream object and file student.dat
	outfile.close();
	ofstream out_dfile("duplicate_checking.txt", ios::app);
	out_dfile.close();
}

void intro();
void entry_menu();
void display_all();

int main()
{
	system("CLS");
	system("color B1");
	char ch;
	Student std_obj;
	cout.setf(ios::fixed|ios::showpoint);
	cout << setprecision(2);
	intro();
	do
	{
		system("CLS");
		intro();
		cout << "\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
		cout << "\n\n\t1. Result Calculation System";
		cout << "\n\n\t2. Student Database Management System";
		cout << "\n\n\t3. Exit";
		cout << "\n\n\n\n\n\tPlease select your option (1-3)";
		cin >> ch;
		switch(ch)
		{
		case '1':
			// shows Result Calculation System
			break;
		case '2':
			//shows SDBMS
			entry_menu();
		case '3':
			//user wants to exit system
			break;
		default: cout << "\a";
		}
		
	} while (ch != 3);

	system("pause"); // second last statement that stops output till user press any key
	return 0; //main ends here
}

void intro()
{
	cout << "\n\n\n ***** WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM ***** \n\n";
}

void entry_menu()
{
	char ch;
	int num;
	Student std;
	system("cls");
	cout << "\n\n\n\t\tSTUDENT DATABASE MANAGEMENT SYSTEM MENU";
	cout << "\n\n\t1. CREATE STUDENT RECORD";
	cout << "\n\n\t2. SHOW RECORDS OF ALL STUDENTS";
	cout << "\n\n\t3. SEARCH STUDENTS RECORD";
	cout << "\n\n\t4. UPDATE STUDENT RECORD";
	cout << "\n\n\t5. DELETE STUDENT RECORD";
	cout << "\n\n\t6. BACK TO HOME SCREEN";
	cout << "\n\n\n\n\t. ENTER YOUR CHOICE (1-6)";
	cin >> ch;
	system("CLS");
	switch (ch)
	{
	case '1':
		// creates student record
		std.write_record_in_file();
		break;
	case '2':
		display_all(); // it is showing records of all students in the file
		break;
	case '3':
		// searching a record of a student
		cout << "\n\n\t Please enter the roll number";
		cin >> num;
		std.show_student_record(num);
		break;
	case '4':
		// updating student's record
		break;
	case '5':
		// delete student's record
		break;
	case '6':
		// go back to home screen
		break;
	default: cout << "\a";
		entry_menu();
	}
	

	
}

void display_all()
{
	//declarations
	Student st;
	ifstream infile;
	// open file
	infile.open("student.dat", ios::binary);
	// if file did not open print error msg & return func else will read records of all students step by step
	if(!infile)
	{
		cout << "File could not be opened, press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
	while (infile.read(reinterpret_cast<char*> (&st), sizeof(Student)))
	{
		st.showdata(); // it's executed for each record
		cout << "\n\n=========================\n";
	}
	// close file
	infile.close();
	cin.ignore();
	cin.get();
}



void Student::getdata()
{
	flag = false;
	cout << "\nEnter the roll no of the student = ";
	cin >> roll_no;
	check_duplicate_in_file();
	if (flag == true)
	{
		cout << "Error duplicate record" << endl;
		return;
	}
	// if flag==false then we will ask user to enter the remaining data of the student
	cout << "\n\n Enter the name of student = ";
	cin.ignore();
	cin.getline(student_name, 50);
	cout << "Enter the marks in Social Studies out of 100 :";
	cin >> social_studies_marks;
	cout << "Enter the marks in Statistics out of 100 :";
	cin >> statistics_marks;
	cout << "Enter the marks in Maths out of 100 :";
	cin >> maths_marks;
	cout << "Enter the marks in English out of 100 :";
	cin >> english_marks;
	cout << "Enter the marks in Computers out of 100 :";
	cin >> computer_marks;

	calculate_grade();
}

void Student::check_duplicate_in_file()
{
	// open file duplicate_checking.txt
	// compare the roll no. that user entered with all of file duplicate_checking.txt.
	//if found, flag=true else false
	int current_roll_no = 0;
	flag = false;
	ifstream infile("duplicate_checking.txt");
	while (!infile.eof())
	{
		infile >> current_roll_no;
		if (current_roll_no == roll_no)
		{
			flag = true;
		}
	}
	infile.close();
	if(flag == false)
	{
		// we are writing the roll no in duplicate_checking.txt
		ofstream outfile("duplicate_checking.txt", ios::app);
		outfile << "\n" << roll_no;
		outfile.close();
	}
}

void Student::showdata()
{
	cout << "Roll number of student = " << roll_no << endl;
	cout << "Student Name = " << student_name << endl;
	cout << "Marks in Social Studies = " << social_studies_marks << endl;
	cout << "Marks in Computer = " << computer_marks << endl;
	cout << "Marks in English = " << english_marks << endl;
	cout << "Marks in Maths = " << maths_marks << endl;
	cout << "Marks in Statistics = " << statistics_marks << endl;
	cout << "% of student marks = " << student_percentage << endl;
	cout << "Grade of student = " << student_grade << endl;
	
}

void Student::tabular_display()
{
	cout << roll_no << setw(4) << student_name << setw(20 - strlen(student_name)) << social_studies_marks << setw(6)
	<< statistics_marks << setw(6) << maths_marks << setw(6) << english_marks << setw(6) << computer_marks << setw(8)
	<< student_percentage << setw(8) << student_grade  << endl;
}

int Student::get_student_roll_no()
{
	return roll_no;
}

void Student::show_student_record(int n)
{
	ifstream infile;
	infile.open("student.dat", ios::binary);
	if(!infile)
	{
		cout << "File could not be opened, press any key to continue";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false; //use it as an indicator to know whether roll number is found
	while (infile.read(reinterpret_cast<char*> (this), sizeof(Student)))
	{
		if(get_student_roll_no() == n)
		{
			showdata(); // prints record of current student
			flag = true; // record is found in the file student.dat
		}

	}
	infile.close();
	if( flag == false)
	{
		cout << "\n\nrecord does not exist";
	}
	cin.ignore();
	cin.get();
}

void Student::write_record_in_file()
{
	//open student.dat
	ofstream outfile;
	outfile.open("student.dat", ios::binary | ios::app);
	getdata();
	//if flag=false enter student record
	if (flag = false)
	{
		outfile.write(reinterpret_cast<char *>(this), sizeof(Student));
		outfile.close();
		cout << "Student record has been created";
	}
	//if flag=true print error
	if (flag = true)
	{
		cout << "Record has not been created because of duplication" << endl;

	}
	cin.ignore();
	cin.get();
	//close file
	outfile.close();
	
}

void Student::calculate_grade()
{
	student_percentage = (social_studies_marks + computer_marks + english_marks + maths_marks + statistics_marks) / 5.0;
	if (student_percentage >= 90)
		student_grade = 'A';
	if (80 <= student_percentage < 90)
		student_grade = 'B';
	if (70 <= student_percentage < 80)
		student_grade = 'C';
	if (60 <= student_percentage < 70)
		student_grade = 'D';
	if (student_percentage < 60)
		student_grade = 'F';
	
	
}

