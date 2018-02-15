#include <cstdlib> 
#include <ctime> 
#include <iostream>

void monop(int n){
	int spaces[40]={0};
	int tracker=0;
	std::srand((unsigned)time(0));
	for(int i=0; i<n; i++){
	int one=std::rand()%6+1, two=std::rand()%6+1;
	std::cout<<one<<" "<<two<<std::endl;
	tracker= (tracker+one+two <40) ? tracker+one+two : tracker+one+two-40;
	spaces[tracker]++;
	}
	for(int i=0; i<40; i++){
		std::cout<<spaces[i]<<", ";
	}
}
int main(){
	monop(5);
}