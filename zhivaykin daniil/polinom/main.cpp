#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include "Polynom.h"

using namespace std;

int main()
{

	string s1;
	string s2;
	int q;

	cout << "--------Polynom_calc--------" << endl << endl;
	//epl x^2-2xy+2z y+2x^2y-1
	cout << "Enter the first polynom :" << endl;
	cin >> s1;
	cout << "Insert 2nd polynom" << endl;
	cin >> s2;
	Polynom p1(s1);
	Polynom p2(s2);
	try
	{
		cout << "1 polynom:" << endl << p1 << endl;
		cout << "2 polynom:" << endl << p2 << endl;
		cout << "Select an action: 1 - sum, 2 - sub, 3 - mult" << endl;
		cin >> q;
			switch (q)
			{
			case 1:
			{
				try
				{
					cout << "Sum: " << p1 + p2 << endl;
					system("pause");
					break;
				}
				catch (const exception& e)
				{
					cout << e.what() << endl;
				}
			}
			case 2:
			{
				try
				{
					cout << "Substraction: " << p1 - p2 << endl;
					system("pause");
					break;
				}
				catch (const exception& e)
				{
					cout << e.what() << endl;
				}
			}
			case 3:
			{
				try
				{
					cout << "Multiplication: " << p1 * p2 << endl;
					system("pause");
					break;
				}
				catch (const exception& e)
				{
					cout << e.what() << endl;
				}
			}
			default:
				cout << "Incorrect input" << endl;
				system("pause");
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
