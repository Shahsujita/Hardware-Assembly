#include"cachelab.h"
#include<stdlib.h>
#include<getopt.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#define MAX 100
int misses,evictions,hits;
int s,E,b;
enum TYPE{HIT,MISS,MISS_HIT,MISS_EVICTION,MISS_EVICTION_HIT};
enum TYPE type;
typedef struct			//use a 2-dimension array to simulate cache
{
        int is_valid;
        int tag;
        int access_time;
}Cache;
Cache **cache;
int GetS(long long add)                       //get the s value of an address
{
	long long temp=0x7fffffffffffffff>>(63-s);
	return (add>>b)&temp;
}
int GetT(long long add)                       //get the t value of an address
{
	long long temp=0x7fffffffffffffff>>(63-s-b);
	return (add>>(s+b))&temp;
}
void update_time(int sel,int tarline)
{
	int i;
        for(i=0;i<E;++i)
        {
                if(cache[sel][i].is_valid==1 && 
                cache[sel][i].access_time>cache[sel][tarline].access_time)     
						 //caches that visited before
                        --cache[sel][i].access_time;
        }
        cache[sel][tarline].access_time=E-1;            //make it the newest
}

enum TYPE calcu(char instr[])			//get result of the instruction
{
        char ins;
        long long address;
	int siz;
        sscanf(instr," %c %llx %d", &ins, &address,&siz);
        int sel=GetS(address);
        int tag=GetT(address);
	int i;
	for(i=0;i<E;++i)
        {
                if(cache[sel][i].is_valid==1 && cache[sel][i].tag==tag)	//found!
                {
                        if(ins=='M')	//hit*2 for modify
                                ++hits;
                        ++hits;
                        update_time(sel,i);
                        return HIT;
                }
        }       
        ++misses;		//not hit,then miss
        for(i=0;i<E;++i)
        {
                if(cache[sel][i].is_valid==0)	//if can find an empty line
                {
                        cache[sel][i].is_valid=1;
                        cache[sel][i].tag=tag;
                        update_time(sel,i);
                        if(ins=='M')	//miss first and hit later for modify
			{       
				++hits;                 
        			return MISS_HIT;
			}
                        else
                                return MISS;
                }
        }
        ++evictions;		//means no room,must do eviction
        for(i=0;i<E;++i)
        {
                if(cache[sel][i].access_time==0)	//find the most early one
                {
                        cache[sel][i].tag=tag;
                        update_time(sel,i);
                        if(ins=='M')	//first miss and eviction and hit later for modify
                        {
                                ++hits;
                                return MISS_EVICTION_HIT;
                        }
                        else 
                                return MISS_EVICTION;
                }
        }
	return 0;
}
int main(int argc, char *argv[])
{
        FILE *f;
        char instr[MAX],trace[MAX];
        int opt,verbose=0;
        opterr=0;
        while((opt=getopt(argc, argv, "vs:E:b:t:"))!=-1)//get basic infomation 
        {
                switch(opt) 
                {
                        case 'v':
                                verbose=1;	//help to debug
				break;
                        case 's':
                                s=atoi(optarg); 
                                break;
                        case 'E':
                                E=atoi(optarg);
                                break;
                        case 'b':
                                b=atoi(optarg);
                                break;
                        case 't':
                                strcpy(trace, optarg);
                                break;
                }
        }
        
        int totsets=(1<<s)*2;	
        cache=(Cache**)malloc(totsets*sizeof(Cache*));	//apply space for cache
        int i;
	for(i=0;i<totsets;++i) 
        {
                cache[i]=(Cache*)malloc(E*sizeof(Cache));
                for(int j=0;j<E;++j) 
                {
                        cache[i][j].is_valid=0;
                        cache[i][j].access_time=cache[i][j].tag=-1;
                }
        }
        f=fopen(trace,"r");
        while(fgets(instr,MAX,f))	//get every instruction
        {
              	if(instr[0]==' ') 	//not instruction load
		{
                	type=calcu(instr);
               		if(verbose)
	       		{
		    	 	switch (type) 
                		{
                	        case HIT:
                                printf("%s hit\n", instr+1);
                                break;
                     	 	case MISS:
                                printf("%s miss\n", instr+1);
                                break;
                        	case MISS_HIT:
                                printf("%s miss hit\n", instr+1);
                                break;
                        	case MISS_EVICTION:
                                printf("%s miss eviction\n", instr+1);
                                break;
                        	case MISS_EVICTION_HIT:
                                printf("%s miss eviction hit\n", instr+1);
                                break;
				}
                	}
        
        	}
	}
        fclose(f);
        printSummary(hits,misses,evictions);	//print results
	free(cache);
        return 0;
}


