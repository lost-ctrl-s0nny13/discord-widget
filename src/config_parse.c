#include "config_parse.h"
#include <stdio.h>
#include <string.h>

uint32_t json_read(t_jpr* result, char* config_path){
    FILE* config = fopen(config_path, "r");
    if(config == NULL){
        return JSON_MISSING;
    }
    
    return READ_SUCCESS;
}