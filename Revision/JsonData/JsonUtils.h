#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "cjson/cJSON.h"

/*
    Reading json data:
    {
        char *json_str = read_file("test.json");
        if(!json_str){
            perror("Failed to open file");
            free(json_str);
            exit(1);
        }
        cJSON *json = cJSON_Parse(json_str);
        if(!json){
            perror("Parsing json failed.");
            free(json_str);
            exit(1);
        }
        cJSON *data = cJSON_GetObjectItem(json,"data");
        cJSON *name = cJSON_GetObjectItem(data,"name");
        if(cJSON_IsString(name)){
            printf("Nom: %s\n",name->valuestring);
        }
        cJSON_Delete(json);
        free(json_str);
    }
    Add json data:
    {
        cJSON *root = cJSON_CreateObject();
        cJSON *data = cJSON_CreateObject();
        cJSON_AddStringToObject(data,"name","Benjamin");
        cJSON_AddItemToObject(root,"data",data);
        char *json_str = cJSON_Print(root);
        if(!__WriteData("test.json",json_str)){
            printf("Writing data failed.\n");
        }
        else{
            printf("Writing data is completed\n");
        }
        cJSON_Delete(root);
    }
 */

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
    fclose(file);
    return 1;
}
