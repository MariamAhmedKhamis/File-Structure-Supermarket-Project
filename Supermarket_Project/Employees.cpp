#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Employees.h"
Employees::Employees()
{
	Name[0] = { '0' };
	job_title[0] = { '0' };
	phone[0] = { '0' };
	Email[0] = { '0' };
}

void Employees::InitRecord(VariableLengthRecord& record)
{
	record.init(4);
	record.AddField(0, 'L', (char)strlen(Name));  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'L', (char)strlen(job_title));
	record.AddField(2, 'L', (char)strlen(phone));
	record.AddField(3, 'L', (char)strlen(Email));
}

int Employees::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   
	recordSize = strlen(Name) + strlen(job_title) + strlen(phone) + strlen(Email) + 11;
	record.Clear(recordSize);
	result = record.Pack(0, (void*)Name, strlen(Name));
	result = result && record.Pack(1, (void*)job_title, strlen(job_title));
	result = result && record.Pack(2, (void*)phone, strlen(phone));
	result = result && record.Pack(3, (void*)Email, strlen(Email));
	return result;
}

int Employees::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, Name, true);
	result = result && record.Unpack(1, job_title, true);
	result = result && record.Unpack(2, phone, true);
	result = result && record.Unpack(3, Email, true);

	return result;
}

void Employees::Add_employee()
{
	fstream File_Employees;
	File_Employees.open("File_Employee.txt", ios::app | ios::binary);
	if (File_Employees.is_open()) 
	{
		int length;
		Employees emp1;
		cin.ignore();
		cout << " Enter Employee's Name :: ";
		cin.getline(emp1.Name, 50);

		cout << " Enter Employee's Job Title :: ";
		cin.getline(emp1.job_title, 50);

		cout << " Enter Employee's Phone :: ";
		cin.getline(emp1.phone, 12);

		cout << " Enter Employee's E-mail :: ";
		cin.getline(emp1.Email, 25);

		File_Employees.put('|');
		short recordSize = strlen(emp1.Name) + strlen(emp1.job_title) + strlen(emp1.phone) + strlen(emp1.Email) + 11;
		File_Employees.write((char*)&recordSize, sizeof(recordSize));

		length = strlen(emp1.Name);
		File_Employees.write((char*)(&length), sizeof(short)); 
		File_Employees.write(emp1.Name, strlen(emp1.Name));

		length = strlen(emp1.job_title);
		File_Employees.write((char*)(&length), sizeof(short)); 
		File_Employees.write(emp1.job_title, strlen(emp1.job_title));

		length = strlen(emp1.phone);
		File_Employees.write((char*)(&length), sizeof(short)); 
		File_Employees.write(emp1.phone, strlen(emp1.phone));

		length = strlen(emp1.Email);
		File_Employees.write((char*)(&length), sizeof(short)); 
		File_Employees.write(emp1.Email, strlen(emp1.Email));

		File_Employees.close();
	}
	else 
		cout << "\n\t* Error! can't open file *\n";
}

void Employees::Display_employee()
{
	fstream File_Employees;
	Employees emp1;
	short recordSize;
	char search;
	File_Employees.open("File_Employee.txt", ios::in | ios::binary);  // in -> read 
	if (File_Employees.is_open())
	{
		while (File_Employees >> search) // read first char of record '|'
		{
			short length;
			if (search == '|')
			{
				File_Employees.read((char*)&recordSize, sizeof(recordSize));

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.Name, length);
				emp1.Name[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.job_title, length);
				emp1.job_title[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.phone, length);
				emp1.phone[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.Email, length);
				emp1.Email[length] = '\0';

				cout << "-----------------------------------------------\n";
				cout << "  Name        ::  " << emp1.Name << endl;
				cout << "  Job Title   ::  " << emp1.job_title << endl;
				cout << "  Phone       ::  " << emp1.phone << endl;
				cout << "  Email       ::  " << emp1.Email << endl;
				cout << "-----------------------------------------------\n";

				File_Employees.clear();
			}
		}
		File_Employees.close();
	}
	else 
		cout << "\n\t* Error! can't open file *\n";
}


void Employees::search_employee()
{
	fstream File_Employees;
	Employees emp1;
	char search;
	short recordSize;
	char name[50];
	cin.ignore();
	cout << "Enter Employee name to search for :: ";
	cin.getline(name, 50);
	cout << endl;
	File_Employees.open("File_Employee.txt", ios::in | ios::binary);
	if (File_Employees.is_open()) {
		while (File_Employees >> search) 
		{
			short length;
			if (search == '|') {

				File_Employees.read((char*)&recordSize, sizeof(recordSize));

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.Name, length);
				emp1.Name[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.job_title, length);
				emp1.job_title[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.phone, length);
				emp1.phone[length] = '\0';

				File_Employees.read((char*)(&length), sizeof(short));
				File_Employees.read(emp1.Email, length);
				emp1.Email[length] = '\0';

				if (strcmp(name, emp1.Name) == 0) { // strcmp return 0 if two equal

					cout << "-----------------------------------------------\n";
					cout << "  Name        ::  " << emp1.Name << endl;
					cout << "  Job Title   ::  " << emp1.job_title << endl;
					cout << "  Phone       ::  " << emp1.phone << endl;
					cout << "  Email       ::  " << emp1.Email << endl;
					cout << "-----------------------------------------------\n";
					File_Employees.clear();
					break; 
				}
			}
		}
		if (strcmp(name, emp1.Name) != 0)
			cout << "\t* Employee is not found!! *\n";
		   File_Employees.close();
	}
	else cout << "\n\t* Error! can't open file *\n";
}

void Employees::Delete_employee()
{
	char name[50];
	cin.ignore();
	cin.getline(name, 50);
	Employees emp;
	fstream File_Employee;
	bool found = false;
	char search;
	short recordSize;
	int pos;
	File_Employee.open("File_Employee.txt", ios::in | ios::binary | ios::out);
	if (File_Employee.is_open())
	{
		while (File_Employee >> search)
		{
			short length;
			if (search == '|')
			{
				File_Employee.read((char*)&recordSize, sizeof(recordSize));

				File_Employee.read((char*)(&length), sizeof(short));
				pos = File_Employee.tellg();
				File_Employee.read(emp.Name, length);

				emp.Name[length] = '\0';

				if (strcmp(emp.Name, name) == 0)
				{
					found = true;
					File_Employee.seekg(pos - 5);     // 5 sizeof(1 byte '|',2 byte size record,2 byte size feild name)
					File_Employee.put('*');          // reset curser to beginging of record
					break;
				}

				else
				{
					File_Employee.read((char*)(&length), sizeof(short));
					File_Employee.read(emp.job_title, length);
					emp.job_title[length] = '\0';

					File_Employee.read((char*)(&length), sizeof(short));
					File_Employee.read(emp.phone, length);
					emp.phone[length] = '\0';

					File_Employee.read((char*)(&length), sizeof(short));
					File_Employee.read(emp.Email, length);
					emp.Email[length] = '\0';
				}
			}
		}
		File_Employee.close();
		if (!found)
			cout << "\t* Employee is not found *\n";
	}
	else cout << "\n\t* Error! can't open file *\n";
}
void Employees::Update_employee()
{
	Delete_employee();
	Add_employee();
}