#ifndef RANDOM_WARPS_H
#define RANDOM_WARPS_H

#define RANDOM_WARP_LIMIT 632
#define RANDOM_WARP_LIMIT_SEARCH_HIGH (RANDOM_WARP_LIMIT - 1)
#define RANDOM_WARP_LIMIT_SEARCH_MID (RANDOM_WARP_LIMIT / 2)
#define RANDOM_WARP_LIMIT_SEARCH_LOW 0

#include "gba/types.h"

void InterceptWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y);
void NewGameRandomWarpsInit();
void CorrectPositionAfterIntercept();
void resetPositionCorrection();

extern s8 xPositionCorrection;
extern s8 yPositionCorrection;

#endif // RANDOM_WARPS_H