#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

void Euler(double h,double w0=1,double T=40,double y=1,double y1=0){
  double A,B,A1,B1,y2,y3;  //Values to update
  ofstream file;
  stringstream H; //Declare a stringstream
  H << fixed << setprecision(2) << h; //set h into a 2 precision string
  file.open("Euler_"+H.str()+".txt");
  file<<"T\ty\twith\th="<<h<<"\n";

  for (double t = 0; t < T; t+=h) {
    y2 = -w0*w0*y;
    y3 = -w0*w0*y1;
    A = h*y1;
    A1 = h*y2;
    B = h*(y1+h*y2);
    B1 = h*(y2+h*y3);
    y = y+0.5*(A+B);
    y1=y1+0.5*(A1+B1);
    file<<t<<"\t"<<y<<"\n";
  }
  file.close();
  cout<<"Result in Euler_"+H.str()+".txt"<<endl;
}

void RK4(double h,double w0=1,double T=40,double y=1,double y1=0){
  double y1_2, y1_3, y1_4;
  double y2, y3, y4;
  ofstream file;
  stringstream H;
  H << fixed << setprecision(2) << h;
  file.open("RK4_"+H.str()+".txt");
  file<<"T\ty\twith\th="<<h<<"\n";

  for (double t = 0; t < T; t+=h) {
    y2=-w0*w0*y;
    y3=-w0*w0*y1;
    y4=pow(w0,4)*y;
    y1_4 = y1+h*y2+0.5*h*h*y3+1.0/6.0*pow(h,3)*y4;
    y1_2 = y1+1.0/3.0*h*y2+1.0/18.0*h*h*y3+pow(h,3)/162.0*y4;
    y1_3 = y1+2.0/3.0*h*y2+2.0/9.0*h*h*y3+2.0/81.0*pow(h,3)*y4;
    y=y+h*(1.0/8.0*y1+3.0/8.0*y1_2+3.0/8.0*y1_3+1.0/8.0*y1_4);
    y1=y1_4;
    file<<t<<"\t"<<y<<"\n";
  }
  file.close();
  cout<<"Result in RK4_"+H.str()+".txt"<<endl;
}


int main(){

  double y=1, y1=0, w0=1, T=40; //Initial state, y1 for y prime
  double h;  //User input of h
  int method = 1;
  cout<<"Please selet a method.\n(1 for Euler Method, 2 for Runge-Kutta 4th order Method, 3 for both.):\n";
  cin>>method;
  cout<<"Input h = ";
  cin>>h;
  cout<<"\nT = ";
  cin>>T;
  cout<<"\nw0 = ";
  cin>>w0;
  if(method == 1){
    cout<<"Using the Euler Method with h="<<h<<", w0="<<w0<<", T="<<T<<endl;
    Euler(h);
  }
  else if (method == 2){
    cout<<"Using the Runge-Kutta 4th order Method with h="<<h<<", w0="<<w0<<", T="<<T<<"."<<endl;
    RK4(h);
  }
  else{
    cout<<"Using the Euler Method with h="<<h<<", w0="<<w0<<", T="<<T<<endl;
    Euler(h);
    cout<<"\n";
    cout<<"Using the Runge-Kutta 4th order Method with h="<<h<<", w0="<<w0<<", T="<<T<<"."<<endl;
    RK4(h);
  }

  return 0;
}
