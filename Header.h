#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <chrono>

using namespace std;

class user
{
private:
	string name;
	string public_key;
	int balance;

public:
    user(string name, string public_key, int bal) 
    {
        this->name = name;
        this->public_key = public_key;
        this->balance = bal;
    }

    string getName()
    {
        return this->name;
    }
    string getPublicKey()
    {
        return this->public_key;
    }
    int getBalance()
    {
        return this->balance;
    }

    void setName(string username)
    {
        this->name = username;
    }
    void setPublicKey(string key)
    {
        this->public_key = key;
    }
    void setBalance(int bal)
    {
        this->balance = bal;
    }

};

class transaction
{
private:
    string transactionID;
    string sender;
    string receiver;
    int sum;

public:
    transaction(string trxID, string send, string rec, int sum)
    {
        this->transactionID = trxID;
        this->sender = send;
        this->receiver = rec;
        this->sum = sum;
    }

    string getID()
    {
        return this->transactionID;
    }

    string getSender()
    {
        return this->sender;
    }

    string getReceiver()
    {
        return this->receiver;
    }

    int getSum()
    {
        return this->sum;
    }

    void setID(string ID)
    {
        this->transactionID = ID;
    }

    void setSender(string send)
    {
        this->sender = send;
    }

    void setReceiver(string receive)
    {
        this->receiver = receive;
    }

    void setSum(int suma)
    {
        this->sum = suma;
    }
};





void genUsers(vector<user> &users);
void genTX(vector<transaction>& transactions, vector<user> users);