#include <iostream>
#include <iomanip>
#include <cmath>
double power(double n, int p){
	double counter=1;
	for (int i=1 ; i<=p; i++){
		counter*=n;
	}
	return(counter);
}

long factorial(int n){
	long out=1;
	for (int j = 2; j<=n; j++){
		out*=j;
	}
	//std::cout << n << " factorial= "<< out << std::endl;
	return(out);
}

int choose (int n, int r){
	return(factorial(n)/(factorial(r)*factorial(n-r)));
}

double bino(int n, double p, int i) {
	double output;
	output=power(p,i)*power((double(1)-p),(n-i))*choose(n,i);
	return(output);
}

int printbi(int n, double p){
	const int len =n;
	char pixels[60][20];
	int colwid= floor(60/(n+1));
	int colhei[len];
	for (int i=0; i<=n; i++){
		colhei[i]=round(bino(n,p,i)*20);
		//std::cout << round(bino(n,p,i)*20);
	}
	for (int i=20; i>=-2; i--){
		if (i>=-1)
			std::cout << std::setprecision (2) << std::fixed << (i+1)/double(20) << '|';
		else 
			std::cout << "    |";
		for (int j=0; j<=(colwid*(1+(n+1/60))); j++){
			int f=floor(j/colwid);
			if (i==-2) {
				if ((j%colwid)==0 and f<=n)
					std::cout << f;
				else if (!(((j%colwid)==1) and (log10(f)>1)))
					std::cout << ' ';
			}
			else if (i==-1){
				std::cout << '-';
			}
			else if (colhei[f]>i){
				pixels[j][i]='&';
				std::cout << pixels[j][i];
			}
			else {
				pixels[j][i]=' ';
				std::cout << pixels[j][i];
			}
		}
		std::cout << std::endl;
		
	}
	return(0);
}
	

int main(){
	/* for (int i=0; i<=15; i++){
		std::cout << i << ' '<< bino(15,0.8,i) << ' ' << choose(15,i) << std::endl;
	} */
	//std::cout << i << " " << binomial(10, 0.1 ,i) << std::endl;
	//std::cout << power(i,2) << std::endl;
	printbi(20,0.2);
	return(0);
}