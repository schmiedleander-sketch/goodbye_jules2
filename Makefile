CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -shared -s
LDFLAGS = -lpsapi

MODS = \
	bin/mcd_godmode.dll \
	bin/mcd_emerald_gold_multiplier.dll \
	bin/mcd_unlimited_arrows.dll \
	bin/mcd_artifact_cooldown.dll \
	bin/mcd_speed_hack.dll \
	bin/mcd_one_hit_kill.dll \
	bin/mcd_drop_rate_booster.dll \
	bin/mcd_free_enchantment.dll \
	bin/mcd_free_vendor_restock.dll \
	bin/mcd_fov_camera_unlocker.dll \
	bin/mcd_mob_freeze_aura.dll \
	bin/mcd_auto_loot_collector.dll \
	bin/mcd_dev_console_unlocker.dll \
	bin/mcd_skip_mission_timer.dll \
	bin/mcd_custom_item_spawner.dll \
	bin/mcd_xp_multiplier.dll \
	bin/mcd_nightmare_difficulty.dll \
	bin/mcd_sound_visual_notifier.dll \
	bin/mcd_no_roll_cooldown.dll \
	bin/mcd_ue_tweak_loader.dll

SDK_SRCS = sdk/mcd_mod_sdk.c sdk/mcd_config.c

.PHONY: all clean directories

all: directories $(MODS)

directories:
	mkdir -p bin

bin/mcd_godmode.dll: src/mod01_godmode/godmode.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_emerald_gold_multiplier.dll: src/mod02_emerald_multiplier/emerald_multiplier.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_unlimited_arrows.dll: src/mod03_unlimited_arrows/unlimited_arrows.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_artifact_cooldown.dll: src/mod04_artifact_cooldown/artifact_cooldown.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_speed_hack.dll: src/mod05_speed_hack/speed_hack.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_one_hit_kill.dll: src/mod06_one_hit_kill/one_hit_kill.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_drop_rate_booster.dll: src/mod07_drop_rate_booster/drop_rate_booster.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_free_enchantment.dll: src/mod08_free_enchantment/free_enchantment.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_free_vendor_restock.dll: src/mod09_free_vendor_restock/free_vendor_restock.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_fov_camera_unlocker.dll: src/mod10_fov_camera_unlocker/fov_camera_unlocker.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_mob_freeze_aura.dll: src/mod11_mob_freeze_aura/mob_freeze_aura.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_auto_loot_collector.dll: src/mod12_auto_loot_collector/auto_loot_collector.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_dev_console_unlocker.dll: src/mod13_dev_console_unlocker/dev_console_unlocker.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_skip_mission_timer.dll: src/mod14_skip_mission_timer/skip_mission_timer.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_custom_item_spawner.dll: src/mod15_custom_item_spawner/custom_item_spawner.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_xp_multiplier.dll: src/mod16_xp_multiplier/xp_multiplier.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_nightmare_difficulty.dll: src/mod17_nightmare_difficulty/nightmare_difficulty.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_sound_visual_notifier.dll: src/mod18_sound_visual_notifier/sound_visual_notifier.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_no_roll_cooldown.dll: src/mod19_no_roll_cooldown/no_roll_cooldown.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/mcd_ue_tweak_loader.dll: src/mod20_ue_tweak_loader/ue_tweak_loader.c $(SDK_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf bin sdk/*.o
