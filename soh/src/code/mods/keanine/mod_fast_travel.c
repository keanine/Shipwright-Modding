#include <z64.h>
#include "global.h"
#include "mod_fast_travel.h"

s16 gFastTravelEnabled = false;

void MOD_FastTravel_SetEntrance(s16 nextEntranceIndex) {
    gPlayState->sceneLoadFlag = 0x14;
    gPlayState->fadeTransition = 0x05;
    gPlayState->nextEntranceIndex = nextEntranceIndex;

    // gSaveContext.cutsceneIndex = 0;
    // gSaveContext.nextTransitionType = 0x03;
    //  gSaveContext.respawnFlag = -1; // Warp Sound on spawn

    if (gSaveContext.gameMode != 0) {
        // During DHWW the cutscene must play at the destination
        gSaveContext.respawnFlag = -3;
    } else if (gSaveContext.respawnFlag == -3) {
        // Unset Zoneout Type -3 to avoid cutscene at destination (technically it's not needed)
        gSaveContext.respawnFlag = 0;
    }
}

void MOD_FastTravel_TryTravel(PauseContext* pauseCtx, Input* input) {
    if (gFastTravelEnabled && CHECK_BTN_ALL(input->press.button, BTN_A)) {
        s16 entranceIndex;
        switch (pauseCtx->cursorPoint[PAUSE_WORLD_MAP]) {
            case 0:
                entranceIndex = 0x0130; // Haunted Wasteland
                break;
            case 1:
                entranceIndex = 0x0129; // Gerudo Fortress
                break;
            case 2:
                entranceIndex = 0x0117; // Gerudo Valley
                break;
            case 3:
                entranceIndex = 0x0102; // Lake Hylia
                break;
            case 4:
                entranceIndex = 0x0157; // Lon Lon Ranch
                break;
            case 5:
                entranceIndex = 0x00B1; // Castle Town Market
                break;
            case 6:
                entranceIndex = 0x00CD; // Hyrule Field
                break;
            case 7:
                // entranceIndex = 0x0147; // Death Mountain Crater
                entranceIndex = 0x014D; // Death Mountain (Goron City)
                break;
            case 8:
                entranceIndex = 0x00DB; // Kakariko Village
                break;
            case 9:
                entranceIndex = 0x011E; // Lost Woods
                break;
            case 10:
                entranceIndex = 0x0211; // Kokiri Forest
                break;
            case 11:
                entranceIndex = 0x0108; // Zora's Domain
                break;
            default:
                entranceIndex = 0x011E; // Lost Woods? how did you get here??
                break;
        }

        // Open/Close Menu. Correctly resets sounds
        func_800F64E0(0);
        //Audio_PlaySoundGeneral(NA_SE_SY_DECIDE, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);

        MOD_FastTravel_SetEntrance(entranceIndex);
    }
}

void MOD_FastTravel_EnableAButtonForMapScreen(u16 pauseScreenType) {
    if (gFastTravelEnabled && (pauseScreenType == PAUSE_MAP)) {
        gSaveContext.buttonStatus[4] = BTN_ENABLED;
    }
}
