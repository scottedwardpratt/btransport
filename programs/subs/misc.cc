#include "bess.cc"		

int degen(int p,int q){
  int answer;
  answer=(p+1)*(q+1)*(p+q+2);
  return answer/2;
}

int Casimir(int p,int q){
	//printf("Ccheck=%g\n",double(p*p+q*q+3*p+3*q+p*q)/3.0);
	return (p*p+q*q+3*p+3*q+p*q)/3;
}

void Casimir12(int p,int q,double &C1,double &C2){
	//printf("Ccheck=%g\n",double(p*p+q*q+3*p+3*q+p*q)/3.0);
	C1=(p*p+q*q+3*p+3*q+p*q)/3.0;
	C2=(p-q)*(3+p+2*q)*(3+q+2*p)/18.0;
}


double omega_massless(double T,double V){
  const double prefactor=(1.0/(2.0*PI*PI*HBARC*HBARC*HBARC));
  return 4.0*V*prefactor*T*T*T;
}

double omegae_massless(double T,double V){
  const double prefactor=(1.0/(2.0*PI*PI*HBARC*HBARC*HBARC));
  return 12.0*V*prefactor*T*T*T*T;
}

double omega_bessel(double mass,double T,double V){
  const double prefactor=(1.0/(PI*PI*HBARC*HBARC*HBARC));
  double z,answer;
  z=mass/T;
  answer=V*pow(mass,3)*prefactor*(z*bessk0(z)+2.0*bessk1(z))/(z*z);
  //printf("omega check: %g %g\n",answer,omega_massless(T,V));
  return answer;
}

// Note: omegae=-(partial/partial beta) omega

double omegae_bessel(double mass,double T,double V){
  const double prefactor=(1.0/(PI*PI*HBARC*HBARC*HBARC));
  double z,answer;
  z=mass/T;
  answer=V*pow(mass,4)*prefactor*(3.0*z*bessk0(z)+(z*z+6.0)*bessk1(z))/(z*z*z);
  //printf("omegae check: %g %g\n",answer,omegae_massless(T,V));
  return answer;
}

double omegap_bessel(double mass,double T,double V){
  const double prefactor=(1.0/(PI*PI*HBARC*HBARC*HBARC));
  double z,answer;
  z=mass/T;
  answer=V*mass*mass*T*T*prefactor*(bessk0(z)+2*bessk1(z)/z);
  //printf("omegae check: %g %g\n",answer,omegae_massless(T,V));
  return answer;
}

double omega_quantum(double mass,double T,double V){
  int ix,iy,iz,imax;
  double length,delp,pmag,e,px,py,pz,p,dele,answer;
  
  length=pow(V,1.0/3.0);
  delp=HBARC*PI/length;
  answer=0.0;
  imax=int(1+2000.0/delp);
  for(ix=0;ix<imax;ix++){
    px=(0.5+ix)*delp;
    for(iy=0;iy<imax;iy++){
      py=(0.5+iy)*delp;
      for(iz=0;iz<imax;iz++){
	pz=(0.5+iz)*delp;
	pmag=sqrt(px*px+py*py+pz*pz);
	e=sqrt(pmag*pmag+mass*mass);
	answer+=2.0*exp(-e/T);
      }
    }
  }
  return answer;
}
