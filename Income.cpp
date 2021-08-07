#include"Income.h"
Income::Income() {

}
Income::Income(Date date, string description, Currency amounts, Currency balance, string note) 
:Account(date,description,amounts, balance, note){

}
Income::Income(const Income& source)
	: Account(source) {
}
Income::~Income() {

}
Income& Income::operator=(const Income& source) {
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
	Date date((char*)"20200101");
	Date dateOne((char*)"20200105");
	accountOne = new Income(date, "�뵷", 500000, 500000, "�ƺ�");


	cout << accountOne->GetDate() << " "
		<< accountOne->GetDescription() << " "
		<< accountOne->GetAmounts() << " "
		<< accountOne->GetBalance() << " "
		<< accountOne->GetNote() << endl;

	

	accountTwo = new Income(dateOne, "����", 100000, 600000, "ȸ��");

	cout << accountTwo->GetDate() << " "
		<< accountTwo->GetDescription() << " "
		<< accountTwo->GetAmounts() << " "
		<< accountTwo->GetBalance() << " "
		<< accountTwo->GetNote() << endl;

	

	accountThree = new Income(dateOne, "����", 100000, 600000, "ȸ��");

	cout << accountThree->GetDate() << " "
		<< accountThree->GetDescription() << " "
		<< accountThree->GetAmounts() << " "
		<< accountThree->GetBalance() << " "
		<< accountThree->GetNote() << endl;

	
	
	if (accountTwo->IsEqual(*accountThree)) {
		cout << "�����ϴ�" << endl;
	}
	

	if (accountOne->IsNotEqual(*accountThree)) {
		cout << "�ٸ��ϴ�" << endl;
	}

	if (accountOne != accountThree) {
		cout << "�ٸ��ϴ�" << endl;
	}

	if (accountTwo != accountThree) {
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