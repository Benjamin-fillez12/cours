#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cjson/cJSON.h"

bool charToBool(const char c){
    return c != '\0' && c != '0';
}

typedef struct INSTANCE_PROPERTIES {
    char* name;
    char type;
    char* value;
} INSTANCE_PROPERTIES , *ISTP;

cJSON *AddItem(cJSON *parent , ISTP props){
    cJSON *item = NULL;
    switch(props->type){
        case 'o':
            item = cJSON_AddObjectToObject(parent,props->name);
            break;
        case 's':
            item = cJSON_AddStringToObject(parent,props->name,props->value);
            break;
        case 'n':
            int charToNum = atoi(props->value);
            item = cJSON_AddNumberToObject(parent,props->name,charToNum);
            break;
        case 'p':
            item = cJSON_AddNullToObject(parent,props->name);
            break;
        case 'a':
            item = cJSON_AddArrayToObject(parent,props->name);
            break;
        case 'f':
            item = cJSON_AddBoolToObject(parent,props->name,charToBool((char)props->value[0]));
            break;
        default:
            break;
    };
    return item;
}

static void DeleteItem(cJSON *parent, cJSON *item){
    if(item->string == NULL || parent->string == NULL){
        perror("Canno't delete a null item\n");
    };
    cJSON_DeleteItemFromObject(parent,item->string);
}
