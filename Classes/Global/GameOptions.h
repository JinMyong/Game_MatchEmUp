//
//  GameOptions.hpp
//  MatchEmUp
//
//  Created by Fredric on 2/25/16.
//
//

#ifndef GameOptions_hpp
#define GameOptions_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Const.h"

#define SCORECOUNT  3

using namespace cocos2d;
using namespace std;

class GameOptions{
private:
    static GameOptions* instance;
    UserDefault* m_userdefault;
    float timerIndicator;
    bool isBackgroundMusic;
    bool isTileSoundEffect;
    bool isAnimalSoundEffect;
    bool isTileName;
    bool isShowImage;
    int  animalPack;
    int  gameLevel;
    
    int nameCount;
    string lastUsedName;
    string currentName;
    string firstUserName;
    string secondUserName;
    
    int m_firstUserFlips;
    int m_secondUserFlips;
    int m_tiles;
    float m_firstAccur;
    float m_secondAccur;
    string m_gameTime;
    
    int m_firstPlayerScore;
    int m_secondPlayerScore;
    
    int m_firstMatches;
    int m_secontMatches;
    
    std::vector<std::string> nameList;
    
    int playerHighScores[SCORECOUNT];
    int allHighScores[SCORECOUNT];
    
    int m_backgroundIndex;
    int m_tileCoverIndex;
    
    bool m_isPurchased;
    
public:
    GameOptions();
    ~GameOptions();
    
    static GameOptions* getInstance();
    
    float  getTimerIndicate();
    bool getBackgroundMusicOption();
    bool getTileSoundEffectOption();
    bool getAnimalSoundEffectOption();
    bool getTileNameOption();
    bool getShowImageOption();
    int  getGameLevel();
    int  getAnimalPack();
    int  getNameCount();
    string getLastUsedName();
    std::vector<std::string> getNameList();
    
    string getFirstUserName();
    int getFirstPlayerScore();
    int getFirstUserFlips();
    float getFirstAccuracy();
    int getFirstMatches();
    
    string getSecondUserName();
    int getSecondPlayerScore();
    int getSecondUserFlips();
    float getSecondAccuracy();
    int getSecondMatches();
    
    string getGameTime();
    int getGameDifficulty();
    int* getPlayerHighScores();
    int* getAllHighScores();
    
    
    bool isPurchasedAnimal(int animalSet);
    bool isPurchasedCount(int count);
    
    int getBackgroundIndex();
    int getTileCoverIndex();
    bool getPurchased();
    
// -------------------------------------------------- //
    
    void setTimerInstance(float value);
    void setBackgroundMusicOption(bool value);
    void setTileSoundEffectOption(bool value);
    void setAnimalSoundEffectOption(bool value);
    void setTileNameOption(bool value);
    void setShowImageOption(bool value);
    void setGameLevel(int value);
    void setAnimalPack(int value);
    
    void setNameCount(int value);
    
    void addUserName(const char* name);
    void removeUserName(int index);
    void setLastUsedName(const char* name);
    
    void setFirstUserName(const char* name);
    void setFirstAccuracy(float value);
    void setFirstPlayerScore(int value);
    void setFirstPlayerFlips(int value);
    void setFirstMatches(int value);
    
    void setSecondPlayerName(const char* name);
    void setSecondPlayerFlips(int value);
    void setSecondMatches(int value);
    
    void setGameDifficulty(int value);
    void setGameTime(string value);
    void setHighScore(int value);
    
    void setPurchasedAnimal(int animalSet);
    void setPurchasedCount(int count);
    
    void setBackgroundIndex(int value);
    void setTileCoverIndex(int value);
    void setPurchased(bool value);
// -------------------------------------------------- //
    
    void syncNameList();
    void sortNameList();
    bool isDuplicateName(const char* name);
    bool isMultiPlayerMode();
    
};


#endif /* GameOptions_hpp */
