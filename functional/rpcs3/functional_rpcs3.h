// functional_rpcs3.c
//
// Written By: Baalbisan
//
// Last Modified; 26/06/2026

#ifndef FUNCTIONAL_RPCS3
#define FUNCTIONAL_RPCS3

#include <stdbool.h>

/*
 * Parses the persistent_settings.dat config in string form and returns the playtime of game with serial "serial".
 * Returns in hours.
 * */
float returnPlaytimeFromRPCS3Dat(char* filepath, char* serial, bool verbose);

#endif // !FUNCTIONAL_RPCS3
