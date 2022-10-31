#include "Header.h"
#include "SHA256.h"

char yn()
{
	char ats;
	while (true)
	{
		cin >> ats;
		if (ats != 'y' && ats != 'n' && ats != 'Y' && ats != 'N')
			cout << "Y/N ";
		else break;
	}
	return ats;
}

void genUsers(vector<user>& users)
{
	char ats;
	user user("", "", 0);
	for (int i = 1; i <= 1000; i++)
	{
		user.setName("user" + to_string(i));
		user.setPublicKey(sha256(user.getName()));
		user.setBalance(rand() % 999900 + 100);
		users.push_back(user);
	}

	cout << "Would you like to print out the users? [Y/N]";
	ats=yn();
	if (ats == 'Y' || ats == 'y')
	{
		for (int i = 0; i < users.size(); i++) {
			cout << "User" + to_string(i + 1) << ":" << endl;
			cout << "Name: " << users.at(i).getName() << endl;
			cout << "Public key: " << users.at(i).getPublicKey() << endl;
			cout << "Balance: " << users.at(i).getBalance() << endl;
			cout << endl;
		}
	}
}

void genTX(vector<transaction>& transactions, vector<user> users)
{
	char ats;
	transaction transaction("", "", "", 0);
	for (int i = 0; i < 10000; i++)
	{
		transaction.setSender(users.at(rand() % 1000).getPublicKey());
		transaction.setReceiver(users.at(rand() % 1000).getPublicKey());
		transaction.setSum(rand() % 10000 + 1);
		transaction.setID(sha256(transaction.getSender() + transaction.getReceiver() + to_string(transaction.getSum())));
		transactions.push_back(transaction);
	}
	cout << "Would you like to print out the transactions? [Y/N]";
	ats = yn();
	if (ats == 'Y' || ats == 'y')
	{

		for (int i = 0; i < transactions.size(); i++) {
			cout << "Transaction" + to_string(i + 1) << ":" << endl;
			cout << "Transaction ID :" << transactions.at(i).getID() << endl;
			cout << "Sender: " << transactions.at(i).getSender() << endl;
			cout << "Receiver: " << transactions.at(i).getReceiver() << endl;
			cout << "Sum: " << transactions.at(i).getSum() << endl;
			cout << endl;
		}
	}
}

