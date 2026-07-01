#pragma once
#include <stdint.h>
#define JSON_MISSING 0b00000000000000000000000000000001U
#define MALLOC_ERROR 0b00000000000000000000000000000010U
#define READ_SUCCESS 0b00000000000000000000000000000000U

#define ICON_PLACEHOLDER ""

typedef struct repo{
    char* url;
    char* description;
    char* icon_path;
}repo;

typedef struct json_parse_result{
    char* account_url;
    repo repositories[4];
    uint32_t repos_filled;
}t_jpr;

uint32_t json_read(t_jpr* result, char* config_path);
void json_free(t_jpr* result);