#include <iostream>
#include <cmath>
#include <algorithm>
#define N 13
#define coll 5000
using namespace std;
class particle{
public:
	void setinit(double,double,double,double);
	void showState();
	double p();
	double ke();
	double x;
	double v;
	double im;
	double r;
};
void particle::showState(){
	cout<<x<<" "<<v<<" ";
}
void particle::setinit(double rin, double imin, double vin, double xin){
	r=rin;
	im=imin;
	v=vin;
	x=xin;
}
double particle::p(){
	return(v/im);
}
double particle::ke(){
	return(pow(v,2)/im/2);
}
class rec{
public:
	void sett(int, double);
	void insert(int,int, double, double, double);
	void show();
	void showDiscrete(double);
private:
	double t[coll+1];
	double x[coll+1][N][3];
};
void rec::sett(int numColl, double tin){
	t[numColl]=tin;
}
void rec::insert(int numColl, int n, double xin, double vin, double kein){
	x[numColl][n][0]=xin;
	x[numColl][n][1]=vin;
	x[numColl][n][2]=kein;
}
void rec::show(){
	for(int i=1;i<coll+1;i++){
		cout<<t[i];
		for(int j=0;j<N;j++){
			cout<<" "<<x[i][j][0]<<" "<<x[i][j][1];
		}
		cout<<endl;
	}
}
void rec::showDiscrete(double dt){
	double ta=0, tb=0, leftke, rightke;
	for(int i=0; i<coll+1; i++){
		while(t[i]>ta){
			cout<<ta;
			for (int j=0;j<N;j++){
				cout<<" "<<x[i][j][0]+x[i][j][1]*tb;
			}
			leftke=0;
			rightke=0;
			for (int j=0;j<N/2;j++){
				leftke+=x[i][j][2];
				rightke+=x[i][N-j-1][2];
			}
			cout<<" "<<leftke<<" "<< x[i][N/2][2] <<" "<<rightke<<" "<< rightke+x[i][N/2][2]+leftke;
			cout<<endl;
			ta+=dt;
			tb+=dt;
		}
		tb=ta-t[i];
	}
}
void collision(particle &a, particle &b){
	if (a.im==0){
		b.v=-b.v;
	} else if (b.im==0){
		a.v=-a.v;
	} else{
		double ma=1/a.im, mb=1/b.im, va=a.v,vb=b.v, pa=a.p(),pb=b.p();
		a.v=(mb*(vb-va)+pa+pb)/(ma+mb);
		b.v=(ma*(va-vb)+pa+pb)/(ma+mb);
	}
}
double leapForward(particle (&parList)[N+2], double t, rec &record, int run){
	double tempt, mint=-1;
	int flag;
	for(int i=0; i<(N+1); i++){
		if (parList[i].v>parList[i+1].v){
			tempt=(parList[i+1].x-parList[i].x-parList[i].r-parList[i+1].r)/(parList[i].v-parList[i+1].v);
			if (tempt==0){
				mint=0;
				flag=i;
				break;
			}
			else if (tempt<mint || mint<0){
				mint=tempt;
				flag=i;			
			}
		}
	}
	record.sett(run,t+mint);
	//cout<<t+mint;
	for(int i=0; i<(N+2); i++){
		parList[i].x+=mint*parList[i].v;
	}
	collision(parList[flag],parList[flag+1]);
	for(int i=1; i<=(N); i++){
		//cout<<" "<<parList[i+1].x<<" "<<parList[i+1].v;
		record.insert(run,i-1,parList[i].x,parList[i].v,parList[i].ke());
	}
	//cout<<endl;
	return(mint+t);
}

int main(){
	particle list[N+2];
	rec record;
	double rList[N];
	double mList[N]={1.1, 1.2, 1.1, 1.3,1.1,1.1, 400.0, 4.0,4.1, 4.2, 4.1, 4.8, 4.4};
	double vList[N];
	double xList[N]={0.1,0.11,0.12,0.13,0.14,0.15,0.8,0.89,0.9,0.91,0.92,0.93,0.94};
	double boxLen=1;
	double dt=0.01;
	double tflag=0;
	/*for (int i=0; i<N; i++){
		xList[i]=(rand()%100)/100.0;
	}
	sort(begin(xList), end(xList));*/
	for (int i=0; i<N; i++){
		rList[i]=0;
		vList[i]=(i==N/2) ? 0.05/2:(rand()%100-50)/1000.0;
		list[i+1].setinit(rList[i], 1/mList[i], vList[i], xList[i]);
	}
	list[0].setinit(0,0,0,0);
	list[N+1].setinit(0,0,0,boxLen);
	record.sett(0,0);
	for(int i=0; i<N; i++){
		record.insert(0,i,list[i+1].x,list[i+1].v,list[i+1].ke());
	}
	cout<<endl;
	for (int i=0;i<coll;i++){
		tflag=leapForward(list,tflag , record, i+1);
	}
	//record.show();
	record.showDiscrete(dt);
}