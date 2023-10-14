#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
#include <boost/math/special_functions.hpp>

const double PI=4.0*atan(1.0);
const double HBARC=197.3269602;

using namespace std;

int main(int argc,char *argv[]){
	int p,q;
	double Q2,Q3;
	FILE *fptrgluon=fopen("pq3_gluon.txt","w");
	FILE *fptrquark=fopen("pq3_quark.txt","w");
	FILE *fptrantiquark=fopen("pq3_antiquark.txt","w");
	for(p=0;p<200;p++){
		for(q=0;q<200;q++){
			//C1=(p*p+q*q+3.0*p+3.0*q+p*q)/3.0;
			//C2=(p-q)*(3.0+p+2.0*q)*(3.0+q+2.0*p)/18.0;
			Q2=(p*p+q*q+3.0*p+3.0*q+p*q)/3.0;
			Q3=(p-q)*(3.0+p+2.0*q)*(3.0+q+2.0*p)/18.0;
			if((p-q)%3 == 0)
				fprintf(fptrgluon,"%3d %3d %g %g\n",p,q,Q2,Q3);
			if((p-q)%3 == 1 || (q-p)%3==2)
				fprintf(fptrquark,"%3d %3d %g %g\n",p,q,Q2,Q3);
			if((p-q)%3 == 2 || (q-p)%3==1)
				fprintf(fptrantiquark,"%3d %3d %g %g\n",p,q,Q2,Q3);
		}
	}
	fclose(fptrgluon);
	fclose(fptrquark);
	fclose(fptrantiquark);
	
	return 0;
}


