#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;


/*根據半徑(r)和分割數計算表面積(n, m)
  利用xxx法, 面上每個點的座標為：
    x = r * cos(s) * sin(t)
    y = r * sin(s) * sin(t)
    z = r * cos(t)
  再以四個點的向量外積算出面積後加總*/
double Sphere_Area(double r, int n, int m){
  double a = M_PI/n, b = 2*M_PI/m;
  double area = 0;
  double p1[3], p2[3], p3[3], p4[3];
  double A[3], B[3];
  double N[3];
  ofstream file; //開檔
  file.open("Sphere_"+to_string(n)+"_"+to_string(m)+".stl");
  file<<"solid sphere_"<<n<<"_"<<m<<"\n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      /*
        更新四個點的座標([0]:x, [1]:y, [2]:z)
        p1--p2
        |    |
        p3--p4
      */
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

      //更新ＡＢ向量
      A[0] = p4[0] - p1[0];
      A[1] = p4[1] - p1[1];
      A[2] = p4[2] - p1[2];

      B[0] = p2[0] - p3[0];
      B[1] = p2[1] - p3[1];
      B[2] = p2[2] - p3[2];

      //計算法相量
      N[0] = A[1]*B[2]-A[2]*B[1];
      N[1] = A[2]*B[0]-A[0]*B[2];
      N[2] = A[0]*B[1]-A[1]*B[0];

      //將新的面的資訊存入stl檔案中
      //因為stl檔中每一個面為三角形構成，因此將正方形分為兩個三角形
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

      //總面積增加新正方形的面積
      //(1/2)*sqrt(Nx^2+Ny^2+Nz^2)
      //
      //       ____________
      // 1   / 2    2    2
      // -| / N  + N  + N
      // 2|/   x    y    z
      area += sqrt(pow(N[0],2)+pow(N[1],2)+pow(N[2],2))/ 2;

    }
  }

  file<<"endsolid\n";
  file.close();//關檔，輸出STL檔
  return area;
}

// 球體積為面積乘上半徑後除以3
double Sphere_Volume(double area, double r){
  return area*r/3;
}

int main(int argc, char const *argv[]) {

  const double r = 1;
  int n, m;

  //帶入球體體積公式和面積公式求值
  //體積 = (4/3)*Pi*r^3
  //面積 = 4*Pi*r^2
  double area = 4*M_PI*pow(r,2), volume = (double)4/3*M_PI*pow(r,3);
  cout<<"Original Sphere :\n";
  cout<<"\tSphere Area\t= "<<area<<"\n\tSphere Volume\t= "<<volume<<endl;

  double a1, v1, a2, v2; //儲存估算面積和體積
  double error_1a, error_1v, error_2a, error_2v; //儲存誤差量

  cout<<"\nCalculating the Sphere area with n=10, m=10."<<endl;
  n=10;m=10;//切成10*10份
  a1 = Sphere_Area(r,n,m); //估算面積
  v1 = Sphere_Volume(a1,r);//估算體積
  error_1a = area - a1;//計算誤差
  error_1v = volume - v1;//計算誤差
  cout<<"\tSphere Area\t= "<<a1<<"\n\tSphere Volume\t= "<<v1;
  cout<<"\n\tArea Error\t= "<<error_1a<<"\n\tVolume Error\t= "<<error_1v<<endl;
  cout<<"STL file generated in Sphere_"<<n<<"_"<<m<<".stl .\n";

  cout<<"\nCalculating the Sphere area with n=100, m=100."<<endl;
  n=100;m=100;//切成100*100份
  a2 = Sphere_Area(r,n,m);//估算面積
  v2 = Sphere_Volume(a2,r);//估算體積
  error_2a = area - a2;//計算誤差
  error_2v = volume - v2;//計算誤差
  cout<<"\tSphere Area\t= "<<a2<<"\n\tSphere Volume\t= "<<v2;
  cout<<"\n\tArea Error\t= "<<error_2a<<"\n\tVolume Error\t= "<<error_2v<<endl;
  cout<<"STL file generated in Sphere_"<<n<<"_"<<m<<".stl .\n";

  return 0;
}
