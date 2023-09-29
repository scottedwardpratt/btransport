class Ttableaux{
public:
  Ttableaux *next;
  int amax;
  int nabx[3];
  char abx[3][PQMAX+1];
  Ttableaux(int pset,int qset);
  void setx();
  void copy(Ttableaux *tableaux_ptr);
  void print();
};

void Ttableaux::copy(Ttableaux *tableaux_ptr){
  int i,j;
  //next=tableaux_ptr->next;
  next=NULL;
  amax=tableaux_ptr->amax;
  for(i=0;i<3;i++){
    nabx[i]=tableaux_ptr->nabx[i];
    for(j=0;j<=PQMAX;j++) abx[i][j]=tableaux_ptr->abx[i][j];
  }
}

Ttableaux::Ttableaux(int pset,int qset){
  int i;
  next=NULL;
  amax=0;
  nabx[0]=qset+pset;
  for(i=0;i<nabx[0];i++) abx[0][i]='x';
  nabx[1]=qset;
  for(i=0;i<nabx[1];i++) abx[1][i]='x';
  nabx[2]=0;
}

void Ttableaux::print(){
  int i,j,p,q;
  p=nabx[0]-nabx[1];
  q=nabx[1]-nabx[2];
  printf("___ P=%d ___ Q=%d ___\n",p,q);
  for(i=0;i<3;i++){
    for(j=0;j<nabx[0];j++){
      printf("%c ",abx[i][j]);
    }
    printf("\n");
  }
}

class Ttableauxlist{
public:
  Ttableaux *first;
  Ttableaux *last;
  Ttableauxlist();
  void add(Ttableaux *tableaux);
};

Ttableauxlist::Ttableauxlist(){
  first=NULL;
  last=NULL;
}

void Ttableauxlist::add(Ttableaux *tableaux){
  if(last==NULL){
    first=tableaux;
    last=tableaux;
  }
  else{
    last->next=tableaux;
    last=tableaux;
  }
}

void addmult(int p1,int q1,int p2,int q2,int **nmult){
  int p,q,ip2,iq2;
  Ttableauxlist *tableauxlist;
  Ttableauxlist *newlist;
  Ttableaux *tableaux;
  Ttableaux *temptableaux;
  Ttableaux *newtableaux;

  tableauxlist=new Ttableauxlist;
  newlist=new Ttableauxlist;

  tableaux=new Ttableaux(p1,q1);
  tableauxlist->add(tableaux);

  for(iq2=0;iq2<q2;iq2++){

    newlist=new Ttableauxlist;

    for(tableaux=tableauxlist->first;tableaux!=NULL;
	tableaux=tableaux->next){
      printf("__________________________________\n");
      // tableaux->print();
      
      if(tableaux->amax<=0){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[0][tableaux->nabx[0]]='a';
	newtableaux->nabx[0]+=1;
	newtableaux->abx[1][tableaux->nabx[1]]='b';
	newtableaux->nabx[1]+=1;
	newlist->add(newtableaux);
	printf("Added type A\n");
	newtableaux->print();
      }

      if(tableaux->amax<=0
	 && tableaux->abx[1][tableaux->nabx[2]]!='b'
	 && tableaux->nabx[2] < tableaux->nabx[1]){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[0][tableaux->nabx[0]]='a';
	newtableaux->nabx[0]+=1;
	newtableaux->abx[2][tableaux->nabx[2]]='b';
	newtableaux->nabx[2]+=1;
	newlist->add(newtableaux);
	printf("Added type B\n");
	newtableaux->print();
      }

      if(tableaux->amax<=1
	 && tableaux->nabx[1]<tableaux->nabx[0]
	 && tableaux->abx[0][tableaux->nabx[0]]!='a'
	 && tableaux->abx[1][tableaux->nabx[2]]!='b'){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[1][tableaux->nabx[1]]='a';
	newtableaux->nabx[1]+=1;
	newtableaux->amax=1;
	newtableaux->abx[2][tableaux->nabx[2]]='b';
	newtableaux->nabx[2]+=1;
	newlist->add(newtableaux);
	printf("Added type C\n");
	newtableaux->print();
      }

    }
    delete tableauxlist;
    tableauxlist=newlist;
  }

  for(ip2=0;ip2<p2;ip2++){
    
    newlist=new Ttableauxlist;

    for(tableaux=tableauxlist->first;tableaux!=NULL;
	tableaux=tableaux->next){
      printf("__________________________________\n");
      //tableaux->print();
  
      if(tableaux->amax==0){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[0][tableaux->nabx[0]]='a';
	newtableaux->nabx[0]+=1;
	newlist->add(newtableaux);
	printf("Added type D\n");
	newtableaux->print();
      }

      if(tableaux->amax<=1
	 && tableaux->abx[0][tableaux->nabx[1]]!='a'
	 && tableaux->nabx[0] > tableaux->nabx[1]){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[1][tableaux->nabx[1]]='a';
	newtableaux->nabx[1]+=1;
	newtableaux->amax=1;
	newlist->add(newtableaux);
	printf("Added type E\n");
	newtableaux->print();
      }

      if(tableaux->nabx[1] > tableaux->nabx[2]
	 && tableaux->abx[1][tableaux->nabx[2]]!='a'
	 && tableaux->abx[0][tableaux->nabx[2]]!='a'){
	newtableaux=new Ttableaux(0,0);
	newtableaux->copy(tableaux);
	newtableaux->abx[2][tableaux->nabx[2]]='a';
	newtableaux->nabx[2]+=1;
	newtableaux->amax=2;
	newlist->add(newtableaux);
	printf("Added type F\n");
	newtableaux->print();
      }

    }
    delete tableauxlist;
    tableauxlist=newlist;
  }


  for(p=0;p<=PQMAX;p++)for(q=0;q<=PQMAX;q++) nmult[p][q]=0;
  for(tableaux=tableauxlist->first;tableaux!=NULL;tableaux=tableaux->next){
    q=tableaux->nabx[1]-tableaux->nabx[2];
    p=tableaux->nabx[0]-tableaux->nabx[1];
    printf("TEST: p=%d, q=%d\n",p,q);
    if(p==0 && q==1) tableaux->print();
    nmult[p][q]+=1;
  }
}
