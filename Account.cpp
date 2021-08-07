//Account.cpp
#include"Account.h"
Account::Account()
	:description(""), note("") {
	this->amounts = 0;
	this->balance = 0;
}

Account::Account(Date date, string description, Currency amounts, Currency balance, string note)
	:date(date),description(description),note(note){
	this->amounts = amounts;
	this->balance = balance;
}

Account::Account(const Account& source)
	:date(source.date), description(source.description), note(source.note){
	this->amounts = source.amounts;
	this->balance = source.balance;
}

Account::~Account() {

}

bool Account::IsEqual(const Account& other) {
	bool ret = false;
	if (this->date.IsEqual(other.date) &&
		this->description == other.description &&
		this->amounts == other.amounts &&
		this->balance == other.balance &&
		this->note == other.note) {
		ret = true;
	}
	return ret;
}

bool Account::IsNotEqual(const Account& other) {
	bool ret = false;

	if (this->date.IsNotEqual(other.date) ||
		this->description != other.description ||
		this->amounts != other.amounts ||
		this->balance != other.balance ||
		this->note != other.note) {
		ret = true;
	}
	return ret;
}

bool Account::operator ==(const Account& other) {
	bool ret = false;
	if (this->date==other.date &&
		this->description == other.description &&
		this->amounts == other.amounts &&
		this->balance == other.balance &&
		this->note == other.note) {
		ret = true;
	}
	return ret;
}

bool Account::operator !=(const Account& other) {
	bool ret = false;

	if (this->date != other.date ||
		this->description != other.description ||
		this->amounts != other.amounts ||
		this->balance != other.balance ||
		this->note != other.note) {
		ret = true;
	}
	return ret;
}

Account& Account::operator = (const Account& source) {
	this->date = source.date;
	this->description = source.description;
	this->amounts = source.amounts;
	this->balance = source.balance;
	this->note = source.note;

	return *this;
}


