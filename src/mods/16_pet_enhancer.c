/**
 * Mod 16: Pet & Companion Enhancer
 * Boosts companion wolves, bats, llamas, and golems with health, damage, and summon caps.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_pet_enhancer",
    "Companion & Pet Master Overhaul",
    "2.0.0",
    "MCD2Modder",
    "Triples pet health and damage output, and increases maximum active companion cap."
)

static float g_PetDamageMult = 3.0f;
static float g_PetHealthMult = 4.0f;
static int32_t g_MaxActiveCompanions = 10;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_ApplyPetBuffs(float* pet_damage, float* pet_health, int32_t* max_slots) {
    if (pet_damage) *pet_damage *= g_PetDamageMult;
    if (pet_health) *pet_health *= g_PetHealthMult;
    if (max_slots) *max_slots = g_MaxActiveCompanions;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
