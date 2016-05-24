//
//  GameConfig.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#include "GameConfig.h"


bool g_bSound=true;

LevelLayout g_llGame[6] =
{
    //W, H, X0, Y0, XGap, YGap, fTScale
    {4, 2, 270, 1197, 503, 543, 1},
    {4, 3, 270, 946, 503, 541, 1},
    {4, 4, 345, 830, 453, 437, 0.9f},
    {5, 4, 224, 877, 400, 406, 0.8f},
    {6, 4, 185, 921, 336, 354, 0.6f},
    {8, 6, 161, 750, 246, 295, 0.5f}
};
int g_nPack = 0;
int g_nLevel = 0;

bool g_optionScenebackisMain = true;

void loadGameInfo(){
//    SimpleAudioEngine::getInstance()->preloadEffect("res/Musics/shining_time.mp3");
    
//    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
//    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
    
//    productParValueIdx=UserDefault::getInstance()->getIntegerForKey("ClickLevel",productParValueIdx);
}

void saveGameInfo(){
//    UserDefault::getInstance()->setIntegerForKey("ClickLevel",productParValueIdx);
}

int getCurrentTime(){
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int crtTime = now->tm_mon*(30*24*3600)+now->tm_mday*(24*3600)+now->tm_hour*3600+now->tm_min*60+now->tm_sec;

    return crtTime;

    //    return now->tm_gmtoff;// crtTime;
}
