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
#include <sstream>

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
    transaction()
    {
        this->transactionID = "";
        this->sender = "";
        this->receiver = "";
        this->sum = 0;
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

class block {
private:
    string blockHash;
    vector<transaction> blockTXs;
    string prevBlockHash;
    int timestamp;
    string version;
    string MerkelRootHash;
    int nonce;
    string diff;
public:
    typedef vector<transaction> transactions;
    block(string blHash, string pBlock, int tstamp, string vers, string Mhash, int nonc, string dif)
    {
        this->blockHash = blHash;
        this->prevBlockHash = pBlock;
        this->timestamp = tstamp;
        this->version = vers;
        this->MerkelRootHash = Mhash;
        this->nonce = nonc;
        this->diff = dif;
    }
    block()
    {
        this->blockHash = "";
        this->prevBlockHash = "";
        this->timestamp = 0;
        this->version = "";
        this->MerkelRootHash = "";
        this->nonce = 0;
        this->diff = "";
    }

    string getBlockHash()
    {
        return this->blockHash;
    }

    transactions getBlockTransactions()
    {
        return this->blockTXs;
    }

    string getPrevHash()
    {
        return this->prevBlockHash;
    }

    int getTime()
    {
        return this->timestamp;
    }

    string getVersion()
    {
        return this->version;
    }

    string getMerkelRootHash()
    {
        return this->MerkelRootHash;
    }

    int getNonce()
    {
        return this->nonce;
    }

    string getDiff()
    {
        return this->diff;
    }

    void setBlockHash(string hash)
    {
        this->blockHash = hash;
    }

    void setNonce(int NewNonce)
    {
        this->nonce = NewNonce;
    }

    void setTransactions(vector<transaction> TXs)
    {
        this->blockTXs = TXs;
    }

    void setPrevHash(string hash)
    {
        this->prevBlockHash = hash;
    }

    void setTime(int time)
    {
        this->timestamp = time;
    }

    void setVersion(string vers)
    {
        this->version = vers;
    }

    void setDifficulty(string difficulty)
    {
        this->diff = difficulty;
    }

    void setMerkelRoot(string merkel)
    {
        this->MerkelRootHash = merkel;
    }
};



void genUsers(vector<user> &users);
void genTX(vector<transaction>& transactions, vector<user> users);
void mining(vector<user> users, vector<transaction> transactions, vector<block>& blockchain);