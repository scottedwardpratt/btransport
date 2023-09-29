#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "bess.h"

const double PI=3.14159265358979323844;

using namespace std;

int main(){
  int n;
  double z,ans,delz;
  
 TRYNEW:
  printf("What is z?\n");
  scanf("%lf",&z);
  delz=z/1000.0;
  ans=bessk0(z);
  printf("K0(%g)=%g\n",z,ans);
  ans=bessk1(z);
  printf("K1(%g)=%g\n",z,ans);
  ans=(bessk0(z+0.5*delz)-bessk0(z-0.5*delz))/delz;
  printf("K0'(%g)=%g\n",z,ans);
  ans=(bessk1(z+0.5*delz)-bessk1(z-0.5*delz))/delz;
  printf("K1'(%g)=%g\n",z,ans);

  printf("What is n? (Choose n>0)");
  scanf("%d",&n);

  ans=bessk(n,z);
  printf("K(%d,%g)=%g\n",n,z,ans);

  printf("Enter 0 to quit, other to continue\n");
  scanf("%d",&n);
  if(n!=0) goto TRYNEW;
  
  return 0;
}

#include "bess.cc"
