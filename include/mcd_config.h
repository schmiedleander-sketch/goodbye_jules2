#ifndef MCD_CONFIG_H
#define MCD_CONFIG_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char key[64];
    char value[128];
} MCD_ConfigEntry;

typedef struct {
    MCD_ConfigEntry entries[32];
    size_t count;
} MCD_Config;

bool MCD_Config_Load(MCD_Config* cfg, const char* filepath);
bool MCD_Config_Save(const MCD_Config* cfg, const char* filepath);
const char* MCD_Config_GetString(const MCD_Config* cfg, const char* key, const char* default_val);
int MCD_Config_GetInt(const MCD_Config* cfg, const char* key, int default_val);
float MCD_Config_GetFloat(const MCD_Config* cfg, const char* key, float default_val);
bool MCD_Config_GetBool(const MCD_Config* cfg, const char* key, bool default_val);
void MCD_Config_SetString(MCD_Config* cfg, const char* key, const char* val);
void MCD_Config_SetInt(MCD_Config* cfg, const char* key, int val);
void MCD_Config_SetFloat(MCD_Config* cfg, const char* key, float val);
void MCD_Config_SetBool(MCD_Config* cfg, const char* key, bool val);

#endif /* MCD_CONFIG_H */
