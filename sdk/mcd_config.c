#include "mcd_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool MCD_Config_Load(MCD_Config* cfg, const char* filepath) {
    if (!cfg || !filepath) return false;
    cfg->count = 0;

    FILE* f = fopen(filepath, "r");
    if (!f) return false;

    char line[256];
    while (fgets(line, sizeof(line), f) && cfg->count < 32) {
        char* hash = strchr(line, '#');
        if (hash) *hash = '\0';
        char* semi = strchr(line, ';');
        if (semi) *semi = '\0';

        char* eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char* k = line;
        char* v = eq + 1;

        while (isspace((unsigned char)*k)) k++;
        char* kend = k + strlen(k) - 1;
        while (kend > k && isspace((unsigned char)*kend)) { *kend = '\0'; kend--; }

        while (isspace((unsigned char)*v)) v++;
        char* vend = v + strlen(v) - 1;
        while (vend > v && isspace((unsigned char)*vend)) { *vend = '\0'; vend--; }

        if (strlen(k) > 0) {
            strncpy(cfg->entries[cfg->count].key, k, sizeof(cfg->entries[cfg->count].key) - 1);
            cfg->entries[cfg->count].key[sizeof(cfg->entries[cfg->count].key) - 1] = '\0';

            strncpy(cfg->entries[cfg->count].value, v, sizeof(cfg->entries[cfg->count].value) - 1);
            cfg->entries[cfg->count].value[sizeof(cfg->entries[cfg->count].value) - 1] = '\0';

            cfg->count++;
        }
    }
    fclose(f);
    return true;
}

bool MCD_Config_Save(const MCD_Config* cfg, const char* filepath) {
    if (!cfg || !filepath) return false;
    FILE* f = fopen(filepath, "w");
    if (!f) return false;

    for (size_t i = 0; i < cfg->count; i++) {
        fprintf(f, "%s=%s\n", cfg->entries[i].key, cfg->entries[i].value);
    }
    fclose(f);
    return true;
}

const char* MCD_Config_GetString(const MCD_Config* cfg, const char* key, const char* default_val) {
    if (!cfg || !key) return default_val;
    for (size_t i = 0; i < cfg->count; i++) {
        if (strcmp(cfg->entries[i].key, key) == 0) {
            return cfg->entries[i].value;
        }
    }
    return default_val;
}

int MCD_Config_GetInt(const MCD_Config* cfg, const char* key, int default_val) {
    const char* val = MCD_Config_GetString(cfg, key, NULL);
    if (!val) return default_val;
    return atoi(val);
}

float MCD_Config_GetFloat(const MCD_Config* cfg, const char* key, float default_val) {
    const char* val = MCD_Config_GetString(cfg, key, NULL);
    if (!val) return default_val;
    return (float)atof(val);
}

bool MCD_Config_GetBool(const MCD_Config* cfg, const char* key, bool default_val) {
    const char* val = MCD_Config_GetString(cfg, key, NULL);
    if (!val) return default_val;
    if (strcmp(val, "true") == 0 || strcmp(val, "1") == 0 || strcmp(val, "yes") == 0) return true;
    if (strcmp(val, "false") == 0 || strcmp(val, "0") == 0 || strcmp(val, "no") == 0) return false;
    return default_val;
}

void MCD_Config_SetString(MCD_Config* cfg, const char* key, const char* val) {
    if (!cfg || !key || !val) return;
    for (size_t i = 0; i < cfg->count; i++) {
        if (strcmp(cfg->entries[i].key, key) == 0) {
            strncpy(cfg->entries[i].value, val, sizeof(cfg->entries[i].value) - 1);
            cfg->entries[i].value[sizeof(cfg->entries[i].value) - 1] = '\0';
            return;
        }
    }
    if (cfg->count < 32) {
        strncpy(cfg->entries[cfg->count].key, key, sizeof(cfg->entries[cfg->count].key) - 1);
        cfg->entries[cfg->count].key[sizeof(cfg->entries[cfg->count].key) - 1] = '\0';
        strncpy(cfg->entries[cfg->count].value, val, sizeof(cfg->entries[cfg->count].value) - 1);
        cfg->entries[cfg->count].value[sizeof(cfg->entries[cfg->count].value) - 1] = '\0';
        cfg->count++;
    }
}

void MCD_Config_SetInt(MCD_Config* cfg, const char* key, int val) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", val);
    MCD_Config_SetString(cfg, key, buf);
}

void MCD_Config_SetFloat(MCD_Config* cfg, const char* key, float val) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f", val);
    MCD_Config_SetString(cfg, key, buf);
}

void MCD_Config_SetBool(MCD_Config* cfg, const char* key, bool val) {
    MCD_Config_SetString(cfg, key, val ? "true" : "false");
}
