//
//  main.c
//  GitPractice
//
//  Created by 郭彥君 on 15/3/2.
//  Copyright (c) 2015年 郭彥君. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 10000
#define TIME_LIMIT 1000
#define MEM_LIMIT 500
#define TIME_OFFSET 10

int main(int argc, const char * argv[])
{
    FILE *fp;
    int cur_time=2, i;
    int p_id = 1000;
    
    
    srand((int)time(NULL));
    fp = fopen("input.txt", "w");
    
    for (i=0; i< COUNT; i++)
    {
        fprintf(fp, "%d ", p_id);
        p_id++;
        
        fprintf(fp, "%d ", cur_time);
        cur_time = cur_time + 1+ (rand()%TIME_OFFSET);
        
        fprintf(fp, "%d ", 1+ (rand()%TIME_LIMIT));
        fprintf(fp, "%d\n", 1+ (rand()%MEM_LIMIT));
        
    }
    
    fclose(fp);
    return 0;
}

