int BIGGESTP;
//#define PRINT_TABLEAUS
class Tweightlist{
public:
	int length;
	double inweight[5];
	double **outweight[5];
};

void RanStepWeighted(int &p,int &q,double randy,double &weight){
	int p1,q1,p2,q2;
	p1=p; q1=q;
	p2=q2=1; // gluons
	int degen1=degen(p1,q1);
	double ransum=0.0,maxsum=0.0;
	 
	int ip2,iq2,i,na0min,na1min,na1max,nb1min,nb1max,iw;
	int na[3],nb[3],nx[3];
	Ttableauxlist alist;
	Ttableaux *atableaux;
	Ttableaux *abtableaux;
	Ttableaux *testtableaux;

	for(i=0;i<3;i++) nb[i]=0;
	nx[0]=p1+q1;
	nx[1]=q1;
	nx[2]=0;

	na0min=p2+q2-(p1+q1);
	if(na0min<0) na0min=0;
	for(na[0]=na0min;na[0]<=p2+q2;na[0]++){
		na1min=(p2+q2-na[0])-q1;
		if(na1min<0) na1min=0;
		na1max=p1;
		if(na1max>p2+q2-na[0]) na1max=p2+q2-na[0];
		for(na[1]=na1min;na[1]<=na1max;na[1]++){
			na[2]=(p2+q2-na[0]-na[1]);
			atableaux=new Ttableaux(na,nb,nx);
			alist.add(atableaux);
		}
	}

	for(atableaux=alist.first;atableaux!=NULL;
	atableaux=atableaux->next){
		nb1min=q2-atableaux->length[1]+atableaux->length[2];
		if(nb1min<0) nb1min=0;
		nb1max=q2;
		if(nb1max>atableaux->length[0]-atableaux->length[1])
			nb1max=atableaux->length[0]-atableaux->length[1];
		if(nb1max>atableaux->na[0]) nb1max=atableaux->na[0];
		for(nb[1]=nb1min;nb[1]<=nb1max;nb[1]++){
			nb[2]=q2-nb[1];
			if(nb[2]<=atableaux->na[0]+atableaux->na[1]-nb[1]){
				p=atableaux->na[0]+nx[0]-atableaux->na[1]-nb[1]-nx[1];
				q=atableaux->na[1]+nb[1]+nx[1]-atableaux->na[2]-nb[2];
				if(p>BIGGESTP)
					BIGGESTP=p;
				maxsum+=1.0;
			}
		}
	}
	weight=maxsum/8.0;
	//printf("maxsum=%g, weight=%g\n",maxsum,weight);

	randy*=maxsum;
	for(atableaux=alist.first;atableaux!=NULL;
	atableaux=atableaux->next){
		nb1min=q2-atableaux->length[1]+atableaux->length[2];
		if(nb1min<0) nb1min=0;
		nb1max=q2;
		if(nb1max>atableaux->length[0]-atableaux->length[1])
			nb1max=atableaux->length[0]-atableaux->length[1];
		if(nb1max>atableaux->na[0]) nb1max=atableaux->na[0];
		for(nb[1]=nb1min;nb[1]<=nb1max;nb[1]++){
			nb[2]=q2-nb[1];
			if(nb[2]<=atableaux->na[0]+atableaux->na[1]-nb[1]){
				p=atableaux->na[0]+nx[0]-atableaux->na[1]-nb[1]-nx[1];
				q=atableaux->na[1]+nb[1]+nx[1]-atableaux->na[2]-nb[2];
				if(p>BIGGESTP)
					BIGGESTP=p;
				ransum+=1.0;
				if(ransum>maxsum+0.5){
					printf("ransum=%g, maxsum=%g\n",ransum,maxsum);
				}
				if(ransum>randy){
					alist.clear();
					return;
				}
			}
		}
	}
	alist.clear();
	printf("DIDN'T FIND RANSTEP!!!!\n");
	exit(1);
}

void RanStep(int &p,int &q,double randy,double &weight){
	weight=1.0;
	int p1,q1,p2,q2;
	p1=p; q1=q;
	p2=q2=1; // gluons
	int degen1=degen(p1,q1);
	double ransum=0.0;
	 
	int ip2,iq2,i,na0min,na1min,na1max,nb1min,nb1max,iw;
	int na[3],nb[3],nx[3];
	Ttableauxlist alist;
	Ttableaux *atableaux;
	Ttableaux *abtableaux;
	Ttableaux *testtableaux;
	for(i=0;i<3;i++) nb[i]=0;
	nx[0]=p1+q1;
	nx[1]=q1;
	nx[2]=0;

	na0min=p2+q2-(p1+q1);
	if(na0min<0) na0min=0;
	for(na[0]=na0min;na[0]<=p2+q2;na[0]++){
		na1min=(p2+q2-na[0])-q1;
		if(na1min<0) na1min=0;
		na1max=p1;
		if(na1max>p2+q2-na[0]) na1max=p2+q2-na[0];
		for(na[1]=na1min;na[1]<=na1max;na[1]++){
			na[2]=(p2+q2-na[0]-na[1]);
			atableaux=new Ttableaux(na,nb,nx);
			alist.add(atableaux);
		}
	}

	for(atableaux=alist.first;atableaux!=NULL;
	atableaux=atableaux->next){
		nb1min=q2-atableaux->length[1]+atableaux->length[2];
		if(nb1min<0) nb1min=0;
		nb1max=q2;
		if(nb1max>atableaux->length[0]-atableaux->length[1])
			nb1max=atableaux->length[0]-atableaux->length[1];
		if(nb1max>atableaux->na[0]) nb1max=atableaux->na[0];
		for(nb[1]=nb1min;nb[1]<=nb1max;nb[1]++){
			nb[2]=q2-nb[1];
			if(nb[2]<=atableaux->na[0]+atableaux->na[1]-nb[1]){
				p=atableaux->na[0]+nx[0]-atableaux->na[1]-nb[1]-nx[1];
				q=atableaux->na[1]+nb[1]+nx[1]-atableaux->na[2]-nb[2];
				if(p>BIGGESTP)
					BIGGESTP=p;
				ransum+=degen(p,q)/(8.0*degen1);
				if(ransum>randy){
					alist.clear();
					return;
				}
			}
		}

	}
	alist.clear();
	printf("DIDN'T FIND RANSTEP!!!!\n");
	exit(1);
}

void addmults(int p1,int q1,int p2,int q2,Tweightlist *weightlist){

	if(fabs(weightlist->inweight[0])>EPSILON){
		int p,q,ip2,iq2,i,na0min,na1min,na1max,nb1min,nb1max,iw;
		int na[3],nb[3],nx[3];
		Ttableauxlist *alist;
		Ttableaux *atableaux;
		Ttableaux *abtableaux;
		Ttableaux *testtableaux;

		alist=new Ttableauxlist;

		for(i=0;i<3;i++) nb[i]=0;
		nx[0]=p1+q1;
		nx[1]=q1;
		nx[2]=0;

		na0min=p2+q2-(p1+q1);
		if(na0min<0) na0min=0;
		for(na[0]=na0min;na[0]<=p2+q2;na[0]++){
			na1min=(p2+q2-na[0])-q1;
			if(na1min<0) na1min=0;
			na1max=p1;
			if(na1max>p2+q2-na[0]) na1max=p2+q2-na[0];
			for(na[1]=na1min;na[1]<=na1max;na[1]++){
				na[2]=(p2+q2-na[0]-na[1]);
				atableaux=new Ttableaux(na,nb,nx);
				alist->add(atableaux);
			}
		}

		for(atableaux=alist->first;atableaux!=NULL;
		atableaux=atableaux->next){
			nb1min=q2-atableaux->length[1]+atableaux->length[2];
			if(nb1min<0) nb1min=0;
			nb1max=q2;
			if(nb1max>atableaux->length[0]-atableaux->length[1])
				nb1max=atableaux->length[0]-atableaux->length[1];
			if(nb1max>atableaux->na[0]) nb1max=atableaux->na[0];
			for(nb[1]=nb1min;nb[1]<=nb1max;nb[1]++){
				nb[2]=q2-nb[1];
				if(nb[2]<=atableaux->na[0]+atableaux->na[1]-nb[1]){
					p=atableaux->na[0]+nx[0]-atableaux->na[1]-nb[1]-nx[1];
					q=atableaux->na[1]+nb[1]+nx[1]-atableaux->na[2]-nb[2];
					if(p>BIGGESTP)
						BIGGESTP=p;
					for(iw=0;iw<weightlist->length;iw++){
						weightlist->outweight[iw][p][q]+=weightlist->inweight[iw];
					}
				}
			}

		}
		alist->clear();
	}
}


void addmults_list(int p1,int q1,double n1,
int p2,int q2,double n2,Tpqlist *pqlist){
	int p,q,ip2,iq2,i,na0min,na1min,na1max,nb1min,nb1max;
	int na[3],nb[3],nx[3];
	Ttableauxlist *alist;
	Ttableauxlist *ablist;
	Ttableaux *atableaux;
	Ttableaux *abtableaux;
	alist=new Ttableauxlist;

	for(i=0;i<3;i++) nb[i]=0;
	nx[0]=p1+q1;
	nx[1]=q1;
	nx[2]=0;

	na0min=p2+q2-(p1+q1);
	if(na0min<0) na0min=0;
	for(na[0]=na0min;na[0]<=p2+q2;na[0]++){
		na1min=(p2+q2-na[0])-q1;
		if(na1min<0) na1min=0;
		na1max=p1;
		if(na1max>p2+q2-na[0]) na1max=p2+q2-na[0];
		for(na[1]=na1min;na[1]<=na1max;na[1]++){
			na[2]=(p2+q2-na[0]-na[1]);
			atableaux=new Ttableaux(na,nb,nx);
			alist->add(atableaux);
		}
	}

	ablist=new Ttableauxlist;
	for(atableaux=alist->first;atableaux!=NULL;
	atableaux=atableaux->next){
#ifdef PRINT_TABLEAUS    
		printf("___________________________________________\n");
#endif
		nb1min=q2-atableaux->length[1]+atableaux->length[2];
		if(nb1min<0) nb1min=0;
		nb1max=q2;
		if(nb1max>atableaux->length[0]-atableaux->length[1])
			nb1max=atableaux->length[0]-atableaux->length[1];
		if(nb1max>atableaux->na[0]) nb1max=atableaux->na[0];
		for(nb[1]=nb1min;nb[1]<=nb1max;nb[1]++){
			nb[2]=q2-nb[1];
			if(nb[2]<=atableaux->na[0]+atableaux->na[1]-nb[1]){
				abtableaux=new  Ttableaux(atableaux->na,nb,nx);
				ablist->add(abtableaux);
#ifdef PRINT_TABLEAUS    
				abtableaux->print();
#endif
				q=abtableaux->length[1]-abtableaux->length[2];
				p=abtableaux->length[0]-abtableaux->length[1];

				if(p>BIGGESTP) BIGGESTP=p;
				if(q>BIGGESTP) BIGGESTP=q;
				pqlist->add(p,q,n1*n2);
			}
		}

	}
	alist->clear();
	ablist->clear();
	delete alist;
	delete ablist;
}
