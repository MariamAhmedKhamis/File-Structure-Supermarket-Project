#pragma once
#include "varlen.h"
//class VariableLengthRecord;

class order
{

	char Customer_name[50];
	char Quantity[30];
	char Product_Name[25];
	char customer_Phone[9];

public:
	order();
	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From Object  to  Record =>  Write

	int Unpack(VariableLengthRecord&);  // From Record to  Object   => Read

	void Add_Order();
	void search_Orders();
	void Display_Orders();
	void Update_Order();
	void Delete_Order();
};

