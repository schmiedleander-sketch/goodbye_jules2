/**
 * Mod 17: Weather & Atmosphere Override
 * Locks camp / mission weather, skybox ambiance, and day-night cycle parameters.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_weather_time_override",
    "Weather & Atmosphere Controller",
    "2.0.0",
    "MCD2Modder",
    "Locks camp lighting, disables blinding fog, and sets custom sun/moon ambiance."
)

typedef enum {
    MCD2_WEATHER_CLEAR = 0,
    MCD2_WEATHER_RAIN = 1,
    MCD2_WEATHER_THUNDER = 2,
    MCD2_WEATHER_SNOW = 3
} MCD2_WeatherType;

static MCD2_WeatherType g_Weather = MCD2_WEATHER_CLEAR;
static float g_TimeOfDay = 12.0f; // Noon
static bool g_FogDisabled = true;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_SetWeather(MCD2_WeatherType type, float time_of_day, bool disable_fog) {
    g_Weather = type;
    g_TimeOfDay = time_of_day;
    g_FogDisabled = disable_fog;
}

MCD2_API void MCD2_GetAtmosphere(MCD2_WeatherType* type, float* time_of_day, bool* fog) {
    if (type) *type = g_Weather;
    if (time_of_day) *time_of_day = g_TimeOfDay;
    if (fog) *fog = g_FogDisabled;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
