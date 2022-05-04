#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "scheduling.h"

/*
##  Round-Robin Scheduling Algorithm  ##

	Parameters:-

	queue: 1D int array containing the CPU burst time for every process in a ready queue
	np: number of processes (length of `queue` array)
	tq: time quantum for the RR algorithm


	Returns:-

	rr_result struct pointer, where
	rr_result -> order: 1D int array, containing the execution order of processes (i.e. `(rr_result -> order)[0]` is the process number of the first process)
		** hint: p1 is always the first item in order of selection in round-robin and FCFS
    rr_result -> order_n: int, representing the size of the `order` array, described above ^
	rr_result -> turnarounds: 1D int array, containing the turnaround time for each process (i.e. `(rr_result -> turnarounds)[0]` is the turnaround time for p1)
*/
rr_result *rr(int *queue, int np, int tq)
{
	rr_result *result = malloc(sizeof(rr_result));
	result->np = np;
	result->turnarounds = malloc(sizeof(int) * np);

	// code here to assign values to result->turnarounds, result->order, and result->order_n
	
	result->order=malloc(np*sizeof(int));
	result->order_n=np;

	for (int i = 0; i < np; i++)
	{
		(result->order)[i] = 0;
		(result->turnarounds)[i] = 0;
	}
	
	bool not_done = true;	
	int i_order=0;
	
	int time = 0;
	
	while(true)
	{
		
		bool not_done = true;	
		for(int i = 0; i<np; i++)
		{
			if(queue[i]>0)
			{
				not_done=false;
				//printf("p%d queue: %d\n", i+1, queue[i]);
				if (queue[i]<=tq)
				{
					time+=queue[i];
				
					if((result->turnarounds)[i]==0)
					{
						if(i==0)
						{
							(result->turnarounds)[i] = time-((result->turnarounds)[i]);
						}
						else
						{
							(result->turnarounds)[i]+=queue[i];
						}
							
					}
					else
					{
						(result->turnarounds)[i] = time-((result->turnarounds)[i]);
					}
					queue[i] = 0;
				}
				else
				{
					if((result->turnarounds)[i]==0&&i!=0)
					{
						(result->turnarounds)[i] += time;
					}
					time+=tq;
					queue[i] -=tq;
				}
				if(i_order<np)
				{
					(result->order)[i_order] = i;
				}
				else
				{
					result->order_n+=1;
					int *new_order = malloc(sizeof(int)*(result->order_n));
					for(int i = 0; i<result->order_n; i++)
					{
						new_order[i] = 0;
					}
					memmove(new_order,result->order, sizeof(int)*(result->order_n-1));
					free(result->order);
					new_order[i_order] = i;
					result->order = new_order;	
				}
				i_order++;
			
			}
		}	
		if(not_done==true)
		{
			break;
		}
	}	
	return result;
}

