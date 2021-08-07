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
	

	accountOne = new Outgo(dateOne,"회식",30000, 30000, "친구" );


	cout << accountOne->GetDate() << " "
		<< accountOne->GetDescription() << " "
		<< accountOne->GetAmounts() << " "
		<< accountOne->GetBalance() << " "
		<< accountOne->GetNote() << endl;

	accountTwo = new Outgo(dateTwo, "음식", 10000, 40000, "한턱 쏘기");


	cout << accountTwo->GetDate() << " "
		<< accountTwo->GetDescription() << " "
		<< accountTwo->GetAmounts() << " "
		<< accountTwo->GetBalance() << " "
		<< accountTwo->GetNote() << endl;


	accountThree = new Outgo(dateOne, "회식", 30000, 30000, "친구");
	cout << accountThree->GetDate() << " "
		<< accountThree->GetDescription() << " "
		<< accountThree->GetAmounts() << " "
		<< accountThree->GetBalance() << " "
		<< accountThree->GetNote() << endl;


	if (accountTwo->IsNotEqual(*accountThree)) {
		cout << "다릅니다" << endl;
	}


	if (accountOne->IsEqual(*accountThree)) {
		cout << "같습니다" << endl;
	}

	if (*accountOne != *accountTwo) {
		cout << "다릅니다" << endl;
	}

	if (*accountOne == *accountThree) {
		cout << "같습니다" << endl;
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