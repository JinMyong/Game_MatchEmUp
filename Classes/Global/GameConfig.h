//
//  GameConfig.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#ifndef __GameConfig__
#define __GameConfig__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameBridge.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define TEXT_GRAYCOLOR Color3B(102, 102, 102)
#define TEXT_BROWNCOLOR Color3B(96, 0, 0)
#define TEXT_YELLOWCOLOR Color3B(254, 212, 0)
typedef struct LevelLayout
{
    int nW;
    int nH;
    int nX0;
    int nY0;
    int nXGap;
    int nYGap;
    float fTScale;
}LevelLayout;

extern LevelLayout g_llGame[6];

extern int g_nPack;
extern int g_nLevel;

extern bool g_optionScenebackisMain;

void loadGameInfo();
void saveGameInfo();

int getCurrentTime();
#endif
