//Account.h
#ifndef _ACCOUNT_H
#define _ACCOUNT_H
#include "Date.h"
#include<string>
using namespace std;
typedef double Currency;

class Account {
public:
	Account();
	Account(Date date, string description, Currency amounts, Currency balance, string note);
	Account(const Account& source);
	virtual ~Account() = 0;
	bool IsEqual(const Account& other);
	bool IsNotEqual(const Account& other);
	Account& operator = (const Account& source);
	bool operator == (const Account& other);
	bool operator != (const Account &other);
	Date& GetDate() const;
	string& GetDescription() const;
	Currency GetAmounts() const;
	Currency GetBalance() const;
	string& GetNote() const;
protected:
	Date date;
	string description;
	Currency amounts;
	Currency balance;
	string note;

};

inline Date& Account::GetDate() const {
	return const_cast<Date&>(this->date);

}

inline string& Account::GetDescription() const {
	return const_cast<string&>(this->description);
}

inline Currency Account::GetAmounts() const {
	return this->amounts;
}

inline Currency Account::GetBalance() const {
	return this->balance;
}

inline string& Account::GetNote() const {
	return const_cast<string&>(this->note);
}

#endif //_ACCOUNT_H