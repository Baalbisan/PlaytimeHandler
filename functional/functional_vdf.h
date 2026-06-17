// functional_vdf.h
//
// Written By: Baalbisan
//
// Last Modified: 12/06/2026

#ifndef FUNCTIONAL_VDF_H
#define FUNCTIONAL_VDF_H

#include "../lib/VDF/keyvalues.h"

/*
 * Parses the PTConfig and returns it as a KV_Pair* object. Pointer MUST be freed with KV_PairDestroy();
 * */
KV_Pair* parseLocalConfigVDF(char* filePath);

/*
 * Returns the playtime in hours as a float string.
 * */
void returnPlaytimeFromLocalConfigVDF(KV_Pair* list, char* gameID, char* playtimeStr);

/*
 * Returns the "format" string from PTConfig, with the playtime integrated.
 * */
void returnFinalizedFormatStr(char* formatStr, char* playtimeStr);

#endif // !FUNCTIONAL_VDF_H
