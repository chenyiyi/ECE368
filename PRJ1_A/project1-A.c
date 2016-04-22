//Chen Yiyi  ID 0026406971
//Li Zhuofan ID 0026552066
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Event0{
    int arrivetime;
    int duration;
    struct Event0 *next;
}Event0;

typedef struct Event1{
    int arrivetime;
    int duration;
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
Event0 * EnQueue0(Queue0 *pqueue, int arrivetime, int duration);
Event1 * EnQueue1(Queue1 *pqueue, int arrivetime, int duration);
Event0 * DeQueue0(Queue0 *pqueue,int  arrivetime);
Event1 * DeQueue1(Queue1 *pqueue,int arrivetime);
char * * explode(const char * str, const char * delims);
int IsEmpty0(Queue0 *pqueue);
int IsEmpty1(Queue1 *pqueue);

int main(int argc, char* argv[]){
    int queue =0; //length of queue
    int waitingtime0 =0; //total waiting time
    int waitingtime1 =0;
    int busytime =0; //total service time
    int status=0; //whether the server is busy

    Event0 * event0 = NULL; //list the event of priority 0
    Event1 * event1 = NULL; //list the event of priority 1
    int time_line =0; //time line
    //int time_arr0;  //Variable for updating arrive time
    int time_dep0 = -1;  //Variable for updating depature time
    //   int time_arr1;
    int time_dep1 = -1;
    
    Queue0 * q0 = InitQueue0();
    Queue1 * q1 = InitQueue1();
    
    if(argc == 2){
    int event = 0;
        int total0 = 0;
        int total1 = 0;
    char* filename = argv[1];
    FILE * fp;
    char* str;
    char** strarr = NULL;
    str = malloc(sizeof(char));
    if((fp = fopen(filename,"r")) == NULL){
        return 0;
    }
    while(fgets(str,200,fp) != NULL){
        strarr = explode(str," ");
        if(atoi(strarr[1]) == 0){
            total0++;
        }
        else{
            total1++;
        }
        event++;
    }
        int total = event;
    fseek(fp,0,SEEK_SET);
    fgets(str,200,fp);
    strarr= explode(str," ");
    while(event != 0){
        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                time_dep0 = (q0->front->duration) + time_line;
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                busytime = busytime + (time_dep0 - time_line);
                event0 = DeQueue0(q0, time_line);
                event--;
            }
            else if(q1 ->size >= 1){
                time_dep1 = (q1->front->duration) +time_line;
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                busytime = busytime + (time_dep0 - time_line);
                event1 = DeQueue1(q1, time_line);
                event--;
            }
            else{
                status =0;
                event--;
            }
        }
        
        if(time_line == time_dep1){
            if (q0 -> size >= 1) {
                time_dep0 = (q0->front->duration) + time_line;
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                busytime = busytime + (time_dep1 - time_line);
                event0 = DeQueue0(q0, time_line);
                event--;
            }
            else if(q1 ->size >= 1){
                time_dep1 = (q1->front->duration) + time_line;
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                busytime = busytime + (time_dep1 - time_line);
                event1 = DeQueue1(q1, time_line);
                event--;
            }
            else{
                status =0;
                event--;
            }
        }
        
        if(time_line == atoi(strarr[0]) && atoi(strarr[1]) == 0){
            if (status == 1) {
                queue = queue + 1;
                event0 = EnQueue0(q0, time_line, atoi(strarr[2]));
                fgets(str,200,fp);
                strarr= explode(str," ");
            }
            else{
                
                time_dep0 = time_line + atoi(strarr[2]);
                fgets(str,200,fp);
                strarr= explode(str," ");
                busytime = busytime + (time_dep0 - time_line);
                status = 1;
            }
        }
        
        if(time_line == atoi(strarr[0]) && atoi(strarr[1]) == 1){
            if (status == 1) {
                queue = queue + 1;
                event1 = EnQueue1(q1, time_line,atoi(strarr[2]));
                fgets(str,200,fp);
                strarr= explode(str," ");
            }
            else{
                time_dep1 = time_line + atoi(strarr[2]);
                fgets(str,200,fp);
                strarr= explode(str," ");
                busytime = busytime + (time_dep1 - time_line);
                status = 1;
            }
        }
        time_line++;
    }
        FILE * fpout = NULL;
        fpout = fopen("proj1a_output","w");
        double avgwait0 = (double)waitingtime0 / total0;
        double avgwait1 = (double)waitingtime1 / total1;
        double avgqueue = (double)queue / total;
        double avguti = busytime;
        fprintf(fpout,"%f\n%f\n%f\n%f\n",avgwait0,avgwait1,avgqueue,avguti);
        fclose(fpout);
    }

else{
int task0 = atoi((const char*) argv[4]);
int task1 = atoi((const char*)argv[4]);
int total0 = task0;
int total1 = task1;
float arrivalrate0 = atof((const char*)argv[1]);
float arrivalrate1 = atof((const char*)argv[2]);
int servicerate = atoi((const char*)argv[3]);
int interarrtime0 = ceil(((-1/arrivalrate0)*(log(1-randf()))));
int interarrtime1 = ceil(((-1/arrivalrate1)*(log(1-randf()))));
int time_arr0 = time_line + interarrtime0;
int time_arr1 = time_line + interarrtime1;
 
    while (task0 != 0 && task1 != 0){
        
        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                busytime = busytime + (time_dep0 - time_line);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                busytime = busytime + (time_dep0- time_line);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
            }
            else{
                status =0;
                task0= task0-1;
            }
        }
        
        if(time_line == time_dep1){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                busytime = busytime + (time_dep1 - time_line);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                busytime = busytime + (time_dep1 - time_line);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
            }
            else{
                status =0;
                task1 = task1-1;
            }
        }
        
        if(time_line == time_arr0){
            if (status == 1) {
                event0 = EnQueue0(q0, time_line,0);
                queue = queue +1;
                time_arr0 = time_line + ceil(((-1/arrivalrate0)*(log(1-randf()))));
            }
            else{
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                time_arr0 = time_line + ceil(((-1/arrivalrate0)*(log(1-randf()))));
                busytime = busytime + time_dep0 - time_line;
                status = 1;
            }
        }
        
        if(time_line == time_arr1){
            if (status == 1) {
                event1 = EnQueue1(q1, time_line,0);
                queue = queue+1;
                time_arr1 = time_line + ceil(((-1/arrivalrate1)*(log(1-randf()))));
            }
            else{
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                time_arr1 = time_line + ceil(((-1/arrivalrate1)*(log(1-randf()))));
                busytime = busytime + time_dep1 - time_line;
                status = 1;
            }
        }
        time_line++;
        
    }
    while (q0->size !=0 || q1->size != 0 ){
        if(time_line == time_dep0){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
            }
            else{
                status =0;
                task0= task0-1;
            }
        }
        
        if(time_line == time_dep1){
            if (q0 -> size >= 1) {
                time_dep0 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime0 = waitingtime0 + time_line - (q0 -> front -> arrivetime);
                event0 = DeQueue0(q0, time_line);
                task0 = task0-1;
            }
            else if(q1 ->size >= 1){
                time_dep1 = time_line + ceil(((-1/servicerate)*(log(1-randf()))));
                waitingtime1 = waitingtime1 + time_line - (q1 -> front -> arrivetime);
                event1 = DeQueue1(q1, time_line);
                task1 = task1-1;
            }
            else{
                status =0;
                task1 = task1-1;
            }
        }
        time_line++;
    }
    FILE * fpout = NULL;
    fpout = fopen("proj1a_output","w");
    double avgwait0 = (double)waitingtime0 / total0;
    double avgwait1 = (double)waitingtime1 / total1;
    double avgqueue = (double)queue / (total0+total1);
    double avguti = busytime ;
    fprintf(fpout,"%f\n%f\n%f\n%f\n",avgwait0,avgwait1,avgqueue,avguti);
    fclose(fpout);
 }
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

Event0* EnQueue0(Queue0 *pqueue, int arrivetime, int duration)
{
    Event0 *pnode = malloc(sizeof(Event0*));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->duration = duration;
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

Event1* EnQueue1(Queue1 *pqueue, int arrivetime, int duration)
{
    Event1 *pnode = malloc(sizeof(Event1*));
    if(pnode != NULL)
    {
        pnode->arrivetime = arrivetime;
        pnode->duration = duration;
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

char * * explode(const char * str, const char * delims)
{
    int n = 0;
    int i = 0;
    int j = 0;
    while(str[i] != '\0')
    {
        if(strchr(delims,str[i]) != NULL){
            n++;
        }
        i++;
    }
    char * * strArr = malloc((n+1) * sizeof(char *));
    size_t arrind = 0;
    size_t last = 0;
    for(i=0;i<=strlen((char*)str);i++)
    {
        if(strchr(delims,str[i]) != NULL)
        {
            char * new_string = (char *)malloc((last+1-arrind) * sizeof(char));
            //strArr[j] = malloc((last+1-arrind) * sizeof(char));
            
            memcpy(new_string,str+arrind,last+1-arrind);
            new_string[last-arrind] = '\0';
            
            //strcpy((char*)strArr,new_string);
            //memcpy((char*)strArr,new_string,last+1-arrind);
            strArr[j] = new_string;
            j++;
            arrind = last+1;
            //free(new_string);
            //strArr++;
        }
        last++;
    }
    // for(i=0;i<=*arrLen;i++)
    // {
    //     free(strArr[i]);
    // }
    return(strArr);
    //free(strArr);
}

