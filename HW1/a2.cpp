#include <iostream>
#include <cmath>

using namespace std;

double a2_value(double P){
  return exp(P)-P-1;
}
double a2_derivation(double P){
  return exp(P)-1;
}

int main(int argc, char const *argv[]) {

  double P0=-100, TOL=0.00000000001;
  int N0 = 100000;
  double root;
  bool NoRoot = false;

  // cout<<"Input P0."<<endl;
  // cin>>P0;

  double P;
  for (int i = 0; i < N0; i++) {
    P=P0-a2_value(P0)/a2_derivation(P0);
    if (abs(P-P0)<TOL) {
      root = P;
      break;
    }
    P0=P;
    if(a2_derivation(P0)==0 || i==N0-1)
      NoRoot = true;
  }

  cout<<"root: "<<root<<endl;

  if(NoRoot)
    cout<<"Solution not found."<<endl;

  return 0;
}
