#include <iostream>
#include <cmath>

using namespace std;

double b2_value(double P){
  return P*P*P-3*P*P-6*P+8;
}
double b2_derivation(double P){
  return 3*P*P-6*P-6;
}

int main(int argc, char const *argv[]) {

  double P0=-100, TOL=0.00001;
  int N0 = 100000;
  double root1, root2;
  bool NoRoot = false;

  // cout<<"Input P0."<<endl;
  // cin>>P0;

  double P;
  for (int i = 0; i < N0; i++) {
    P=P0-b2_value(P0)/b2_derivation(P0);
    if (abs(P-P0)<TOL) {
      root1 = P;
      break;
    }
    P0=P;
    if(b2_derivation(P0)==0 || i==N0-1)
      NoRoot = true;
  }

  P0 = 100;
  for (int i = 0; i < N0; i++) {
    P=P0-b2_value(P0)/b2_derivation(P0);
    if (abs(P-P0)<TOL) {
      root2 = P;
      break;
    }
    P0=P;
    if(b2_derivation(P0)==0 || i==N0-1)
      NoRoot = true;
  }

  if(abs(root1-root2)<TOL){
    cout<<"root: "<<root1<<endl;
  }
  else {
    cout<<"root1: "<<root1<<endl;
    cout<<"root2: "<<root2<<endl;
  }

  if(NoRoot)
    cout<<"Solution not found."<<endl;

  return 0;
}
