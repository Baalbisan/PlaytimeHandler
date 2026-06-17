// functional_fetch.c
//
// Written By: Baalbisan
//
// Last Modified: 17/06/2026
#include "./functional_fetch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cJSON/cJSON.h"

cJSON* parseFastfetchConfig(char *filePath){
    FILE* fetchConfFptr;
    fetchConfFptr = fopen(filePath, "r");
    if (fetchConfFptr == NULL){
        fprintf(stderr, "ERROR: Fastfetch config could not be opened. Ensure your file structure follows the documentation.\n");
        exit(1);
    }

    // read and pass to buffer
    char* parseBuffer = (char*)malloc(sizeof(char)* 30720); //TODO: Make self-incrementing.
    int len = fread(parseBuffer, 1, 5800, fetchConfFptr);
    fclose(fetchConfFptr);

    // parse json into obj to be returned
    cJSON* fetchConfJson = cJSON_Parse(parseBuffer);
    if (fetchConfJson == NULL){
        const char* err = cJSON_GetErrorPtr();
        if (err != NULL){
            fprintf(stderr, "ERROR: %s", err);
        }
        else {
            fprintf(stderr, "ERROR: Unknown Error during function parseFastfetchConfig call. \nThis is not a user error... Please open an issue on github.\n");
        }
        free(parseBuffer);
        cJSON_Delete(fetchConfJson);
        exit(1);
    }

    free(parseBuffer);
    return fetchConfJson;
}

void writeNewFormatIntoFetchConfig(cJSON* fetchConfJson, char* filePath, int depth, char* formatStr){
    // open file
    FILE* fetchConfFptr;
    fetchConfFptr = fopen(filePath, "w");
    if (fetchConfFptr == NULL){
        fprintf(stderr, "ERROR: Fastfetch config could not be opened. Ensure your file structure follows the documentation.\n");
        exit(1);
    }

    // Get and modify needed module
    cJSON* modulesArr = cJSON_GetObjectItemCaseSensitive(fetchConfJson, "modules");
    cJSON* module;
    int count = 0;
    cJSON_ArrayForEach(module, modulesArr){
        if (!strcmp(cJSON_GetObjectItemCaseSensitive(module, "type")->valuestring, "custom")){
            count++;
        }

        if (count == depth){
            cJSON_ReplaceItemInObjectCaseSensitive(module, "format", cJSON_CreateString(formatStr));
        }
    }

    // Write into file
    char* finalizedJsonStr = cJSON_Print(fetchConfJson);
    fprintf(stderr, "%s", finalizedJsonStr);
    fputs(finalizedJsonStr, fetchConfFptr);
    fprintf(stderr, "Fastfetch config written without error!\n");
    fclose(fetchConfFptr);
    cJSON_free(finalizedJsonStr);
}
