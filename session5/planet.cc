#include <iostream>
#include <cmath>[	]
#define D 2
using namespace std;
class planet {
public:
	void printall(int);
	void setx(long double, long double);
	void setv(long double, long double);
	void force(double);
	void rotate(double);
	long double sqrdist();
	double t;
	long double x[D];
	long double v[D];
	long double f[D];
	double m;
};
void planet::printall(int det){
	if (det==0){
		cout<< "x=["<<x[0]<<","<<x[1]<<"]"<<endl;
		cout<< "v=["<<v[0]<<","<<v[1]<<"]"<<endl;
		cout<< "f=["<<f[0]<<","<<f[1]<<"]"<<endl<<endl;
	}
	if (det==1){
		cout<<t<<" "<<x[0]<<" "<<x[1]<<" "<<v[0]<<" "<<v[1]<<endl;
	}

}
long double planet::sqrdist(){
	double sum=0;
	for (int i=0; i<D ; i++){
		sum+=pow(x[i],2.0);
	}
	double output=(pow(sqrt(sum),3.0));
	return(output);
	
}
void planet::setx(long double x1, long double x2){
	x[0]=x1;
	x[1]=x2;
}
void planet::setv(long double x1, long double x2){
	v[0]=x1;
	v[1]=x2;
}
void planet::force(double A){
	double dist=sqrdist();
	for (int i=0; i<2; i++){
		f[i]=x[i]*A/dist;
	}	
}
void planet::rotate(double theta){
	double v_temp=v[0];
	v[0]=cos(theta)*v[0]-sin(theta)*v[1];
	v[1]=sin(theta)*v_temp+cos(theta)*v[1];
}
void euler(planet &obj, double M, double G, double dt,int steps){
	double A=-1*G*M*obj.m;
	for (int j=0; j<steps; j++){
		obj.force(A);
		for (int i=0;i<2;i++){
			obj.x[i]+=dt*obj.v[i];
			obj.v[i]+=dt*obj.f[i]/obj.m;
		}	
		obj.t+=dt;	
		obj.printall(1);
	}
}
void leapfrog(planet &obj, double M, double G, double dt,int steps){
	for (int j=0; j<steps; j++){
		for (int i=0;i<2;i++){
			obj.x[i]+=	0.5*dt*obj.v[i];
		}	
		obj.t+=dt*0.5;
		obj.force(A);
		for (int i=0;i<2;i++){
			obj.v[i]+=dt*obj.f[i]/obj.m;
			obj.x[i]+=	dt*0.5*obj.v[i];
		}
		obj.t+=dt*0.5;
		obj.printall(1);
	}
}
int main(){
	planet obj;
	obj.setv(0.4,0);
	obj.m=1;
	double M=1;
	double G=0.5;
	double dt=0.0002;
	for (int i=0; i<20; i++){
		obj.t=0;
		obj.setx(1.5,2);
		leapfrog(obj, M, G, dt, 200000);
		cout<<endl<<endl;
		obj.setv(0.4,0);
		obj.rotate(0.25*(i+1));
	}
}
