//here begins "monopoly.cc"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h> 

void monopoly(double *a,double *b, int N){
	int prob[11]={1,2,3,4,5,6,5,4,3,2,1}; // probability density of rolling 2 dice, do try other interesting ones!
	for(int i=0; i<N; i++){
		if (a[i]!=0) {
			for(int j=0; j<11; j++){ //11 is len(prob)
				b[(i+j+2<N) ? i+j+2 : i+j+2-N]+=a[i]*prob[j]/36; //36 is sum(prob);
			}
		}
	}
}
void print(double *a,int N,int maxHeight){
	double max=0;
	const int Num=N;
	int binWid=2;
	int height[Num];
	for (int i=0; i<N; i++){ //finds maximum probability
		max= (a[i]>max) ? a[i] : max;
	}
	double vDiv = max/maxHeight;
	for (int i=0; i<N; i++){ //decides height of each bin
		height[i]=round(a[i]/vDiv);
	}
	for (int vPix=maxHeight; vPix>=-1; vPix--){
		(vPix>=0) ? std::cout << std::setprecision (4) << std::fixed << (double(vPix) * vDiv) << '|': std::cout << "      |"; //prints y axis labels
		for (int hPix=0; hPix<N; hPix++){
			if (vPix>=0){
				std::cout << std::string(binWid, (vPix==0) ? '-': (height[hPix]>=vPix) ? '#' : ' '); //prints graph area
			}
			else if (vPix==-1 && hPix%2==0) {
				std::cout << hPix+1 << std::string(2*binWid-((hPix==0) ? 1 : ceil(log10((1+hPix)))), ' ' ); //prints x axis labels
			} 
		}
		std::cout<<std::endl;
	}
}

int main(){
	double *a;
	double *b;
	int N=50; //Models a monopoly board of size N
	a=new double[N];
	b=new double[N];
	int steps;
	while(true){
		a[0]=1;
		for (int i=1; i<N; i++){ 
			a[i]=0; //initilise array a to all 0's
		}
		std::cout << "Enter a number of moves: "; // prompt user input
		std::cin >> steps;
		while(std::cin.fail() || (steps<0)) { // while loop catches any invalid inputs
		    
			std::cin.clear(); //clears std::cin.fail() error
			std::cin.ignore(10000,'\n'); // ignore all previous inputs
		    std::cout << "Bad entry.  Enter a positive integer: "; //re-prompt input
		    std::cin >> steps;
		}
	    if (steps==0){ //Enter 0 to escape out of while(true) loop
	    	break;
	    }
		std::cout << std::endl;
		for(int i=0; i< steps; i++){
			for (int k=0;k<N;k++){
				b[k]=0;
			}
			monopoly(a,b,N);
			std::cout<<std::endl<<i+1<<" Moves"<<std::endl;
			print(b,N,20);
			for (int j=0; j<N; j++){
				a[j]=b[j];
			}
			usleep(100000); //pause 0.2 seconds
		}
		std::cout << std::endl;
	}
	delete [] a;
	delete [] b; 
}