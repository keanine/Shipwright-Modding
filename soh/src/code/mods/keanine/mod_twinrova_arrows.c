#include "z_boss_tw.h";

static int16_t KOTAKE = 0x00;
static int16_t KOUME = 0x01;

void TwinrovaArrows_CheckArrowCollision(BossTw* this, BossTw* sKoumePtr, BossTw* sKotakePtr);
static void TwinrovaArrows_HitCorrect(BossTw* this);
static void TwinrovaArrows_HitIncorrect(BossTw* this);

void TwinrovaArrows_CheckArrowCollision(BossTw* this, BossTw* sKoumePtr, BossTw* sKotakePtr) {
    ColliderInfo* info = this->collider.info.acHitInfo;

    if (this->actor.params == KOTAKE) {
        if (info->toucher.dmgFlags & DMG_ARROW_FIRE) {
            osSyncPrintf("[MOD] KOTAKE HIT WITH FIRE ARROW");
            TwinrovaArrows_HitCorrect(this);

        } else if (info->toucher.dmgFlags & DMG_ARROW_ICE) {
            TwinrovaArrows_HitIncorrect(this);
        }

    } else if (this->actor.params == KOUME) {
        if (info->toucher.dmgFlags & DMG_ARROW_ICE) {
            osSyncPrintf("[MOD] KOTAKE HIT WITH ICE ARROW");
            TwinrovaArrows_HitCorrect(this);

        } else if (info->toucher.dmgFlags & DMG_ARROW_FIRE) {
            TwinrovaArrows_HitIncorrect(this);
        }
    }

    //if ((sKoumePtr->actor.colChkInfo.health + sKotakePtr->actor.colChkInfo.health) >= 4) {
    //    // BossTw_SetupWait(this, play);
    //}
}

static void TwinrovaArrows_HitCorrect(BossTw* this) {
    osSyncPrintf("[MOD] KOTAKE HIT WITH FIRE ARROW");
    if (this->actor.colChkInfo.health < 2) {
        this->actor.colChkInfo.health = 2;
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_HIT_SOUND);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_DAMAGE_VOICE);
}

static void TwinrovaArrows_HitIncorrect(BossTw* this) {
    Audio_PlayActorSound2(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
    if (this->actor.params == KOTAKE) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_LAUGH);
    } else if (this->actor.params == KOUME) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_LAUGH2);
    }
}