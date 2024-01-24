#include"Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Order.h"
#include"Employees.h"
using namespace std;
int main()
{
	Product p1;
	order o1;
	Employees emp;
	int choice, option;
	cout << "\n \t* WELCOME TO OUR SUPERMARKET SYSTEM! *" << endl;
	do {
		cout << "\n Which file would you like to open\n\n 1) Product\n 2) Order\n 3) Employees\n 4) Exit\n\n Enter your Option :: ";
		cin >> option;
		switch (option) {
		case 1:
		{
			do {
				cout << "\n 1) Add Product\n";
				cout << " 2) Display Product\n";
				cout << " 3) Search Product\n";
				cout << " 4) Update Product\n";
				cout << " 5) Delete Product\n";
				cout << " 6) Exit \n";
				cout << "\n Select choice :: ";
				cin >> choice;
				cout << endl;

				switch (choice)
				{
				case 1: {
					p1.Add_product();
					system("CLS");
				}
					  break;
				case 2:
				{
					p1.Display_product();
				}
				break;
				case 3:
				{
					p1.search_product();
				}
				break;
				case 4:
				{
					cout << endl << "Enter ID of the Product you want to Update :: ";
					p1.Update_product();
				}
				break;
				case 5:
				{
					cout << endl << "Enter ID to Delete :: ";
					p1.Delete_product();
				}
				break;
				case 6: {
					system("CLS");
				}
					  break;
				default:
				{
					cout << "\t* Wrong choice *\n";
				}
				break;
				}
			} while (choice != 6);
			break;
		}


		case 2:
		{
			do {
				cout << "\n 1) Add Order\n";
				cout << " 2) Display Order\n";
				cout << " 3) Search Order\n";
				cout << " 4) Update Order\n";
				cout << " 5) Delete Order\n";
				cout << " 6) Exit \n";
				cout << "\n Select choice :: ";
				cin >> choice;
				cout << endl;
				switch (choice)
				{
				case 1:
				{
					o1.Add_Order();

				}

				break;
				case 2:
				{


					o1.Display_Orders();
				}
				break;
				case 3:
				{

					o1.search_Orders();
				}
				break;
				case 4:
				{
					cout << "Enter Order name you want to Update :: ";

					o1.Update_Order();
				}
				break;
				case 5:
				{
					cout << "Enter Order name you want to delete :: ";

					o1.Delete_Order();
				}
				break;
				case 6:
				{
					system("CLS");
				}
				break;
				default:
				{
					cout << "\t* Wrong choice *\n";
				}
				break;
				}
			} while (choice != 6);

			break;
		}


		case 3:
		{
			do {

				cout << "\n 1) Add Employee\n";
				cout << " 2) Display Employees\n";
				cout << " 3) Search Employee\n";
				cout << " 4) Update Employee\n";
				cout << " 5) Delete Employee\n";
				cout << " 6) Exit \n";
				cout << "\n Select choice :: ";
				cin >> choice;
				cout << endl << endl;
				switch (choice)
				{
				case 1: {
					emp.Add_employee();

				}

					  break;
				case 2:
				{
					emp.Display_employee();
				}
				break;
				case 3:
				{
					emp.search_employee();
				}
				break;
				case 4:
				{
					cout << " Enter Name of Employee that you want to update :: ";
					emp.Update_employee();
				}
				break;
				case 5:
				{
					cout << " Enter Name of Employee that you want to delete :: ";
					emp.Delete_employee();
				}
				break;
				case 6:
				{
					system("CLS");
				}
				break;
				default:
				{
					cout << "\t* Wrong choice *\n";
				}
				break;
				}

			} while (choice != 6);

			break;
		}
		case 4:
		{
			system("CLS");
		}
		break;
		}

	} while (option != 4);


	return 0;
}