//
//  main.c
//  Porject2
//
//  Created by Yi on 15/2/14.
//  Copyright (c) 2015年 Yi. All rights reserved.
//
// Chen Yiyi Id:0026406971
// Li zhuofan Id:002652066

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct task0{
    int num_sub0;
    int arrivetime;
    int *arr;
    struct task0 * next;
}task0;

typedef struct task1{
    int num_sub1;
    int arrivetime;
    int *arr;
    struct task1 * next;
}task1;

typedef struct queue0{
    task0 * front;
    task0 * rear;
}queue0;

typedef struct queue1{
    task1 * front;
    task1 * rear;
}queue1;


float randf();
double uniform(double a,double b,long int *seed);
queue0 *Initqueue0();
queue1 *Initqueue1();
task0* Enqueue0(queue0 *pqueue, int sub_task, int arrivetime, int *arr);
task1* Enqueue1(queue1 *pqueue, int sub_task, int arrivetime, int *arr);
int IsEmpty0(queue0 *pqueue);
int IsEmpty1(queue1 *pqueue);
char * * explode(const char * str, const char * delims);
task0 * Dequeue0(queue0 *pqueue, task0 *current_task, task0 *task_before);
task1 * Dequeue1(queue1 *pqueue, task1 *current_task, task1 *task_before);


int main(int argc, char * argv[]) {
    int time_line = 0;
    int pro_check;
    int num_type0 = 0;
    int num_type1 = 0;
    float arr_rate0;
    float arr_rate1;
    float service_rate;
    int num_subtype0 =0;
    int num_subtype1 =0;
    int available_pro = 0;
    int processor[64];
    int i;
    int aw0 = 0;
    int aw1 = 0;
    int aqlength = 0;
    int uti = 0;
    int maxservicetime = 0;
    int minservicetime = 100;
    int *arr;
    arr = malloc(sizeof(int)*33);
    int service_time;
    int project_end = 0;
    task0 *task_track0;
    task_track0 = malloc(sizeof(task0));
    task1 *task_track1;
    task_track1 = malloc(sizeof(task1));
    task0 *fordequeue0;
    fordequeue0 = malloc((sizeof(task0)));
    task1 *fordequeue1;
    fordequeue1 = malloc((sizeof(task1)));
    queue0 * q0 = Initqueue0();
    queue1 * q1 = Initqueue1();
    task0 * lc0;
    lc0 = malloc(sizeof(task0));
    task1 * lc1;
    lc1 = malloc(sizeof(task1));
    int num_intype0;
    int num_intype1;
    
    
    for(i=0; i<64; i++){
        processor[i] =0;
    }
    srand(time(NULL));
    long int s = rand();
    
    
    if(argc == 2){
        char* filename = argv[1];
        FILE * fp;
        char* str;
        str = malloc(sizeof(char)*65);
        char** strarr;
        strarr = malloc(sizeof(char*)*200);
        if((fp = fopen(filename,"r")) == NULL)
            return 0;
        while(fgets(str,200,fp) != NULL){
            strarr = explode(str," ");
            if(atoi(strarr[1]) == 0)
                num_type0 ++;
            else
                num_type1 ++;
        }
        num_intype0 = num_type0;
	num_intype1 = num_type1;
        fseek(fp,0,SEEK_SET);
        fgets(str,200,fp);
        strarr = explode(str," ");
        
        int serve_check = 0; //check if task has already been served.
        
        while(num_type0 != 0 || num_type1 !=0){
            available_pro = 0;
            for (i=0; i<64; i++) {
                if (processor[i] ==0) {
                    available_pro ++;
                }
            }
            //search queue0 and queue1
            
            task_track0 = q0->front;
            while(task_track0 != NULL){
                if (task_track0->num_sub0 <= available_pro) {
                    aw0 = aw0 + time_line - task_track0->arrivetime;
                    available_pro = available_pro - task_track0->num_sub0;
                    int p = 0; //processor check
                    i = 0;
                    while(task_track0->num_sub0 !=0){
                        if (processor[p] == 0) {
                            service_time = task_track0->arr[i];
                            i++;
                            processor[p] = service_time;
                            task_track0->num_sub0--;
                        }
                        p++;
                    }
                    task_track0 = Dequeue0(q0, task_track0, fordequeue0);
                }
                else{
                    fordequeue0 = task_track0;
                    task_track0 = fordequeue0->next;
                }
            }
            
            
            task_track1 = q1->front;
            while(task_track1 != NULL){
                if (task_track1->num_sub1 <= available_pro) {
                    aw1 = aw1 + time_line - task_track1->arrivetime;
                    available_pro = available_pro - task_track1->num_sub1;
                    int q = 0;//processor check
                    i = 0;
                    while(task_track1->num_sub1 !=0){
                        if (processor[q] == 0) {
                            service_time = task_track1->arr[i];
                            i++;
                            processor[q] = service_time;
                            task_track1->num_sub1--;
                        }
                        q++;
                    }
                    task_track1 = Dequeue1(q1, task_track1, fordequeue1);
                }
                else{
                    fordequeue1 = task_track1;
                    task_track1 = fordequeue1->next;
                }
            }
            
            
            available_pro = 0;
            
            if (atoi(strarr[1]) == 0 && project_end != 1){
                if(time_line == atoi(strarr[0])){
                    num_subtype0 = atoi(strarr[2]); //random equation needed
                    pro_check = 0;
                    while (pro_check < 64) {
                        if (processor[pro_check] == 0) {
                            available_pro ++;
                        }
                        pro_check ++;
                    }
                    pro_check = 0;
                    if(available_pro >= num_subtype0){
                        i = 3;
                        while (num_subtype0 != 0) {
                            if (processor[pro_check] ==0) {
                                service_time = atoi(strarr[i]);
                                i++;
                                if(service_time > maxservicetime)
                                    maxservicetime = service_time;
                                if(service_time < minservicetime)
                                    minservicetime = service_time;
                                processor[pro_check] = service_time;
                                num_subtype0 --;
                            }
                            pro_check ++;
                        }
                        serve_check = 1;
                        num_type0--;
                    }
                    else{
                        for(i=3; i<(num_subtype0 + 3);i++){
                            arr[i-3] = atoi(strarr[i]);
                        }
                        task_track0 = Enqueue0(q0, num_subtype0, time_line, arr);
                        num_type0--;
                        serve_check = 1;
                    }
                    pro_check = 0;
                    available_pro =0;
                }
            }
            
            if (atoi(strarr[1]) == 1 && project_end != 1){
                if(time_line == atoi(strarr[0])){
                    num_subtype1 = atoi(strarr[2]); //random equation needed
                    pro_check = 0;
                    while (pro_check < 64) {
                        if (processor[pro_check] == 0) {
                            available_pro ++;
                        }
                        pro_check ++;
                    }
                    pro_check = 0;
                    if(available_pro >= num_subtype1){
                        i = 3;
                        while (num_subtype1 != 0) {
                            if (processor[pro_check] ==0) {
                                service_time = atoi(strarr[i]);
                                i++;
                                if(service_time > maxservicetime)
                                    maxservicetime = service_time;
                                if(service_time < minservicetime)
                                    minservicetime = service_time;
                                processor[pro_check] = service_time;
                                num_subtype1 --;
                            }
                            pro_check ++;
                        }
                        serve_check = 1;
                        num_type1--;
                    }
                    else{
                        for(i=3;i<(num_subtype1 + 3);i++){
                            arr[i-3] = atoi(strarr[i]);
                        }
                        task_track1 = Enqueue1(q1, num_subtype1, time_line, arr);
                        num_type1--;
                        serve_check = 1;
                    }
                }
            }
            if(serve_check == 1){
                
                if(fgets(str,200,fp)!=NULL){
                strarr = explode(str," ");
                serve_check = 0;
                }
                else
                    project_end = 1;
            }
            else{
                available_pro =0;
                lc0 = q0->front;
                while(lc0 != NULL){
                    aqlength++;
                    lc0 = lc0->next;
                }
                lc1 = q1->front;
                while(lc1 != NULL){
                    aqlength++;
                    lc1 = lc1->next;
                }
                for(i=0; i<64; i++){
                    if(processor[i]!=0)
                        uti++;
                }
                for (i=0; i<64; i++) {
                    if (processor[i]!=0){
                        processor[i]--;
                    }
                }
                time_line ++;
            }
        }

        available_pro = 0;
        for (i=0; i<64; i++) {
            if (processor[i] ==0) {
                available_pro ++;
            }
        }
        while(available_pro != 64){
            for (i=0; i<64; i++) {
                if (processor[i]!=0){
                    processor[i]--;
                }
            }
            for(i=0; i<64; i++){
                if(processor[i]!=0)
                    uti++;
            }
            time_line ++;
            available_pro = 0;
            for (i=0; i<64; i++) {
                if (processor[i] ==0) {
                    available_pro ++;
                }
            }
        }

    }
    
    
    else{
        num_type0 = atoi(argv[4]);
        num_type1 = atoi(argv[4]);
        arr_rate0 = atof(argv[1]);
        arr_rate1 = atof(argv[2]);
        service_rate = atof(argv[3]);
        num_intype0 = num_type0;
	num_intype1 = num_type1;
        int interarrtime0 = (int)ceil(((-1/arr_rate0)*(log(1-randf()))));
        int interarrtime1 = (int)ceil(((-1/arr_rate1)*(log(1-randf()))));
        int time_arr0 = time_line + interarrtime0;
        int time_arr1 = time_line + interarrtime1;
        
        
        while(num_type0!=0 || num_type1!=0){
            for (i=0; i<64; i++) {
                if (processor[i] ==0) {
                    available_pro ++;
                }
            }
            //search queue0 and queue1
            task_track0 = q0->front;
            while(task_track0 != NULL){
                if (task_track0->num_sub0 <= available_pro) {
                    aw0 = aw0 + time_line - task_track0->arrivetime;
                    available_pro = available_pro - (task_track0->num_sub0);
                    int p = 0; //processor check
                    while(task_track0->num_sub0 !=0){
                        if (processor[p] == 0) {
                            service_time = (int)ceil(((-1/service_rate)*log(1-randf())));
                            processor[p] = service_time;
                            task_track0->num_sub0--;
                        }
                        p++;
                    }
                    task_track0 = Dequeue0(q0, task_track0, fordequeue0);
                }
                else{
                    fordequeue0 = task_track0;
                    task_track0 = fordequeue0->next;
                }
            }
            
            
            task_track1 = q1->front;
            while(task_track1 != NULL){
                if (task_track1->num_sub1 <= available_pro) {
                    aw1 = aw1 + time_line - task_track1->arrivetime;
                    available_pro = available_pro - (task_track1->num_sub1);
                    int q = 0;//processor check
                    while(task_track1->num_sub1 !=0){
                        if (processor[q] == 0) {
                            service_time = (int)ceil(((-1/service_rate)*log(1-randf())));
                            processor[q] = service_time;
                            task_track1->num_sub1--;
                        }
                        q++;
                    }
                    task_track1 = Dequeue1(q1, task_track1, fordequeue1);
                }
                else{
                    fordequeue1 = task_track1;
                    task_track1 = fordequeue1->next;
                }
            }
            
            available_pro = 0;
            
            
            if (time_line == time_arr0) {
                if(num_type0 > 1)
                    time_arr0 = time_line + (int)ceil(((-1/arr_rate0)*(log(1-randf()))));
                num_subtype0 = (int)ceil(uniform(0,32,&s)-0.5); //random equation needed
                pro_check = 0;
                while (pro_check < 64) {
                    if (processor[pro_check] == 0) {
                        available_pro ++;
                    }
                    pro_check ++;
                }
                pro_check = 0;
                if(available_pro >= num_subtype0){
                    while (num_subtype0 != 0) {
                        if (processor[pro_check] ==0) {
                            service_time = (int)ceil(((-1/service_rate)*log(1-randf())));
                            if(service_time > maxservicetime)
                                maxservicetime = service_time;
                            if(service_time < minservicetime)
                                minservicetime = service_time;
                            processor[pro_check] = service_time;
                            num_subtype0 --;
                            available_pro --;
                        }
                        pro_check ++;
                    }
                    num_type0--;
                }
                else{
                    task_track0 = Enqueue0(q0, num_subtype0, time_line, arr);
                    num_type0--;
                }
            }
            
            available_pro =0;
            
            
            if (time_line == time_arr1) {
                if(num_type1 > 1)
                    time_arr1 = time_line + ceil(((-1/arr_rate1)*(log(1-randf()))));
                num_subtype1 = (int)ceil(uniform(0,32,&s)-0.5); //random equation needed
                pro_check = 0;
                while (pro_check < 64) {
                    if (processor[pro_check] == 0) {
                        available_pro ++;
                    }
                    pro_check ++;
                }
                pro_check = 1;
                if(available_pro >= num_subtype1){
                    while (num_subtype1 != 0) {
                        if (processor[pro_check] ==0) {
                            service_time = (int)ceil(((-1/service_rate)*log(1-randf())));
                            if(service_time > maxservicetime)
                                maxservicetime = service_time;
                            if(service_time < minservicetime)
                                minservicetime = service_time;
                            processor[pro_check] = service_time;
                            num_subtype1 --;
                            available_pro --;
                        }
                        pro_check ++;
                    }
                    num_type1--;
                }
                else{
                    task_track1 = Enqueue1(q1, num_subtype1, time_line, arr);
                    num_type1--;
                }
            }
            lc0 = q0->front;
            while(lc0 != NULL){
                aqlength++;
                lc0 = lc0->next;
            }
            lc1 = q1->front;
            while(lc1 != NULL){
                aqlength++;
                lc1 = lc1->next;
            }
            for(i=0; i<64; i++){
                if(processor[i]!=0)
                    uti++;
            }
            for (i=0; i<64; i++) {
                if (processor[i]!=0){
                    processor[i]--;
                }
            }
            available_pro =0;
            time_line ++;
        }
        
    }
    FILE * fpout = NULL;
    fpout = fopen("proj1b_output","w");
    double avg_wait0 = (double)aw0/(double)num_intype0;
    double avg_wait1 = (double)aw1/(double)num_intype1;
    double avlength = (double)aqlength/(double)(num_intype1 + num_intype0);
    double utili = (double)uti/(double)time_line/64;
    double banlan = (((double)maxservicetime - (double)minservicetime)/((double)uti/64));
    fprintf(fpout,"%f\n%f\n%f\n%f\n%f\n",avg_wait0, avg_wait1, avlength, utili, banlan);
    fclose(fpout);
    return 0;
}



double uniform(double a,double b,long int *seed){
    double t;
    *seed=2045*(*seed)+1;
    *seed=*seed-(*seed/1048576)*1048576;
    t=(*seed)/1048576.0;
    t=a+(b-a)*t;
    return t;
}

queue0 *Initqueue0(){
    queue0 *pqueue = (queue0*) malloc(sizeof(queue0));
    if(pqueue!= NULL){
        pqueue->front = NULL;
        pqueue->rear = NULL;
    }
    return pqueue;
}

queue1 *Initqueue1(){
    queue1 *pqueue = (queue1*) malloc(sizeof(queue1));
    if(pqueue!= NULL){
        pqueue->front = NULL;
        pqueue->rear = NULL;
    }
    return pqueue;
}

task0* Enqueue0(queue0 *pqueue, int sub_task, int arrivetime, int *arr){
    task0 * ptask = malloc(sizeof(task0*));
    ptask->arr = malloc(sizeof(int)*33);
    int i;
    if (ptask != NULL) {
        ptask->num_sub0 = sub_task;
        ptask->arrivetime = arrivetime;
        for(i = 0; i < sub_task; i++){
        ptask->arr[i] = arr[i];
        }
        ptask->next = NULL;
        
        if(IsEmpty0(pqueue))
            pqueue->front = ptask;
        else
            pqueue->rear->next = ptask;
        pqueue->rear = ptask;
    }
    return ptask;
}

task1* Enqueue1(queue1 *pqueue, int sub_task, int arrivetime, int *arr){
    task1 * ptask = malloc(sizeof(task1*));
    ptask->arr = malloc(sizeof(int)*33);
    int i;
    if (ptask != NULL) {
        ptask->num_sub1 = sub_task;
        ptask->arrivetime = arrivetime;
        for(i = 0; i < sub_task; i++){
            ptask->arr[i] = arr[i];
        }
        ptask->next = NULL;
        
        if(IsEmpty1(pqueue))
            pqueue->front = ptask;
        else
            pqueue->rear->next = ptask;
        pqueue->rear = ptask;
    }
    return ptask;
}

int IsEmpty0(queue0 *pqueue){
    if(pqueue->front==NULL&&pqueue->rear==NULL)
        return 1;
    else
        return 0;
}

int IsEmpty1(queue1 *pqueue){
    if(pqueue->front==NULL&&pqueue->rear==NULL)
        return 1;
    else
        return 0;
}


task0 * Dequeue0(queue0 *pqueue, task0 *current_task, task0 *task_before){
    if (pqueue->front == current_task) {
        pqueue->front = current_task->next;
        current_task = pqueue->front;
    }
    else{
        task0 * temp = current_task;
        current_task = current_task -> next;
        task_before -> next = current_task;
        temp->next = NULL;
    }
    if(pqueue->front==NULL)
        pqueue->rear = NULL;
    return(current_task);
}

task1 * Dequeue1(queue1 *pqueue, task1 *current_task, task1 *task_before){
    if (pqueue->front == current_task) {
        pqueue->front = current_task->next;
        current_task = pqueue->front;
    }
    else{
        task1 * temp = current_task;
        current_task = current_task -> next;
        task_before -> next = current_task;
        temp->next = NULL;
    }
    if(pqueue->front==NULL)
        pqueue->rear = NULL;
    return(current_task);
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

float randf(){
    return (float)rand()/(RAND_MAX + 1.0);
}



