#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int count = 0;
vector<vector<string> > accounts;

int registration() 
{
	system("cls");
	
	std::string userId, email, password, confirmPassword;
	cout << "\nEnter your Student ID, it will be your username.\nUSERNAME: " ;
	cin >> userId;
	cout << "Enter your UST Email address.\nEMAIL: ";
	cin >> email;
	
	while (1)
	{
		cout << "\nHello, " << email << " !" << endl;
		cout << "Please enter a new password for your account\nPASSWORD: " ;
		cin >> password;
		
		if (password == "exit")
		{
			return 0;
		}
		cout << "CONFIRMED PASSWORD: ";
		cin >> confirmPassword;
		
		if (password != confirmPassword)
		{
			cout << "confirmed passowrd does not match password\n";
			continue;			
		} else {
			break;
		}
	}
	
	count++;
	std::ofstream records;
	records.open("accounts.csv", std::ios_base::app);
	
	records << "\n" << count << "," << userId << "," << email << "," << password;
	records.close();
	return 1;
	
}

int verifyLogin(string username, string password)
{
	accounts.clear();
	vector<string> row;
	string line, word;
	ifstream records("accounts.csv", ios::in);
	if (records.is_open())
	{
		while(getline(records, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
			{
				row.push_back(word);
			}
			accounts.push_back(row);
		}
	} else {
		return -1;
	}

	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i][1] == username && accounts[i][3] == password)
		{
			return i;
		}
	}
	return -1;
}

int login()
{
	string username, password;
	system("cls");
	while (1)
	{
		cout << "\nPlease enter your username and passowrd (type 'quit' to exit)\n";
		cout << "USERNAME: ";
		cin >> username;
		if (username == "quit")
		{
			return -1;
		}
		cout << "PASSWORD: ";
		cin >> password;
		if (password == "quit")
		{
			return -1;
		}

		int accountIndex = verifyLogin(username, password);
		if (accountIndex >= 0)
		{
			return accountIndex;
		} else {
			cout << "Unable to login please check your username and password again\n";	
			continue;
		}
	}
	return 0;
}

int searchAccount(string username)
{
	accounts.clear();
	vector<string> row;
	string line, word;
	ifstream records("accounts.csv", ios::in);
	if (records.is_open())
	{
		while(getline(records, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
			{
				row.push_back(word);
			}
			accounts.push_back(row);
		}
	} else {
		return 0;
	}

	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i][1] == username)
		{
			return 1;
		}
	}
	return 0;
}
int forgot()
{
	string username;
	system("cls");
	cout << "forgot password? select an option from the following\n";
	cout << "Enter your username (type 'quit' to exit)\nUSERNAME: ";
	cin >> username;
	if (username == "quit") 
	{
		return 0;
	}
	if (searchAccount(username))
	{
		cout << "We have found your account, please check your UST email inbox for the password reset link.\n";
	}
	return 0;
}


int main (void)
{
	bool quit = false;
	while (!quit)
	{
		cout << "\nWelcome to the Library's main page.\n";
		
		cout << "Please enter the designated number for the following options below:\n";

		cout << "1 - Login.\n";	
		cout << "2 - Create an account.\n";
		cout << "3 - Forgot Password\n";
		cout << "4 - exit\n:";
		
		int choice;
		cin >> choice;
		
		switch(choice)
		{
			case 1:
				int index;
				index = login();
				if (index >= 0)
				{
					system("cls");
					cout << "Welcome " << accounts[index][1] << "!\n";
					cout << "Your login is successful. Thank you for loggin in!\n";
				}
				break;
			case 2:
				if (registration())
				{
					cout << "Account Successfully Registered\n";
				} else
				{
					cout << "Account Creation was Unsuccessful\n";
				}
				break;
			case 3:
				forgot();
				break;
			case 4:
				cout << "Thank you have a great day!\n";
				quit = true;
				break;
			default:
				system("cls");
		}
	}
}



