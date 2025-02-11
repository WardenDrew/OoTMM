#include <combo.h>
#include <combo/item.h>
#include <combo/sr.h>

static void addHealth(u8 count)
{
    gSaveContext.healthDelta += count * 0x10;
}

static void refillMagic(int level)
{
    gSave.playerData.magicLevel = 0;
    gSave.playerData.magicAmount = level * 0x30;
    gSaveContext.magicFillTarget = level * 0x30;
}

static void addRupees(s16 count)
{
    gSaveContext.save.rupeesDelta += count;
}

static void reloadIconsC(GameState_Play* play)
{
    for (int i = 1; i < 4; i++)
        Interface_LoadItemIconImpl(play, i);
}

static void reloadHookshot(GameState_Play* play)
{
    Actor_Player* link;

    link = GET_LINK(play);
    link->state &= ~(PLAYER_ACTOR_STATE_HOLD_ITEM | PLAYER_ACTOR_STATE_USE_ITEM);
    reloadIconsC(play);
}

static void addSilverPouchRupees(int id)
{
    addRupees(gSilverRupeeData[id].count * 5);
}

static void addMagicalRupeeRupees(void)
{
    for (int i = 0; i < ARRAY_SIZE(gSilverRupeeData); i++)
        addSilverPouchRupees(i);
}

void comboAddItemSharedForeignEffect(GameState_Play* play, s16 gi)
{
    if (comboConfig(CFG_SHARED_WALLETS))
    {
        switch (gi)
        {
        case GI_OOT_RUPEE_GREEN:
        case GI_OOT_TC_RUPEE_GREEN:
            addRupees(1);
            break;
        case GI_OOT_RUPEE_BLUE:
        case GI_OOT_TC_RUPEE_BLUE:
        case GI_OOT_RUPEE_SILVER_DC:
        case GI_OOT_RUPEE_SILVER_BOTW:
        case GI_OOT_RUPEE_SILVER_SPIRIT_CHILD:
        case GI_OOT_RUPEE_SILVER_SPIRIT_SUN:
        case GI_OOT_RUPEE_SILVER_SPIRIT_BOULDERS:
        case GI_OOT_RUPEE_SILVER_SPIRIT_LOBBY:
        case GI_OOT_RUPEE_SILVER_SPIRIT_ADULT:
        case GI_OOT_RUPEE_SILVER_SHADOW_SCYTHE:
        case GI_OOT_RUPEE_SILVER_SHADOW_PIT:
        case GI_OOT_RUPEE_SILVER_SHADOW_SPIKES:
        case GI_OOT_RUPEE_SILVER_SHADOW_BLADES:
        case GI_OOT_RUPEE_SILVER_IC_SCYTHE:
        case GI_OOT_RUPEE_SILVER_IC_BLOCK:
        case GI_OOT_RUPEE_SILVER_GTG_SLOPES:
        case GI_OOT_RUPEE_SILVER_GTG_LAVA:
        case GI_OOT_RUPEE_SILVER_GTG_WATER:
        case GI_OOT_RUPEE_SILVER_GANON_SPIRIT:
        case GI_OOT_RUPEE_SILVER_GANON_LIGHT:
        case GI_OOT_RUPEE_SILVER_GANON_FIRE:
        case GI_OOT_RUPEE_SILVER_GANON_FOREST:
        case GI_OOT_RUPEE_SILVER_GANON_SHADOW:
        case GI_OOT_RUPEE_SILVER_GANON_WATER:
            addRupees(5);
            break;
        case GI_OOT_POUCH_SILVER_DC:
            addSilverPouchRupees(SR_DC);
            break;
        case GI_OOT_POUCH_SILVER_BOTW:
            addSilverPouchRupees(SR_BOTW);
            break;
        case GI_OOT_POUCH_SILVER_SPIRIT_CHILD:
            addSilverPouchRupees(SR_SPIRIT1);
            break;
        case GI_OOT_POUCH_SILVER_SPIRIT_SUN:
            addSilverPouchRupees(SR_SPIRIT2);
            break;
        case GI_OOT_POUCH_SILVER_SPIRIT_BOULDERS:
            addSilverPouchRupees(SR_SPIRIT3);
            break;
        case GI_OOT_POUCH_SILVER_SPIRIT_LOBBY:
            addSilverPouchRupees(SR_SPIRIT1);
            break;
        case GI_OOT_POUCH_SILVER_SPIRIT_ADULT:
            addSilverPouchRupees(SR_SPIRIT2);
            break;
        case GI_OOT_POUCH_SILVER_SHADOW_SCYTHE:
            addSilverPouchRupees(SR_SHADOW1);
            break;
        case GI_OOT_POUCH_SILVER_SHADOW_PIT:
            addSilverPouchRupees(SR_SHADOW3);
            break;
        case GI_OOT_POUCH_SILVER_SHADOW_SPIKES:
            addSilverPouchRupees(SR_SHADOW4);
            break;
        case GI_OOT_POUCH_SILVER_SHADOW_BLADES:
            addSilverPouchRupees(SR_SHADOW2);
            break;
        case GI_OOT_POUCH_SILVER_IC_SCYTHE:
            addSilverPouchRupees(SR_IC1);
            break;
        case GI_OOT_POUCH_SILVER_IC_BLOCK:
            addSilverPouchRupees(SR_IC2);
            break;
        case GI_OOT_POUCH_SILVER_GTG_SLOPES:
            addSilverPouchRupees(SR_GTG1);
            break;
        case GI_OOT_POUCH_SILVER_GTG_LAVA:
            addSilverPouchRupees(SR_GTG2);
            break;
        case GI_OOT_POUCH_SILVER_GTG_WATER:
            addSilverPouchRupees(SR_GTG3);
            break;
        case GI_OOT_POUCH_SILVER_GANON_SPIRIT:
            addSilverPouchRupees(SR_GANON1);
            break;
        case GI_OOT_POUCH_SILVER_GANON_LIGHT:
            addSilverPouchRupees(SR_GANON2);
            break;
        case GI_OOT_POUCH_SILVER_GANON_FIRE:
            addSilverPouchRupees(SR_GANON3);
            break;
        case GI_OOT_POUCH_SILVER_GANON_FOREST:
            addSilverPouchRupees(SR_GANON4);
            break;
        case GI_OOT_POUCH_SILVER_GANON_SHADOW:
            addSilverPouchRupees(SR_GANON1);
            break;
        case GI_OOT_POUCH_SILVER_GANON_WATER:
            addSilverPouchRupees(SR_GANON2);
            break;
        case GI_OOT_RUPEE_MAGICAL:
            addMagicalRupeeRupees();
            break;
        case GI_OOT_RUPEE_RED:
        case GI_OOT_TC_RUPEE_RED:
            addRupees(20);
            break;
        case GI_OOT_RUPEE_PURPLE:
        case GI_OOT_TC_RUPEE_PURPLE:
            addRupees(50);
            break;
        case GI_OOT_RUPEE_HUGE:
            addRupees(200);
            break;
        }
    }

    if (comboConfig(CFG_SHARED_HEALTH))
    {
        switch (gi)
        {
        case GI_OOT_RECOVERY_HEART:
            addHealth(1);
            break;
        case GI_OOT_HEART_PIECE:
        case GI_OOT_TC_HEART_PIECE:
        case GI_OOT_HEART_CONTAINER:
        case GI_OOT_HEART_CONTAINER2:
        case GI_OOT_DEFENSE_UPGRADE:
            addHealth(20);
            break;
        }
    }
}

int comboAddItemEffect(GameState_Play* play, s16 gi)
{
    int count;

    count = 0;
    switch (gi)
    {
    case GI_MM_SWORD_KOKIRI:
    case GI_MM_SWORD_RAZOR:
    case GI_MM_SWORD_GILDED:
        Interface_LoadItemIconImpl(play, 0);
        break;
    case GI_MM_PROGRESSIVE_SHIELD_HERO:
    case GI_MM_SHIELD_HERO:
    case GI_MM_SHIELD_MIRROR:
        UpdateEquipment(play, GET_LINK(play));
        break;
    case GI_MM_MAGIC_UPGRADE:
        refillMagic(1);
        break;
    case GI_MM_MAGIC_UPGRADE2:
        refillMagic(2);
        break;
    case GI_MM_RECOVERY_HEART:
        addHealth(1);
        break;
    case GI_MM_HEART_PIECE:
    case GI_MM_HEART_CONTAINER:
    case GI_MM_DEFENSE_UPGRADE:
        addHealth(20);
        break;
    case GI_MM_RUPEE_GREEN:
        addRupees(1);
        break;
    case GI_MM_RUPEE_BLUE:
        addRupees(5);
        break;
    case GI_MM_RUPEE_RED:
        addRupees(20);
        break;
    case GI_MM_RUPEE_PURPLE:
        addRupees(50);
        break;
    case GI_MM_RUPEE_SILVER:
        addRupees(100);
        break;
    case GI_MM_RUPEE_GOLD:
        addRupees(200);
        break;
    case GI_MM_STRAY_FAIRY:
        if (play->sceneId == SCE_MM_LAUNDRY_POOL || play->sceneId == SCE_MM_CLOCK_TOWN_EAST)
            count = comboAddStrayFairyMm(4);
        else
            count = comboAddStrayFairyMm(gSaveContext.dungeonId);
        break;
    case GI_MM_SMALL_KEY:
        count = comboAddSmallKeyMm(gSaveContext.dungeonId);
        break;
    case GI_MM_KEY_RING:
        comboAddKeyRingMm(gSaveContext.dungeonId);
        break;
    case GI_MM_BOSS_KEY:
        comboAddBossKeyMm(gSaveContext.dungeonId);
        break;
    case GI_MM_MAP:
        comboAddMapMm(gSaveContext.dungeonId);
        break;
    case GI_MM_COMPASS:
        comboAddCompassMm(gSaveContext.dungeonId);
        break;
    case GI_MM_POTION_RED:
    case GI_MM_POTION_BLUE:
    case GI_MM_POTION_GREEN:
    case GI_MM_SEAHORSE:
    case GI_MM_SEAHORSE2:
    case GI_MM_MILK:
    case GI_MM_CHATEAU:
    case GI_MM_OCARINA_OF_TIME:
    case GI_MM_FAIRY:
        reloadIconsC(play);
        break;
    case GI_MM_HOOKSHOT:
        reloadHookshot(play);
        break;
    }

    if (comboConfig(CFG_FILL_WALLETS))
    {
        switch (gi)
        {
        case GI_MM_WALLET:
        case GI_MM_WALLET2:
        case GI_MM_WALLET3:
        case GI_MM_WALLET4:
        case GI_MM_WALLET5:
            addRupees(gMmMaxRupees[gSave.inventory.upgrades.wallet]);
            break;
        }
    }

    return count;
}
