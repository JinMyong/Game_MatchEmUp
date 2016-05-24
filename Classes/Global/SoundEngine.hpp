//
//  SoundEngine.hpp
//  MatchEmUp
//
//  Created by Fredric on 2/25/16.
//
//

#ifndef SoundEngine_hpp
#define SoundEngine_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class SoundEngine{
private:
    static SoundEngine* sharedSoundEngine;
    int woodpecker_index;
public:
    SoundEngine();
    ~SoundEngine();
    static SoundEngine* getInstance();
    
    void preloadSounds();
    
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void muteBackgroundMusic();
    void unMuteBackgoundMusic();
    
    void muteSoundEffect();
    void unMuteSoundEffect();
    void playDoneEffect();
    void playFlipEffect();
    void playMatchEffect();
    void playWoodPeckerEffect();
    void stopWoodPeckerEffect();
    void playItemSoundEffect(int pack, int index);
};

#endif /* SoundEngine_hpp */
