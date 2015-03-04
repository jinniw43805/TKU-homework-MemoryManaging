//
//  main.c
//  GitPractice
//
//  Created by 郭彥君 on 15/3/2.
//  Copyright (c) 2015年 郭彥君. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


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
    int startAd;
    int endAd;
    enum state{allocate,release};
    struct schedule_node *next;
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
int main(int argc, const char * argv[])
{
    char tmp[50];
    char *tok=" ";
    char *parseTmpString;
    
    Queue q;
    q.head=NULL;
    q.tail=NULL;
    Schedule_queue Scheq;
    Scheq.head=NULL;
    Scheq.tail=NULL;
    
    Node *ptr;
    Node *ptrSchedule;
    FILE *fp;
    
    int i,t,globalEndTime=0;
    
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
        if (newnode->endTime > globalEndTime) {
            globalEndTime=newnode->endTime;
        }
        //End calculate
     //   printf("%d %d %d %d",newnode->processID,newnode->startAd,newnode->processTime,newnode->alloSpace);
        
        //為第一個節點
        if (q.head == NULL) {
            q.head=newnode;
            q.tail=newnode;
        }else{//為最後一個節點
            q.tail->next=newnode;
            q.tail=newnode;
            q.tail->next=NULL;
        }
        
        
        printf("\n");
        
    }
    
    
    //End read

    //enqueue
    enSchedule_queue(&q, &Scheq);
    //End enqueue
    //Test read whether success
//    printf("processID startTime processTime alloSpace endTime\n");
//    ptr=q.head;
//    int count=0;
//    while (ptr!=NULL) {
//       
//           printf("%d %d %d %d %d",ptr->processID,ptr->startTime,ptr->processTime,ptr->alloSpace,ptr->endTime);
//        printf("\n");
//        ptr=ptr->next;
//    }
//    printf("System end time: %d \n",globalEndTime);
//    
    ptr=q.head;
    //Test end
    
    //First-Allocation Algo
    Queue firstQ;
    printf("\n%d\n",ptr->startTime);
    
    
    
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
    Schedule_node *new_sche_node_allo;
    Schedule_node *new_sche_node_relea;
    ptr=queue->head;
    while (ptr!=NULL) {
        //Test for queue
//        printf("%d %d %d %d %d",ptr->processID,ptr->startTime,ptr->processTime,ptr->alloSpace,ptr->endTime);
//        printf("\n");
        //End test
        new_sche_node_allo=(Schedule_node*)malloc(sizeof(Schedule_node));
        
        new_sche_node_allo->processID=ptr->processID;
        new_sche_node_allo->time=ptr->startTime;
        
        new_sche_node_relea=(Schedule_node*)malloc(sizeof(Schedule_node));
        
        new_sche_node_relea->processID=ptr->processID;
        new_sche_node_relea->time=ptr->endTime;
        ptr=ptr->next;
    }
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