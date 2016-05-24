//
//  GameOptions.cpp
//  MatchEmUp
//
//  Created by Fredric on 2/25/16.
//
//

#include "GameOptions.h"
#include "SoundEngine.hpp"
#include "GameConfig.h"

GameOptions* GameOptions::instance = NULL;

GameOptions* GameOptions::getInstance()
{
    if (instance == NULL) {
        instance = new GameOptions();
    }
    return instance;
}
GameOptions::GameOptions()
{
    m_userdefault = UserDefault::getInstance();
    timerIndicator = m_userdefault->getFloatForKey(kTimerTiles, 1.0f);
    isBackgroundMusic = m_userdefault->getBoolForKey(kBackgroundMusic, false);
    isTileSoundEffect = m_userdefault->getBoolForKey(kTileSoundEffect, false);
    isAnimalSoundEffect = m_userdefault->getBoolForKey(kAnimalSoundEffect, true);
    isTileName = m_userdefault->getBoolForKey(kShowTileName, true);
    isShowImage = m_userdefault->getBoolForKey(kShowImageAfterFlip, false);
    animalPack = m_userdefault->getIntegerForKey(kAnimalPack, 0);
    gameLevel = m_userdefault->getIntegerForKey(kGameLevel, 0);
    
    m_tiles = g_llGame[g_nLevel].nW * g_llGame[g_nLevel].nH;
//    m_tiles = 8;
    
    nameCount = m_userdefault->getIntegerForKey(kNameCount, 0);
    lastUsedName = m_userdefault->getStringForKey(kLastUsedName, "");
    m_backgroundIndex = m_userdefault->getIntegerForKey(kBackgroundIndex, 0);
    m_tileCoverIndex = m_userdefault->getIntegerForKey(kTileCoverIndex, 0);
    
    m_isPurchased = m_userdefault->getBoolForKey(kIsPurchased, false);
    
    m_userdefault->setBoolForKey(StringUtils::format("%s%d", kPurchaseAnimal, 0).c_str(), true);
    m_userdefault->setBoolForKey(StringUtils::format("%s%d", kPurchaseCount, 0).c_str(), true);
    
    for (int i = 0 ; i < nameCount; i++) {
        string name = m_userdefault->getStringForKey(StringUtils::format("%s%d",kNameList, i).c_str());
        nameList.push_back(name);
    }
    
    for (int i = 1; i < 6; i++) {
        m_userdefault->setBoolForKey(StringUtils::format("%s%d", kPurchaseAnimal, i).c_str(), false);
    }
    
// -------------------------------------------- //
    
    if (isBackgroundMusic) {
        SoundEngine::getInstance()->unMuteBackgoundMusic();
    }else
    {
        SoundEngine::getInstance()->muteBackgroundMusic();
    }
}

#pragma mark - Get Methods

float GameOptions::getTimerIndicate(){
    return timerIndicator;
}
bool GameOptions::getBackgroundMusicOption(){
    return isBackgroundMusic;
}
bool GameOptions::getTileSoundEffectOption(){
    return isTileSoundEffect;
}
bool GameOptions::getAnimalSoundEffectOption(){
    return isAnimalSoundEffect;
}
bool GameOptions::getTileNameOption(){
    return isTileName;
}

bool GameOptions::getShowImageOption()
{
    return isShowImage;
}

int GameOptions::getGameLevel()
{
    return gameLevel;
}

int GameOptions::getAnimalPack()
{
    return animalPack;
}

int GameOptions::getNameCount()
{
    nameCount = UserDefault::getInstance()->getIntegerForKey(kNameCount, 0);
    return nameCount;
}

string GameOptions::getLastUsedName()
{
    return lastUsedName;
}

std::vector<std::string> GameOptions::getNameList()
{
    return nameList;
}

string GameOptions::getFirstUserName()
{
    return firstUserName;
}

string GameOptions::getSecondUserName()
{
    return secondUserName;
}

int GameOptions::getFirstUserFlips()
{
    return m_firstUserFlips;
}

int GameOptions::getSecondUserFlips()
{
    return m_secondUserFlips;
}

int GameOptions::getGameDifficulty()
{
    return m_tiles;
}

float GameOptions::getFirstAccuracy()
{
    return m_firstAccur;
}

float GameOptions::getSecondAccuracy()
{
    return m_secondAccur;
}

string GameOptions::getGameTime()
{
    return m_gameTime;
}

int GameOptions::getFirstPlayerScore()
{
    return m_firstPlayerScore;
}

int GameOptions::getSecondPlayerScore()
{
    return m_secondPlayerScore;
}

int* GameOptions::getPlayerHighScores()
{
    string username = getFirstUserName();
    for (int i = 0; i < SCORECOUNT; i++) {
        string key = StringUtils::format("%s_%d", username.c_str(), i);
        playerHighScores[i] = m_userdefault->getIntegerForKey(key.c_str(), 0);
    }
    return playerHighScores;
}

int* GameOptions::getAllHighScores()
{
    UserDefault* userdefault = UserDefault::getInstance();
    for (int i = 0; i < SCORECOUNT; i++) {
        string key = StringUtils::format("%s%d", kHighScore, i);
        allHighScores[i] = userdefault->getIntegerForKey(key.c_str(), 0);
    }
    return allHighScores;
}

int GameOptions::getFirstMatches()
{
    return m_firstMatches;
}

int GameOptions::getSecondMatches()
{
    return m_secontMatches;
}

int GameOptions::getBackgroundIndex()
{
    return m_backgroundIndex;
}

int GameOptions::getTileCoverIndex()
{
    return m_tileCoverIndex;
}

bool GameOptions::isPurchasedAnimal(int animalSet)
{
    string key = StringUtils::format("%s%d", kPurchaseAnimal, animalSet);
    return m_userdefault->getBoolForKey(key.c_str(), false);
}

bool GameOptions::isPurchasedCount(int count)
{
    string key = StringUtils::format("%s%d", kPurchaseAnimal, count);
    return m_userdefault->getBoolForKey(key.c_str(), false);
}

bool GameOptions::getPurchased()
{
    return m_isPurchased;
}

#pragma mark - Set Methods

void GameOptions::setTimerInstance(float value)
{
    timerIndicator = value;
    UserDefault::getInstance()->setIntegerForKey(kTimerTiles, timerIndicator);
}

void GameOptions::setBackgroundMusicOption(bool value){
    isBackgroundMusic = value;
    UserDefault::getInstance()->setBoolForKey(kBackgroundMusic, isBackgroundMusic);
    
    if (isBackgroundMusic) {
        SoundEngine::getInstance()->unMuteBackgoundMusic();
    }else
    {
        SoundEngine::getInstance()->muteBackgroundMusic();
    }
}

void GameOptions::setTileSoundEffectOption(bool value){
    isTileSoundEffect = value;
    UserDefault::getInstance()->setBoolForKey(kTileSoundEffect, isTileSoundEffect);
}

void GameOptions::setAnimalSoundEffectOption(bool value){
    isAnimalSoundEffect = value;
    UserDefault::getInstance()->setBoolForKey(kAnimalSoundEffect, isAnimalSoundEffect);
}

void GameOptions::setTileNameOption(bool value){
    isTileName = value;
    UserDefault::getInstance()->setBoolForKey(kShowTileName, isTileName);
}

void GameOptions::setShowImageOption(bool value)
{
    isShowImage = value;
    UserDefault::getInstance()->setBoolForKey(kShowImageAfterFlip, isShowImage);
}

void GameOptions::setAnimalPack(int value)
{
    animalPack = value;
    UserDefault::getInstance()->setIntegerForKey(kAnimalPack, animalPack);
}

void GameOptions::setGameLevel(int value)
{
    gameLevel = value;
    UserDefault::getInstance()->setIntegerForKey(kGameLevel, gameLevel);
}

void GameOptions::setNameCount(int value)
{
    nameCount = value;
    UserDefault::getInstance()->setIntegerForKey(kNameCount, nameCount);
}

void GameOptions::setLastUsedName(const char *name)
{
    lastUsedName = name;
    UserDefault::getInstance()->setStringForKey(kLastUsedName, lastUsedName.c_str());
}

void GameOptions::setFirstUserName(const char *name)
{
    firstUserName = name;
}

void GameOptions::setSecondPlayerName(const char *name)
{
    secondUserName = name;
}

void GameOptions::setFirstPlayerFlips(int value)
{
    m_firstUserFlips = value;
}

void GameOptions::setSecondPlayerFlips(int value)
{
    m_secondUserFlips = value;
}

void GameOptions::setGameDifficulty(int value)
{
    m_tiles = value;
}

void GameOptions::setFirstAccuracy(float value)
{
    m_firstAccur = value;
}

void GameOptions::setGameTime(string value)
{
    m_gameTime = value;
}

void GameOptions::setFirstPlayerScore(int value)
{
    m_firstPlayerScore = value;
}

void GameOptions::setHighScore(int value)
{
    int phighScore[SCORECOUNT];
    int ahighScore[SCORECOUNT];
    string username = getFirstUserName();
    UserDefault* userdefault = UserDefault::getInstance();
    
    // Read high scores of current user.
    for (int i = 0; i < SCORECOUNT; i++) {
        string key = StringUtils::format("%s_%d", username.c_str(), i);
        phighScore[i] = userdefault->getIntegerForKey(key.c_str(), 0);
    }
    
    if (phighScore[SCORECOUNT - 1] < value) {
        // Sort high scores.
        phighScore[SCORECOUNT - 1] = value;
        for (int i = 0 ; i < SCORECOUNT - 1; i++) {
            for (int j = 1; j < SCORECOUNT; j++) {
                if (phighScore[i] < phighScore[j]) {
                    int temp = phighScore[i];
                    phighScore[i] = phighScore[j];
                    phighScore[j] = temp;
                }
            }
        }
        // Save high scores
        for (int i = 0 ; i < SCORECOUNT; i++) {
            string key = StringUtils::format("%s_%d", username.c_str(), i);
            userdefault->setIntegerForKey(key.c_str(), phighScore[i]);
        }
    }
    
    // Read All High scores
    for (int i = 0; i < SCORECOUNT; i++) {
        string key = StringUtils::format("%s%d", kHighScore, i);
        ahighScore[i] = userdefault->getIntegerForKey(key.c_str(), 0);
    }
    if (ahighScore[SCORECOUNT - 1] < value) {
        // Sort high scores.
        ahighScore[SCORECOUNT - 1] = value;
        for (int i = 0 ; i < SCORECOUNT - 1; i++) {
            for (int j = 1; j < SCORECOUNT; j++) {
                if (ahighScore[i] < ahighScore[j]) {
                    int temp = ahighScore[i];
                    ahighScore[i] = ahighScore[j];
                    ahighScore[j] = temp;
                }
            }
        }
        // Save high scores
        for (int i = 0 ; i < SCORECOUNT; i++) {
            string key = StringUtils::format("%s%d", kHighScore, i);
            userdefault->setIntegerForKey(key.c_str(), ahighScore[i]);
        }
    }
}

void GameOptions::setFirstMatches(int value)
{
    m_firstMatches = value;
}

void GameOptions::setSecondMatches(int value)
{
    m_secontMatches = value;
}

void GameOptions::setPurchasedAnimal(int animalSet)
{
    string key = StringUtils::format("%s%d", kPurchaseAnimal, animalSet);
    m_userdefault->setBoolForKey(key.c_str(), true);
}

void GameOptions::setPurchasedCount(int count)
{
    string key = StringUtils::format("%s%d", kPurchaseAnimal, count);
    m_userdefault->setBoolForKey(key.c_str(), true);
}

void GameOptions::setBackgroundIndex(int value)
{
    m_backgroundIndex = value;
    m_userdefault->setIntegerForKey(kBackgroundIndex, m_backgroundIndex);
}

void GameOptions::setTileCoverIndex(int value)
{
    m_tileCoverIndex = value;
    m_userdefault->setIntegerForKey(kTileCoverIndex, m_tileCoverIndex);
}

void GameOptions::setPurchased(bool value)
{
    m_isPurchased = value;
    m_userdefault->setBoolForKey(kIsPurchased, value);
}

#pragma mark -

void GameOptions::addUserName(const char* name)
{
    if (sizeof(name) / sizeof('a') == 0) {
        return;
    }

    setLastUsedName(name);

    nameList.push_back(name);
    
    syncNameList();
}

void GameOptions::removeUserName(int index)
{
    string removeitem = nameList[index];
    vector<string>::iterator result = find(nameList.begin(), nameList.end(), removeitem);
    nameList.erase(result);
    
    syncNameList();
}

void GameOptions::syncNameList()
{
    nameCount = (int)nameList.size();
    UserDefault::getInstance()->setIntegerForKey(kNameCount, nameCount);
    sortNameList();
    for (int i = 0 ; i < nameCount; i++) {
        string name = nameList[i];
        UserDefault::getInstance()->setStringForKey(StringUtils::format("%s%d",kNameList, i).c_str(), name.c_str());
    }
}

void GameOptions::sortNameList()
{
    std::sort(nameList.begin(), nameList.end());
}

bool GameOptions::isDuplicateName(const char* name)
{
    bool retval = false;
    for (int index = 0; index < nameList.size(); index++) {
        string arr_name = nameList[index];
        if (arr_name.compare(name) == 0) {
            retval = true;
            break;
        }
    }
    return retval;
}


bool GameOptions::isMultiPlayerMode()
{
    if (secondUserName.length() > 0 ) {
        return true;
    }else
    {
        return false;
    }
}
