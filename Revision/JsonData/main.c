#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <gtk/gtk.h>
#include <cJSON.h>

#include "application.h"
#include "JsonUtils.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const char __OPERATION_ARRAY[] = {'+','/','*','-'};

typedef struct BuildClassicSetting {
    bool Shadows;
    int maxGraphicSetting;
    int renderDistance;
} BuildClassicSetting , *defaultSettingValue;

typedef struct calcCombination {
    int x;
    int y;
    char o;
} calcCombination, *__CCombination;

static void bindDefaultSettings(defaultSettingValue settings){
    settings->maxGraphicSetting = 10;
    settings->renderDistance = 150;
    settings->Shadows = true;
}

char *processCalcOperation(__CCombination calcResult){
    char *formatStrCalc = (char *)malloc(sizeof(char) + 1024);
    double stockResult;
    char getOperationSymbol = __OPERATION_ARRAY[(rand() % (sizeof(__OPERATION_ARRAY)/sizeof(__OPERATION_ARRAY[0]))) + 1];
    calcResult->o = getOperationSymbol;
    switch(getOperationSymbol){
        case '+':
            stockResult = calcResult->x + calcResult->y;
            break;
        case '/':
            stockResult = calcResult->x / calcResult->y;
            break;
        case '-':
            stockResult = calcResult->x - calcResult->y;
            break;
        case '*':
            stockResult = calcResult->x * calcResult->y;
            break;
        default:
            stockResult = calcResult->x % calcResult->y;
            break;
    }
    snprintf(formatStrCalc
        ,1024,
        "%ld %c %ld = %lf",
        calcResult->x,getOperationSymbol,calcResult->y,stockResult
    );
    return formatStrCalc;
}

static void __registerCalc(cJSON *root,char *calc){
    if(!root){
        perror("Root is not a JSON object");
    }
    cJSON *calcData = cJSON_CreateObject();
    cJSON_AddStringToObject(calcData,"result",calc);
    cJSON_AddItemToObject(root,"Calcul",calcData);
}

static void closesFiles(int file_count, ...){
    va_list args;
    va_start(args,file_count);
    for(int i = 0; i < file_count; i++){
        FILE *file = va_arg(args,FILE*);
        if(file){
            fclose(file);
        }
    }
}

char *Reconcile(cJSON *rootA,cJSON *rootB){
    cJSON *item = NULL;
    cJSON_ArrayForEach(item,rootA){
        if(item->string == NULL){continue;};
        if(cJSON_IsObject(item)){
            cJSON *objectBInRootA = cJSON_GetObjectItem(rootB,item->string);
            char *objectBInRootA_Info = cJSON_Print(objectBInRootA);
            if(!objectBInRootA_Info){
                printf("%s is now added\n",objectBInRootA->string);
                cJSON_AddItemToObject(rootB,objectBInRootA->string,objectBInRootA);
            };
            cJSON *element = NULL;
            cJSON_ArrayForEach(element,item){
                if(element->string == NULL){continue;};
                cJSON *objectIsInRootB = cJSON_GetObjectItem(item,element->string);
                char *objectInfo = cJSON_Print(objectIsInRootB);
                if(objectInfo != NULL){
                    cJSON *checkItemRootB = cJSON_GetObjectItem(
                        (cJSON*)cJSON_GetObjectItem(rootB,item->string),
                        element->string
                    );
                    char *checkItemValue = cJSON_Print(checkItemRootB);
                    if(!checkItemValue){
                        if(cJSON_IsNumber(objectIsInRootB)){
                            int valueA = (int)((cJSON*)cJSON_GetObjectItem((cJSON*)cJSON_GetObjectItem(rootA,item->string),element->string)->valueint);
                            cJSON_AddNumberToObject((cJSON*)cJSON_GetObjectItem(rootB,item->string),element->string,valueA);
                        }
                        else if(cJSON_IsString(objectIsInRootB)){
                            cJSON_AddStringToObject((cJSON*)cJSON_GetObjectItem(rootB,item->string),element->string,element->valuestring);
                        }
                        else if(cJSON_IsObject(objectIsInRootB)){
                            cJSON_AddItemToObject((cJSON*)cJSON_GetObjectItem(rootB,item->string),element->string,element);
                        }
                    };
                    free(checkItemValue);
                };
                free(objectInfo);
            }
            free(objectBInRootA_Info);
        };
    }
    char *newReconcileData = cJSON_Print(rootB);
    return newReconcileData;
}

static void modifyCalc(cJSON *root){
    cJSON *getCalcObject = cJSON_GetObjectItem(root,"Calcul");
    if(getCalcObject == NULL){
        perror("Current object is null");
    };
    cJSON *getResultItem = cJSON_GetObjectItem(getCalcObject,"result");
    __CCombination new_calc = malloc(sizeof(calcCombination));
    new_calc->x = rand();
    new_calc->y = rand();
    char *processCalcState = processCalcOperation(new_calc);
    if(processCalcState == NULL){
        perror("Current calcul failed: ");
    };
   cJSON_SetValuestring(getResultItem,processCalcState);
   char *updateData = cJSON_Print(root);
   __WriteJSONData("./Software/test.json",updateData);
}

static void launchDataPackages(){
    FILE *jsonFile;
    char *getDefaultTemplateAsync = __ReadJSONFIle("./Software/defaultTest.json");
    char *getJsonData = __ReadJSONFIle("./Software/test.json");
    if(!getJsonData || !getDefaultTemplateAsync){
        closesFiles(1,jsonFile);
        free(getJsonData);
        free(getDefaultTemplateAsync);
    };
    cJSON *compactJsonData = cJSON_Parse(getJsonData);
    cJSON *compactDefaultJsonTemplateAsync = cJSON_Parse(getDefaultTemplateAsync);
    char *convert_json_data = cJSON_Print(compactJsonData);
    char *convert_default_template_json_data = cJSON_Print(compactDefaultJsonTemplateAsync);
    if(!jsonFile){
        closesFiles(1,jsonFile);
        free(getJsonData);
        free(getDefaultTemplateAsync);
        free(convert_json_data);
        free(convert_default_template_json_data);
        perror("Failed to open file");
    };
    if(convert_json_data){
        char *RData = Reconcile(compactDefaultJsonTemplateAsync,compactJsonData);
        jsonFile = fopen("./Software/test.json","w");
        fputs(RData,jsonFile);
        closesFiles(1,jsonFile);
        cJSON_Delete(compactJsonData);
        free(convert_default_template_json_data);
        free(convert_json_data);
        free(getDefaultTemplateAsync);
        free(getJsonData);
        printf("Reconcile event ended: [[Result]: %s]\nAny new modification will be saved.\n",RData);
        cJSON *updateReconciledData = cJSON_Parse((char*)__ReadJSONFIle("./Software/test.json"));
        modifyCalc(updateReconciledData);
        free(RData);
    }
    else {
        cJSON_Delete(compactJsonData);
        jsonFile = fopen("./Software/test.json","w");
        printf("Default data is building up!\n");
        defaultSettingValue settings = malloc(sizeof(BuildClassicSetting));
        if(!settings){
            perror("Memory allocation failed");
        }
        bindDefaultSettings(settings);
        cJSON *root = cJSON_CreateObject();
        cJSON *data = cJSON_CreateObject();
        cJSON_AddNumberToObject(data,"maxGraphics",settings->maxGraphicSetting);
        cJSON_AddNumberToObject(data,"renderDistance",settings->renderDistance);
        cJSON_AddBoolToObject(data,"Shadows",settings->Shadows);
        cJSON_AddItemToObject(root,"data",data);
        __CCombination calc = malloc(sizeof(calcCombination));
        calc->x = rand();
        calc->y = rand();
        char *getProcessedCalc = processCalcOperation(calc);
        __registerCalc(root,getProcessedCalc);
        char *convert_json_datab = cJSON_Print(root);
        fputs(convert_json_datab,jsonFile);
        fflush(jsonFile);
        fclose(jsonFile);
        cJSON *updateDefaultData = cJSON_Parse((char*)__ReadJSONFIle("./Software/test.json"));
        printf("Analysing current file before reconcile event: %s\n",cJSON_Print(updateDefaultData));
        jsonFile = fopen("./Software/test.json","w");
        char *RData = Reconcile(compactDefaultJsonTemplateAsync,updateDefaultData);
        fputs(RData,jsonFile);
        cJSON_Delete(root);
        free(convert_json_datab);
        closesFiles(1,jsonFile);
        free(getJsonData);
        free(convert_default_template_json_data);
        free(convert_json_data);
        free(calc);
        printf("Reconcile event ended: [[Result]: %s]\n",RData);
        printf("Data is now builded !\n");
        free(RData);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    launchDataPackages();
    int application_status = constructApplication(argc,argv);
    return application_status;
}
