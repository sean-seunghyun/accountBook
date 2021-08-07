//Outgo.cpp
#include"Outgo.h"
Outgo::Outgo() {

}

Outgo::Outgo(Date date, string description, Currency amounts, Currency balance, string note)
	:Account(date, description, amounts, balance, note){

}

Outgo::Outgo(const Outgo& source)
	: Account(source) {

}

Outgo::~Outgo() {

}

Outgo& Outgo::operator=(const Outgo& source) {
	Account::operator=(source);

	return *this;
}


#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Account *accountOne;
	Account *accountTwo;
	Account *accountThree;
	Date dateOne("20200101");
	Date dateTwo("20200102");
	

	accountOne = new Outgo(dateOne,"ȸ��",30000, 30000, "ģ��" );


	cout << accountOne->GetDate() << " "
		<< accountOne->GetDescription() << " "
		<< accountOne->GetAmounts() << " "
		<< accountOne->GetBalance() << " "
		<< accountOne->GetNote() << endl;

	accountTwo = new Outgo(dateTwo, "����", 10000, 40000, "���� ���");


	cout << accountTwo->GetDate() << " "
		<< accountTwo->GetDescription() << " "
		<< accountTwo->GetAmounts() << " "
		<< accountTwo->GetBalance() << " "
		<< accountTwo->GetNote() << endl;


	accountThree = new Outgo(dateOne, "ȸ��", 30000, 30000, "ģ��");
	cout << accountThree->GetDate() << " "
		<< accountThree->GetDescription() << " "
		<< accountThree->GetAmounts() << " "
		<< accountThree->GetBalance() << " "
		<< accountThree->GetNote() << endl;


	if (accountTwo->IsNotEqual(*accountThree)) {
		cout << "�ٸ��ϴ�" << endl;
	}


	if (accountOne->IsEqual(*accountThree)) {
		cout << "�����ϴ�" << endl;
	}

	if (*accountOne != *accountTwo) {
		cout << "�ٸ��ϴ�" << endl;
	}

	if (*accountOne == *accountThree) {
		cout << "�����ϴ�" << endl;
	}




	if (accountOne != 0) {
		delete accountOne;
 }

	if (accountTwo != 0) {
		delete accountTwo;
	}

	if (accountThree != 0) {
		delete accountThree;
	}


	return 0;
}
#endif