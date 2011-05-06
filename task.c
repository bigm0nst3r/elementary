#include<string.h>
#include<stdlib.h>
#include "task.h"
#define MAX_NO_OF_TASKS 2



int task_queue[MAX_NO_OF_TASKS];

void scheduler_init(char t_name[20],int t_id)
{
	task_queue[t_id] = t_id;
	
}


int context_switch(int old_task_no)
{
	int new_task_no;
	
	if(old_task_no == 0){
		return 1;
	}
		
	else if(old_task_no == 1){
	
		return 0;
	}
	/*
	new_task_no = (old_task_no+1)%MAX_NO_OF_TASKS;
	
	
	Context Switch Code */
	
	
	
	//return new_task_no;
}



