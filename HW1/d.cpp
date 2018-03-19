#include <iostream>
#include <cmath>
#include <vector>

class Diff{
public:
  void setPow(int p);
  void setCoefAt(int i, double c);
  void diff();
  double f(double p);
  double ff(double p);

private:
  int pow, dpow;
  std::vector<double> coef, dcoef;

};

#define TOL 0.00001
#define N 100000

using namespace std;

int main(int argc, char const *argv[]) {

  double P0=-1000;

  int pow;
  double coef;
  Diff G;
  int rootIdx = 0;
  double root[10], delta = 1;
  bool NoRoot = true, firstRoot = true;

  cout<<"Input highest power of the equation.\n";
  cin>>pow;
  G.setPow(pow);
  cout<<"Input the coefficient in descending order.:\n(Separated by space or enter)\n";
  for (int i = pow; i >= 0; i--) {
    cin>>coef;
    G.setCoefAt(i, coef);
  }
  G.diff();

  double P;
  for (double i = -1000; i < 1000; i+=delta) {
    P0 = i;
    for (int j = 0; j < N; j++) {
      P=P0-G.f(P0)/G.ff(P0);
      if(firstRoot && abs(P-P0)<TOL){
        root[rootIdx] = P;
        cout<<"root "<<rootIdx+1<<" : "<<root[rootIdx]<<endl;
        firstRoot = false;
        NoRoot = false;
      }
      if (abs(P-P0)<TOL && abs(P-root[rootIdx])>1) {
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


void Diff::setPow(int p){
  pow = p;
  dpow = p-1;
  coef.resize(pow+1);
  dcoef.resize(dpow+1);
}

void Diff::setCoefAt(int i, double c){
  coef.at(i) = c;
}

void Diff::diff(){
  for (int i = 1; i <= pow; i++) {
    dcoef.at(i-1) = i*coef.at(i);
  }
}

double Diff::f(double p){
  double value = 0;
  for (int i = pow; i > 0; i--) {
    value = (value+coef.at(i))*p;
  }
  value += coef.at(0);
  return value;
}

double Diff::ff(double p){
  double value = 0;
  for (int i = dpow; i > 0; i--) {
    value = (value+dcoef.at(i))*p;
  }
  value += dcoef.at(0);
  return value;
}
