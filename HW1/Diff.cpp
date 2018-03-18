#include "Diff.h"

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
