int degen(int p,int q){
  int answer;
  answer=(p+1)*(q+1)*(p+q+2);
  return answer/2;
}

double omega_bessel(double T,double V){
  return (2.0*V/(PI*PI*HBARC*HBARC*HBARC))*T*T*T;
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
