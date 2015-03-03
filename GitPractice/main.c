//
//  main.c
//  GitPractice
//
//  Created by 郭彥君 on 15/3/2.
//  Copyright (c) 2015年 郭彥君. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define COUNT 10000
#define TIME_LIMIT 1000
#define MEM_LIMIT 500
#define TIME_OFFSET 10

unsigned char buffer [100000];
//test
unsigned char testbuffer [10];
//test
typedef struct node{
    int processID;
    int startTime;
    int processTime;
    int alloSpace;
    int endTime;
    struct node *next;
}Node;

typedef struct lognode{
    int processID;
    int startTime;
};
typedef struct queue{
    struct node *head;
    struct node *tail;
}Queue;

char tmp[50];
FILE *fp;

int main(int argc, const char * argv[])
{
    char tmp[50];
    char *tok=" ";
    char *parseTmpString;
    
    Queue q;
    q.head=NULL;
    q.tail=NULL;
    
    Node *ptr;
    
    FILE *fp;
    
    int i,t,globalEndTime=0;
    
    //Read file
    
    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("File open failed\n");
        exit(1);
    }
    
    //End Read
    
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
    /*
    Queue firstQ;
    for (t=0; t<=globalEndTime; t++) {
        
        while (ptr->startTime==t) { //once startTime==currentTime, than handle this process
            
            ptr=ptr->next;
        }
    }
    */
    //End First
    
    //Best-Allocation Algo
    
    //End Best
    
    //Worst-Allocation Algo
    
    //End Worst
    
    fclose(fp);
    return 0;
}

