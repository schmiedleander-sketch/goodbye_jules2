#include "mcd_config.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(void) {
    printf("[*] Running MCD Config Unit Tests...\n");

    MCD_Config cfg;
    bool loaded = MCD_Config_Load(&cfg, "configs/godmode.ini");
    assert(loaded == true);
    assert(cfg.count > 0);

    bool godmode_enabled = MCD_Config_GetBool(&cfg, "enabled", false);
    assert(godmode_enabled == true);
    int godmode_hotkey = MCD_Config_GetInt(&cfg, "hotkey_vk", 0);
    assert(godmode_hotkey == 112);

    /* Test Speed Hack config */
    loaded = MCD_Config_Load(&cfg, "configs/speed_hack.ini");
    assert(loaded == true);
    float speed = MCD_Config_GetFloat(&cfg, "speed_multiplier", 1.0f);
    assert(speed > 2.0f);

    /* Test modifying and saving */
    MCD_Config_SetFloat(&cfg, "speed_multiplier", 3.75f);
    assert(MCD_Config_GetFloat(&cfg, "speed_multiplier", 1.0f) == 3.75f);

    /* Test drop rate booster config */
    loaded = MCD_Config_Load(&cfg, "configs/drop_rate_booster.ini");
    assert(loaded == true);
    float unique_rate = MCD_Config_GetFloat(&cfg, "unique_drop_rate", 0.0f);
    assert(unique_rate == 1.00f);
    bool max_slots = MCD_Config_GetBool(&cfg, "always_max_slots", false);
    assert(max_slots == true);

    printf("[+] All MCD Config Unit Tests Passed Successfully!\n");
    return 0;
}
