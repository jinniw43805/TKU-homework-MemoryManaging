//
//  main.c
//  GitPractice
//
//  Created by 郭彥君 on 15/3/2.
//  Copyright (c) 2015年 郭彥君. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer [100000];

typedef struct node{
    int processID;
    int startTime;
    int processTime;
    int alloSpace;
    int endTime;
    struct node *next;
}Node;
typedef struct schedule_node{
    int processID;
    int time;
    int alloSpace;
    enum states{allocate,release}States;
    struct schedule_node *next;
    
    //for allocate node
    struct schedule_node *releaseNode;
    
    //for release node
    int startAd;
    int endAd;
}Schedule_node;

typedef struct queue{
    struct node *head;
    struct node *tail;
}Queue;

typedef struct schedule_queue{
    struct schedule_node *head;
    struct schedule_node *tail;
}Schedule_queue;

char tmp[50];
FILE *fp;

void printBufferStatus (void);
void initBufferStatus(void);
void enSchedule_queue(Queue *queue,Schedule_queue *Scheq);
void process_schedule_queue(Schedule_queue *Scheq);
int main(int argc, const char * argv[])
{
    char tmp[50];
    char *tok=" ";
    char *parseTmpString;
    
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    Schedule_queue *Scheq;
    Scheq=(Schedule_queue*)malloc(sizeof(Schedule_queue));
    Scheq->head=NULL;
    Scheq->tail=NULL;
    
    
    Node *ptr;
    FILE *fp;
    
    int i,t;
    
    //Read file
    
    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("File open failed\n");
        exit(1);
    }
    
    //End Read
    
    //init buffer
    initBufferStatus();
    //
    //Read file to Queue
    Node *newnode;
    while (fgets(tmp, 50, fp) != NULL) {
        // If read a new line , than allocation a new node
        
        newnode=(Node*)malloc(sizeof(Node));
        //
        
        
        parseTmpString=strtok(tmp," ");
        newnode->processID=atoi(parseTmpString);
        
        parseTmpString=strtok(NULL, " ");
        newnode->startTime=atoi(parseTmpString);
        
        
        parseTmpString=strtok(NULL, " ");
        newnode->processTime=atoi(parseTmpString);
        
        parseTmpString=strtok(NULL, " ");
        newnode->alloSpace=atoi(parseTmpString);
        
        newnode->endTime=(newnode->processTime)+(newnode->startTime);
        
        //Calculate when system stop
        //End calculate
        //   printf("%d %d %d %d",newnode->processID,newnode->startAd,newnode->processTime,newnode->alloSpace);
        
        //為第一個節點
        if (q->head == NULL) {
            q->head=newnode;
            q->tail=newnode;
        }else{//為最後一個節點
            q->tail->next=newnode;
            q->tail=newnode;
            q->tail->next=NULL;
        }
        
        
    }
    
    //End read
    
    //enqueue
    
    enSchedule_queue(q, Scheq);
    //End enqueue
    Schedule_node *ptrSchedule;
    ptrSchedule=Scheq->head;
    while (ptrSchedule!=NULL) {
        if (ptrSchedule->States==allocate) {
            printf("Enter process ID: %d , Enter time: %d\n",ptrSchedule->processID,ptrSchedule->time);
        }else if (ptrSchedule->States==release){
            printf("Release process ID: %d ,Release time: %d\n",ptrSchedule->processID,ptrSchedule->time);
        }
        ptrSchedule=ptrSchedule->next;
    }
    //Test read whether success
        printf("processID startTime processTime alloSpace endTime\n");
        ptr=q->head;
        int count=0;
        while (ptr!=NULL) {
    
               printf("%d %d %d %d %d",ptr->processID,ptr->startTime,ptr->processTime,ptr->alloSpace,ptr->endTime);
            printf("\n");
            ptr=ptr->next;
        }

    ptr=q->head;
    //Test end
    
    //First-Allocation Algo
    Queue firstQ;
    
    
    //End First
    
    //Best-Allocation Algo
    
    //End Best
    
    //Worst-Allocation Algo
    
    //End Worst
    
    
    //printfBuffer
    
    
    // printBufferStatus();
    
    //end printfBuffer
    
    fclose(fp);
    return 0;
}
void enSchedule_queue(Queue *queue,Schedule_queue *Scheq){
    Node *ptr;
    Schedule_node *ptrSchedule;
    
    ptr=queue->head;
    while (ptr!=NULL) {
        Schedule_node *new_sche_node_allo;
        Schedule_node *new_sche_node_relea;
        //Test for queue
        printf("%d %d %d %d %d",ptr->processID,ptr->startTime,ptr->processTime,ptr->alloSpace,ptr->endTime);
        printf("\n");
        //End test
        
        
        //allocate event
        new_sche_node_allo=(Schedule_node*)malloc(sizeof(Schedule_node));
        new_sche_node_allo->processID=ptr->processID;
        new_sche_node_allo->time=ptr->startTime;
        new_sche_node_allo->alloSpace=ptr->alloSpace;
        new_sche_node_allo->States=allocate;
        
        //release event
        
        new_sche_node_relea=(Schedule_node*)malloc(sizeof(Schedule_node));
        new_sche_node_relea->processID=ptr->processID;
        new_sche_node_relea->time=ptr->endTime;
        new_sche_node_relea->alloSpace=ptr->alloSpace;
        new_sche_node_relea->States=release;
        
        
        //binding allocate node with release node
        new_sche_node_allo->releaseNode=new_sche_node_allo;
        //visit the schedule queue
        
        //if first event
        if (Scheq->head==NULL && Scheq->tail==NULL) {
            Scheq->head=new_sche_node_allo;
            Scheq->tail=new_sche_node_relea;
            new_sche_node_allo->next=new_sche_node_relea;
            new_sche_node_relea->next=NULL;
        }else{
            
            
            //for allocate
            ptrSchedule=Scheq->head;
            while (ptrSchedule!=NULL) {
                if (new_sche_node_allo->time > Scheq->tail->time) {
                    Scheq->tail->next=new_sche_node_allo;
                    Scheq->tail=new_sche_node_allo;
                }else if (new_sche_node_allo->time < Scheq->head->time){
                    new_sche_node_allo->next=Scheq->head;
                    Scheq->head=new_sche_node_allo;
                }else if (new_sche_node_allo->time > ptrSchedule->time &&
                          new_sche_node_allo->time < ptrSchedule->next->time){
                    new_sche_node_allo->next=ptrSchedule->next;
                    ptrSchedule->next=new_sche_node_allo;
                }
                ptrSchedule=ptrSchedule->next;
            }
            //for release
            ptrSchedule=Scheq->head;
            while (ptrSchedule!=NULL) {
                if (new_sche_node_relea->time > Scheq->tail->time) {
                    Scheq->tail->next=new_sche_node_relea;
                    Scheq->tail=new_sche_node_relea;
                }else if (new_sche_node_relea->time < Scheq->head->time){
                    new_sche_node_relea->next=Scheq->head;
                    Scheq->head=new_sche_node_relea;
                }else if (new_sche_node_relea->time > ptrSchedule->time &&
                          new_sche_node_relea->time < ptrSchedule->next->time){
                    new_sche_node_relea->next=ptrSchedule->next;
                    ptrSchedule->next=new_sche_node_relea;
                }
                ptrSchedule=ptrSchedule->next;
            }
        }
        ptr=ptr->next;
    }
}
void process_schedule_queue(Schedule_queue *Scheq){
    Schedule_node *ptrSchedule;
}
void printBufferStatus(void){
    int i;
    for (i = 0; i< 100000; i++)
    {
        printf("%c ",buffer[i]);
    }
    
}
void initBufferStatus(void){
    int i;
    for (i=0; i<100000; i++) {
        buffer[i]='0';
    }
};