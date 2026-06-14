#include "Hashmap.h"

void greetings()
{
	cout << "Hi Welcome to your local Password Manager.\n";
}
void options()
{
	cout << "1. Insert New Password\n";
	cout << "2. Remove Password\n";
	cout << "3. Find Password (Website,Username)\n";
	cout << "4. Give All Passwords (Username)\n";
	cout << "5. Literally All Passwords\n";
	cout << "0. Exit :(\n";
}
int main()
{
	greetings();

	PasswordManager Test;

	int option = INT_MIN;
	while (option)
	{
		options();
		cin >> option;

		if (option == 0) { cerr << "Miss u :/\n";break; }

		if (option == 1)
		{
			string a, b, c;
			cerr << "Insert Website Name : ";
			cin >> a;
			cerr << "Insert UserName : ";
			cin >> b;
			cerr << "Insert Password : ";
			cin >> c;

			Test.insert(a, b, c);
		}
		if (option == 2)
		{
			string a, b;
			cerr << "Insert Website Name : ";
			cin >> a;
			cerr << "Insert UserName : ";
			cin >> b;

			Test.remove(a, b);
		}
		if (option == 3)
		{
			string a, b;
			cerr << "Insert Website Name : ";
			cin >> a;
			cerr << "Insert UserName : ";
			cin >> b;

			Test.display(a, b);
		}
		if (option == 4)
		{
			string b;
			cerr << "Insert UserName : ";
			cin >> b;

			Test.display(b);
		}
		if (option == 5)
		{
			Test.display();
		}
		else
		{
			cerr << " wrong option\n";
		}
	}
}