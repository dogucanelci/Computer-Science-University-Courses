#include "data_structs.h"
#include <iostream>
#include <stdlib.h>
#include<fstream>
#include<stdlib.h>
#include <string.h>
#include <strings.h>
using namespace std;

void Scheduler(Queue *main_queue){
    int clock=0;
    int pri_2_counter=0;
    int cum_lateness=0;
    MultiQueue *multiqueue=new MultiQueue;
    multiqueue->init(0); //multiqueue ye ait queues elemaninin i. olan queue sini hazirliyor.
    multiqueue->init(1);
    multiqueue->init(2);
    Process *trav=new Process;
    trav=main_queue->head;
    while(!main_queue->isEmpty() || (!multiqueue->queues[0].isEmpty() || !multiqueue->queues[1].isEmpty() || !multiqueue->queues[2].isEmpty())){
        while(trav){
            if(trav->arrival_time<=clock){
                multiqueue->queues[trav->priority-1].queue(trav);
                trav=trav->next;
                main_queue->dequeue();
                
            }
            else{
                trav=trav->next;
            }
        }
        trav=main_queue->head;
        if(multiqueue->queues[0].isEmpty()){
            if(( multiqueue->queues[1].isEmpty() && !multiqueue->queues[2].isEmpty() ) || (!multiqueue->queues[2].isEmpty() &&  pri_2_counter>=2)){  //q3 te islem yapiliyor
                //if(pri_2_counter>=2){
                pri_2_counter=0;
                //}
                clock=clock+multiqueue->queues[2].head->task_stack.head->duration;
                cout<<multiqueue->queues[2].head->name<<" "<<multiqueue->queues[2].head->task_stack.head->name<<endl;
                //cum_lateness=cum_lateness+clock - (multiqueue->queues[2].head->task_stack.head->duration+multiqueue->queues[2].head->arrival_time);
                delete multiqueue->queues[2].head->task_stack.pop();
                if(multiqueue->queues[2].head->task_stack.isEmpty()){
                    cum_lateness=cum_lateness+clock-multiqueue->queues[2].head->deadline;
                    multiqueue->queues[2].dequeue();
                }
            }
            else if(!multiqueue->queues[1].isEmpty()){   //q2 bos degil
                clock=clock+multiqueue->queues[1].head->task_stack.head->duration;
                cout<<multiqueue->queues[1].head->name<<" "<<multiqueue->queues[1].head->task_stack.head->name<<endl;
                //cum_lateness=cum_lateness+clock - (multiqueue->queues[1].head->task_stack.head->duration+multiqueue->queues[1].head->arrival_time);
                delete multiqueue->queues[1].head->task_stack.pop();
                if(multiqueue->queues[1].head->task_stack.isEmpty()){
                    cum_lateness=cum_lateness+clock-multiqueue->queues[1].head->deadline;
                    multiqueue->queues[1].dequeue();
                    
                }
                pri_2_counter++;
                if(pri_2_counter>=2 && multiqueue->queues[2].isEmpty()){
                    pri_2_counter=0;
                }
            }
            else{
                clock++;
            }
        }
    
    else{
        if(!multiqueue->queues[0].isEmpty()){   //q1 bos degil
                clock=clock+multiqueue->queues[0].head->task_stack.head->duration;
                cout<<multiqueue->queues[0].head->name<<" "<<multiqueue->queues[0].head->task_stack.head->name<<endl;
                //cum_lateness=cum_lateness+clock - (multiqueue->queues[0].head->task_stack.head->duration+multiqueue->queues[0].head->arrival_time);
                delete multiqueue->queues[0].head->task_stack.pop();
                if(multiqueue->queues[0].head->task_stack.isEmpty()){
                    cum_lateness=cum_lateness+clock-multiqueue->queues[0].head->deadline;
                    multiqueue->queues[0].dequeue();
                }
            }
        }
    }    
       

cout<<"Cumulative Lateness: "<<cum_lateness<<endl;
//cout lateless time 

}


int main(int argc, char* argv[])
{
string process_name;
int p_priority;
int p_arrival_time;
int p_task_count;
string p_subtask_name;
int p_task_duration;

Queue main_queue;
main_queue.init();
int counter1=0;
int counter2=0;
//const char* filename = "scheduler input.txt";
const char* filename = argv[1];
ifstream file(filename);
if(!file)
{
	cerr << "Cannot open file" << endl;
	return EXIT_FAILURE;
}
while(!file.eof()){
if(counter1==0){
	Process *process1=new Process;
	Stack *stack1=new Stack;
	Subtask *subt1=new Subtask;
	process1->deadline=0;
	file>>process_name>>p_priority;
	process1->name=process_name;
	process1->priority=p_priority;
	counter1++;
	if(counter1==1){
		file>>p_arrival_time>>p_task_count;
		process1->arrival_time=p_arrival_time;
		process1->task_count=p_task_count;
		counter1++;
		if(counter1==2){
			stack1->init();
			while(counter2!=p_task_count){
				file>>p_subtask_name>>p_task_duration;
				subt1->duration=p_task_duration;
				subt1->name=p_subtask_name;
				process1->deadline=process1->deadline+subt1->duration;
				stack1->push(subt1);
				counter2++;
			}
				process1->deadline=process1->deadline+process1->arrival_time;
				process1->task_stack=*stack1;
				main_queue.queue(process1);
				counter1=0;
				counter2=0;	
		}
	}
}
}

Scheduler(&main_queue);
//getchar();
return 0; 
}





