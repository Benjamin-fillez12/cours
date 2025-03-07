#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <cJSON.h>

char *__ReadJSONFIle(const char *filename){
    FILE *file = fopen(filename,"r");
    if(!file){
        perror("Failed to open file");
        return NULL;
    };
    fseek(file,0,SEEK_END);
    long lenght = ftell(file);
    rewind(file);
    char *content = (char *)malloc(lenght + 1);
    if(!content){
        fclose(file);
        return NULL;
    }
    fread(content,1,lenght,file);
    content[lenght] = '\0';
    fclose(file);
    return content;
}

int __WriteJSONData(const char *filename,const char *data){
    FILE *file = fopen(filename,"w");
    if(!file){
        perror("Failed to open file");
        return 0;
    }
    fputs(data,file);
    fflush(file);
    fclose(file);
    return 1;
}
