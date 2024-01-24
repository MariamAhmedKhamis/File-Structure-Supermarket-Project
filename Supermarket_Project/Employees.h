#pragma once
#include "varlen.h"
class Employees
{

	char Name[50];
	char job_title[50];
	char phone[12];
	char Email[25];

public:
	Employees();
	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From Object  to  Record =>  Write

	int Unpack(VariableLengthRecord&);  // From Record to  Object   => Read

	void Add_employee();
	void search_employee();
	void Display_employee();
	void Update_employee();
	void Delete_employee();
};