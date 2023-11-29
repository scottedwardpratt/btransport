#include <cstdlib>
#include <cmath>
#include <cstdio>
#include "msu_commonutils/randy.h"

const double PI=3.14159265358979323844;
const double HBARC=197.3269602;

using namespace std;
using namespace NMSUPratt;

#include "subs/misc.cc"
#include "subs/newpq.cc"
#include "subs/tableaux.cc"
#include "subs/addmults.cc"
	


int main(){
	long long int ip,ntot=0,iran,nran=40000;
	int A,Amax;
	int nquarks,nanti,ngluons;
	double nsinglets,nbar,D,Q2bar;
	double sigma2_Q2_tot, sigma2_Q3_tot,sigma2_BQ3_tot,Q2bar_tot;
	double sigma2_Q2,sigma2_Q3,sigma2_BQ3;
	
	Tpq *pq;
	Tpqlist **pqlist;
	NMSUPratt::Crandy *randy=new Crandy(time(NULL));
	
	double eta_quark,eta_gluon=0.0;
	printf("Enter eta_quark: ");
	scanf("%lf",&eta_quark);
	int ASuperMax=12*eta_quark+9*eta_gluon+20;
	
	randy->set_mean(eta_quark);
	
	pqlist=new Tpqlist *[ASuperMax+1];
	for(A=0;A<=ASuperMax;A++)
		pqlist[A]=new Tpqlist(ASuperMax);

	sigma2_Q2_tot=0.0;
	sigma2_Q3_tot=0.0;
	sigma2_BQ3_tot=0.0;
	Q2bar_tot=0.0;
	
	for(iran=0;iran<nran;iran++){
		do{
			nquarks=randy->poisson();
			nanti=randy->poisson();
			ngluons=0;
			Amax=ngluons+nquarks+nanti;
		}while(Amax>=ASuperMax);
		//printf("-------------------\nnquarks=%d, nanti=%d\n",nquarks,nanti);
		
		pqlist[0]->clear();
		pqlist[0]->add(0,0,1);
		//pqlist[0]->print();
		for(A=1;A<=Amax;A++){
			pqlist[A]->clear();
			//printf("------ A-1=%d ------\n",A-1);
			//pqlist[A-1]->print();
			for(pq=pqlist[A-1]->first;pq!=NULL;pq=pq->next){
				if(A<=ngluons)
					addmults_list(pq->p,pq->q,pq->n,1,1,1,pqlist[A]);
				if(A>ngluons && A<=ngluons+nquarks)
					addmults_list(pq->p,pq->q,pq->n,1,0,1,pqlist[A]);
				if(A>ngluons+nquarks)
					addmults_list(pq->p,pq->q,pq->n,0,1,1,pqlist[A]);
			}
			pqlist[A]->compress();
		}
		D=pow(3.0,Amax);
		sigma2_Q2=sigma2_Q3=sigma2_BQ3=Q2bar=0.0;
		for(pq=pqlist[Amax]->first;pq!=NULL;pq=pq->next){
			Q2bar+=double(pq->n)*double(pq->C1)*double(pq->degen)/D;
			sigma2_Q2+=double(pq->n)*double(pq->C1*pq->C1)*double(pq->degen)/D;
			if(pq->C1>0.00001){
				sigma2_Q3+=double(pq->n)*double(pq->C2*pq->C2)*double(pq->degen)/D;
				sigma2_BQ3+=double(pq->n)*double(nquarks-nanti)*double(pq->C2)*double(pq->degen)/D;
			}
		}
		//printf("D=%lld =? %g\n",D,pow(3.0,Amax));
		//printf("sigma2_Q2=%g\n",sigma2_Q2);
		Q2bar_tot+=Q2bar;
		sigma2_Q2_tot+=sigma2_Q2;
		sigma2_Q3_tot+=sigma2_Q3;
		sigma2_BQ3_tot+=sigma2_BQ3;
			
	}
	Q2bar_tot=Q2bar_tot/double(nran);
	sigma2_Q2_tot=sigma2_Q2_tot/double(nran);
	sigma2_Q3_tot=sigma2_Q3_tot/double(nran);
	sigma2_BQ3_tot=sigma2_BQ3_tot/double(nran);
	printf("Q2bar=%g\n",Q2bar_tot);
	printf("sigma2_Q2=%g\n",sigma2_Q2_tot/(Q2bar_tot*Q2bar_tot));
	printf("sigma2_Q3=%g\n",sigma2_Q3_tot/(Q2bar_tot*Q2bar_tot*Q2bar_tot));
	printf("sigma2_BQ3=%g\n",sigma2_BQ3_tot/(Q2bar_tot));
	printf("Q2bar*DB/DQ3=%g\n",Q2bar_tot*sigma2_BQ3_tot/sigma2_Q3_tot);

	return 0;
}
