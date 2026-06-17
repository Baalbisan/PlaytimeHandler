// functional_vdf.c
//
// Written By: Baalbisan
//
// Last Modified: 13/06/2026
#include "./functional_vdf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/VDF/keyvalues.h"

KV_Pair* parseLocalConfigVDF(char* filePath){
    FILE* LCVDFFilePtr;
    LCVDFFilePtr = fopen(filePath, "r");
    if (LCVDFFilePtr == NULL){
        fprintf(stderr, "ERROR: localconfig.vdf was not found. Most likely the wrong SteamUID has been entered in pt_config.json.\n");
    }

    //Parse the file
    KV_Pair* list = KV_ParseFile(filePath);

    if (!list){
        fprintf(stderr, "ERROR: %s", KV_GetError());
        KV_PairDestroy(list);
        exit(1);
    }

    return list;
}

void returnPlaytimeFromLocalConfigVDF(KV_Pair* list, char* gameID, char* playtimeStr){
    KV_Pair* gameIDList;
    gameIDList = KV_FindPair(KV_FindPair(KV_FindPair(KV_FindPair(KV_FindPair(
        KV_FindPair(list, "UserLocalConfigStore"),
        "Software"),
        "Valve"),
        "Steam"),
        "apps"),
        gameID
    );
    float pt = strtof(KV_FindString(gameIDList, "Playtime", "0"), NULL)/60;
    sprintf(playtimeStr, "%.2f", (float)pt);
}

void returnFinalizedFormatStr(char* formatStr, char* playtimeStr){
    char first[256];
    char last[256];
    strcpy(first, strtok(formatStr, "%"));
    strcpy(last, strtok(NULL, "%"));

    for (int i = 0; i < strlen(playtimeStr); i++){
        last[i] = playtimeStr[i];
    }

    sprintf(formatStr, "%s%s", first, last);
}
