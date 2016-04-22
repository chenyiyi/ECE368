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

float randf(){
    return (float)rand()/(RAND_MAX + 1.0);
}

Queue0 * InitQueue0();
Queue1 * InitQueue1();
Event0 * EnQueue0(Queue0 *pqueue, int arrivetime);
Event1 * EnQueue1(Queue1 *pqueue, int arrivetime);
Event0 * DeQueue0(Queue0 *pqueue,int  arrivetime);
Event1 * DeQueue1(Queue1 *pqueue,int arrivetime);
int IsEmpty0(Queue0 *pqueue);
int IsEmpty1(Queue1 *pqueue);

int main(int argc, char* argv[]){
    int interarrtime0;//interarrival time in priority 0
    int interarrtime1;
    int queue =0; //length of queue
    int waitingtime0 =0; //total waiting time
    int waitingtime1 =0;
    int busytime =0; //total service time
    int status=0; //whether the server is busy
    int task0 = atoi((const char*) argv[4]);
    int task1 = atoi((const char*)argv[4]);
    float arrivalrate0 = atof((const char*)argv[1]);
    float arrivalrate1 = atof((const char*)argv[2]);
    int servicerate = atoi((const char*)argv[3]);
    Event0 * event0 = NULL; //list the event of priority 0
    Event1 * event1 = NULL; //list the event of priority 1
    int time_line =0; //time line
    int time_arr0;  //Variable for updating arrive time
    int time_dep0 = -1;  //Variable for updating depature time
    int time_arr1;
    int time_dep1 = -1;
    
    Queue0 * q0 = InitQueue0();
    Queue1 * q1 = InitQueue1();
    interarrtime0 = ceil(((-1/arrivalrate0)*(log(1-randf()))));
    interarrtime1 = ceil(((-1/arrivalrate1)*(log(1-randf()))));
    time_arr0 = time_line + interarrtime0;
    time_arr1 = time_line + interarrtime1;
    
    
    while (task0 != 0 && task1 != 0){

        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + link0->front->duration;
                waitingtime0 = waitingtime0 + time_line - link0->front->departure;
		busytime = busytime + lin0->front->departure;
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
               
            }
            else if(q1 ->size >= 1){
		time_dep1 = time_line + link1->front->duration;
                waitingtime1 = waitingtime1 + time_line - link1->front->departure;
		busytime = busytime + lin0->front->departure;
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
            }
            else{
                status =0;
                //*event0 = DeQueue0(q0, time_line);
                task0= task0-1;
                
            }
        }
        
        if(time_line == time_dep1){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + link0->front->duration;
                waitingtime0 = waitingtime0 + time_line - link0->front->departure;
		busytime = busytime + lin0->front->departure;
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
            }
            else if(q1 ->size >= 1){
	      time_dep1 = time_line + link1->front->duration;
	      waitingtime1 = waitingtime1 + time_line - link1->front->departure;
	      busytime = busytime + lin0->front->departure;
	      event1 = DeQueue1(q1, time_line);
	      task1 = task1-1;
            }
            else{
                status =0;
                //  *event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
               
            }
        }
        
        if(time_line == time_arr0){
            if (status == 1) {
                event0 = EnQueue0(q0, time_line);
		queue = queue +1;
                time_arr0 = time_line + link0->front->arrive;
               
            }
            else{
                time_dep0 = time_line + link0->front->duration;
                time_arr0 = time_line + link0->front->arrive;
                busytime = busytime + duration;
                status = 1;
               
            }
        }
        
        if(time_line == time_arr1){
            if (status == 1) {
                event1 = EnQueue1(q1, time_line);
		queue = queue+1;
		time_arr0 = time_line + link1->front->arrive;
            }
            else{
	      time_dep1 = time_line + link1->front->duration;
	      time_arr1 = time_line + link1->front->arrive;
	      busytime = busytime + duration;
	      status = 1;
            }
        }
        time_line++;
        printf("rand: %f\n",randf());
        
    }











    while (q0->size !=0 || q1->size != 0 ){
        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
                printf("d0 0,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
                printf("d0 1,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
            else{
                status =0;
                //*event0 = DeQueue0(q0, time_line);
                task0= task0-1;
                printf("d0 ,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
        }
        
        if(time_line == time_dep1){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
                printf("d1 0,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
                printf("d1 1,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
            else{
                status =0;
                //  *event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
                printf("d1 ,time:%d, status:%d, a0:%d, a1:%d,d0:%d,d1:%d,size0:%d, size1:%d\n", time_line,status,time_arr0,time_arr1,time_dep0,time_dep1,q0->size,q1->size);
            }
        }
        time_line++;
    }
    printf("waiting time1 :%d, waiting time2: %d, service time :%d, queue: %d\n", waitingtime0/1000,waitingtime1/1000, busytime, queue/1000);
 
    
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

Event0* EnQueue0(Queue0 *pqueue, int arrivetime)
{
    Event0 *pnode = malloc(sizeof(Event0*));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->next = NULL;
        
        if(IsEmpty0(pqueue))
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
    return pnode;
}

Event1* EnQueue1(Queue1 *pqueue, int arrivetime)
{
    Event1 *pnode = malloc(sizeof(Event1*));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->next = NULL;
        
        if(IsEmpty1(pqueue))
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
    return pnode;
}

Event0* DeQueue0(Queue0 *pqueue,int arrivetime){
    Event0 *pnode = pqueue->front;
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

Event1* DeQueue1(Queue1 *pqueue,int arrivetime){
    Event1 *pnode = pqueue->front;
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
