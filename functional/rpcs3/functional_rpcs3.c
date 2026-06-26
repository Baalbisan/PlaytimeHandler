// functional_rpcs3.c
//
// Written By: Baalbisan
//
// Last Modified; 26/06/2026
#include "functional_rpcs3.h"

# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int returnPlaytimeFromRPCS3Dat(char* filepath, char* serial, bool verbose, char* playtimeStr){
    if (serial == NULL){
        return -1;
    }

    FILE* perSetFptr;
    perSetFptr = fopen(filepath, "r");

    if (perSetFptr == NULL && verbose){
        fprintf(stderr, "WARNING: Rpcs3's persistent_settings.dat not found");
        return -1;
    }

    char* line = NULL;
    size_t len = 0;
    bool playtimeFlag = false;

    while (getline(&line, &len, perSetFptr) != -1) {//till EOF
        if (!strcmp(line, "[Playtime]")){
            playtimeFlag = true;
        }

        if (playtimeFlag){
            char* tok = strtok(line, "=");
            if (!strcmp(serial, tok)){//GAME FOUND :D
                tok = strtok(NULL, "=");
                sprintf(playtimeStr, "%.2f", strtof(tok, NULL)/60/60);
                return 0;
            }
            else {
                fprintf(stderr, "ERROR: Playtime not found for Rpcs3 game %s in Rpcs3's persistent_settings.dat", serial);
                exit(1);
            }
        }
    }

    free(line);
    fclose(perSetFptr);
}
