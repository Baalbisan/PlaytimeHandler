// main.c
//
// Written By: Baalbisan
//
// Last Modified: 26/06/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/cJSON/cJSON.h"
#include "./functional/functional_ptconf.h"
#include "./functional/functional_vdf.h"
#include "./functional/functional_fetch.h"
#include "./functional/rpcs3/functional_rpcs3.h"
#include "lib/VDF/keyvalues.h"

int main (){
    bool verbose = true;
    char* homeDir = getenv("HOME");
    char SteamUID32[11];//i.e. 52079950
    char playtimeStr[10]; //up to 999999999 minutes
    char vdfFilePath[256];
    char rpcs3FilePath[256];
    char ffetchConfigFilePath[256];
    char ptConfigPath[256];

    // Take gameIDs and uID form PTConfig.
    sprintf(ptConfigPath, "%s/.config/fastfetch/pt_config.json", homeDir);
    cJSON* ptConfigJson = parsePTConfig(ptConfigPath);
    int gameIDLen = getGameIDArrLen(ptConfigJson);
    char* gameIDArr[gameIDLen];
    returnGameIDArr(ptConfigJson, gameIDArr, gameIDLen);

    convertSteamID64toSteamID32(SteamUID32, returnSteamUID64(ptConfigJson));

    // Generate path to localconfig.vdf and parse.
    sprintf(vdfFilePath, "%s/.steam/steam/userdata/%s/config/localconfig.vdf", homeDir, SteamUID32);
    KV_Pair* localConfigVDF;
    localConfigVDF = parseLocalConfigVDF(vdfFilePath);

    // Generate path to persistent_settings.dat
    sprintf(rpcs3FilePath, "%s/.config/rpcs3/GuiConfigs/persistent_settings.dat", homeDir);

    // Open Fastfetch config.
    sprintf(ffetchConfigFilePath, "%s/.config/fastfetch/config.jsonc", homeDir);
    cJSON* fetchConfigJson;
    fetchConfigJson = parseFastfetchConfig(ffetchConfigFilePath);

    // Generate formatting strs for every game in the gameIDArr. Write into Fastfetch config.
    for (int i = 0; i < gameIDLen; i++){
        int depth = returnFastfetchModuleDepth(ptConfigJson, gameIDArr[i]);
        GameType type = returnGameType(ptConfigJson, gameIDArr[i]);
        char formatStr[256];
        strcpy(formatStr, returnFastfetchModuleFormat(ptConfigJson, gameIDArr[i]));
        switch (type) {
            case STEAM:{
                returnPlaytimeFromLocalConfigVDF(localConfigVDF, gameIDArr[i], playtimeStr);
                break;
            }
            case RPCS3:{
                returnPlaytimeFromRPCS3Dat(rpcs3FilePath, gameIDArr[i], verbose, playtimeStr);
                break;
            }
            default:{
                break;
            }
        }
        returnFinalizedFormatStr(formatStr, playtimeStr);
        writeNewFormatIntoFetchConfig(fetchConfigJson, ffetchConfigFilePath, depth, formatStr);
    }

    KV_PairDestroy(localConfigVDF);
    cJSON_Delete(ptConfigJson);
    cJSON_Delete(fetchConfigJson);
    return 0;
}
