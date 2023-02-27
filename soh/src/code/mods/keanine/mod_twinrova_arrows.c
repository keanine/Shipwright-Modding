#include "z_boss_tw.h";

void CheckArrowCollision(BossTw* this);

void CheckArrowCollision(BossTw* this, BossTw* sKoumePtr, BossTw* sKotakePtr) {
    ColliderInfo* info = this->collider.info.acHitInfo;
    if (this->actor.params == TW_KOTAKE) {
        if (info->toucher.dmgFlags & DMG_ARROW_FIRE) {
            osSyncPrintf("[MOD] KOTAKE HIT WITH FIRE ARROW");
            if (this->actor.colChkInfo.health < 2) {
                this->actor.colChkInfo.health = 2;
            }
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_DAMAGE_VOICE);
        }
    } else if (this->actor.params == TW_KOUME) {
        if (info->toucher.dmgFlags & DMG_ARROW_ICE) {
            osSyncPrintf("[MOD] KOTAKE HIT WITH ICE ARROW");
            if (this->actor.colChkInfo.health < 2) {
                this->actor.colChkInfo.health = 2;
            }
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_TWINROBA_DAMAGE_VOICE);
        }
    }

    if ((sKoumePtr->actor.colChkInfo.health + sKotakePtr->actor.colChkInfo.health) >= 4) {
        // BossTw_SetupWait(this, play);
    }
}