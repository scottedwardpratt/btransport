#include "bess.h"
#include <math.h>

double getomega(double mass,double temperature,double volume){
  double answer,mass2,mass3,mass4;
  double k0,k1,z,prefact;
  const double HBARC=197.326;
  const double HBARC3=HBARC*HBARC*HBARC;
  const double PI = M_PI;

  mass3=mass*mass*mass;  
  z=mass/temperature;
  k0=bessk0(z);
  k1=bessk1(z);
  prefact=1.0/(2.0*PI*PI*HBARC3);
  answer=volume*prefact*mass3*(k0*z+2.0*k1)/(z*z);

  return answer;
}

