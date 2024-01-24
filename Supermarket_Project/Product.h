#pragma once
#include "varlen.h"
class Product
{
	char id[10];
	char Name[50];
	char quntity[10];
	char price[10];
public:
	Product();
	void InitRecord(VariableLengthRecord&); //set Record  Configuration
	int Pack(VariableLengthRecord&);	//  From Object   to  Record =>  Write
	int Unpack(VariableLengthRecord&);  // From Record to  Object   => Read

	void Add_product();
	void search_product();
	void Display_product();
	void Update_product();
	void Delete_product();
};