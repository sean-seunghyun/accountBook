//Date.h
#ifndef _DATE_H
#define _DATE_H
enum WeekDay {SUN=0, MON=1, TUE=2, WED=3, THU=4, FRI=5, SAT=6};
enum Month{JAN=1, FEB=2, MAR=3, APR=4, MAY=5, JUN=6, JUL=7, AUG=8, SEP=9, OCT=10, NOV=11, DEC=12 };

class Date {


public :
	//������
	Date();
	//�Ҹ���
	~Date();
	//������ �����ε�
	Date(int year, Month month, int day);
	Date(char(*date));
	//���������
	Date(const Date& source);
	//����ȯ �Լ�
	operator char*();

	//static ����
	static Date Today();

	Date Yesterday();
	Date Tomorrow();
	Date PreviousDate(int days);
	Date NextDate(int days);
	//������ ���� ��������
	bool IsEqual(const Date& other);
	bool IsNotEqual(const Date& other);
	bool IsGreaterThan(const Date& other);
	bool IsLessThan(const Date& other);
	//������ �Լ�
	Date operator -- ();
	Date operator --(int);
	Date operator ++();
	Date operator ++(int);
	Date operator - (int days);
	Date operator + (int days);
	bool operator == (const Date& other);
	bool operator != (const Date& other);
	bool operator > (const Date& other);
	bool operator >= (const Date& other);
	bool operator < (const Date& other);
	bool operator <= (const Date& other);
	Date& operator = (const Date& source);
	int GetYear() const;
	Month GetMonth() const;
	int GetDay() const;
	WeekDay GetWeekDay() const;

private:
	int year;
	Month month;
	int day;
	WeekDay weekDay;
};

inline int Date::GetYear() const {
	return this->year;
}
inline Month Date::GetMonth() const {
	return this->month;
}
inline int Date::GetDay() const {
	return this->day;
}
inline WeekDay Date::GetWeekDay() const {
	return this->weekDay;
}
#endif//_DATE_H