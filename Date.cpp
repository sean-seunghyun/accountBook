//Date.cpp
#include "Date.h"
#include<ctime>
#include<cstdio>
#pragma warning(disable:4996)

//생성자
Date::Date() {
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

//소멸자
Date::~Date() {

}

//생성자 오버로딩
Date::Date(int year, Month month, int day) {
	struct tm date = { 0, };
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
}

Date::Date(char(*date)) {
	struct tm date_ = { 0, };
	int year;
	Month month;
	int day;

	sscanf(date, "%4d%02d%02d", &year, &month, &day);

	date_.tm_year = year - 1900;
	date_.tm_mon = month - 1;
	date_.tm_mday = day;
	mktime(&date_);
	this->year = date_.tm_year + 1900;
	this->month = static_cast<Month>(date_.tm_mon + 1);
	this->day = date_.tm_mday;
	this->weekDay = static_cast<WeekDay>(date_.tm_wday);

}

//복사 생성자
Date::Date(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}

//형변환함수
Date::operator char*() {
	static char buffer[9];
	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);

	return buffer;
}


Date Date::Today() {
	time_t timer;
	struct tm *today;
	Date today_;
	time(&timer);
	today = localtime(&timer);
	today_.year = today->tm_year + 1900;
	today_.month = static_cast<Month>(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);
	
	return today_;
}

Date Date::Yesterday() {
	struct tm yesterday = { 0, };
	Date yesterday_;

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;
	mktime(&yesterday);
	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = static_cast<Month>(yesterday.tm_mon+1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}

Date Date::Tomorrow() {
	struct tm tomorrow = { 0, };
	Date tomorrow_;

	tomorrow.tm_year = this->year - 1900;
	tomorrow.tm_mon = this->month - 1;
	tomorrow.tm_mday = this->day + 1;
	mktime(&tomorrow);
	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = static_cast<Month>(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = static_cast<WeekDay>(tomorrow.tm_wday);

	return tomorrow_;
}


Date Date::PreviousDate(int days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;
	mktime(&previousDate);
	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);

	return previousDate_;
}

Date Date::NextDate(int days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;
	mktime(&nextDate);
	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);

	return nextDate_;
}

//참조에 의한 정보전달
bool Date::IsEqual(const Date& other) {
	bool ret = false;
	if (this->year == other.year &&
		this->month == other.month &&
		this->day == other.day) {
		ret = true;
	}
	return ret;
}

bool Date::IsNotEqual(const Date& other) {
	bool ret = false;
	if (this->year != other.year||
		this->month != other.month||
		this->day != other.day) {
		ret = true;
	}
	return ret;
}


bool Date::IsGreaterThan(const Date& other) {
	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day > other.day) {
		ret = true;
	}
	return ret;	
}

bool Date::IsLessThan(const Date& other) {
	bool ret= false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day < other.day) {
		ret = true;
	}
	return ret;
}


//연산자함수
Date Date::operator -- () {
	struct tm date = { 0, };
	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

Date Date::operator --(int) {
	struct tm date = { 0, };
	Date date_;
	date_.year = this->year;
	date_.month = this->month;
	date_.day = this->day;
	date_.weekDay = this->weekDay;


	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;
	mktime(&date);
	this->year = date.tm_year+1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

Date Date::operator++() {
	struct tm date = { 0, };
	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

Date Date::operator ++(int) {
	struct tm date = { 0, };
	Date date_;
	date_.year = this->year;
	date_.month = this->month;
	date_.day = this->day;
	date_.weekDay = this->weekDay;


	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

Date Date::operator - (int days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;
	mktime(&previousDate);
	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);

	return previousDate_;

}

Date Date::operator + (int days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;
	mktime(&nextDate);
	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);

	return nextDate_;
}

bool Date::operator == (const Date& other) {
	bool ret = false;
	if (this->year == other.year &&
		this->month == other.month &&
		this->day == other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator != (const Date& other) {
	bool ret = false;
	if (this->year != other.year ||
		this->month != other.month ||
		this->day != other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator > (const Date& other) {
	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day > other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator >= (const Date& other) {
	bool ret = false;

	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day > other.day) {
		ret = true;
	}

	else if (this->year == other.year &&
		this->month == other.month &&
		this->day == other.day) {
		ret = true;
	}

	return ret;
}

bool Date::operator < (const Date& other) {
	bool ret= false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day < other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator <= (const Date& other) {
	bool ret= false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year &&
		this->month == other.month &&
		this->day < other.day) {
		ret = true;
	}

	else if (this->year == other.year &&
		this->month == other.month &&
		this->day == other.day) {
		ret = true;
	}

	return ret;
}

//치환연산자
Date& Date::operator = (const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

#if 0
#include<iostream>
using namespace std;

int main(int argc, char* argv[]) {
	Date date;
	Date today;
	Date yesterday;
	Date tomorrow;
	Date previousDate;
	Date nextDate;
	Date theDayAfterTomorrow;
	bool ret;

	today=Date::Today();
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;

	

	tomorrow = today++;
	cout << static_cast<char*>(tomorrow) << endl;

	theDayAfterTomorrow = ++tomorrow;
	cout << static_cast<char*>(theDayAfterTomorrow) << endl;

	yesterday = --today;


	if (today != tomorrow) {
		cout << "다릅니다." << endl;
	}
	previousDate = today - (2);
	cout << static_cast<char*>(previousDate) << endl;

	nextDate = previousDate + (2);
	cout << static_cast<char*>(nextDate) << endl;

	if (tomorrow == nextDate) {
		cout << "같습니다." << endl;
	}

	if (theDayAfterTomorrow > today) {
		cout << "더 늦은 날짜입니다." << endl;
	}

	if (yesterday >= today) {
		cout << "더 늦거나 같은 날짜입니다." << endl;
	}

	if (previousDate < yesterday) {
		cout << "더 이른 날짜입니다." << endl;
	}

	if (today <= yesterday) {
		cout << "더 이르거나 같은 날짜입니다." << endl;
	}



	tomorrow = ++yesterday;
	cout << tomorrow.GetYear() << "-"
		<< tomorrow.GetMonth() << "-"
		<< tomorrow.GetDay() << endl;
	

	today = date.Today();
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;

	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << endl;


	ret = today.IsNotEqual(yesterday);
	if (ret == true) {
		cout << "다릅니다." << endl;
	}

	tomorrow = today.Tomorrow();
	cout << tomorrow.GetYear() << "-"
		<< tomorrow.GetMonth() << "-"
		<< tomorrow.GetDay() << endl;

	theDayAfterTomorrow = tomorrow.Tomorrow();
	cout << theDayAfterTomorrow.GetYear() << "-"
		<< theDayAfterTomorrow.GetMonth() << "-"
		<< theDayAfterTomorrow.GetDay() << endl;

	nextDate = today.NextDate(2);
	cout << nextDate.GetYear() << "-"
		<< nextDate.GetMonth() << "-"
		<< nextDate.GetDay() << endl;


	ret = nextDate.IsEqual(theDayAfterTomorrow);
	if (ret == true) {
		cout << "같습니다." << endl;
	}

	ret = tomorrow.IsGreaterThan(today);
	if (ret == true) {
		cout << "더 늦은 날짜입니다." << endl;
	}

	previousDate = today.PreviousDate(1);
	cout << previousDate.GetYear() << "-"
		<< previousDate.GetMonth() << "-"
		<< previousDate.GetDay() << endl;


	ret = today.IsLessThan(tomorrow);
	if (ret == true) {
		cout << "더 이른 날짜입니다." << endl;
	}

	Date birthDay(1993, JAN, 8);
	cout << birthDay.GetYear() << "-"
		<< birthDay.GetMonth() << "-"
		<< birthDay.GetDay() << endl;

	
	Date birthDay2((char*)"19930108");
	cout << birthDay2.GetYear() << "-"
		<< birthDay2.GetMonth() << "-"
		<< birthDay2.GetDay() << endl;


	return 0;
}

#endif

