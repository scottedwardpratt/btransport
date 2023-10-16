class Tpq{
public:
  int p,q;
	long long int degen;
  double n;
  Tpq *next;
  Tpq(int pset,int qset,double nset);
	double C1,C2;
	void Casimir12(){
		C1=(p*p+q*q+3.0*p+3.0*q+p*q)/3.0;
		C2=(p-q)*(3.0+p+2.0*q)*(3.0+q+2.0*p)/18.0;
	}
};

Tpq::Tpq(int pset,int qset,double nset){
	p=pset;
	q=qset;
	n=nset;
	next=NULL;
	degen=(p+1)*(q+1)*(p+q+2)/2;
	Casimir12();
}

class Tpqlist{
public:
	int pqmax;
	Tpq ***pqptr_array;
	Tpq *first;
	Tpq *last;
	Tpqlist(int Amax);
	void add(int p,int q,double n);
	void clear();
	void cgluon(int ell);
	void cquark(int ell);
	void compress();
	void print();
};

Tpqlist::Tpqlist(int pqmax_set){
	int p,q;
	pqmax=pqmax_set;
	first=NULL;
	last=NULL;
	pqptr_array=new Tpq **[pqmax+1];
	for(p=0;p<=pqmax;p++){
		pqptr_array[p]=new Tpq *[pqmax+1];
		for(q=0;q<=pqmax;q++)
			pqptr_array[p][q]=NULL;
	}
}

void Tpqlist::compress(){
  Tpq *pq1,*pq2,*oldpq1,*pqtemp,*nextpq1;

  for(pq2=first->next;pq2!=NULL;pq2=pq2->next){
    oldpq1=NULL;

    for(pq1=first;pq1!=pq2;pq1=nextpq1){

      nextpq1=pq1->next;
      if(pq1->p==pq2->p && pq1->q==pq2->q){
	if(pq1==first){
	  pqtemp=first;
	  first=first->next;
	  pq1=first;
	}
	else{
	  pqtemp=pq1;
	  if(oldpq1==NULL){
	    printf("oldpq1=NULL?? error!\n");
	    exit(1);
	  }
	  oldpq1->next=pq1->next;
	  pq1=oldpq1;
	}
	pq2->n+=pqtemp->n;
	delete pqtemp;
      }
      else{
	oldpq1=pq1;
      }
    }
  }

}

void Tpqlist::print(){
	Tpq *pqptr;
	pqptr=first;
	double Bx,phi;
	printf("------------------------------------------------------------\n");
	do{
		pqptr->Casimir12();
		phi=2.0*PI*pqptr->C2/3.0;
		Bx=sin(3*phi)/sin(2.0*PI/9.0);
		phi=phi-Bx*2*PI/27.0;
		phi=phi-2.0*PI*rint(phi/(2.0*PI));
		//Fx=3*floor(pqptr->C2);
		//Bx=3*pqptr->C2-floor(3*pqptr->C2);
		printf("(%2d,%2d), degen=%5d, number=%5ld, C1=%12.6f, C2=%12.6f, phi=%9.3f, Bx=%9.6f\n",
		pqptr->p,pqptr->q,
		degen(pqptr->p,pqptr->q),lrint(pqptr->n),pqptr->C1,pqptr->C2,phi*180.0/PI,Bx);
		pqptr=pqptr->next;
	} while(pqptr!=NULL);
}

void Tpqlist::add(int p,int q,double n){
  Tpq *pq;
  if(p>pqmax || q>pqmax){
    printf("Trying to add to list something that is out of bounds!\n");
    exit(1);
  }
  pq=new Tpq(p,q,n);
  if(first==NULL){
    first=pq;
    last=pq;
  }
  else{
    last->next=pq;
    last=pq;
  }
}

void Tpqlist::clear(){
	Tpq *next;
	next=first;
	while(first!=NULL){
		next=first->next;
		delete first;
		first=next;
	}
	first=NULL;
	last=NULL;
	for(int p=0;p<=pqmax;p++){
		for(int q=0;q<=pqmax;q++){
				pqptr_array[p][q]=NULL;
		}
	}
}

void Tpqlist::cgluon(int ell){
  clear();
  if(ell==1) add(1,1,1.0);
  if(ell==2){
    add(2,2,1.0);
    add(0,3,-1.0);
    add(3,0,-1.0);
    add(0,0,1.0);
  }
  if(ell>=3){
    add(ell,ell,1.0);
    add(ell-2,ell+1,-1.0);
    add(ell+1,ell-2,-1.0);
    add(ell-2,ell-2,-1.0);
    add(ell,ell-3,1.0);
    add(ell-3,ell,1.0);
    add(0,0,2.0);
  }
}

void Tpqlist::cquark(int ell){
  clear();
  if(ell==1) add(1,0,1.0);
  if(ell==2){
    add(2,0,1.0);
    add(0,1,-1.0);
  }
  if(ell>=3){
    add(ell,0,1.0);
    add(ell-2,1,-1.0);
    add(ell-3,0,1.0);
  }
}
