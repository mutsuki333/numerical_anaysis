#include <iostream>
#include <cmath>

using namespace std;

double c1_value(double P){
  return P*P+4*P-10;
}
double c1_derivation(double P){
  return 2*P+4;
}

int main(int argc, char const *argv[]) {

  double P0, TOL=0.00001;
  int N0 = 100000, rootIdx = 0;
  double root[10], delta = 5;
  bool NoRoot = true, firstRoot = true;

  // cout<<"Input P0."<<endl;
  // cin>>P0;

  double P;

  for (double i = -1000; i < 1000; i+=delta) {
    P0 = i;
    for (int j = 0; j < N0; j++) {
      P=P0-c1_value(P0)/c1_derivation(P0);
      if(firstRoot && abs(P-P0)<TOL){
        root[rootIdx] = P;
        cout<<"root "<<rootIdx+1<<" : "<<root[rootIdx]<<endl;
        firstRoot = false;
        NoRoot = false;
      }
      if (abs(P-P0)<TOL && abs(P-root[rootIdx])>TOL) {
        rootIdx++;
        root[rootIdx] = P;
        cout<<"root "<<rootIdx+1<<" : "<<root[rootIdx]<<endl;
        break;
      }
      P0=P;
    }
  }

  if(NoRoot)
    cout<<"Solution not found."<<endl;

  return 0;
}
