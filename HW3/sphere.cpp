#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

double Sphere_Area(double r, int n, int m){
  double a = M_PI/n, b = 2*M_PI/m;
  double area = 0;
  double p1[3], p2[3], p3[3], p4[3];
  double A[3], B[3];
  double N[3];
  ofstream file;
  file.open("Sphere_"+to_string(n)+"_"+to_string(m)+".stl");
  file<<"solid shpere_"<<n<<"_"<<m<<"\n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      p1[0] = r*sin(j*a)*cos(i*b);
      p1[1] = r*sin(j*a)*sin(i*b);
      p1[2] = r*cos(j*a);

      p2[0] = r*sin(j*a)*cos((i+1)*b);
      p2[1] = r*sin(j*a)*sin((i+1)*b);
      p2[2] = r*cos(j*a);

      p3[0] = r*sin((j+1)*a)*cos(i*b);
      p3[1] = r*sin((j+1)*a)*sin(i*b);
      p3[2] = r*cos((j+1)*a);

      p4[0] = r*sin((j+1)*a)*cos((i+1)*b);
      p4[1] = r*sin((j+1)*a)*sin((i+1)*b);
      p4[2] = r*cos((j+1)*a);

      A[0] = p4[0] - p1[0];
      A[1] = p4[1] - p1[1];
      A[2] = p4[2] - p1[2];

      B[0] = p2[0] - p3[0];
      B[1] = p2[1] - p3[1];
      B[2] = p2[2] - p3[2];

      N[0] = A[1]*B[2]-A[2]*B[1];
      N[1] = A[2]*B[0]-A[0]*B[2];
      N[2] = A[0]*B[1]-A[1]*B[0];

      file<<"\tfacet normal "<<scientific<<N[0]<<" "<<N[1]<<" "<<N[2]<<"\n";
      file<<"\t\touter loop\n";
      file<<"\t\t\tvertex "<<scientific<<p2[0]<<" "<<p2[1]<<" "<<p2[2]<<"\n";
      file<<"\t\t\tvertex "<<scientific<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<"\n";
      file<<"\t\t\tvertex "<<scientific<<p4[0]<<" "<<p4[1]<<" "<<p4[2]<<"\n";
      file<<"\t\tendloop\n";
      file<<"\tendfacet\n";

      file<<"\tfacet normal "<<scientific<<N[0]<<" "<<N[1]<<" "<<N[2]<<"\n";
      file<<"\t\touter loop\n";
      file<<"\t\t\tvertex "<<scientific<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<"\n";
      file<<"\t\t\tvertex "<<scientific<<p3[0]<<" "<<p3[1]<<" "<<p3[2]<<"\n";
      file<<"\t\t\tvertex "<<scientific<<p4[0]<<" "<<p4[1]<<" "<<p4[2]<<"\n";
      file<<"\t\tendloop\n";
      file<<"\tendfacet\n";

      area += sqrt(pow(N[0],2)+pow(N[1],2)+pow(N[2],2))/ 2;

    }
  }

  file<<"endsolid\n";
  file.close();
  return area;
}

double Sphere_Volume(double area, double r){
  return area*r/3;
}

int main(int argc, char const *argv[]) {

  const double r = 1;
  int n, m;

  double area = 4*M_PI*pow(r,2), volume = (double)4/3*M_PI*pow(r,3);
  cout<<"Original Sphere :\n";
  cout<<"\tSphere Area\t= "<<area<<"\n\tSphere Volume\t= "<<volume<<endl;

  double error_1a, error_1v, error_2a, error_2v;
  double a1, v1, a2, v2;

  cout<<"\nCalculating the Sphere area with n=10, m=10."<<endl;
  n=10;m=10;
  a1 = Sphere_Area(r,n,m);
  v1 = Sphere_Volume(a1,r);
  error_1a = area - a1;
  error_1v = volume - v1;
  cout<<"\tSphere Area\t= "<<a1<<"\n\tSphere Volume\t= "<<v1;
  cout<<"\n\tArea Error\t= "<<error_1a<<"\n\tVolume Error\t= "<<error_1v<<endl;
  cout<<"STL file generated in Sphere_"<<n<<"_"<<m<<".stl .\n";

  cout<<"\nCalculating the Sphere area with n=100, m=100."<<endl;
  n=100;m=100;
  a2 = Sphere_Area(r,n,m);
  v2 = Sphere_Volume(a2,r);
  error_2a = area - a2;
  error_2v = volume - v2;
  cout<<"\tSphere Area\t= "<<a2<<"\n\tSphere Volume\t= "<<v2;
  cout<<"\n\tArea Error\t= "<<error_2a<<"\n\tVolume Error\t= "<<error_2v<<endl;
  cout<<"STL file generated in Sphere_"<<n<<"_"<<m<<".stl .\n";

  return 0;
}
