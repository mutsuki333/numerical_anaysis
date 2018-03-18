#ifndef DIFF
#define DIFF

#include <iostream>
#include <vector>
#include <cmath>



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


#endif
