// main.c
//
// Written By: Baalbisan
//
// Last Modified: 17/06/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/cJSON/cJSON.h"
#include "./functional/functional_ptconf.h"
#include "./functional/functional_vdf.h"
#include "./functional/functional_fetch.h"
#include "lib/VDF/keyvalues.h"

#define PTCONFIG_PATH "./pt_config.json"

int main (){
    char* homeDir = getenv("HOME");
    char SteamUID32[11];//i.e. 52079950
    char playtimeStr[10]; //up to 999999999 minutes
    char vdfFilePath[256];
    char ffetchConfigFilePath[256];

    // Take gameIDs and uID form PTConfig.
    cJSON* ptConfigJson = parsePTConfig(PTCONFIG_PATH);
    int gameIDLen = getGameIDArrLen(ptConfigJson);
    char* gameIDArr[gameIDLen];
    returnGameIDArr(ptConfigJson, gameIDArr, gameIDLen);

    convertSteamID64toSteamID32(SteamUID32, returnSteamUID64(ptConfigJson));

    // Generate path to localconfig.vdf and parse.
    sprintf(vdfFilePath, "%s/.steam/steam/userdata/%s/config/localconfig.vdf", homeDir, SteamUID32);
    KV_Pair* localConfigVDF;
    localConfigVDF = parseLocalConfigVDF(vdfFilePath);

    // Open Fastfetch config.
    sprintf(ffetchConfigFilePath, "%s/.config/fastfetch/config.jsonc", homeDir);
    cJSON* fetchConfigJson;
    fetchConfigJson = parseFastfetchConfig(ffetchConfigFilePath);

    // Generate formatting strs for every game in the gameIDArr. Write into Fastfetch config.
    for (int i = 0; i < gameIDLen; i++){
        int depth = returnFastfetchModuleDepth(ptConfigJson, gameIDArr[i]);
        char formatStr[256];
        strcpy(formatStr, returnFastfetchModuleFormat(ptConfigJson, gameIDArr[i]));
        returnPlaytimeFromLocalConfigVDF(localConfigVDF, gameIDArr[i], playtimeStr);
        returnFinalizedFormatStr(formatStr, playtimeStr);
        writeNewFormatIntoFetchConfig(fetchConfigJson, ffetchConfigFilePath, depth, formatStr);
    }

    KV_PairDestroy(localConfigVDF);
    cJSON_Delete(ptConfigJson);
    cJSON_Delete(fetchConfigJson);
    return 0;
}
