#include <iostream>
#include <cmath>

using namespace std;

double c2_value(double P){
  return P*P*P-3*P*P-6*P+8;
}
double c2_derivation(double P){
  return 3*P*P-6*P-6;
}

int main(int argc, char const *argv[]) {

  double P0, TOL=0.00001;
  int N0 = 100000, rootIdx = 0;
  double root[10], delta = 1;
  bool NoRoot = true, firstRoot = true;

  // cout<<"Input P0."<<endl;
  // cin>>P0;

  double P;

  for (double i = -1000; i < 1000; i+=delta) {
    P0 = i;
    for (int j = 0; j < N0; j++) {
      P=P0-c2_value(P0)/c2_derivation(P0);
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
