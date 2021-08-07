//AccountBook.cpp
#include"AccountBook.h"
#include"Account.h"
#include"Income.h"
#include"Outgo.h"

AccountBook::AccountBook(Long capacity)
	:accounts(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

AccountBook::AccountBook(const AccountBook& source)
	: accounts(source.accounts) {
	Account *account;
	Long i = 0;
	while (i < source.length) {
		account = (const_cast<AccountBook&>(source)).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account)) {
			account = new Income(*(dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account)) {
			account = new Outgo(*(dynamic_cast<Outgo*>(account)));
		}
		this->accounts.Modify(i, account);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

AccountBook::~AccountBook() {
	Account *account;
	Long i = 0;
	while (i < this->length) {
		account = this->accounts.GetAt(i);
		if (account != 0) {
			delete account;
		}
		i++;
	}
}

AccountBook& AccountBook::operator= (const AccountBook& source) {
	Account *account;
	Long i = 0;
	while (i < this->length) {
		account = this->accounts.GetAt(i);
		if (account != 0) {
			delete account;
		}
		i++;
	}

	this->accounts = source.accounts;
	i = 0;
	while (i < source.length) {
		account = (const_cast<AccountBook&>(source)).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account)) {
			account = new Income(*(dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account)) {
			account = new Outgo(*(dynamic_cast<Outgo*>(account)));
		}
		this->accounts.Modify(i, account);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long AccountBook::Record(Date date, const string& description, Currency amounts, const string& note) {
	Currency balance = 0;
	Account *account;
	Account *accountBefore;
	Long index;
	if (this->length > 0) {
		accountBefore = this->accounts.GetAt(this->length - 1);
		balance = accountBefore->GetBalance();
	}
	balance = balance + amounts;
	if (amounts > 0) {
		account = new Income(date, description, amounts, balance, note);
	}
	else {
		account = new Outgo(date, description, -amounts, balance, note);
	}
	if (this->length < this->capacity) {
		index = this->accounts.Store(this->length, account);
	}
	else {
		index = this->accounts.AppendFromRear(account);
		this->capacity++;
	}
	this->length++;

	return index;
}

void AccountBook::Find(Date date, Long *(*indexes), Long *count) {
	this->accounts.LinearSearchDuplicate(&date, indexes, count, CompareDates);
}

void AccountBook::Find(string description, Long *(*indexes), Long *count) {
	this->accounts.LinearSearchDuplicate(&description, indexes, count, CompareDescriptions);
}


void AccountBook::Find(Date start, const Date& end, Long *(*indexes), Long *count) {
	Long(*keys);
	Long countKeys;
	Long i = 0;
	Long j;
	*indexes = new Long[this->length];
	*count = 0;
	while (start <= end) {
		this->accounts.LinearSearchDuplicate(&start, &keys, &countKeys, CompareDates);
		j = 0;
		while (j < countKeys) {
			(*indexes)[i] = keys[j];
			i++;
			(*count)++;
			j++;
		}
		if (keys != 0) {
			delete[] keys;
		}
		start++;
	}
}

void AccountBook::Find(Date date, string description, Long *(*indexes), Long *count) {
	Long(*keys);
	Long countKeys;
	Long i = 0;
	Long j = 0;
	Account *account;
	string descriptionFromKeys;
	this->accounts.LinearSearchDuplicate(&date, &keys, &countKeys, &CompareDates);
	*indexes = new Long[countKeys];
	*count = 0;
	while (i < countKeys) {
		account = this->accounts.GetAt(keys[i]);
		descriptionFromKeys = account->GetDescription();
		if (descriptionFromKeys.compare(description) == 0) {
			(*indexes)[j] = keys[i];
			j++;
			(*count)++;
		}
		i++;
	}
	if (keys != 0) {
		delete[] keys;
	}
}

Long AccountBook::Correct(Long index, Currency amounts, string note) {
	Date date;
	string description;	
	Currency balance=0;
	Currency balanceBefore;
	Long indexAfter;
	Account *account;
	Account *accountBefore;

	//인덱스번째 계정을 불러온다.
	account = this->accounts.GetAt(index);
	//불러온 계정의 날짜를 읽는다.
	date = account->GetDate();
	//불러온 계정의 적요를 읽는다.
	description = account->GetDescription();
	//불러온 계정의 노트를 읽는다. ->필요없어짐
	//note = account->GetNote();
	if (index > 0) {
		accountBefore = this->accounts.GetAt(index - 1);
		balance = accountBefore->GetBalance();
	}
	if (dynamic_cast<Income*>(account)) {
		balance = balance + amounts;
		if (account != 0) {
			delete account;
		}
		account = new Income(date, description, amounts, balance, note);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		balance = balance - amounts;
		if (account != 0) {
			delete account;
		}
		account = new Outgo(date, description, amounts, balance, note);
	}
	index = this->accounts.Modify(index, account);
	indexAfter = index + 1;
	while (indexAfter < this->length) {
		account = this->accounts.GetAt(indexAfter);
		date = account->GetDate();
		description = account->GetDescription();
		amounts = account->GetAmounts();
		note = account->GetNote();
		accountBefore = this->accounts.GetAt(indexAfter - 1);
		balanceBefore = accountBefore->GetBalance();
		if (dynamic_cast<Income*>(account)) {
			balance = balance + amounts;
			if (account != 0) {
				delete account;
			}
			account = new Income(date, description, amounts, balance, note);
		}
		else if (dynamic_cast<Outgo*>(account)) {
			balance = balance - amounts;
			if (account != 0) {
				delete account;
			}
			account = new Outgo(date, description, amounts, balance, note);
		}
		this->accounts.Modify(indexAfter, account);
		indexAfter++;
	}
	return index;
}

void AccountBook::Calculate(Date start, const Date& end, Currency *totalIncome, Currency *totalOutgo, Currency *difference) {
	Account *account;
	Long(*indexes);
	Long count;
	Currency amounts;
	Long i;
	*totalIncome = 0;
	*totalOutgo = 0;
	*difference = 0;
	while (start <= end) {
		this->accounts.LinearSearchDuplicate(&start, &indexes, &count, CompareDates);
		i = 0;
		while (i < count) {
			account = this->accounts.GetAt(indexes[i]);
			amounts = account->GetAmounts();
			if (dynamic_cast<Income*>(account)) {
				(*totalIncome) += amounts;
			}
			else if (dynamic_cast<Outgo*>(account)) {
				(*totalOutgo) += amounts;
			}
			*difference = *totalIncome - *totalOutgo;
			i++;
		}
		if (indexes != 0) {
			delete[] indexes;
		}
		start++;
	}
}

Account* AccountBook::GetAt(Long index) {
	Account *account;
	account = this->accounts.GetAt(index);

	return account;
}

int CompareDates(void *one, void *other) {
	Account* *one_ = static_cast<Account**>(one);
	Date *other_ = static_cast<Date*>(other);
	int ret;
	if ((*one_)->GetDate() > *other_) {
		ret = 1;
	}
	else if ((*one_)->GetDate() == *other_) {
		ret = 0;
	}
	else if ((*one_)->GetDate() < *other_) {
		ret = -1;
	}
	return ret;
}

int CompareDescriptions(void *one, void *other) {
	Account* *one_ = static_cast<Account**>(one);
	string *other_ = static_cast<string*>(other);

	return (*one_)->GetDescription().compare(*other_);
}



#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	AccountBook accountBook;
	Long count;
	Long(*indexes);
	Currency totalIncome;
	Currency totalOutgo;
	Currency difference;
	Long index;
	Account *account;
	Long i;
	
	
	index = accountBook.Record("20200101", "용돈", 500000, "아빠");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " "
		<< account->GetDescription() << " "
		<< account->GetAmounts() << " "
		<< account->GetBalance() << " "
		<< account->GetNote() << endl;


	index = accountBook.Record("20200101", "회식", -30000, "친구들");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " "
		<< account->GetDescription() << " "
		<< account->GetAmounts() << " "
		<< account->GetBalance() << " "
		<< account->GetNote() << endl;


	index = accountBook.Record("20200107", "교통", -100000, "");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " "
		<< account->GetDescription() << " "
		<< account->GetAmounts() << " "
		<< account->GetBalance() << " "
		<< account->GetNote() << endl;

	index = accountBook.Record("20200108", "용돈", 300000, "엄마");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " "
		<< account->GetDescription() << " "
		<< account->GetAmounts() << " "
		<< account->GetBalance() << " "
		<< account->GetNote() << endl;

	cout << "찾기-날짜" << endl;
	Date date("20200101");
	accountBook.Find(date, &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " "
			<< account->GetDescription() << " "
			<< account->GetAmounts() << " "
			<< account->GetBalance() << " "
			<< account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << "찾기-적요" << endl;
	string description("교통");
	accountBook.Find(description, &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " "
			<< account->GetDescription() << " "
			<< account->GetAmounts() << " "
			<< account->GetBalance() << " "
			<< account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << "찾기-날짜 범위" << endl;
	Date start("20200101");
	Date end("20200105");
	accountBook.Find(start, end, &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " "
			<< account->GetDescription() << " "
			<< account->GetAmounts() << " "
			<< account->GetBalance() << " "
			<< account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	cout << "찾기-날짜, 적요" << endl;
	date= Date("20200108");
	description =string("용돈");
	accountBook.Find(date, description, &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " "
			<< account->GetDescription() << " "
			<< account->GetAmounts() << " "
			<< account->GetBalance() << " "
			<< account->GetNote() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	cout << "고치기" << endl;
	index = accountBook.Correct(0, 100000);
	i = 0;
	while (i <accountBook.GetLength()) {
		account = accountBook.GetAt(i);
		cout << account->GetDate() << " "
			<< account->GetDescription() << " "
			<< account->GetAmounts() << " "
			<< account->GetBalance() << " "
			<< account->GetNote() << endl;
		i++;
	}

	cout << "계산하기" << endl;
	start = Date("20200108");
	end = Date("20200110");

	accountBook.Calculate(start, end, &totalIncome, &totalOutgo, &difference);
	cout << totalIncome << " "
		<< totalOutgo << " "
		<< difference << endl;

	return 0;
}
#endif