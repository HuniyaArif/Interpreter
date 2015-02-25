#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
class Variable
{
	char name;
	int value;

public:

	void setval(char n, int val)
	{
		this->name = n;
		this->value = val;
	}

	int getval()
	{
		return this->value;
	}

	char getname()
	{
		return this->name;
	}

	template<typename t1, typename t2>
	double addition(t1 a, t2 b)
	{
		this->value = a + b;
		return value;
	}

	template<typename t1, typename t2>
	double subtraction(t1 a, t2 b)
	{
		this->value = a - b;
		return value;
	}

	template<typename t1, typename t2>
	double multiplication(t1 a, t2 b)
	{
		this->value = a * b;
		return value;
	}

	template<typename t1, typename t2>
	double divison(t1 a, t2 b)
	{
		this->value = a / b;
		return value;
	}

};


int interpreter(char str[256]){

	ifstream is(str);
	//checks the existence of the file
	if (!is){
		cout << "Unable to open " << endl;
		return 0;
	}

	int iflag = 0;
	int cflag = 0;
	int eflag=0;
	int index3 = 0;
	int index2 = 0;
	int index = 0;
	int flag = 0;
	int result = 0;
	vector<char *> v;
	char buffer[256];
	int maxlines = 0;
	char * pch;
	int value;
	char * name;
	char *comp = "let";
	char *comp2 = "print";
	Variable ob[20];

	//reading line by line 
	while (is.getline(buffer, 256, '\n')){

		cflag=0;
		flag=0;
		pch = strtok(buffer, " ");
		while (pch != NULL)
		{
			//checking to see if char is equal to print
			if (!strcmp(pch,comp2))
			{  
			iflag=2;
			}
			//checking to see if char is equal to let
			if (!strcmp(pch,comp))
			{
			iflag = 1; 
			}

			if (iflag==2){
				if (!strcmp(pch,comp2));
				else{
					//saves the name of print variable
				name = pch;
				}
			}
			else if (iflag == 1){
			//for syntax errors 0=x
			if(cflag==0 && isdigit(*pch)){
				cout <<"Improper declaration."<< endl;
				cflag=0;
				return 0;
			}
			else if(cflag>1 || *pch == '+' || *pch == '-' || *pch == '/' || *pch == '*'){
				//for syntax errors x + y = 0
				cout <<"Improper declaration."<< endl;
				cflag=0;
				return 0;
			}
			else if (isdigit(*pch)){

				value = int(*pch - '0');
			}
			else if (!strcmp(pch,comp));
			else if(!(*pch == '=') && !(isdigit(*pch)) )
			{
				//saves the name of variable
				name = pch;
				cflag++;
			}
		    }
			else{
				//it's an equation
				if (isdigit(*pch)){
					v.push_back(pch);
				}
				else if (*pch == '='){
					flag++;
				}
				else if (*pch == '+' || *pch == '-' || *pch == '/' || *pch == '*'){

					v.push_back(pch);
				}
				else{
					//name of variable

					//see if name of variable is declared
            for (int i = 0; i < 20; i++){
				if (*pch == ob[i].getname()){
					eflag=1;
					break;
				}
			}

			if(eflag==0){
				cout <<"Variable is not declared."<< endl;
				eflag=0;
				return 0;
			}
			eflag=0;

			//by flag=0, we know it came before =
					if (flag == 0){
						name = pch;
					}
					else{
						v.push_back(pch);
					}

				}


			}
				pch = strtok(NULL, " ");

		}

		if (iflag == 2){
			//check the existence of name
			for (int i = 0; i < 20; i++){
				if (*name == ob[i].getname()){
					cout << *name<< " has value: " << ob[i].getval() << endl;
					eflag=1;
					break;
				}
			}
			if(eflag==0){
				cout <<"Variable is not declared."<< endl;
				eflag=0;
				iflag=0;
				return 0;
			}
			eflag=0;
			iflag = 0;
		}
		else if (iflag == 1){
			//making an object of x
			ob[maxlines].setval(*name, value);
			iflag = 0;
		}
		else{
			//find the index where name exists in array
			for (int i = 0; i < 20; i++){
				if (*name == ob[i].getname()){
					index = i;
					break;
				}
			}


			char *b=new char[10];
			for (int i = 0; i<v.size(); i++){
			
				//if the operation is addition
				if (*v.at(i) == '+'){


					if (isdigit(*v.at(i - 1)) && isdigit(*v.at(i + 1))){
						//if both integers
						result = ob[index].addition<int, int>(int(*v.at(i - 1) - '0'), int(*v.at(i + 1) - '0'));
						
					}
					else if (isdigit(*v.at(i - 1))){
						//if one of them is integer, find the value of another
						
						for (int j = 0; j < 20; i++){
							if (*v.at(i + 1) == ob[j].getname()){
								index2 = j;
								break;
							}
						}

						result = ob[index].addition<int, int>(int(*v.at(i - 1) - '0'), ob[index2].getval());
						
					}
					else if (isdigit(*v.at(i + 1))){
						//if one of them is integer, find the value of another
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){
								
								index2 = j;
								break;
							}
						}
						result = ob[index].addition<int, int>(int(*v.at(i + 1) - '0'), ob[index2].getval());
						
						
					}
					else{
						//if both are variables
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						for (int j = 0; j < 20; j++){
							if (*v.at(i + 1) == ob[j].getname()){

								index3 = j;
								break;
							}
						}
						result = ob[index].addition<int, int>(ob[index2].getval(), ob[index3].getval());
					

					}

		    itoa(result,b,10);
			v[i+1]=b;
				
					
				}
				//if the operation is subtraction, it follows the same procedure as addition
				else if (*v.at(i) == '-'){


					if (isdigit(*v.at(i - 1)) && isdigit(*v.at(i + 1))){
						result = ob[index].subtraction<int, int>(int(*v.at(i - 1) - '0'), int(*v.at(i + 1) - '0'));
						
					}
					else if (isdigit(*v.at(i - 1))){
						for (int j = 0; j < 20; i++){
							if (*v.at(i + 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].subtraction<int, int>(int(*v.at(i - 1) - '0'), ob[index2].getval());
						
					}
					else if (isdigit(*v.at(i + 1))){
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].subtraction<int, int>(int(*v.at(i + 1) - '0'), ob[index2].getval());
						

					}
					else{
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						for (int j = 0; j < 20; j++){
							if (*v.at(i + 1) == ob[j].getname()){

								index3 = j;
								break;
							}
						}
						result = ob[index].subtraction<int, int>(ob[index2].getval(), ob[index3].getval());
						

					}

		//convert to character and replace old position
		    itoa(result,b,10);
			v[i+1]=b;
			
					
				}
				//if the operation is multiplication, it follows the same procedure as addition
				else if (*v.at(i) == '*'){


					if (isdigit(*v.at(i - 1)) && isdigit(*v.at(i + 1))){
						result = ob[index].multiplication<int, int>(int(*v.at(i - 1) - '0'), int(*v.at(i + 1) - '0'));
						
					}
					else if (isdigit(*v.at(i - 1))){
					
						for (int j = 0; j < 20; i++){
							if (*v.at(i + 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].multiplication<int, int>(int(*v.at(i - 1) - '0'), ob[index2].getval());
						
					}
					else if (isdigit(*v.at(i + 1))){
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].multiplication<int, int>(int(*v.at(i + 1) - '0'), ob[index2].getval());
					

					}
					else{
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						for (int j = 0; j < 20; j++){
							if (*v.at(i + 1) == ob[j].getname()){

								index3 = j;
								break;
							}
						}
						result = ob[index].multiplication<int, int>(ob[index2].getval(), ob[index3].getval());
						

					}
		
		    itoa(result,b,10);
			v[i+1]=b;
		

				}
				//if the operation is division, it follows the same procedure as addition
				else if (*v.at(i) == '/'){

				

					if (isdigit(*v.at(i - 1)) && isdigit(*v.at(i + 1))){
						result = ob[index].divison<int, int>(int(*v.at(i - 1) - '0'), int(*v.at(i + 1) - '0'));
						
					}
					else if (isdigit(*v.at(i - 1))){
						
						for (int j = 0; j < 20; i++){
							if (*v.at(i + 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].divison<int, int>(int(*v.at(i - 1) - '0'), ob[index2].getval());
						
					}
					else if (isdigit(*v.at(i + 1))){
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						result = ob[index].divison<int, int>(int(*v.at(i + 1) - '0'), ob[index2].getval());
					

					}
					else{
						
						for (int j = 0; j < 20; j++){
							if (*v.at(i - 1) == ob[j].getname()){

								index2 = j;
								break;
							}
						}
						for (int j = 0; j < 20; j++){
							if (*v.at(i + 1) == ob[j].getname()){

								index3 = j;
								break;
							}
						}
						result = ob[index].divison<int, int>(ob[index2].getval(), ob[index3].getval());
						

					}

			
		    itoa(result,b,10);
			v[i+1]=b;
		
					
				}
			
			
			}
			//clean the vector for every line
			v.clear();
			

			

		}

		maxlines++;
	}

	return 0;
}