#include <iostream>
#include <cmath>
#define D 2
using namespace std;
class planet {
public:
	void printall(int);
	void setx(long double, long double);
	void setv(long double, long double);
	double ke();
	double t;
	long double x[D];
	long double v[D];
	long double f[D];
	double gpe;
	double m;
};
double planet::ke(){
	//calculates ke of each planet
	double sum=0;
	for (int i=0; i<D; i++){
		sum+=pow(v[i],2);
	}
	return(sum);
}
void planet::setx(long double x1, long double x2){
	//initiates position
	x[0]=x1;
	x[1]=x2;
}
void planet::setv(long double x1, long double x2){
	//initiates velocity
	v[0]=x1;
	v[1]=x2;
}
double sqrdist(planet &objA, planet &objB){
	//finds scalar distance between 2 planets
	double sum=0;
	for (int i=0; i<D; i++){
		sum+=pow((objB.x[i]-objA.x[i]),2.0);
	}
	double output=sqrt(sum);
	return(output);
	
}
void force(double G, planet &objA, planet &objB, planet &objC){
	//calculates and updates the force on all 3 objects
	double distAB=sqrdist(objA,objB);
	double distBC=sqrdist(objB,objC);
	double distAC=sqrdist(objA,objC);
	double f_AB, f_AC, f_BC;
	for (int i=0; i<D; i++){
		f_AB=(objA.x[i]-objB.x[i])*G*objB.m*objA.m/pow(distAB,3);
		f_BC=(objB.x[i]-objC.x[i])*G*objC.m*objB.m/pow(distBC,3);
		f_AC=(objA.x[i]-objC.x[i])*G*objC.m*objA.m/pow(distAC,3);
		objA.f[i]=-f_AB-f_AC;
		objB.f[i]=f_AB-f_BC;
		objC.f[i]=f_AC+f_BC;
	}
	objA.gpe=-G*objA.m*(objB.m/distAB+objC.m/distAC);
	objB.gpe=-G*objB.m*(objA.m/distAB+objC.m/distBC);
	objC.gpe=-G*objC.m*(objA.m/distAC+objB.m/distBC);
}

void printalll(planet objlist[3]){
	//prints in readable format for gnuplot
	double sumke=0, sumgpe=0;
	cout<<objlist[0].t;
	for(int i=0; i<3; i++){
		cout<<" "<<objlist[i].x[0]<<" "<<objlist[i].x[1]<<" "<<objlist[i].ke();
		sumke+=objlist[i].ke();
		sumgpe+=objlist[i].gpe;
	}
	cout<<" "<<sumke<<" "<<sumgpe<<" "<<sumke+sumgpe<<endl;
}
void leapfrog(planet objlist[3], double G, double dt,int steps){
	//implements leapfrog method
	cout<<objlist[0].x[0]<<endl;
	for (int j=0; j<steps; j++){
		for (int k=0;k<3;k++){
			for (int i=0;i<2;i++){
				objlist[k].x[i]+=0.5*dt*objlist[k].v[i];
			}	
			objlist[k].t+=dt*0.5;
		}
		force(G,objlist[0], objlist[1], objlist[2]);
		for (int k=0;k<3;k++){
			for (int i=0;i<2;i++){
				objlist[k].v[i]+=dt*objlist[k].f[i]/objlist[k].m;
				objlist[k].x[i]+=	dt*0.5*objlist[k].v[i];
			}
			objlist[k].t+=dt*0.5;
		}
		printalll(objlist);
	}
}

int main(){
	planet objA,objB,objC;
	objA.m=1;
	objB.m=1;
	objC.m=1;
	objA.setx(0,1);
	objB.setx(-1,-1/3);
	objC.setx(1,-1/3);
	objA.setv(0.4,0.4);
	objB.setv(0,-0.4);
	objC.setv(-0.4,0);
	planet objs[3]={objA, objB, objC};
	double G=0.5;
	double dt=0.0002;
	for(int j=0;j<3;j++){
		objs[j].t=0;
	}
	leapfrog(objs, G, dt, 200000);
}

