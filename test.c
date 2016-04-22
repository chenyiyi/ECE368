//
//  main.c
//  practice1
//
//  Created by Lee Chrison Moon on 14/12/28.
//  Copyright (c) 2014年 Lee Chrison Moon. All rights reserved.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Event0{
    int arrivetime;
    struct Event0 *next;
}Event0;

typedef struct Event1{
    int arrivetime;
    struct Event1 *next;
}Event1;

typedef struct Queue0{
    Event0 *front;
    Event0 *rear;
    int size;
}Queue0;

typedef struct Queue1{
    Event1 *front;
    Event1 *rear;
    int size;
}Queue1;

double randf(){
    return (double)(rand() % 1001) * 0.001f;
}

Queue0 * InitQueue0();
Queue1 * InitQueue1();
Event0 EnQueue0(Queue0 *pqueue, int arrivetime);
Event1 EnQueue1(Queue1 *pqueue, int arrivetime);
Event0 DeQueue0(Queue0 *pqueue,int * arrivetime);
Event1 DeQueue1(Queue1 *pqueue,int * arrivetime);
int IsEmpty0(Queue0 *pqueue);
int IsEmpty1(Queue1 *pqueue);

int main(int argc, char ** argv){
    int interarrtime0;//interarrival time in priority 0
    int interarrtime1;
    int queue =0; //length of queue
    int waitingtime0 =0; //total waiting time
    int waitingtime1 =0;
    int busytime =0; //total service time
    int status=0; //whether the server is busy
    int task0 = *argv[4];
    int task1 = *argv[4];
    float arrivalrate0 = *argv[1];
    float arrivalrate1 = *argv[2];
    int servicerate = *argv[3];
    Event0 * event0 = NULL; //list the event of priority 0
    Event1 * event1 = NULL; //list the event of priority 1
    int time_line =0; //time line
    int time_arr0;  //Variable for updating arrive time
    int time_dep0 = -1;  //Variable for updating depature time
    int time_arr1;
    int time_dep1 = -1;
    
    Queue0 * q0 = InitQueue0();
    Queue1 * q1 = InitQueue1();
    interarrtime0 = (int)((-1/arrivalrate0)*(log(1-randf())));
    interarrtime1 = (int)((-1/arrivalrate1)*(log(1-randf())));
    time_arr0 = time_line + interarrtime0;
    time_arr1 = time_line + interarrtime1;
   // time_dep0 = time_line + (int)((-1/servicerate)*(log(1-randf())));
    
  //  event0 = EnQueue0(q0, time_line);
  //  event1 = EnQueue1(q1, time_line);
    
    while (task0 != 0 && task1 != 0) {
        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                q0 -> size--;
                time_dep0 = time_line + (int)((-1/servicerate)*(log(1-randf())));
                waitingtime0 = waitingtime0 + time_line - q0 -> front -> arrivetime;
            }
        }
        
        if(time_line == time_dep1){
            if (q1 -> size >= 1) {
                q1 -> size--;
                time_dep1 = time_line + (int)((-1/servicerate)*(log(1-randf())));
                waitingtime1 = waitingtime1 + time_line - q1 -> front -> arrivetime;
            }
        }
        
        if(time_line == time_arr0){
            if (status == 1) {
                *event0 = EnQueue0(q0, time_line);
            }
            else{
                time_dep0 = time_line + (int)((-1/servicerate)*(log(1-randf())));
                busytime = busytime + time_dep0 - time_line;
            }
        }
        
        if(time_line == time_arr1){
            if (status == 1) {
                event1 = EnQueue1(q1, time_line);
            }
            else{
                time_dep1 = time_line + (int)((-1/servicerate)*(log(1-randf())));
                busytime = busytime + time_dep1 - time_line;
            }
        }
        
        
               
    }
    
    printf("%d\n", interarrtime0);
    return 0;
}


Queue0 *InitQueue0(){
    Queue0 *pqueue = (Queue0 *)malloc(sizeof(Queue0));
    if(pqueue!=NULL){
        pqueue->front = NULL;
        pqueue->rear = NULL;
        pqueue->size = 0;
    }
    return pqueue;
}

Queue1 *InitQueue1(){
    Queue1 *pqueue = (Queue1 *)malloc(sizeof(Queue1));
    if(pqueue!=NULL){
        pqueue->front = NULL;
        pqueue->rear = NULL;
        pqueue->size = 0;
    }
    return pqueue;
}

Event0 EnQueue0(Queue0 *pqueue, int arrivetime)
{
    Event0 *pnode = malloc(sizeof(Event0));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->next = NULL;
        
        if(IsEmpty(pqueue))
        {
            pqueue->front = pnode;
        }
        else
        {
            pqueue->rear->next = pnode;
        }
        pqueue->rear = pnode;
        pqueue->size++;
    }
    return *pnode;
}

Event1 EnQueue1(Queue1 *pqueue, int arrivetime)
{
    Event1 *pnode = malloc(sizeof(Event1));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->next = NULL;
        
        if(IsEmpty(pqueue))
        {
            pqueue->front = pnode;
        }
        else
        {
            pqueue->rear->next = pnode;
        }
        pqueue->rear = pnode;
        pqueue->size++;
    }
    return *pnode;
}

Event0 DeQueue0(Queue0 *pqueue,int * arrivetime){
    Event0 pnode = pqueue->front;
    if(IsEmpty0(pqueue)!=1&&pnode!=NULL)
    {
        pqueue->front = pnode->next;
        pqueue->size--;
        free(pnode);
        if(pqueue->size==0)
            pqueue->rear = NULL;
    }
    return pqueue->front;
}

Event1 DeQueue1(Queue1 *pqueue,int * arrivetime){
    Event1 pnode = pqueue->front;
    if(IsEmpty1(pqueue)!=1&&pnode!=NULL)
    {
        pqueue->front = pnode->next;
        pqueue->size--;
        free(pnode);
        if(pqueue->size==0)
            pqueue->rear = NULL;
    }
    return pqueue->front;
}

int IsEmpty0(Queue0 *pqueue)
{
    if(pqueue->front==NULL&&pqueue->rear==NULL&&pqueue->size==0)
        return 1;  
    else  
        return 0;  
}  
int IsEmpty1(Queue1 *pqueue)
{  
    if(pqueue->front==NULL&&pqueue->rear==NULL&&pqueue->size==0)  
        return 1;  
    else  
        return 0;  
}  


/*Event0 * create_event0(char eventtype, int time){
	Event0 * eventnode;
	eventnode = malloc(sizeof(event0));
	eventnode -> eventtype = eventtype;
	eventnode -> time = time;
	eventnode -> next = NULL;
	return eventnode;
 }
 
 Event1 * create_event1(char eventtype, int time){
	Event1 * eventnode;
	eventnode = malloc(sizeof(event1));
	eventnode -> eventtype = eventtype;
	eventnode -> time = time;
	eventnode -> next = NULL;
	return eventnode;
 }
 
 Event0 * event0_add(Event0 * eventfirst, Event0 * eventadd){
	while(eventfirst->next != NULL){
 eventfirst = eventfirst -> next;
	}
	eventfirst-> next = eventadd;
	return eventfirst;
 }
 
 Event1 * event1_add(Event1 * eventfirst, Event1 * queueadd){
	while(eventfirst->next != NULL){
 eventfirst = eventfirst -> next;
	}
	eventfirst-> next = eventadd;
	return eventfirst;
 }*/

