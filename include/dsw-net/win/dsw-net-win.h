#pragma once
#include <stdint.h>
#include "config_parse/config_parse.h"

typedef struct github_stats_result{
    int public_repos;
    int followers;
    int spr[4];//stars per repo
}t_gsr;

uint32_t fetch_github_stats(t_gsr* result, t_cpr* config);
uint32_t push_discord_widget(t_gsr* result, t_cpr* config);