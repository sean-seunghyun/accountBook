//AccountBook.h
#ifndef _ACCOUNTBOOK_H
#define _ACCOUNTBOOK_H
#include"Array.h"
#include"Date.h"
#include<string>
using namespace std;
typedef double Currency;
typedef signed long int Long;
class Account;
class AccountBook {
public:
	AccountBook(Long capacity = 256);
	AccountBook(const AccountBook& source);
	~AccountBook();
	Long Record(Date date, const string& description, Currency amounts, const string& note);
	void Find(Date date, Long *(*indexes), Long *count);
	void Find(string description, Long *(*indexes), Long *count);
	void Find(Date start, const Date& end, Long *(*indexes), Long *count);
	void Find(Date date, string description, Long *(*indexes), Long *count);
	Long Correct(Long index, Currency amounts,string note);
	void Calculate(Date start, const Date& end, Currency *totalIncome, Currency *totalOutgo, Currency *difference);
	Account* GetAt(Long index);	
	AccountBook& operator = (const AccountBook& source);	
	Long GetCapacity() const;
	Long GetLength() const;

private:
	Array<Account*> accounts;
	Long capacity;
	Long length;

};
int CompareDates(void *one, void *other);
int CompareDescriptions(void *one, void *other);



inline Long AccountBook::GetCapacity() const {
	return this->capacity;
}

inline Long AccountBook::GetLength() const {
	return this->length;
}


#endif // !_ACCOUNTBOOK_H
