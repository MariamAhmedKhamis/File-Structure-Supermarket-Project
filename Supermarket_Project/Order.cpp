#include <cstring>
#include <iostream>
#include <fstream>
#include "Order.h"
order::order()
{
	Customer_name[0] = { '0' };
	Quantity[0] = { '0' };
	Product_Name[0] = { '0' };
	customer_Phone[0] = { '0' };
}

void order::InitRecord(VariableLengthRecord& record)
{
	record.init(4);
	record.AddField(0, 'L', (char)strlen(Customer_name));  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'L', (char)strlen(Quantity));
	record.AddField(2, 'L', (char)strlen(Product_Name));
	record.AddField(3, 'L', (char)strlen(customer_Phone));
}

int order::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;    
	recordSize = strlen(Customer_name) + strlen(Quantity) + strlen(Product_Name) + strlen(customer_Phone) + 11;
	record.Clear(recordSize);
	result = record.Pack(0, (void*)Customer_name, strlen(Customer_name));
	result = result && record.Pack(1, (void*)Quantity, strlen(Quantity));
	result = result && record.Pack(2, (void*)Product_Name, strlen(Product_Name));
	result = result && record.Pack(3, (void*)customer_Phone, strlen(customer_Phone));
	return result;
}

int order::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, Customer_name, true);
	result = result && record.Unpack(1, Quantity, true);
	result = result && record.Unpack(2, Product_Name, true);
	result = result && record.Unpack(3, customer_Phone, true);

	return result;
}

void order::Add_Order() {
	fstream File_Orders;
	File_Orders.open("File_Orders.txt", ios::app | ios::binary);
	if (File_Orders.is_open()) {
		int length;
		order d1;

		cin.ignore();
		cout << " Enter Your Name    :: ";
		cin.getline(d1.Customer_name, 50);

		cout << " Enter The Product Quantity    :: ";
		cin.getline(d1.Quantity, 30);

		cout << " Enter The Product Name      :: ";
		cin.getline(d1.Product_Name, 25);

		cout << " Enter Customer Phone Number   :: ";
		cin.ignore();
		cin.getline(d1.customer_Phone, 9);


		File_Orders.put('|');
		short recordSize = strlen(d1.Customer_name) + strlen(d1.Quantity) + strlen(d1.Product_Name) + strlen(d1.customer_Phone);
		File_Orders.write((char*)&recordSize, sizeof(recordSize));

		length = strlen(d1.Customer_name);
		File_Orders.write((char*)(&length), sizeof(short)); 
		File_Orders.write(d1.Customer_name, strlen(d1.Customer_name));

		length = strlen(d1.Quantity);
		File_Orders.write((char*)(&length), sizeof(short));
		File_Orders.write(d1.Quantity, strlen(d1.Quantity));

		length = strlen(d1.Product_Name);
		File_Orders.write((char*)(&length), sizeof(short));
		File_Orders.write(d1.Product_Name, strlen(d1.Product_Name));

		length = strlen(d1.customer_Phone);
		File_Orders.write((char*)(&length), sizeof(short));
		File_Orders.write(d1.customer_Phone, strlen(d1.customer_Phone));

		File_Orders.close();
	}
	else cout << "Error! open file.";

}
void order::Display_Orders()
{
	fstream File_Order;
	order d1;
	short recordSize;
	char search;
	File_Order.open("File_Orders.txt", ios::in | ios::binary);
	if (File_Order.is_open())
	{
		while (File_Order >> search)
		{

			short length;
			if (search == '|')
			{
				File_Order.read((char*)&recordSize, sizeof(recordSize));

				File_Order.read((char*)(&length), sizeof(short));
				File_Order.read(d1.Customer_name, length);
				d1.Customer_name[length] = '\0';

				File_Order.read((char*)(&length), sizeof(short));
				File_Order.read(d1.Quantity, length);
				d1.Quantity[length] = '\0';

				File_Order.read((char*)(&length), sizeof(short));
				File_Order.read(d1.Product_Name, length);
				d1.Product_Name[length] = '\0';

				File_Order.read((char*)(&length), sizeof(short));
				File_Order.read(d1.customer_Phone, length);
				d1.customer_Phone[length] = '\0';

				{
					cout << "-----------------------------------------------\n";
					cout << "  Customer_name              ::  " << d1.Customer_name << endl;
					cout << "  Quantit                    ::  " << d1.Quantity << endl;
					cout << "  Product_Name               ::  " << d1.Product_Name << endl;
					cout << "  customer_Phone_Number      ::  " << d1.customer_Phone << endl;
					cout << "-----------------------------------------------\n";
					File_Order.clear();
				}
			}
		}
		File_Order.close();
	}
	else cout << "\n\t* Error! can't open file *\n\n";
}

void order::search_Orders()
{
	fstream File_Orders;
	order d1;
	char search;
	short recordSize;
	char name[50];
	cin.ignore();
	cout << "Enter Customer's name to search for The Order :: ";
	cin.getline(name, 50);
	cout << endl;
	File_Orders.open("File_Orders.txt", ios::in | ios::binary);
	if (File_Orders.is_open())
	{

		while (File_Orders >> search)
		{
			short length;
			if (search == '|') {

				File_Orders.read((char*)&recordSize, sizeof(recordSize));

				File_Orders.read((char*)(&length), sizeof(short));
				File_Orders.read(d1.Customer_name, length);
				d1.Customer_name[length] = '\0';

				File_Orders.read((char*)(&length), sizeof(short));
				File_Orders.read(d1.Quantity, length);
				d1.Quantity[length] = '\0';

				File_Orders.read((char*)(&length), sizeof(short));
				File_Orders.read(d1.Product_Name, length);
				d1.Product_Name[length] = '\0';

				File_Orders.read((char*)(&length), sizeof(short));
				File_Orders.read(d1.customer_Phone, length);
				d1.customer_Phone[length] = '\0';


				if (strcmp(d1.Customer_name, name) == 0) {

					cout << "-----------------------------------------------\n";
					cout << " Customer Name            ::  " << d1.Customer_name << endl;
					cout << " Product Quintity         ::  " << d1.Quantity << endl;
					cout << " Product Name             ::  " << d1.Product_Name << endl;
					cout << " Customer Phone Number    ::  " << d1.customer_Phone << endl;
					cout << "-----------------------------------------------\n";

					File_Orders.clear();
					break;
				}
			}
		}
		if (strcmp(name, d1.Customer_name) != 0)
			cout << "Order is not found!!\n";
		//to able to read again
		File_Orders.close();
	}
	else
		cout << "\n\t* Error! can't open file *\n\n";
}


void order::Delete_Order() {
	char name[50];
	cin.ignore();
	cin.getline(name, 50);
	order d1;
	fstream File_order;
	bool found = false;
	char search;
	short recordSize;
	int pos;
	File_order.open("File_Orders.txt", ios::in | ios::binary | ios::out);
	if (File_order.is_open())
	{
		while (File_order >> search)
		{
			short length;
			if (search == '|') {
				File_order.read((char*)&recordSize, sizeof(recordSize));
				File_order.read((char*)(&length), sizeof(short));
				pos = File_order.tellg();
				File_order.read(d1.Customer_name, length);
				d1.Customer_name[length] = '\0';
				if (strcmp(d1.Customer_name, name) == 0)
				{
					found = true;
					File_order.seekg(pos - 5);
					File_order.put('*');
					break;
				}
				else
				{

					File_order.read((char*)(&length), sizeof(short));
					File_order.read(d1.Quantity, length);
					d1.Quantity[length] = '\0';
					File_order.read((char*)(&length), sizeof(short));
					File_order.read(d1.Product_Name, length);
					d1.Product_Name[length] = '\0';
					File_order.read((char*)(&length), sizeof(short));
					File_order.read(d1.customer_Phone, length);
					d1.customer_Phone[length] = '\0';
				}
			}
		}
		File_order.close();
		if (!found)
			cout << "\t* Order is not found *\n";
	}
	else
		cout << "\n\t* Error! can't open file *\n\n";
}

void order::Update_Order()
{
	Delete_Order();
	Add_Order();
}