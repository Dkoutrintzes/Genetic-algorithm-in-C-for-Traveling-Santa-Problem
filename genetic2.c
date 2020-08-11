#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define popsize 200
struct chromosome {
	int route[20];
	double fit;
};
    struct chromosome newroad[popsize];
	struct chromosome oldroad[popsize];
	struct chromosome allroad[400];
	struct chromosome temp,final;
	int parents[popsize];
	void sort();

           double distance[20][20];

void fillRandom();
//void crossover2(int st,int q,int r,int l);
void printPop(){
	int j,i;
	printf("I AM THE oldroad\n");
	for(i=0;i<popsize;i++){
    	printf("chrom: %d [",i);
        for(j=0;j<20;j++){
            printf("%d ",oldroad[i].route[j]);
         }
         printf("] %lf\n",oldroad[i].fit);
         //getchar();
    }
    printf("\n\nI AM THE newroad\n");
    for(i=0;i<popsize;i++){
    	printf("chrom: %d [",i);
        for(j=0;j<20;j++){
            printf("%d ",newroad[i].route[j]);
         }
         printf("] %lf\n",newroad[i].fit);
         //getchar();
    }
printf("\n\n+I AM THE allroad\n");
    for(i=0;i<popsize*2;i++){
    	printf("chrom: %d [",i);
        for(j=0;j<20;j++){
            printf("%d ",allroad[i].route[j]);
         }
         printf("] %lf\n",allroad[i].fit);
         
    }
    getchar();
	 
}
void mutation();
void selectParents();
double fitness(struct chromosome * c);
void crossover();
int main() {
	double locations[20][2]= {{20,20},{20,40},{20,160},{40,120},{60,20},{60,80},{60,200},{80,180},{100,40},{100,120},{100,160},{120,80},{140,140},{140,180},{160,20},{180,100},{180,60},{180,200},{200,40},{200,60}};
	srand (time(NULL));
	//srand (50);
	int i,j,x,u,n,s,k,q,r,flag,p1,p2,min;
	int count=0;
	
	int end=0;
	int endcounter=0;
	final.fit=1000000;
	double t1,t2;
	for(i=0; i<20; i++) {
		for(j=0; j<20; j++) {
                 t1= (locations[i][0]-locations[j][0])*(locations[i][0]-locations[j][0]);
                 t2=(locations[i][1]-locations[j][1])*(locations[i][1]-locations[j][1]);
				 distance[i][j]=sqrt(t1+t2);
            
		}
	}
	fillRandom();
	//printPop();
	//getchar();
	                      

do{
	
	for(i=0;i<popsize;i++){
		oldroad[i].fit=fitness(&oldroad[i]);
	//	printf("%d\n",oldroad[i].fit);
	}

	selectParents();

	crossover();

	
	//mutation
	mutation();
				

	for(i=0;i<popsize;i++){
		oldroad[i].fit=fitness(&oldroad[i]);
		newroad[i].fit=fitness(&newroad[i]);
	//	printf("%d\n",oldroad[i].fit);
	}				

//sort
      	
	sort();
	
		for(i=0;i<popsize;i++){
			oldroad[i]=allroad[i];
		}
		printf("%d) ",count);
		for(i=0;i<20;i++){
			printf("%d ",allroad[0].route[i]);	
		}
	//	printPop();
		printf("-- %lf\n",allroad[0].fit);	
	if(allroad[0].fit!=final.fit){
		final=allroad[0];
		endcounter=0;
	//	printf("hello1\n");
	}else{
		endcounter++;
		if(endcounter==300){
			end=1;
		//	printf("hello2\n");
		}
	}

//printf("%lf--%d\n",final.fit,count);	
	count++;
	
}while(count!=40000 && end!=1);
 system("pause");
 return 0;
}


void crossover(){
	int t;
		int p1,p2,i,j,x,u,flag,q,r;
		for(i=0;i<popsize;i+=2){
			p1=parents[i];
			p2=parents[i+1];
			//printf("crossover: %d-%d  ",p1,p2 );
			//getchar();
			q=rand()%20;
			r=rand()%20;
			if(r<q){
				int temp;
				temp=r;
				r=q;
				q=temp;
			}
			//printf("points: %d-%d \n ",q,r );

			//printf("  %d-%d  ",q,r);
			for(j=q;j<=r;j++){
				newroad[i].route[j]=oldroad[p1].route[j];
				newroad[i+1].route[j]=oldroad[p2].route[j];
			}
			//printf("Child 1\n");
			for (t=0;t<20;t++){
				//printf("%d ",newroad[i].route[t]);
			}
			//printf("\nChild 2\n");
			for (t=0;t<20;t++){
				//printf("%d ",newroad[i+1].route[t]);
			}//printf("\n");
			//getchar();
			//crossover2(0,q,r,i);
			x=0;
				//0->q new[i]
			for(u=0;u<q;u++){
				do{
					flag=0;
					for(j=q;j<r;j++){
						if(newroad[i].route[j]!=oldroad[p2].route[x]){
							flag++;
						}
					}
					x++;	
				}while(flag!=r-q && x<20);
						if(flag==r-q){
							newroad[i].route[u]=oldroad[p2].route[x-1];
						}
			}
			//r->19 new[i]
			for(u=r;u<20;u++){	
				do{
					flag=0;
					for(j=q;j<r;j++){
						if(newroad[i].route[j]!=oldroad[p2].route[x]){
							flag++;
						}
					}
					x++;	
				}while(flag!=r-q && x<20);
					if(flag==r-q){
						newroad[i].route[u]=oldroad[p2].route[x-1];
					}
			}
			//0->q new[i+1]
			x=0;	
			for(u=0;u<q;u++){
				
				do{
					flag=0;
						for(j=q;j<r;j++){
							if(newroad[i+1].route[j]!=oldroad[p1].route[x]){
								flag++;
							}
						}
					x++;	
				}while(flag!=r-q && x<20);
				if(flag==r-q){
					newroad[i+1].route[u]=oldroad[p1].route[x-1];
				}		
			}	
			//r->19 new[i+1]	
			for(u=r;u<20;u++){
				do{
					flag=0;
						for(j=q;j<r;j++){
							if(newroad[i+1].route[j]!=oldroad[p1].route[x]){
								flag++;
							}
						}
					x++;	
				}while(flag!=r-q && x<20);
				if(flag==r-q){
					newroad[i+1].route[u]=oldroad[p1].route[x-1];
				}
			}
			/*printf("FINAL Child 1\n");
			for (t=0;t<20;t++){
				printf("%d ",newroad[i].route[t]);
			}
			printf("\nFINAL Child 2\n");
			for (t=0;t<20;t++){
				printf("%d ",newroad[i+1].route[t]);
			}printf("\n");getchar();*/
	}//end for 2 parents
}
void mutation(){
	int i,j,q,s,r,x;
	for(i=0;i<popsize;i++){
		q=rand()%popsize;
		do{
		s=rand()%20;
		r=rand()%20;
	}while(s=r);
		if(q==30){
		 x=newroad[i].route[s];
		 newroad[i].route[s]=newroad[i].route[r];
		 newroad[i].route[r]=x;	
		}else if(q==15){
			x=newroad[i].route[s];
			oldroad[i].route[s]=oldroad[i].route[r];
			oldroad[i].route[r]=x;	
		}
	}
}

void selectParents(){
	double 	s=0.0;
	int i,j;
	double k,n;
	for(i=0;i<popsize;i++){
		s+=oldroad[i].fit;
	}
	//printf("s=%lf\n",s);
	//getchar();
	for(i=0;i<popsize;i++){
		n=rand()%(int)s;
		k=0;
		for(j=0;j<popsize;j++){
			k+=oldroad[j].fit;
			if(k>=n){
				break;
			}
		}
		parents[i]=j;
		//printf("p%d=%d\n",i,parents[i]);
	}
	//getchar();
	
}
void fillRandom(){
     int i,j,u,x;
     for(i=0; i<popsize; i++) {
		for(j=0; j<20; j++) {
	loop1:			x=rand()%20;
			for(u=0; u<j; u++) {
				if(x==oldroad[i].route[u]) {
					goto loop1;
				}
			}
			oldroad[i].route[j]=x;
				
			}
			for(u=0; u<20; u++) {
				
			}
			oldroad[i].fit=fitness(&oldroad[i]);
		}
}
	// 
double fitness(struct chromosome * c){
		int i,j;
		double f=0.0;
		for(i=0;i<19;i++){
			
				f+=distance[c->route[i]][c->route[i+1]];
				//printf("%lf ... %d %d\n",distance[c->route[i]][c->route[i+1]],c->route[i],c->route[i+1]);
				//printf("[%d %d]",c->route[i],c->route[i+1]);
				//getchar();

		}
		f+=distance[c->route[19]][c->route[0]];
		//printf("%lf ",f);
		//getchar();

		return f;
}
void sort(){
     int i,j,x,q,min;
     struct chromosome temp;
     //sort old
 
		for(i=0;i<popsize;i++){
			min=10000;
			for(j=i;j<popsize;j++){
				if(oldroad[j].fit<min){
					min=oldroad[j].fit;
					x=j;
				}
			}
			temp=oldroad[i];
			oldroad[i]=oldroad[x];
			oldroad[x]=temp;
		}
		//sort new
		for(i=0;i<popsize;i++){
			min=10000;
			for(j=i;j<popsize;j++){
				if(newroad[j].fit<min){
					min=newroad[j].fit;
					x=j;
				}
			}
			temp=newroad[i];
			newroad[i]=newroad[x];
			newroad[x]=temp;
		}
		
		j=0;
		x=0;
		for(i=0;i<2*popsize;i++){
			if(oldroad[j].fit<newroad[x].fit){
				allroad[i]=oldroad[j];
				j++;
				if(j==popsize){
					for(i=i+1;i<2*popsize;i++){
						allroad[i]=newroad[x];
				  		x++;	
					}
					break;
				}
			}else{
				allroad[i]=newroad[x];
				x++;
				if(x==popsize){
					for(i=i+1;i<2*popsize;i++){
						allroad[i]=oldroad[j];
				  		j++;	
					}
					break;
				}
			}
		}
     }
