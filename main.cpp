/***********************HEADER FILES****************************************/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<conio.h>
#include<cstdlib>
#include<unistd.h>
#include<windows.h>

using namespace std;

void Main_Menu();

/***********************ENTITY CLASS****************************************/
class Person
{
	private:
	int		rollno;											//Roll No of Student (Digits)
	char	name[50];										//Name of Student					
	float	ada, ppr, maths, rm;							//Mark of Subjects i.e. ADA, PPR, MATHS, RM
	double	cgpa;											//Total CGPA
	char	grade_ADA, grade_PPR, grade_RM, grade_MATHS;	//Grade of Subjects

	public:
	char	calculate_grade(float);								
	void	calculate();
	void	getdata();
	void	showdata();
	int		retrollno();

    Person()
    {
        rollno =0;
        ada=ppr=maths=rm=0.0;
        cgpa=0.0;
        grade_ADA=grade_PPR=grade_RM=grade_MATHS='NA';
    }
    

};

/***********Function to calculate grade*************************************/
char Person::calculate_grade(float g)
{
	float per;
	per = g/0.3;											// 30/3=10

	if(per>90)
    	return 'A';

	else
	{
    	if(per>80)
        	return 'B';

    	else
    	{
        	if(per>60)
            	return 'C';

        	else
        	{
            	if(per>35)
               		return 'D';

            	else
                	return 'E';

        	}
    	
		}
	
	}

}

/***********Function to calculate CGPA**************************************/
void Person::calculate()
{
	cgpa 		= (ada + maths + ppr + rm) / 12; 			// ((ada+maths+ppr+rm)/3)/4 = all /12

	grade_ADA	= calculate_grade(  ada	 );
	grade_PPR	= calculate_grade(  ppr	 );
	grade_MATHS = calculate_grade( maths );
	grade_RM 	= calculate_grade(	 rm	 );
}

/***********Function to get data from user*********************************/
void Person::getdata()
{
	cout << "\nEnter roll number of STUDENT   : ";
	cin >> rollno;
	cout << "\nEnter the Name of STUDENT      : ";
	cin.ignore();										// to clear characters from input buffer 
	cin.getline(name, 50);								// to get space separated name
	cout << "\nEnter marks of PPR   out of 30 : ";
	cin >> ppr;
	cout << "\nEnter marks of ADA   out of 30 : ";
	cin >> ada;
	cout << "\nEnter marks of MATHS out of 30 : ";
	cin >> maths;
	cout << "\nEnter marks of RM    out of 30 : ";
	cin >> rm; 
	
	if(ada>30) ada=30;if(ppr>30) ppr=30;if(maths>30) maths=30;if(rm>30) rm=30; //if marks>30 do 30

	//To calculate CGPA and grades
	calculate();										
}

/***********Function to show student result*********************************/
void Person::showdata()
{
	cout << "\nRoll number of STUDENT 	: " << rollno;
	cout << "\nName of STUDENT        	: " << name;
	cout <<"\n\nSubject        Marks        Grade";
	cout <<  "\n---------------------------------------";
	cout <<  "\nPPR        :     "<<ppr  << "      :    " << grade_PPR;
	cout <<  "\nADA        :     "<<ada  << "      :    " << grade_ADA;
	cout <<  "\nMATHS      :     "<<maths<< "      :    " << grade_MATHS;
	cout <<  "\nRM         :     "<<rm   << "      :    " << grade_RM;

	cout << "\n\nCGPA of STUDENT is     : " << cgpa;

}

/***********Function to return roll number*********************************/
int Person::retrollno()
{
	return rollno;
}


/***********************TEACHER CLASS****************************************/
class Teacher
{
	public:
	void add();
	void display_all();
	void display_sp(int roll);
	void modify_student(int roll);
	void delete_student(int n);
	void show_menu();

};

/**************************ADDING A RECORD***********************************/
void Teacher::add()
{
	Person st;
	ofstream outFile;											//outFile Object "to write"
	outFile.open("studentlist.dat", ios::binary | ios::app);	//open(filename, mode)
	st.getdata();
	outFile.write(reinterpret_cast < char * > ( & st), sizeof(Person));
	outFile.close();

	cout << "\n\nStudent record has been created ...\n";
	//cin.ignore(); cin.get();
}

/********************DISPLAYING ALL THE RECORDS*****************************/
void Teacher::display_all()
{
	Person st;
	ifstream inFile;
	inFile.open("studentlist.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be open !!!! Press any Key...\n";
		//cin.ignore(); cin.get();
		return;
	}
	cout << "\n\n";
	cout << "\n************************************************************************\n";
	cout << "                           DISPLAY ALL RECORD !!!                           ";
	cout << "\n************************************************************************\n";

	while (inFile.read(reinterpret_cast < char * > ( & st), sizeof(Person)))
	{
		//cout<<st.rollno;
		st.showdata();
		cout << "\n\n------------------------------------------------------------------------\n";
	}
	
	inFile.close();
	//cin.ignore(); cin.get();
}

/********************DISPLAYING A STUDENT RECORD****************************/
void Teacher::display_sp(int str1)
{
	Person 		st;
	ifstream 	inFile;

	inFile.open("studentlist.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be open !!! Press any Key...";
		//cin.ignore(); cin.get();
		return;
	}

	int flag = 0;
	while (inFile.read(reinterpret_cast < char * > ( & st), sizeof(Person)))
	{

		if (st.retrollno() == str1)
		{
			st.showdata();
			flag = 1;
		}
	}

	inFile.close();

	if (flag == 0)
	{
		cout << "\n\nRECORD DOESN'T EXIST...";
	}
	cout << "\n\n";
	cin.ignore();
	cin.get();
}

/************************MODIFYING A RECORD*********************************/
void Teacher::modify_student(int n)
{
	int 	found = 0;
	Person 	st;
	fstream File;
	File.open("studentlist.dat", ios::binary | ios:: in | ios::out);

	//if file doesn't open then return
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}

	while (!File.eof() && found == 0)
	{
		File.read(reinterpret_cast < char * > ( & st), sizeof(Person));
		if (st.retrollno() == n)
		{
			st.showdata();
			cout << "\n\nPlease enter the New Details of STUDENT" << endl;
			st.getdata();

			//int pos = (-1) * static_cast < int > (sizeof(st));
			//File.seekp(pos, ios::cur);

			File.seekp(File.tellp()-sizeof(Person));
			File.write(reinterpret_cast < char * > ( & st), sizeof(Person));

			cout << "\n\n    Record Updated.....";
			found = 1;
		}
	}
	
	File.close();
	
	if (found == 0)
	{
		cout << "\n\n Record Not Found ";
	}
	cin.ignore();
	cin.get();
}

/*************************DELETING A RECORD*********************************/
void Teacher::delete_student(int n)
{
	int			flag = 0;
	char 		ans;
	Person		st;
	ifstream	inFile;
	inFile.open("studentlist.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);

	while (inFile.read(reinterpret_cast < char * > ( & st), sizeof(Person)))
	{
		if (st.retrollno() != n)
		{
			outFile.write(reinterpret_cast < char * > ( & st), sizeof(Person));
		}
		if (st.retrollno() == n)
		{
			st.showdata();
			flag = 1;
		}
	}

	outFile.close();
	inFile.close();

	if (flag == 1)
	{
		
		cin.ignore();
		cout<<"\n\n Do you want to delete above record (y/n): ";
		cin>>ans;
		if(ans=='Y'||ans=='y')
		{
			remove("studentlist.dat");
			rename("Temp.dat", "studentlist.dat");
			cout << "\n\n\tRecord Deleted ..\n\n";
		}
		else
		{
			remove("Temp.dat");
			cout << "\n\n\tRecord not Deleted ..\n\n";
		}
	}
	else
	{
		cout << "\n\n\t\t---Unable to delete--- \n\n\t\t---Record not found--- \n\n";
	}

	cin.ignore();
	cin.get();
}

/*************************SHOWING TEACHER MENU******************************/
void Teacher::show_menu()
{
	int n;
	start:
	system("cls");
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t-----------------------------------" << "\n";
	cout << "\t\t\t               MENU                " << "\n";
	cout << "\t\t\t-----------------------------------" << "\n";
	cout << "\t\t\t     1. ADD A NEW RECORD           " << "\n";
	cout << "\t\t\t     2. SEARCH FOR A RECORD        " << "\n";
	cout << "\t\t\t     3. MODIFY A RECORD            " << "\n";
	cout << "\t\t\t     4. DELETE A RECORD            " << "\n";
	cout << "\t\t\t     5. DISPLAY ALL THE RECORDS    " << "\n";
	cout << "\t\t\t     6. GO TO MAIN MENU            " << "\n\n";
	cout << "\t\t\t     ENTER YOUR OPTION: ";
	cin >> n;
	system("cls");
	int num;
	switch (n)
	{
		case 1:	add();
				break;

		case 2:	cout << "\n\t\t RESULT MANAGEMENT SYSTEM	   ";
				cout << "\n\n\t Please Enter the roll number : ";
				cin >> num;
				display_sp(num);
				break;

		case 3:	system("cls");
				cout << "\n\t\t RESULT MANAGEMENT SYSTEM       ";
				cout << "\n\n\t Please Enter the roll number : ";
				cin >> num;
				modify_student(num);
				break;

		case 4:	system("cls");
				cout << "\n\t\t RESULT MANAGEMENT SYSTEM       ";
				cout << "\n\n\t Please Enter the roll number : ";
				cin >> num;
				delete_student(num);
				break;

		case 5:	display_all();
				break;

		case 6: Main_Menu();
				break;
		default:cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!!!";
				cout << "\n\n\n\n\n\n\n\n";
	}
	system("PAUSE");
	goto start;
}

/***********************STUDENT CLASS***************************************/
class Student: public Teacher 
{
	public:
	void show_menu();

};

/*************************SHOWING STUDENT MENU******************************/
void Student::show_menu()
{
	int n;
	start:
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t-------------------------------" << "\n";
	cout << "\t\t\t             MENU              " << "\n";
	cout << "\t\t\t-------------------------------" << "\n";
	cout << "\t\t\t   1. SEARCH FOR YOUR RECORD   " << "\n";
	cout << "\t\t\t   2. VIEW ALL STUDENTS RECORD " << "\n";
	cout << "\t\t\t   3. GO TO MAIN MENU		  " << "\n\n";
	cout << "\t\t\t   ENTER YOUR OPTION          : ";
	cin >> n;
	
	system("cls");
	int num;
	Student s;
	switch (n)
	{
		case 1:	cout << "\n\t\t STUDENT REPORT CARD PROJECT";
				cout << "\n\n\t Please Enter the roll number ";
				cin >> num;
				s.display_sp(num);
				break;
				
		case 2:	s.display_all();
				break;

		case 3:	Main_Menu();
				break;

		default:cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!!";
				cout << "\n\n\n\n\n\n\n\n";
	}

	system("PAUSE");
	goto start;

}

/***********************Introduction****************************************/
void Intro()
{

	system("color 0A");
    cout << "\n\n\n";
	cout << "\t\t\t****************************PPR FUN PROJECT************************" << "\n\n\n\n";
	cout << "\t\t\t************************RESULT MANAGEMENT SYSTEM*******************" << "\n\n";
	cout << "\t\t\t                        By                                         " << "\n";
	cout << "\t\t\t                                  Abhay Vinod Satyarthi  MIT2020068" << "\n";
	cout << "\t\t\t                                  Amruta Haspe           MIT2020095" << "\n";
	cout << "\t\t\t                                  Aman Kumar             MIT2020093" << "\n";
	cout << "\t\t\t                                  Amit Kumar             MIT2020094" << "\n";
	Sleep(2000);

	/* Initialize char for printing loading bar*/
	char a = 177, b = 219;

	cout << "\n\n\n\n";
	cout << "\t\t\t\t\t\t"<<"Loading...\n\n";
	cout << "\t\t\t\t\t\t";

	// Print initial loading bar
	for (int i = 0; i < 26; i++) cout<<a;

	/* Set the cursor again starting point of loading bar*/
	cout << "\r";
	cout << "\t\t\t\t\t\t";

	// Print loading bar progress
	for (int i = 0; i < 26; i++)
	{
		cout<<b;
		// Sleep for 1 second
		Sleep(100);
	}
	
	system("cls");
}

/***********************PRINTING THE MAIN MENU******************************/
void Main_Menu()
{
	int ch;
	start:
	system("cls");
	cout << "\n\n\n\n\n";
	cout << "\t\t-------------------------------------------" << "\n";
	cout << "\t\t               MAIN MENU                   " << "\n";
	cout << "\t\t-------------------------------------------" << "\n\n\n";
	cout << "\t\t           SELECT DESIGNATION              " << "\n\n";
	cout << "\t\t-------------------------------------------" << "\n";
	cout << "\t\t  1. TEACHER     2. STUDENT      3. EXIT   " << "\n";
	cout << "\t\t-------------------------------------------" << "\n\n";
	cout << "\t\t             ENTER AN OPTION            : ";
	cin >> ch;

	system("cls");
	char pass[6];
	pass[5]='\0';
	switch (ch)
	{
		case 1:	system("cls");
				//calling teacher menu
				Teacher t;
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\t\t\tENTER THE PASSWORD : ";
				for(int i=0;i<5;++i)
				{
					pass[i]=getch();
					cout<<"*";
				}
				cout<<"\n\n";
				if(strcmp(pass,"ADMIN")==0)							
				{
					cout <<           "\n\n\t\t\tACCESS GRANTED...!!!!\n";
					Sleep(2000);
					system("cls");
					t.show_menu();
				}
				else
				{
					cout <<           "\n\n\t\t\tWRONG PASSWORD...!!!!\n";
					cout <<           "\n\n\t\t\tTRY AGAIN :(  ...!!!!\n";
					Sleep(2000);
					system("cls");
					goto start;
				}
				break;

		case 2:	system("cls");
				//calling student menu
				Student s;
				s.show_menu();
				break;

		case 3:	//Successfully Termination of the program
				exit(0);
				break;

		default:cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPLEASE ENTER THE CHOICE (1-3) ONLY:(";
				cout << "\n\n\n\n\n\n\n\n";
				system("PAUSE");
	}
	
	goto start;
}

/***********************:) MAIN FUNCTION************************************/
int main()
{

	//INTRO
	Intro();

	//MAIN_MENU
	Main_Menu();

	return 0;
}

/***********************LAST LINE OF CODE************************************/
