#include "config_parse/config_parse.h")
#include <stdio.h>
#include <malloc.h>
#include <string.h>

char* extract_value(void* buffer, long start, long end){
    size_t size = (size_t)(end - start);
    char* ret_value = (char*)malloc(size + 1);
    if(ret_value == NULL) return NULL;
    memcpy(ret_value, (char*)buffer + start, size);
    ret_value[size] = '\0';
    return ret_value;
}

uint32_t config_read(t_cpr* result, char* config_path){
    memset(result, 0x00, sizeof(t_cpr));
    FILE* config = fopen(config_path, "rb");
    if(config == NULL){
        return CONFIG_MISSING;
    }
    fseek(config, 0, SEEK_END);
    long filesize = ftell(config);
    rewind(config);
    void* buffer = malloc((filesize + 1) * sizeof(char));
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
    int expr_found = 0;
    for(long i = 0; i < filesize; ++i){
        if(((char*)buffer)[i] == '='){
            if(result->repos_filled == 4){
                free(buffer);
                return CONFIG_ERROR;
            }
            ++expr_count;
            expr_found = 1;
        }
        if(expr_found == 1)
        switch(expr_count){
            case 1:
            if((result->account_url = extract_value(buffer, i+1, semicolon_index[0])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 2:
            if((result->icon_placeholder_url = extract_value(buffer, i+1, semicolon_index[1])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 3:
            if((result->repositories[0].url = extract_value(buffer, i+1, semicolon_index[2])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 4:
            if((result->repositories[0].description = extract_value(buffer, i+1, semicolon_index[3])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 5:
            if((result->repositories[0].icon_path = extract_value(buffer, i+1, semicolon_index[4])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            ++(result->repos_filled);
            expr_found = 0;
            break;
            case 6:
            if((result->repositories[1].url = extract_value(buffer, i+1, semicolon_index[5])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 7:
            if((result->repositories[1].description = extract_value(buffer, i+1, semicolon_index[6])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 8:
            if((result->repositories[1].icon_path = extract_value(buffer, i+1, semicolon_index[7])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            ++(result->repos_filled);
            expr_found = 0;
            break;
            case 9:
            if((result->repositories[2].url = extract_value(buffer, i+1, semicolon_index[8])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 10:
            if((result->repositories[2].description = extract_value(buffer, i+1, semicolon_index[9])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 11:
            if((result->repositories[2].icon_path = extract_value(buffer, i+1, semicolon_index[10])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            ++(result->repos_filled);
            expr_found = 0;
            break;
            case 12:
            if((result->repositories[3].url = extract_value(buffer, i+1, semicolon_index[11])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 13:
            if((result->repositories[3].description = extract_value(buffer, i+1, semicolon_index[12])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            expr_found = 0;
            break;
            case 14:
            if((result->repositories[3].icon_path = extract_value(buffer, i+1, semicolon_index[13])) == NULL){
                free(buffer);
                return MALLOC_ERROR;
            }
            ++(result->repos_filled);
            expr_found = 0;
            break;
            default:
            expr_found = 0;
            break;
            
        }
    }
    //parsing values end

    free(buffer);
    return READ_SUCCESS;
}

void config_free(t_cpr *result){
    free(result->account_url);
    result->account_url = NULL;
    free(result->icon_placeholder_url);
    result->icon_placeholder_url = NULL;
    for(int i = 0; i < 4; ++i){
        free(result->repositories[i].url);
        result->repositories[i].url = NULL;
        free(result->repositories[i].description);
        result->repositories[i].description = NULL;
        free(result->repositories[i].icon_path);
        result->repositories[i].icon_path = NULL;
    }
}