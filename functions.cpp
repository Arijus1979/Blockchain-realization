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

void verifyTX(int location, int random, vector<user> &users, vector<transaction> &transactions, bool &verification, block &temporary, vector<transaction> &TXs)
{
	if (users.at(location).getBalance() >= transactions.at(random).getSum())
	{
		/*cout << location << endl;
		cout << random << endl;
		cout << users.at(location).getBalance() << " " << transactions.at(random).getSum() << endl;
		cout << transactions.at(random).getID() << endl;
		cout << endl;*/
		TXs.push_back(transactions.at(random));
		//cout << TXs.size();

		//cout << transactions.at(random).getID() << endl;
		if (TXs.back().getID() != transactions.at(random).getID())
		{
			TXs.pop_back();
		}
		//cout << transactions.size() << endl;
		transactions.erase(transactions.begin() + random);
		//cout << transactions.size() << endl;
		//cout << endl;
		verification = true;
	}
	else
	{
		/*cout << location << endl;
		cout << random << endl;
		cout << users.at(location).getBalance() << " " << transactions.at(random).getSum() << endl;
		cout << transactions.at(random).getID() << endl;
		cout << users.at(location).getPublicKey() << endl;
		cout << transactions.at(random).getSender() << endl;
		cout << endl;*/
		transactions.erase(transactions.begin() + random);
		verification = false;
	}
	//cout << TXs.size() << endl;
	temporary.setTransactions(TXs);
}

string MerkelRootGen(block& blockchain)
{
	stringstream ss;
	for (int i = 0; i < blockchain.getBlockTransactions().size(); i++)
	{
		ss << blockchain.getBlockTransactions().at(i).getID();
		//cout << blockchain.getBlockTransactions().at(i).getID() << endl;
	}
	return sha256(ss.str());
}

string setBlock(block &blockchain, string previousHash, int k)
{
	string newhash;
	if (k == 1)
		blockchain.setPrevHash(sha256("first_block"));

	else
		blockchain.setPrevHash(previousHash);

	blockchain.setTime(time(0));
	blockchain.setVersion("v" + to_string(k));
	blockchain.setDifficulty("00");
	blockchain.setMerkelRoot(MerkelRootGen(blockchain));

	int x = blockchain.getDiff().size();
	
	int nonce = 0;
	while (true)
	{
		newhash = sha256(blockchain.getDiff() + blockchain.getMerkelRootHash() + 
			blockchain.getPrevHash() + to_string(blockchain.getTime()) + 
			blockchain.getVersion() + to_string(nonce));
		if (newhash.substr(0, x) == blockchain.getDiff())
		{
			blockchain.setNonce(nonce);
			return newhash;
		}
		nonce++;
	}
	return "0";
}

void mining(vector<user> users, vector<transaction> transactions, vector<block>& blockchain)
{
	vector<transaction> TXs;
	bool verification;
	int k = 0, q = 0;
	
	while (transactions.size() != 0)
	{
		block temporary;
		while (q <= 100 && transactions.size() != 0/*blockchain.size() <= 100*/)
		{
			//cout << blockchain.size() << endl;
			int random = rand() % transactions.size(), location;
			//cout << transactions.size() << endl;
			for (location = 0; location < users.size(); location++)
			{
				if (transactions.at(random).getSender() == users.at(location).getPublicKey())
				{
					break;
				}
			}
			
			verifyTX(location, random, users, transactions, verification, temporary, TXs);
			q++;
		}
		k++;

		if (k == 1)
		{
			temporary.setBlockHash(setBlock(temporary, "", k));
			//cout << temporary.getBlockHash() << endl;
		}
		else
		{
			temporary.setBlockHash(setBlock(temporary, blockchain.at(k - 2).getBlockHash(), k));
		}

		blockchain.push_back(temporary);
		cout << "Block mined! hash: " << blockchain.at(k - 1).getBlockHash() << " " << blockchain.at(k - 1).getBlockTransactions().size() << endl;
		TXs.clear();

		for (auto tran : blockchain.at(k - 1).getBlockTransactions()) 
		{
			int send = 0, get = 0;
			for (int i = 0; i < 1000; i++) {
				if (users.at(i).getPublicKey() == tran.getSender())
					send = i;
				else if (users.at(i).getPublicKey() == tran.getReceiver())
					get = i;
				if (send != 0 && get != 0)
					break;
			}

			users.at(send).setBalance(users.at(send).getBalance() - tran.getSum());
			users.at(get).setBalance(users.at(send).getBalance() + tran.getSum());
		}
		q = 0;
	}
}