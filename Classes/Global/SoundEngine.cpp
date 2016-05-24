//
//  SoundEngine.cpp
//  MatchEmUp
//
//  Created by Fredric on 2/25/16.
//
//

#include "SoundEngine.hpp"
#include "Const.h"

SoundEngine* SoundEngine::sharedSoundEngine = NULL;

SoundEngine* SoundEngine::getInstance()
{
    srandom((int)time(NULL));
    if (sharedSoundEngine == NULL) {
        sharedSoundEngine = new SoundEngine();
    }
    return sharedSoundEngine;
}

SoundEngine::SoundEngine()
{
    
}
SoundEngine::~SoundEngine()
{
    
}

void SoundEngine::preloadSounds()
{
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_BACKGROUND);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_DONE);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FLIP);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MATCH);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_WOODPECKER);
}

void SoundEngine::playBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_BACKGROUND, true);
}

void SoundEngine::stopBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundEngine::muteBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
}

void SoundEngine::unMuteBackgoundMusic()
{
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
}

void SoundEngine::muteSoundEffect()
{
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
}

void SoundEngine::unMuteSoundEffect()
{
    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
}

void SoundEngine::playDoneEffect()
{
    SimpleAudioEngine::getInstance()->playEffect(EFFECT_DONE);
}

void SoundEngine::playFlipEffect()
{
    SimpleAudioEngine::getInstance()->playEffect(EFFECT_FLIP);
}

void SoundEngine::playMatchEffect()
{
    SimpleAudioEngine::getInstance()->playEffect(EFFECT_MATCH);
}

void SoundEngine::playWoodPeckerEffect()
{
    woodpecker_index = SimpleAudioEngine::getInstance()->playEffect(EFFECT_WOODPECKER, true);
}

void SoundEngine::stopWoodPeckerEffect()
{
    SimpleAudioEngine::getInstance()->stopEffect(woodpecker_index);
}

void SoundEngine::playItemSoundEffect(int pack, int index)
{
    char fileName[128];
    sprintf(fileName, "%ssnd%d_%02d.mp3", EFFECT_ITEM, pack + 1, index + 1);
    SimpleAudioEngine::getInstance()->playEffect(fileName);
}
