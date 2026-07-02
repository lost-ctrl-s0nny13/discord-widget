#pragma once
#include <stdint.h>
#define CONFIG_MISSING 0b00000000000000000000000000000001U
#define MALLOC_ERROR   0b00000000000000000000000000000010U
#define READ_ERROR     0b00000000000000000000000000000100U
#define READ_SUCCESS   0b00000000000000000000000000000000U

typedef struct repo{
    char* url;
    char* description;
    char* icon_path;
}repo;

typedef struct config_parse_result{
    char* account_url;
    repo repositories[4];
    uint32_t repos_filled;
}t_cpr;

uint32_t config_read(t_cpr* result, char* config_path);
void config_free(t_cpr* result);