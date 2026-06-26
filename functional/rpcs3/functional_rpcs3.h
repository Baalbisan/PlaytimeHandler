// functional_rpcs3.c
//
// Written By: Baalbisan
//
// Last Modified; 26/06/2026

#ifndef FUNCTIONAL_RPCS3_H
#define FUNCTIONAL_RPCS3_H

#include <stdbool.h>

/*
 * Parses the persistent_settings.dat config in string form and returns the playtime of game with serial "serial".
 * Returns in hours.
 * int value is -1 if we need to exit, 0 if successful.
 * */
int returnPlaytimeFromRPCS3Dat(char* filepath, char* serial, bool verbose, char* playtimeStr);

#endif // !FUNCTIONAL_RPCS3_H
