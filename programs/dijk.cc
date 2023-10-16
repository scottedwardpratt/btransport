#include "/Users/scottpratt/git/commonutils/software/include/msu_commonutils/commondefs.h"

using namespace std;

void Setlambda(vector<Eigen::Matrix<complex<double>,3,3>> &lambda);

int main(){
	int a,b,c,aprime,bprime;
	complex<double> ci(0,1.0);
	vector<Eigen::Matrix<complex<double>,3,3>> lambda(8);
	Eigen::Matrix<complex<double>,3,3> M;
	Setlambda(lambda);
	vector<vector<vector<complex<double>>>> f,d;
	f.resize(8);
	d.resize(8);
	for(a=0;a<8;a++){
		f[a].resize(8);
		d[a].resize(8);
		for(b=0;b<8;b++){
			f[a][b].resize(8);
			d[a][b].resize(8);
			for(c=0;c<8;c++){
				f[a][b][c]=0.0;
				d[a][b][c]=0.0;
			}
		}
	}
	for(a=0;a<8;a++){
		for(b=0;b<8;b++){
			for(c=0;c<8;c++){
				M=-0.25*ci*(lambda[a]*lambda[b]-lambda[b]*lambda[a])*lambda[c];
				f[a][b][c]=M.trace();
				M=0.25*(lambda[a]*lambda[b]+lambda[b]*lambda[a])*lambda[c];
				d[a][b][c]=M.trace();
				//printf("f[%d][%d][%d]=(%6.3f,%6.3f), d[%d][%d][%d]=(%6.3f,%6.3f)\n",
				////a,b,c,real(f[a][b][c]),imag(f[a][b][c]),
				//a,b,c,real(d[a][b][c]),imag(d[a][b][c]));
			}
		}
	}
	
	for(a=0;a<8;a++){
		for(b=0;b<=a;b++){
			for(aprime=0;aprime<8;aprime++){
				for(bprime=0;bprime<=a;bprime++){
					complex<double> C;
					C=0.0;
					for(c=0;c<8;c++){
						C+=d[a][b][c]*d[aprime][bprime][c];
					}
					//printf("S(%d,%d;%d,%d)=(%g,%g) ",a,b,aprime,bprime,real(C),imag(C));
					C=0.0;
					for(c=0;c<8;c++){
						C+=f[a][b][c]*f[aprime][bprime][c];
					}
					if(a!=b && aprime!=bprime){
						if(real(C*conj(C))>0.000001)
						 printf("A(%d,%d;%d,%d)=(%g,%g)\n",a,b,aprime,bprime,real(C),imag(C));
					}
					//printf("\n");
				}
			}
		}
	}
	
	printf("----------------\nd_abcd_a'bc=\n");
	Eigen::Matrix<complex<double>,8,8> D;
	for(a=0;a<8;a++){
		for(aprime=0;aprime<8;aprime++){
			D(a,aprime)=0.0;
			for(b=0;b<8;b++){
				for(c=0;c<8;c++){
					D(a,aprime)+=d[a][b][c]*d[b][c][aprime];
				}
			}
			printf("(%7.4f,%7.4f) ",real(D(a,aprime)),imag(D(a,aprime)));
		}
		printf("\n");
	}
	printf("----------------\n");
	
	// Calc constant sum_abc d_abc^2
	double sum=0.0;
	for(a=0;a<8;a++){
		for(b=0;b<8;b++){
			for(c=0;c<8;c++){
				sum+=real(d[a][b][c]*conj(d[a][b][c]));
			}
		}
	}
	printf("Sum_{abc}d_{abc}^2=%g\n",sum);
	
	complex<double> Qabc,guess;
	for(a=0;a<8;a++){
		for(b=0;b<8;b++){
			for(c=0;c<8;c++){
				Qabc=(lambda[a]*lambda[b]*lambda[c]).trace();
				guess=2.0*(d[a][b][c]+ci*f[a][b][c]);
				if(abs(Qabc-guess)>.0001)
					printf("(%g,%g) =? (%g,%g)\n",real(Qabc),imag(Qabc),real(guess),imag(guess));
				
			}
		}
	}
	
	complex<double> d2=0.0,funkyd=0.0,d2test=0.0;
	int i,j,k;
	for(a=0;a<8;a++){
		for(b=0;b<8;b++){
			for(c=0;c<8;c++){
				d2test+=2.0*d[a][b][c]*d[a][b][c];
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						for(k=0;k<3;k++){
							d2+=d[a][b][c]*lambda[a](i,j)*lambda[b](j,k)*lambda[c](k,i);
							funkyd+=d[a][b][c]*lambda[a](j,k)*lambda[b](j,i)*lambda[c](k,i);
						}
					}
				}
			}
		}
	}
	printf("d2=(%g,%g) =? (%g,%g), funky=(%g,%g)\n",real(d2),imag(d2),real(d2test),imag(d2test),real(funkyd),imag(funkyd));
	
	
	
	return 0;
}


void Setlambda(vector<Eigen::Matrix<complex<double>,3,3>> &lambda){
	complex<double> ci(0.0,1.0);
	lambda[0] << 0,1,0,
	             1,0,0,
							 0,0,0;
							 
	lambda[1] << 0,-ci,0,
	             ci,0,0,
							 0,0,0;
							 
	lambda[2] << 1,0,0,
						 	 0,-1,0,
						 	 0,0,0;
							 
	lambda[3] << 0,0,1,
						 	 0,0,0,
						 	 1,0,0;
							 
	lambda[4] << 0,0,-ci,
							 0,0,0,
							ci,0,0;
							
	lambda[5] << 0,0,0,
	             0,0,1,
	             0,1,0;
							 
	lambda[6] << 0,0,0,
							 0,0,-ci,
							 0,ci,0;
							 
	lambda[7] << 1.0/sqrt(3.0),0,0,
							 0,1.0/sqrt(3.0),0,
							 0,0,-2.0/sqrt(3.0);	
}