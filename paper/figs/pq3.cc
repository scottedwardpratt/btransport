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
	FILE *fptrgluon=fopen("pq3_gluon.txt","w");
	FILE *fptrquark=fopen("pq3_quark.txt","w");
	FILE *fptrantiquark=fopen("pq3_antiquark.txt","w");
	for(p=0;p<50;p++){
		for(q=0;q<50;q++){
			if((p-q)%3 == 0)
				fprintf(fptrgluon,"%3d %3d\n",p,q);
			if((p-q)%3 == 1)
				fprintf(fptrquark,"%3d %3d\n",p,q);
			if((p-q)%3 == 2)
				fprintf(fptrantiquark,"%3d %3d\n",p,q);
		}
	}
	fclose(fptrgluon);
	fclose(fptrquark);
	fclose(fptrantiquark);
	
	return 0;
}


