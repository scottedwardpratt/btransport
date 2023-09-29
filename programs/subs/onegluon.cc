#include <cstdlib>
#include <cmath>
#include <cstdio>

const double PI=3.14159265358979323844;

long IDUM=-12345; double ran2(void);
double dotproduct(double *pa,double *pb);

using namespace std;

int d(int i,int j);

int main(){
  int i,j;

  for(i=2;i<10;i++){
    printf("%5d",i);
    for(j=2;j<10;j++){
      printf("i=%d,j=%d, d(i,j)*d(1,0)=%d =? %d\n",
	     i,j,d(i,j)*d(1,0),d(i+1,j)+d(i-1,j+1)+d(i,j-1));
    }
  }
  for(i=1;i<10;i++){
    printf("%5d",i);
    for(j=1;j<10;j++){
      printf("i=%d,j=%d, d(i,j)*d(1,1)=%d =? %d\n",
	     i,j,d(i,j)*d(1,1),
	     d(i+1,j+1)+d(i+2,j-1)+d(i-2,j+1)
	     +2*d(i,j)+d(i-1,j+2)+d(i+1,j-2)+d(i-1,j-1));
    }
  }
  return 0;
}

int d(int i,int j){
  if(i>=0 && j>=0) return ((i+1)*(j+1)*(i+j+2))/2;
  else return 0;
}

