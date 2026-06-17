// functional_fetch.c
//
// Written By: Baalbisan
//
// Last Modified: 17/06/2026

#ifndef FUNCTIONAL_FETCH_H
#define FUNCTIONAL_FETCH_H

#include "../lib/cJSON/cJSON.h"

/*
 * Parses the Fastfetch config and returns it as a cJSON obj.
 * */
cJSON* parseFastfetchConfig(char *filePath);

/*
 * Searches modules till it finds the "depth" of the correct 'custom" type module.
 * Replaces "format" property of the "custom" module with the new formatStr.
 * */
void writeNewFormatIntoFetchConfig(cJSON* fetchConfJson, char* filePath, int depth, char* formatStr);

#endif // !FUNCTIONAL_FETCH_H
