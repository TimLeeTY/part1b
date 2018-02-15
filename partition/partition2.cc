#include <iostream>
#include <ctime> 

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
	for(int i=1; i<=110; i++){
		std::cout<<i<<" "<<partition(i,i)<<std::endl;
	}
}