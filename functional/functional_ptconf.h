// functional_ptconf.h
//
// Written By: Baalbisan
//
// Last Modified: 26/06/2026

#ifndef FUNCTIONAL_PTC_H
#define FUNCTIONAL_PTC_H

#include <stdbool.h>
#include "../lib/cJSON/cJSON.h"

#define STEAMID64_BASE 76561197960265728

typedef enum{
    STEAM = 0, RPCS3
}GameType;

/*
 * Parses the PTConfig and returns it as a cJSON* object. Pointer MUST be freed with cJSON_Delete();
 * */
cJSON* parsePTConfig(char* filePath);

/*
 * Returns the length of the "games" array from PTConfig.
 * */
int getGameIDArrLen(cJSON* ptConfJson);

/*
 * Parses the "games" array in PTConfig and returns an array of strings, containing the gameids.
 * "len" represents the length of the "games" Json array in PTConfig.
 * */
void returnGameIDArr(cJSON *ptConfJson, char* gameIDsArr[], int len);

/*
 * Checks the validity of a SteamID64, based on the fact they always start with 7656119.
 * Returns true if valid, false if invalid.
 * */
bool checkSteamID64Validity(char* SteamID64);

/*
 * Parses the SteamUID field in PTConfig and returns the id in SteamID64 format.
 * Contains internal validity check and thus depends on checkSteamID64Validity.
 * */
char* returnSteamUID64(cJSON* ptConfJson);

/*
 * Converts a SteamID64 in string format to SteamID32 in string format.
 * */
void convertSteamID64toSteamID32(char* SteamID32, char* SteamID64);

/*
 * Parses the "games" array in PTConfig and returns the "format" field's value.
 * */
char* returnFastfetchModuleFormat(cJSON* ptConfJson, char* gameID);

/*
 * Returns the depth of the module to be modified.
 * */
int returnFastfetchModuleDepth(cJSON* ptConfJson, char* gameID);

/*
 * Returns the type of the game, as a value of the GameType enum.
 * */
GameType returnGameType(cJSON* ptConfJson, char* gameID);

#endif // !FUNCTIONAL_PTC_H
