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

//test
unsigned char testbuffer [8];
//test

typedef struct node{
    int processID;
    int startTime;
    int processTime;
    int alloSpace;
    int endTime;
    struct node *next;
}Node;

typedef struct log_node{
    int processID;
    int startTime;
    struct log_node *next;
}Log_node;

typedef struct remove_node{
    int processID;
    int startAd;
    int endAd;
    int entTime;
    struct remove_node *next;
}Remove_node;

typedef struct queue{
    struct node *head;
    struct node *tail;
}Queue;


typedef struct log_queue{
    struct log_node *head;
    struct log_node *tail;
}Log_queue;

typedef struct remove_queue{
    struct remove_node *head;
    struct remove_node *tail;
}Remove_queue;
char tmp[50];
FILE *fp;

void printBufferStatus (void);
void initBufferStatus(void);
int main(int argc, const char * argv[])
{
    char tmp[50];
    char *tok=" ";
    char *parseTmpString;
    
    Queue q;
    q.head=NULL;
    q.tail=NULL;
    
    Remove_queue removeq;
    removeq.head=NULL;
    removeq.tail=NULL;
    
    Log_queue logq;
    logq.head=NULL;
    logq.tail=NULL;
    
    Node *ptr;
    Log_node *ptrLog;
    
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
    
    while (fgets(tmp, 50, fp) != NULL) {
        // If read a new line , than allocation a new node
        Node *newnode;
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
            if(q.tail==NULL){
                q.tail->next=newnode;
                newnode->next=NULL;
            }else{
                q.tail->next=newnode;
                q.tail=newnode;
            }
        }
        
        
        printf("\n");
        
    }
    
    
    //End read

    
    //Test read whether success
    printf("processID startTime processTime alloSpace\n");
    ptr=q.head;
    while (ptr!=NULL) {
           printf("%d %d %d %d %d",ptr->processID,ptr->startTime,ptr->processTime,ptr->alloSpace,ptr->endTime);
        printf("\n");
        ptr=ptr->next;
    }
    printf("System end time: %d \n",globalEndTime);
    ptr=q.head;
    //Test end
    
    //First-Allocation Algo
    Queue firstQ;
    
    for (t=0; t<=globalEndTime; t++) {
        //Delete area
        //end Delete
        printf("\n%d\n",ptr->startTime);
        /*
        while (ptr->startTime==t) { //Once startTime==currentTime, than handle this process
            //process
                //allocate a new node for log
                Log_node *newLog_node;
                newLog_node=(Log_node*)malloc(sizeof(Log_node));
                
                newLog_node->processID=ptr->processID;
                newLog_node->startTime=ptr->startTime;
            
                if (logq.head == NULL) { //First Node
                    logq.head=newLog_node;
                    logq.tail=newLog_node;
                }else{
                    logq.tail->next=newLog_node;
                    logq.tail=newLog_node;
                }
            
            
            ptr=ptr->next;
        }
         */
    }
    
    //End First
    
    //Best-Allocation Algo
    
    //End Best
    
    //Worst-Allocation Algo
    
    //End Worst
    
    
    //printfBuffer
    

    printBufferStatus();
    
    //end printfBuffer
    
    fclose(fp);
    return 0;
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