#include "SHA256.h"
#include "Header.h"


int main()
{
	vector<user> users;
	vector<transaction> transactions;
	vector<block> blockchain;
	genUsers(users);
	genTX(transactions, users);
	mining(users, transactions, blockchain);


}

