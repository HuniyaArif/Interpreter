#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Source.h"

using namespace std;

int main(){

	char str[256];
	cout << "Enter the name of existing file. " << endl;
	cin.get(str, 256);
	//calling the function
	interpreter(str);

	return 0;
}