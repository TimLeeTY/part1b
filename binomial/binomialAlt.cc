#include <iostream>
#include <iomanip>
#include <cmath>
long double power(double n, int p){
	long double counter=1;
	for (int i=1 ; i<=p; i++){
		counter*=n;
	}
	return(counter);
}
long double choose (int n, int r){ //avoids factorials to minimise length of numbers used
	long double tracker=1;
	for(int i=1; i<=r; i++){ 
		tracker*=(n+1-i);
	}
	for(int i=1; i<=r; i++){ 
		tracker /= i;
	}
	//std::cout << n << " choose " << r << " is "<< tracker << std::endl; 
	return(tracker);
}

long double bino(int n, double p, int i) {
	long double output = (i>n || i<0) ? 0 : choose(n,i)*power(p,i)*power((1-p),(n-i));
	//std::cout << n << " " << p << " " << i << " " << output << std::endl;
	return(output);
}

void printbi(int n, double p, int w, int h){
	int binWid = 0, binSize = 1; //binWid holds width of each bin in pixels, binSize holds size of each bin (number of k's included)
	double vDiv; //Holds the size of vertical divisions 
	const int maxWidth = w, maxHeight = h; //Horizontal and vertical dimensions of drawn graph
	while (binWid==0){ //Decides size and width of bins
		(maxWidth*binSize/(n+1) >=1) ? binWid = maxWidth*(binSize)/(n+1) : binSize++; // implicit floor
	}
	const int binNum = (n+1)/binSize+1; //calculates number of bins required
	int binLabel[binNum][2]; //first row holds label; second row holds number of spaces
	double binValue[binNum][2]; //first row holds actual probability; second row holds height of bin in pixels
	for (int i=0; i <= binNum; ){ //decides how x axis should be labeled
		int labLen= (i==0) ? 1 : ceil(log10(i*binSize+1)), track = labLen/binWid+2;
		binLabel[i][0]=binSize*i;
		binLabel[i][1]=0;		
		binLabel[i+1][0]=-1;
		binLabel[i+1][1]=(track*binWid-labLen);
		for (int j=2; j<track ;j++){
			binLabel[i+j][1]=-1;
		}
		i+=track;
	}
	double max=0, sum; //holds largest probability
	for (int i=0; i<binNum; i++){ //sums total probability for each bin
		sum=0;
		for (int j=0; j<binSize; j++){
			sum+=bino(n,p,j+i*binSize);
		}
		binValue[i][0] = sum;
		max= (sum>max) ? sum : max;
	}
	vDiv = max/maxHeight;
	//std::cout << "vDiv = "<<  vDiv << std::endl; //debugging purposes
	for (int i=0; i<binNum; i++){ //decides height of each bin
		binValue[i][1]=round(binValue[i][0]/vDiv);
		//std::cout << "Value = "<< binValue[i][0]<< ", Height = " << binValue[i][1] << std::endl;; //debugging purposes
	}
	for (int vPix=maxHeight; vPix>=-1; vPix--){
		(vPix>=0) ? std::cout << std::setprecision (3) << std::fixed << (double(vPix) * vDiv) << '|': std::cout << "     |"; //prints y axis labels
		for (int hPix=0; hPix<binNum; hPix++){
			if (vPix>=0){
				std::cout << std::string(binWid, (vPix==0) ? '-': (binValue[hPix][1]>=vPix) ? '#' : ' '); //prints graph area
			}
			else if ((vPix==-1) && binLabel[hPix][1] !=-1 ) {
				(binLabel[hPix][0]>=0) ? std::cout << binLabel[hPix][0] : std::cout << std::string( binLabel[hPix][1], ' ' ); //prints x axis labels
			} 
		}
		switch (maxHeight-vPix){
			case 5:
			case 0:
				std::cout<< std::string(12,'-');
				break;
			case 1:
				std::cout<< "|n=" << n << std::string(8-ceil(log10(n+1)),' ')<<'|';
				break;
			case 2:
				std::cout<< "|p=" << std::setprecision (3) << p <<"   |";
				break;
			case 3:
				std::cout<< "|m=" << std::setprecision (1) << n*p << std::string(6-ceil(log10(n*p+1)),' ')<<"|";
				break;
			case 4:
				std::cout<< "|stdv=" << std::setprecision (2) << p*n*(1-p) << std::string(ceil(log10(p*n*(1-p))),' ') <<'|';
				break;
		}
		std::cout <<std::endl;
	}

}

int main(){
	std::cout << "This programme has been tested for n up to ~1700, go any higher and you'll break maths as we know it (sorry)." << std::endl;
	std::cout << "Please use a monospaced font on your terminal to display the graph properly, you have been warned." << std::endl;
std::cout << "Please note the x axis labels work in a way such that the labelled column is the one corresponding the the leftmost digit of the label" << std::endl;
	while (true){
		int n, h=25, w=80;
		double p;
		std::cout << "Enter a value for n: "; // prompt user input
		std::cin >> n;
		while(std::cin.fail() || n<0) { // while loop catches any invalid inputs
		    std::cin.clear(); //clears std::cin.fail() error
			std::cin.ignore(10000,'\n'); // ignore all previous inputs
		    std::cout << "Bad entry.  Enter a positive integer: "; //re-prompt input
		    std::cin >> n;
		}
		std::cout << "Enter a value for p: "; // prompt user input
		std::cin >> p;
		while(std::cin.fail() || (p>1) || (p<0)) { // while loop catches any invalid inputs
		    std::cin.clear(); //clears std::cin.fail() error
			std::cin.ignore(10000,'\n'); // ignore all previous inputs
		    std::cout << "Bad entry.  Enter a number between 0 and 1: "; //re-prompt input
		    std::cin >> p;
		}
		std::cout << std::endl;
		printbi(n,p,w,h);
		std::cout << "The mean is " << n*p << " and the standard deviation is " << sqrt(n*p*(1-p)) <<std::endl;
	}
	return(0);
}