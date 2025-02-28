#include <stdio.h>
#include <stdlib.h>

#include "cjson/cJSON.h"
#include "JsonUtils.h"

void readSimpleData(){
    char *json_str = __ReadJSONFIle("test.json");
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

void addSimpleData(){
    cJSON *root = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data,"name","Benjamin");
    cJSON_AddItemToObject(root,"data",data);
    char *json_str = cJSON_Print(root);
    if(!__WriteJSONData("test.json",json_str)){
        printf("Writing data failed.\n");
    }
    else{
        printf("Writing data is completed\n");
    }
    cJSON_Delete(root);
}

int main() {
    addSimpleData();
    readSimpleData();
    return 0;
}
