#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <vector>

const double PI=3.14159265358979323844;
const double HBARC=197.3269602;

using namespace std;

#include "subs/misc.cc"
#include "subs/newpq.cc"
#include "subs/tableaux.cc"
#include "subs/addmults.cc"

int main(){
	int A,Amax,Nmax=21;
	int nquarks,nanti,ngluons=0,qcount,p,q,b;
	double dtrue,dtot,nsinglets;
	Tpq *pq,*pqnew;
	Tpqlist **pqlist;
	int pqmax=Nmax;
	vector<vector<int>> smallestA;
	vector<vector<int>> npaths;
	vector<vector<vector<int>>> bvec;
	smallestA.resize(pqmax);
	npaths.resize(pqmax);
	bvec.resize(pqmax);
	for(p=0;p<pqmax;p++){
		smallestA[p].resize(pqmax);
		npaths[p].resize(pqmax);
		bvec[p].resize(pqmax);
		for(q=0;q<pqmax;q++){
			smallestA[p][q]=1000;
			npaths[p][q]=0;
		}
	}
	
	pqlist=new Tpqlist *[Nmax+1];
	for(A=0;A<=Nmax;A++)
		pqlist[A]=new Tpqlist(Nmax+1);
	pqlist[0]->add(0,0,1);
	
	for(nquarks=0;nquarks<=Nmax;nquarks++){
		for(nanti=0;nanti<=Nmax-nquarks;nanti++){
			for(A=0;A<=Nmax;A++){
				pqlist[A]->clear();
			}
			b=nquarks-nanti;
			Amax=nquarks+nanti;
			pqlist[0]->add(0,0,1);
			if(Amax>0 && Amax<=Nmax){
				for(A=1;A<=Amax;A++){
					//pqlist[A]->clear();
					for(pq=pqlist[A-1]->first;pq!=NULL;pq=pq->next){
						if(A<=nquarks)
							addmults_list(pq->p,pq->q,pq->n,1,0,1,pqlist[A]);
						else if(A>nquarks)
							addmults_list(pq->p,pq->q,pq->n,0,1,1,pqlist[A]);	
					}
					pqlist[A]->compress();
				}
				if((nquarks==2 && nanti==0) || (nquarks==0 && nanti==2))
					pqlist[Amax]->print();

				for(pq=pqlist[Amax]->first;pq!=NULL;pq=pq->next){
					//if(nquarks==nanti)
						//pqlist[Amax]->print();
					p=pq->p; q=pq->q;
					if(p<pqmax && q<pqmax){
						if(Amax<smallestA[p][q]){
							smallestA[p][q]=Amax;
							npaths[p][q]=1;
							bvec[p][q].clear();
							bvec[p][q].push_back(b);
						}
						else if(Amax==smallestA[p][q]){
							npaths[p][q]=1;
							bvec[p][q].push_back(b);
						}
					}
				}
			}	
		}
	}
	
	double bbar,bdenom;
	for(p=0;p<pqmax;p++){
		for(q=0;q<pqmax;q++){
			b=p-q;
			if(p+q<Nmax){
				bbar=bdenom=0.0;
				printf("%2d %2d: %3d %3d ------ ",p,q,smallestA[p][q],npaths[p][q]);
				for(int ib=0;ib<bvec[p][q].size();ib++){
					printf("%3d ",bvec[p][q][ib]);
					bbar+=npaths[p][q]*bvec[p][q][ib];
					bdenom+=npaths[p][q];
				}
				printf("  <b>=%g\n",bbar/bdenom);
			}
		}
	}
	return 0;
}
