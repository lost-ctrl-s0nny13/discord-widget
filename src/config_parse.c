#include "config_parse.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

uint32_t config_read(t_cpr* result, char* config_path){
    FILE* config = fopen(config_path, "rb");
    if(config == NULL){
        return CONFIG_MISSING;
    }
    fseek(config, 0, SEEK_END);
    long filesize = ftell(config) + 1;
    rewind(config);
    void* buffer = malloc((filesize) * sizeof(char));
    if(buffer == NULL){
        fclose(config);
        return MALLOC_ERROR;
    }
    ((char*)buffer)[filesize] = '\0';
    size_t read_bytes = fread(buffer, sizeof(char), (size_t) filesize, config);
    if(read_bytes != filesize){
        free(buffer);
        fclose(config);
        return READ_ERROR;
    }
    fclose(config);
    //parsing values start
    long semicolon_index[14];
    int semicolons_found = 0;
    for(long i = 0; i < filesize; ++i){
        if(((char*)buffer)[i] == ';'){
            semicolon_index[semicolons_found] = i;
            ++semicolons_found;
        }
    }
    int expr_count = 0;
    for(long i = 0; i < filesize; ++i){
        if(((char*)buffer)[i] == '='){
            ++expr_count;
        }
        switch(expr_count){
            case 1:
            
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            break;
            case 9:
            break;
            case 10:
            break;
            case 11:
            break;
            case 12:
            break;
            case 13:
            break;
            case 14:
            break;
            default:
            break;
        }
    }
    //parsing values end

    free(buffer);
    fclose(config);
    return READ_SUCCESS;
}