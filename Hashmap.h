#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;	

int stringtoint(string s)
{
	int num = 0;
	for (char c : s)
	{
		num += c;
	}
	return num;
}
int to_int(string a)
{
	int n = 0;
	for (char c : a)
	{
		n = n * 10 + (c - '0');
	}
	return n;
}

string encrypt(string password)
{
	string encrypted = "";
	for (char c : password)
	{
		encrypted += to_string(c+(stringtoint("Askari") % 256)) + " ";
	}
	return encrypted;
}
int ff(string a,int b,int c)
{
	string g;

	c -= b;
	
	for (int i = b;i < b+c;i++)
	{
		g += a[i];
	}
	return to_int(g);
}
string decrypt(string encrypted)
{
	string decrypted = "";
	int i = 0;
	
	while (i < encrypted.length())
	{
		int z = 0;
		for (int n = i;n < encrypted.length();n++)
		{
			if (encrypted[n] == ' ')break;
			z++;
		}
		if(z>0)
			decrypted += char(ff(encrypted, i, i + z)-stringtoint("Askari")%256);
		
		i += z + 1;
		z = 0;
	}
	return decrypted;
}

struct node
{
	string website;
	string username;
	string password;

	node* next;

	node(string a, string b, string c) :website(a), username(b), password(c), next(nullptr) {};
};

class linkedlist
{
protected:
	node* head;

public:
	linkedlist() :head(nullptr) {};
	void insert(string a, string b, string c)
	{
		if (!head) {
			head = new node(a, b, c);
		}
		else
		{
			node* temp = head;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new node(a, b, c);
		}
	}
	void remove(string a, string b)
	{
		if (!head) return;

		node* temp = head;
		node* prev = nullptr;
		while (temp)
		{
			if(temp->website==a&&temp->username==b)
			{
				if (temp == head)
				{
					head = head->next;
					delete temp;
					return;
				}
				else
				{
					prev->next = temp->next;
					delete temp;
					return;
				}
			}
			prev = temp;
			temp = temp->next;
		}
	}
	void display()
	{
		node* temp = head;
		while (temp)
		{
			cout << "Website: " << temp->website << ", Username: " << temp->username << ", Password: " << decrypt(temp->password) << endl;
			temp = temp->next;
		}
	}
	void display(string a, string b)
	{
		node* temp = head;

		while (temp)
		{
			if (temp->website == a && temp->username == b)
			{
				cout << "Website: " << temp->website << ", Username: " << temp->username << ", Password: " << decrypt(temp->password) << endl;
				return;
			}
			temp = temp->next;
		}
	}
	void display(string b)
	{
		node* temp = head;
		while (temp)
		{
			if (temp->website == b)
			{
				cout << "Website: " << temp->website << ", Username: " << temp->username << ", Password: " << decrypt(temp->password) << endl;
			}
			temp = temp->next;
		}
	}
	void update(string a, string b, string c)
	{
		node* temp = head;
		while (temp)
		{
			if (temp->website == a && temp->username == b)
			{
				temp->password = c;
				return;
			}
			temp = temp->next;
		}
	}
	~linkedlist() {
		node* temp = head;
		while (temp)
		{
			node* next = temp->next;
			delete temp;
			temp = next;
		}
	}
	node* returnhead()
	{
		return head;
	}
};

class hashmap
{
	const int size = 20;
	linkedlist* table;
	
public:
	hashmap() {
		table = new linkedlist[size];
	}

	int hashfunction(string key) {
		int hash = 0;
		for (char c : key) {
			hash += c;
		}
		return hash % size;
	}
	
	
	void insert(string website, string username, string password,bool fromfile) {
		int index = hashfunction(website);
		if(fromfile)
			table[index].insert(website, username, password);
		else
			table[index].insert(website,username,encrypt(password));

		ofstream in("Passwords.txt",ios::app);

		if(!fromfile)
			append(in,website,username,encrypt(password));

	}
	void append(ofstream& in,string a,string b,string c)
	{
		in<<a<<" "<<b<<" "<<c<<endl;
		in.close();
	}
	void readfromfile()
	{
		ifstream file("Passwords.txt");
		if (!file)
		{
			ofstream f("Passwords.txt");
			f.close();

			return;
		}
		string a = "", b = "", c = "";
		while (file >> a >> b)
		{
			char ws;
			file>>ws;
			getline(file,c);
			
			if (a != "" && b != "" && c != "")
			{
				insert(a, b, c,true);
			}
		}
		file.close();
	}
	
	void writetofile()
	{
		ofstream file("Passwords.txt");
		for (int i = 0; i < size; i++) {
			node* temp = table[i].returnhead();
			while (temp)
			{
				file << temp->website << " " << temp->username << " " << temp->password << endl;
				temp = temp->next;
			}
		}
		file.close();
	}

	void remove(string website, string username) {
		int index = hashfunction(website);
		table[index].remove(website, username);
		writetofile();
	}

	void update(string website, string username, string password) {
		int index = hashfunction(website);
		table[index].update(website, username, password);
		writetofile();
	}

	void display() {
		for (int i = 0; i < size; i++) {
			table[i].display();
		}
	}

	void display(string website, string username) {
		int index = hashfunction(website);
		table[index].display(website, username);
	}

	void display(string website) {
		for (int i = 0; i < size; i++) {
			table[i].display(website);
		}
	}

	~hashmap() {
		
		delete[] table;
	}
};

class PasswordManager
{
	hashmap* LOL;

public: 
	PasswordManager():LOL(new hashmap) {
		LOL->readfromfile();
	};
	void insert(string a, string b, string c)
	{
		LOL->insert(a, b, c,0);
	}
	void remove(string a, string b)
	{
		LOL->remove(a, b);
	}
	void update(string a, string b, string c)
	{
		LOL->update(a, b, c);
	}
	void display()
	{
		LOL->display();
	}
	void display(string a, string b)
	{
		LOL->display(a, b);
	}
	void display(string b)
	{
		LOL->display(b);
	}
};
