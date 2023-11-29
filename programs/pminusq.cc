#include <cstdlib>
#include <cmath>
#include <cstdio>

const double PI=3.14159265358979323844;
const double HBARC=197.3269602;

using namespace std;

#include "subs/misc.cc"
#include "subs/pq.cc"
#include "subs/tableaux.cc"
#include "subs/addmults.cc"

int main(){
  int A,Amax;
  int nquarks,nanti,ngluons;
  double dtrue,dtot,nsinglets,pminusqbar=0.0,Q3bar=0.0,Q2bar=0.0;
  Tpq *pq;
  Tpqlist **pqlist;
	
  //printf("Enter Ngluons, Nquarks and Nantiquarks : ");
	ngluons=nanti=0;
  scanf("%d",&nquarks);
	
	
  Amax=ngluons+nquarks+nanti;
  pqlist=new Tpqlist *[Amax+1];
  for(A=0;A<=Amax;A++)
		pqlist[A]=new Tpqlist(int(1.5*ngluons)+nquarks+nanti);
  pqlist[0]->add(0,0,1);
	
  for(A=1;A<=Amax;A++){
    pqlist[A]->clear();
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
	
  dtot=0;
  nsinglets=0;
  for(pq=pqlist[Amax]->first;pq!=NULL;pq=pq->next){
    dtot+=degen(pq->p,pq->q)*pq->n;
    if(pq->p==0 && pq->q==0)
			nsinglets+=pq->n;
		pminusqbar+=(pq->p-pq->q)*degen(pq->p,pq->q)*pq->n;
		Q3bar+=pq->C2*degen(pq->p,pq->q)*pq->n;
		Q2bar+=pq->C1*degen(pq->p,pq->q)*pq->n;
  }
	pminusqbar=pminusqbar/dtot;
	Q3bar=Q3bar/dtot;
	Q2bar=Q2bar/dtot;
  dtrue=pow(double(3),nquarks+nanti)*pow(8.0,ngluons);
  printf("dtot=%g =? %g\n",dtot,dtrue);
  printf("Nsinglets=%g\n",nsinglets);
	printf("%5d <p-q>=%10.5f, <Q3>=%10.5f=?%10.5f\n",nquarks-nanti,pminusqbar,Q3bar,(10.0/9.0)*(nquarks-nanti));
	printf("<Q2>=%g =? %g\n",Q2bar,(4.0/3.0)*(nquarks+nanti)+3*ngluons);
		//for(A=0;A<=Amax;A++) pqlist[A]->print();
	pqlist[Amax]->print();
	
	FILE *fptr=fopen("pminusq_vs_B.txt","a");
	fprintf(fptr,"%5d  %10.5f %10.5f  %10.5f\n",nquarks,Q2bar,pminusqbar,Q3bar);
	fclose(fptr);
		
  return 0;
}
