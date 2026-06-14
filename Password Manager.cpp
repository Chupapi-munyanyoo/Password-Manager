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
	cout << "4. Give All Passwords (website)\n";
	cout << "5. Literally All Passwords\n";
	cout << "6. Update Password (website,username and new password)\n";
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
		cin.ignore();

		if (option == 0) { cerr << "Miss u :/\n";break; }

		else if (option == 1)
		{
			string a, b, c;
			cerr << "Insert Website Name : ";
			getline(cin,a);
			cerr << "Insert UserName : ";
			getline(cin,b);
			cerr << "Insert Password : ";
			getline(cin,c);

			cout<<endl;

			Test.insert(a, b, c);
		}
		else if (option == 2)
		{
			string a, b;
			cerr << "Insert Website Name : ";
			getline(cin,a);
			cerr << "Insert UserName : ";
			getline(cin,b);

			Test.remove(a, b);
			cout<<endl;
		}
		else if (option == 3)
		{
			string a, b;
			cerr << "Insert Website Name : ";
			getline(cin,a);
			cerr << "Insert UserName : ";
			getline(cin,b);
			cout<<endl;
			
			Test.display(a, b);
		}
		else if (option == 4)
		{
			string b;
			cerr << "Insert Website : ";
			getline(cin,b);
			
			cout<<endl;
			
			Test.display(b);
		}
		else if (option == 5)
		{
			cout<<endl;
			
			Test.display();
		}
		else if(option == 6)
		{
			cout<<endl;
			string a, b, c;
			cerr << "Insert Website Name : ";
			getline(cin,a);
			cerr << "Insert UserName : ";
			getline(cin,b);
			cerr << "Insert New Password : ";
			getline(cin,c);

			Test.update(a,b,c);
		}
		else
		{
			cerr << " wrong option\n";
			cout<<endl;
			
		}
	}
}