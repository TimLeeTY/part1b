#include <iostream>
#include <ctime>// timing for optimisation purposes
// Short script to calculate the number of unique ways to partition some number
// e.g. 5 can be partitioned in the following 7 ways:
// ooooo, oooo-o, ooo-oo, ooo-o-o, oo-oo-o, oo-o-o-o, o-o-o-o-o
// i.e. 5= 4+1 = 3+2 = 3+1+1 = 2+2+1 = 2+1+1+1 = 1+1+1+1+1
// The following function uses the fact that the partition of n is equal to one more than the sum of the partitions of all x smaller that n with that largest partition of each case being (n-x)
// e.g. 5 = 4+(1) = 3+(2) = 3+(1+1) = 2+(2+1) = 2+(1+1+1) = 1+(1+1+1+1)
// i.e. f(5,5)=1+f(4,1)+f(3,2)+f(2,3)+f(1,4)
// partition takes 2 parameters, r is the number being partitioned, and n the largest partition considered.

int partition(int r, int n) { // function partition with parameters r & x
	if (n<=1)
		return(1); // only one way to sum to any number using just 1's
	int isum = 0; // intitate variable isum that keeps an overall tally	
	if (r<=n)
		isum = 1; // accounts for case where no partitions occur
	for(int i=1; (i<=n) and (i<r); i++){ //sums i over range 1 to the smaller n or (r-1); i cannot be equal or larger than r as that aways returns 0
		isum+=partition(r-i,i); // calls partition again to count # of ways to partition (r-i) with partitions no larger than i
	} 
	return(isum);
}

int main() {
    std::clock_t start;
	while (true){
	    double duration;
		std::cout << "Enter a positive integer: "; // prompt user input
		int j;
		std::cin >> j;
		while(std::cin.fail() or j<0) { // while loop catches any invalid inputs
		    std::cin.clear(); //clears std::cin.fail() error
			std::cin.ignore(10000,'\n'); // ignore all previous inputs
		    std::cout << "Bad entry.  Enter a positive integer: "; //re-prompt input
		    std::cin >> j;
		}
	    start = std::clock(); // timing for optimisation purposes
		std::cout <<"There are " << partition(j,j) << " ways to partition "<< j << std::endl;
	    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; // timing for optimisation purposes
	    std::cout<<"process time: "<< duration <<" seconds \n"; // timing for optimisation purposes
	}
}


