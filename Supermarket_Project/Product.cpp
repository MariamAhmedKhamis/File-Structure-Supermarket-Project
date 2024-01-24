#include "Product.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Product::Product()
{
	id[0] = { '0' };
	Name[0] = { '0' };
	quntity[0] = { '0' };
	price[0] = { '0' };
}
void Product::InitRecord(VariableLengthRecord& record)
{
	record.init(4);
	record.AddField(0, 'L', (char)strlen(id));  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'L', (char)strlen(Name));
	record.AddField(2, 'L', (char)strlen(quntity));
	record.AddField(3, 'L', (char)strlen(price));
}

int Product::Pack(VariableLengthRecord& record) // object->record->file
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result , recordSize = 0;
	recordSize = strlen(id) + strlen(Name) + strlen(quntity) + strlen(price) + 11; // 2B ber len for field + 2B len rec + 1B delemiter '|' 
	record.Clear(recordSize); 
	result = record.Pack(0, (void*)id, strlen(id));
	result = result && record.Pack(1, (void*)Name, strlen(Name));
	result = result && record.Pack(2, (void*)quntity, strlen(quntity));
	result = result && record.Pack(3, (void*)price, strlen(price));
	return result;
}

int Product::Unpack(VariableLengthRecord& record) // record -> object
{
	int result;
	result = record.Unpack(0, id, true);
	result = result && record.Unpack(1, Name, true);
	result = result && record.Unpack(2, quntity, true);
	result = result && record.Unpack(3, price, true);
	return result;
}

void Product::Add_product()
{
	fstream File_product;
	File_product.open("File_Product.txt", ios::app | ios::binary);
	if (File_product.is_open())
	{
		int length;
		Product p1;

		cin.ignore();
		cout << " Enter Product Id :: ";
		cin.getline(p1.id, 10);

		cout << " Enter Product Name :: ";
		cin.getline(p1.Name, 50);

		cout << " Enter Product quntity :: ";
		cin.getline(p1.quntity, 10);

		cout << " Enter Product price :: ";
		cin.getline(p1.price, 10);


		File_product.put('|');

		short recordSize = strlen(p1.id) + strlen(p1.Name) + strlen(p1.quntity) + strlen(p1.price)+11;
		File_product.write((char*)&recordSize, sizeof(recordSize));

		length = strlen(p1.id);
		File_product.write((char*)(&length), sizeof(short)); // len field 2B (id) , (pointer to char , size اللي هكتب فيه)
		File_product.write(p1.id, strlen(p1.id)); // data id 

		length = strlen(p1.Name);
		File_product.write((char*)(&length), sizeof(short));
		File_product.write(p1.Name, strlen(p1.Name));

		length = strlen(p1.quntity);
		File_product.write((char*)(&length), sizeof(short));
		File_product.write(p1.quntity, strlen(p1.quntity));

		length = strlen(p1.price);
		File_product.write((char*)(&length), sizeof(short));
		File_product.write(p1.price, strlen(p1.price));

		File_product.close();
	}
	else
	cout << "\n\t* Error! can't open file *\n";
}

void Product::Display_product()
{
	fstream File_product;
	Product p1;
	short recordSize;
	char search;
	File_product.open("File_Product.txt", ios::in | ios::binary); // read

	if (File_product.is_open())
	{
		//File_product.read((char*)&search, 1)
		while (File_product >> search)      // read first char of record -> '|'
		{
			short length;
			if (search == '|')
			{
				File_product.read((char*)&recordSize, sizeof(recordSize));

				File_product.read((char*)(&length), sizeof(short)); // len id 
				File_product.read(p1.id, length); // data id
				p1.id[length] = '\0';   // put /0 in end of id data   

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.Name, length);
				p1.Name[length] = '\0';

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.quntity, length);
				p1.quntity[length] = '\0';

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.price, length);
				p1.price[length] = '\0';


				cout << "-----------------------------------------------\n";
				cout << "  id         ::  " << p1.id << endl;
				cout << "  Name       ::  " << p1.Name << endl;
				cout << "  quntity    ::  " << p1.quntity << endl;
				cout << "  price      ::  " << p1.price << endl;
				cout << "-----------------------------------------------\n";

				File_product.clear(); 
			}

		}
		File_product.close();
	}
	else 
		cout << "\n\t* Error! can't open file *\n";

}

void Product::Update_product()
{
	Delete_product();
	Add_product();
}

void Product::search_product()
{
	fstream File_product;
	Product p1;
	char search;
	short recordSize;
	char ID[10];
	cout << "Enter ID to search for :: ";
	cin.ignore();
	cin.getline(ID, 10);
	File_product.open("File_Product.txt", ios::in | ios::binary); // read
	if (File_product.is_open()) 
	{
		while (File_product >> search)
		{
			short length;
			if (search == '|') {

				File_product.read((char*)&recordSize, sizeof(recordSize));

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.id, length);
				p1.id[length] = '\0';

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.Name, length);
				p1.Name[length] = '\0';

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.quntity, length);
				p1.quntity[length] = '\0';

				File_product.read((char*)(&length), sizeof(short));
				File_product.read(p1.price, length);
				p1.price[length] = '\0';

				if (strcmp(ID, p1.id) == 0) // strcmp return 0 if two equal
				{ 
					cout << "-----------------------------------------------\n";
					cout << "  id         ::  " << p1.id << endl;
					cout << "  Name       ::  " << p1.Name << endl;
					cout << "  quntity    ::  " << p1.quntity << endl;
					cout << "  price      ::  " << p1.price << endl;
					cout << "-----------------------------------------------\n";
					File_product.clear();
					break;
				}
			}
		}
		if ( strcmp(ID, p1.id) != 0 )
			cout << "\t* Product is not found!! *\n";
		File_product.close();
	}
	else cout << "\n\t* Error! can't open file *\n";
}


void Product::Delete_product()
{
	char ID[10];
	cin.ignore();
	cin.getline(ID, 10);
	Product p1;
	fstream  File_product;
	bool found = false;
	char search;
	short recordSize;
	int pos;
	File_product.open("File_Product.txt", ios::in | ios::binary | ios::out); // read & write 
	if (File_product.is_open())
	{
		while (File_product >> search)
		{
			short length;
			if (search == '|')
			{
				File_product.read((char*)&recordSize, sizeof(recordSize));

				File_product.read((char*)(&length), sizeof(short)); // read len for id
				pos = File_product.tellg();        // return pos of cursor 
				//cout << " pos " << pos << endl;
				File_product.read(p1.id, length);  // read data in len & put in id
				p1.id[length] = '\0';

				if ( strcmp(ID, p1.id) == 0 )  
				{
					found = true;
				   File_product.seekg(pos - 5); // 5 sizeof ( 1 byte '|',2 byte size record,2 byte size feild name)
				   File_product.put('*');      // seekg -> reset curser to beginging of record
					break;
				}

				else
				{
					File_product.read((char*)(&length), sizeof(short));
					File_product.read(p1.Name, length);
					p1.Name[length] = '\0';

					File_product.read((char*)(&length), sizeof(short));
					File_product.read(p1.quntity, length);
					p1.quntity[length] = '\0';

					File_product.read((char*)(&length), sizeof(short));
					File_product.read(p1.price, length);
					p1.price[length] = '\0';
				}
			}
		}
		File_product.close();
	if (!found)
		cout << "\t* Product is not found *\n";
}

}