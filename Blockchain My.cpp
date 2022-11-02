#include "SHA256.h"
#include "Header.h"


int main()
{
	vector<user> users;
	vector<transaction> transactions;
	vector<block> blockchain;
	genUsers(users);
	printUser(users);
	genTX(transactions, users);
	printTX(transactions);
	mining(users, transactions, blockchain);
	printBlock(blockchain);

}

