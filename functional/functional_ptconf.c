// functional.c
//
// Written By: Baalbisan
//
// Last Modified: 17/06/2026
#include "./functional_ptconf.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cJSON/cJSON.h"

cJSON* parsePTConfig(char* filePath){
    FILE *ptConfigFptr;
    ptConfigFptr = fopen(filePath, "r");

    if (ptConfigFptr == NULL){
        fprintf(stderr, "ERROR: pt_config.json not found.\n");
        exit(1);
    }

    //read from file, pass to buffer.
    char parseBuffer[1024*8];
    int len = fread(parseBuffer, 1, sizeof(parseBuffer), ptConfigFptr);
    fclose(ptConfigFptr);

    //parse json into obj to be returned
    cJSON *ptConfJson = cJSON_Parse(parseBuffer);
    if (ptConfJson == NULL){
        const char *err = cJSON_GetErrorPtr();
        if (err != NULL){
            fprintf(stderr,"ERROR: %s\n", err);
        }
        else {
            fprintf(stderr, "ERROR: Unknown Error during function parsePTConfig call. \nThis is not a user error... Please open an issue on github.\n");
        }
        cJSON_Delete(ptConfJson);
        exit(1);
    }

    return ptConfJson;
}

int getGameIDArrLen(cJSON* ptConfJson){
    cJSON* games = cJSON_GetObjectItemCaseSensitive(ptConfJson, "games");
    return cJSON_GetArraySize(games);
}

void returnGameIDArr(cJSON *ptConfJson, char* gameIDsArr[], int len){
    cJSON*games = cJSON_GetObjectItemCaseSensitive(ptConfJson, "games");
    cJSON* game;
    int idx = 0;

    cJSON_ArrayForEach(game, games){
        cJSON* elem;
        cJSON_ArrayForEach(elem, game){
            if (!strcmp(elem->string, "gameid")){
                gameIDsArr[idx] = elem->valuestring;
                idx++;
            }
        }
    }
}

bool checkSteamID64Validity(char* SteamID64){
    //SteamID64 always starts with 7656119
    char* validityKey = "7656119";
    for (int i = 0; i < 7; i++){
        if (validityKey[i] != SteamID64[i]){
            return false;
        }
    }
    return true;
}

char* returnSteamUID64(cJSON* ptConfJson){
    if (cJSON_GetObjectItemCaseSensitive(ptConfJson, "SteamUID") == NULL){
            fprintf(stderr, "ERROR: ""SteamUID"" field not found, ensure it exists.\n");
            exit(1);
    }

    if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(ptConfJson, "SteamUID"))){
        fprintf(stderr, "ERROR: The value of ""SteamUID"" isn't a string. Ensure your pt_config follows the documentation.\n");
        exit(1);
    }

    if (!checkSteamID64Validity(cJSON_GetObjectItemCaseSensitive(ptConfJson, "SteamUID")->valuestring)){
        fprintf(stderr, "ERROR: The steam user ID entered is invalid. Ensure you have copied and entered the correct ID, as per the documentation.\n");
        exit(1);
    }

    return cJSON_GetObjectItemCaseSensitive(ptConfJson, "SteamUID")->valuestring;
}

void convertSteamID64toSteamID32(char* SteamID32,char* SteamID64){
    unsigned long long SteamID64_llu = strtoll(SteamID64, NULL, 0);
    unsigned long long SteamID32_llu = (SteamID64_llu - 76561197960265728);

    sprintf(SteamID32, "%llu", SteamID32_llu);
}

char* returnFastfetchModuleFormat(cJSON* ptConfJson, char* gameID){
    cJSON* games = cJSON_GetObjectItemCaseSensitive(ptConfJson, "games");
    cJSON* game;
    cJSON_ArrayForEach(game, games){
        if (cJSON_GetObjectItemCaseSensitive(game, "gameid") == NULL){
            fprintf(stderr, "ERROR: ""gameid"" field not found. Ensure it exists.\n");
            exit(1);
        }

        // Datatype checks
        if (cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(game, "gameid"))){
            fprintf(stderr, "ERROR: ""gameid"" field entered as a number.\n\tFIX: replace the value of ""gameid"" with ""[gameid]"".\n");
            exit(1);
        }

        if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(game ,"format"))){
            fprintf(stderr, "ERROR: The value of ""format"" isn't a string. Ensure your pt_config follows the documentation.\n");
        }

        if (!strcmp(cJSON_GetObjectItemCaseSensitive(game, "gameid")->valuestring, gameID))
            return cJSON_GetObjectItemCaseSensitive(game, "format")->valuestring;
    }
    fprintf(stderr, "ERROR: ""gameid"" field not found, ensure your pt_config file follows the documentation.\n");
    exit(1);
}

int returnFastfetchModuleDepth(cJSON* ptConfJson, char* gameID){
    cJSON* games = cJSON_GetObjectItemCaseSensitive(ptConfJson, "games");
    cJSON* game;
    cJSON_ArrayForEach(game, games){
        if (cJSON_GetObjectItemCaseSensitive(game, "depth") == NULL){
            fprintf(stderr, "ERROR: ""depth"" field not found for gameid %s. Ensure it exists.\n", gameID);
            exit(1);
        }


        // Datatype checks
        if (cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(game, "gameid"))){
            fprintf(stderr, "ERROR: ""gameid"" field entered as a number.\n\tFIX: replace the value of ""gameid"" with ""[gameid]"".\n");
            exit(1);
        }

        if (!cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(game ,"depth"))){
            fprintf(stderr, "ERROR: The value of ""depth"" isn't a number. Ensure your pt_config follows the documentation.\n");
            exit(1);
        }

        if (!strcmp(cJSON_GetObjectItemCaseSensitive(game, "gameid")->valuestring, gameID))
            return cJSON_GetObjectItemCaseSensitive(game, "depth")->valueint;
    }
    fprintf(stderr, "ERROR: ""gameid"" field not found, ensure your pt_config file follows the documentation.\n");
    exit(1);
}
