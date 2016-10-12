#include "interface.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

Interface::Interface(){

};

int Interface::getGridSize(){
	int size;
	do {
	cout << "What size grid do you want? (integer between 10 and 50): ";
	cin >> size;
	} while (size == 0 || size < 10 || size > 50);



	return size;

};



/*int main(){
	Interface natasha; // = new Interface();
	cout<< natasha.getGridSize() <<endl;

	return 0;

}*/