#include <iostream>

int main(){
	int N=100;
	int *x;
	double *y;
    x= new int[N];
	y= new double[N];
    for (int i=0; i<N; i++){
		x[i]=i+1;
		y[i]=0;
		for (int j=0; j<=i; j++){
			y[i]+=double(1)/(j+1);
		}
		std::cout<<x[i]<<","<<y[i]<<std::endl;
    }
	
}