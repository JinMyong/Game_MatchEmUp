//
//  GameScene.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#include "GameScene.h"
#include "MainScene.h"
#include "GameSettings.h"
#include "ScoreScene.h"
#include "OptionScene.h"
#include "SelectScene.h"
#include "SoundEngine.hpp"


char g_sAnimalNames[6][24][32] =
{
    //Animal 1
    {
        "anteater",     "armadillo",    "bat",          "beaver",       "beluga whale",
        "cape buffalo", "dolphin",      "donkey",       "goat",         "hippo",
        "horse",        "hyena",        "kangaroo",     "killer whale", "lemur",
        "llama",        "moose",        "ostrich",      "penguin",      "platypus",
        "rooster",      "seal",         "turkey",       "vulture",
    },
    //Animal 2
    {
        "alligator",    "bear",         "bull",         "bunny",        "chick",
        "dog",          "duck",         "elephant",     "giraffe",      "gorilla",
        "hippo",        "koala bear",   "leopard",      "lion",         "monkey",
        "mouse",        "panda bear",   "penguin",      "pig",          "polar bear",
        "raccoon",      "ram",          "rhinoceros",   "tiger",
    },
    //Animal 3
    {
        "alligator",    "bear",         "bee",          "camel",        "caterpillar",
        "chicken",      "chicks",       "dog",          "flamingo",     "fox",
        "frog",         "giraffe",      "hippopotamus", "horse",        "monkey",
        "parrot",       "penguin",      "pig",          "rhinoceros",   "snake",
        "tiger",        "turtle",       "wildebeest",   "zebra",
    },
    //Animal 4
    {
        "bear",         "camel",        "dog",          "eagle",        "fly",
        "goat",         "hippopotamus", "insects",      "jaguar",       "kangaroo",
        "leopard",      "monkey",       "narwhal",      "ostrich",      "penguin",
        "quail",        "rabbit",       "seal",         "tiger",        "viper",
        "wolf",         "x-ray fish",   "yak",          "zebra",
    },
    //Animal 5
    {
        "ant",          "bee",          "cow",          "duck",         "elephant",
        "fox",          "geese",        "hamster",      "insects",      "jaguar",
        "koala bear",   "lion",         "mouse",        "narwhal",      "owl",
        "panda",        "queen bee",    "rhinoceros",   "sheep",        "turtle",
        "unicorn",      "vampire bat",  "walrus",       "zebra",
    },
    //Transport
    {
        "flying saucer", "bulldozer",   "car hauler",   "cement truck", "crane",
        "digger",        "truck",       "fire truck",   "helicopter",   "race car",
        "indy car",      "fighter jet", "jumbo jet",    "earth mover",  "logging truck",
        "police car",    "car",         "rocket",       "semi truck",   "ship",
        "astronaut",     "submarine",   "tow truck",    "chinook helicopter",
    },
};
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }

    m_gameoptions = GameOptions::getInstance();
    m_firstMatches = 0;
    m_secondMatches = 0;
    
    createBg();
    createBtn();
    createPause();
    createLabel();
    
    initGame();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    m_org_cardScaleX = m_sTile[0]->getScaleX();
    m_org_cardScaleY = m_sTile[0]->getScaleY();
    
    hideTileName = CallFunc::create([&]{m_lTileName->setString("");});
    return true;
}

void GameScene::createBg()
{
    string bg_name = StringUtils::format("backgrounds/bkg_%d", m_gameoptions->getBackgroundIndex());
    newSprite(bg_name.c_str(), G_SWIDTH/2, G_SHEIGHT/2, this, 0, RATIO_XY);
    newSprite("g_title", getX(1000), getY(275), this, 1, RATIO_XY);
    newSprite("gamescene/timer", getX(240), getY(355), this, 1, RATIO_XY);
    newSprite("gamescene/t_timer", getX(225), getY(275), this, 1, RATIO_XY);
    
    newSprite("gamescene/tiles", getX(1775), getY(342), this, 1, RATIO_XY);
    newSprite("gamescene/t_flipped", getX(1775), getY(165), this, 1, RATIO_XY);
    newSprite("gamescene/t_matches", getX(1725), getY(455), this, 1, RATIO_XY);
    
    // Added by fredric to show Tile Name
    m_tileNameBoard = newSprite("gamescene/animal_name", getX(720), getY(2525), this, 1, RATIO_XY);
    m_tileNameBoard->setScaleX(G_SCALEX * 1.5);
    if (m_gameoptions->getTileNameOption()) {
        m_tileNameBoard->setVisible(true);
    }else
    {
        m_tileNameBoard->setVisible(false);
    }
    // Add end.
    
    // Added by fredric to show player name.
    
    m_userName = newLabel(m_gameoptions->getFirstUserName().c_str(), "fonts/GROBOLD.ttf", DISO(85), getX(900), getY(580), this, 2, RATIO_1);
    m_userName->setColor(TEXT_BROWNCOLOR);
    isSecondPlayer = false;
    m_gameoptions->setFirstPlayerFlips(0);
    m_gameoptions->setSecondPlayerFlips(0);

    // Add end.
}

void GameScene::createBtn()
{
    MenuItemImage *iPause = newButton("gamescene/btn_pause", getX(1745), getY(2525), CC_CALLBACK_1(GameScene::onMenu, this), RATIO_XY);
    iPause->setTag(101);
    
    m_mMain = Menu::create(iPause, NULL);
    m_mMain->setPosition(Point(0,0));
    addChild(m_mMain, 1);
}

void GameScene::createLabel()
{
    
    m_lTime = newLabel("00:00", "fonts/GROBOLD.ttf", DISO(80), getX(225), getY(380), this, 2, RATIO_1);
    m_lTime->setColor(TEXT_YELLOWCOLOR);
    m_lTime->setAlignment(TextHAlignment::CENTER);
    
    m_lFlipped = newLabel("0", "fonts/GROBOLD.ttf", DISO(90), getX(1775), getY(250), this, 2, RATIO_1);
    m_lFlipped->setColor(TEXT_YELLOWCOLOR);
    m_lFlipped->setAlignment(TextHAlignment::CENTER);
    
    m_lMatchLeft = newLabel("0", "fonts/GROBOLD.ttf", DISO(75), getX(1895), getY(455), this, 2, RATIO_1);
    m_lMatchLeft->setColor(TEXT_YELLOWCOLOR);
    m_lMatchLeft->setAlignment(TextHAlignment::CENTER);
    
    // Added by Fredric to show animal name
    m_lTileName = newLabel("", "fonts/GROBOLD.ttf", DISO(85), m_tileNameBoard->getPositionX(), m_tileNameBoard->getPositionY(), this, 2, RATIO_1);
    m_lTileName->setColor(TEXT_BROWNCOLOR);
    m_lTileName->setAlignment(TextHAlignment::CENTER);
    
    if (m_gameoptions->getTileNameOption()) {
        m_lTileName->setVisible(true);
    }else
    {
        m_lTileName->setVisible(false);
    }
    
    // Add end.
}

void GameScene::createPause()
{
    m_sBOverlay = newSprite("g_blackoverlay", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, this, 3, RATIO_XY);
    m_sPause = newSprite("gamescene/pausepopup", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, this, 3, RATIO_O);
    
    MenuItemImage *iPOptions = newButton("gamescene/btn_poption", G_SWIDTH * 0.5, getY(1090), CC_CALLBACK_1(GameScene::onMenu, this), RATIO_O);
    iPOptions->setTag(1000);
    
    MenuItemImage *iPMain = newButton("gamescene/btn_pmain", G_SWIDTH * 0.5, getY(1340), CC_CALLBACK_1(GameScene::onMenu, this), RATIO_O);
    iPMain->setTag(1001);
    
    MenuItemImage *iPQuit = newButton("gamescene/btn_pquit", G_SWIDTH * 0.5, getY(1590), CC_CALLBACK_1(GameScene::onMenu, this), RATIO_O);
    iPQuit->setTag(1002);
    
    MenuItemImage *iPResume = newButton("gamescene/btn_presume", getX(1115), m_sPause->getPositionY() - m_sPause->getContentSize().height * m_sPause->getScaleY() * 0.5 + DISY(200), CC_CALLBACK_1(GameScene::onMenu, this), RATIO_O);
//    getY(1840)
    iPResume->setTag(1003);

    m_mPause = Menu::create(iPOptions, iPMain, iPQuit, iPResume, NULL);
    m_mPause->setPosition(Point(0, 0));
    addChild(m_mPause, 4);
    
    showPause(false);
}

void GameScene::initGame()
{
    srand((int)time(NULL));
    m_nOpen1 = -1;
    m_nOpen2 = -1;
    
    prev_open1 = -1; // Added by Fredric for cover tile.
    prev_open2 = -1; // Added by Fredric for cover tile.
    
    m_bCanTouch = true;
    
    m_nW = g_llGame[g_nLevel].nW;
    m_nH = g_llGame[g_nLevel].nH;
    
    int tiles = m_nW * m_nH;
    m_gameoptions->setGameDifficulty(tiles);
    
    m_nPack = g_nPack;
    
    //Create Item Info
    if (m_nW * m_nH == 48) {
        for(int i = 0; i < m_nW * m_nH; i+=2)
        {
            m_nTileInfo[i] = m_nTileInfo[i+1] = i / 2;
        }
    }else
    {
        for(int i = 0; i < m_nW * m_nH; i+=2)
        {
            int nTileInfo;
            bool isDuplicate = false;
            do  {
                nTileInfo = rand() % 24;
                for (int idx = 0; idx < m_nW * m_nH; idx++) {
                    if (nTileInfo == m_nTileInfo[idx]) {
                        isDuplicate = true;
                        break;
                    }else
                    {
                        isDuplicate = false;
                    }
                }
//                log("isDuplicate : %s", isDuplicate?"true":"false");
            }while (isDuplicate);
            m_nTileInfo[i] = m_nTileInfo[i+1] = nTileInfo;
        }
    }
    
    //Shuffle
    for(int i = 0; i < m_nW * m_nH; i++)
    {
        int nRandPos = rand() % (m_nW * m_nH);
        
        //Swap
        int nTemp = m_nTileInfo[i];
        m_nTileInfo[i] = m_nTileInfo[nRandPos];
        m_nTileInfo[nRandPos] = nTemp;
    }
    
    //Create Visual Items
    for(int i = 0; i < m_nW; i++)
    {
        for(int j = 0; j < m_nH; j++)
        {
            int nIndex = i * m_nH + j;
            //Actual Object
            char sObjName[64];
            sprintf(sObjName, "gamescene/img/img%d_%d", g_nPack + 1, m_nTileInfo[nIndex] + 1);
            m_sItem[nIndex] = newSprite(sObjName, getX(g_llGame[g_nLevel].nX0 + i * g_llGame[g_nLevel].nXGap), getY(g_llGame[g_nLevel].nY0 + j * g_llGame[g_nLevel].nYGap), this, 1, RATIO_XY);
            m_sItem[nIndex]->setScale(G_SCALEO * g_llGame[g_nLevel].fTScale);
            m_sItem[nIndex]->setTag(tUnMatchedState); //Mark Item as not matched
            
            //Tile Back
            string tilecoverName = StringUtils::format("gamescene/cover/card_%d", m_gameoptions->getTileCoverIndex());
            m_sTile[nIndex] = newSprite(tilecoverName.c_str(), m_sItem[nIndex]->getPositionX(), m_sItem[nIndex]->getPositionY(), this, 2, RATIO_XY);
            
            m_sTile[nIndex]->setScale(m_sItem[nIndex]->getScale());
            //m_sTile[nIndex]->setOpacity(100);
        }
    }
    
    setMatchLeftText();
    schedule(schedule_selector(GameScene::onTimer), 1);
}

int GameScene::getMatchLeft()
{
    int nMatchLeft = 0;
    for(int i = 0; i < m_nW * m_nH; i++)
    {
        if(m_sItem[i]->getTag() == tUnMatchedState) //Unmatched
        {
            nMatchLeft++;
        }
    }
    return nMatchLeft / 2;
}

void GameScene::showPause(bool bIsShow)
{
    m_mMain->setEnabled(!bIsShow);
    m_sPause->setVisible(bIsShow);
    m_sBOverlay->setVisible(bIsShow);
    m_mPause->setVisible(bIsShow);
    m_bIsPaused = bIsShow;
}

void GameScene::onTimer(float dt)
{
    // Added by Fredric to detect show tile name.
    if (m_gameoptions->getTileNameOption()) {
        m_tileNameBoard->setVisible(true);
        m_lTileName->setVisible(true);
    }else
    {
        m_tileNameBoard->setVisible(false);
        m_lTileName->setVisible(false);
    }
    // Added end.
    
    if(!m_bIsPaused)
    {
        m_nTime++;
        setTimerText();
    }
}

void GameScene::setFlippedText(int value)
{
    char sFlipped[16];
    sprintf(sFlipped, "%d", value);
    m_lFlipped->setString(sFlipped);
}

void GameScene::setMatchLeftText()
{
    char sMatchLeft[8];
    sprintf(sMatchLeft, "%d", getMatchLeft());
    m_lMatchLeft->setString(sMatchLeft);
}

void GameScene::setTimerText()
{
    char sTimer[64];
    sprintf(sTimer, "%2.2d:%2.2d", m_nTime / 60, m_nTime % 60);
    m_lTime->setString(sTimer);
}

void GameScene::onMenu(Ref *sender)
{
    MenuItemImage *item = (MenuItemImage *)sender;
    Director::getInstance()->resume();
    if(item->getTag() == 101) //Pause
    {
        Director::getInstance()->pause();
        showPause(true);
    }
    else if(item->getTag() == 1000) //Option
    {
        Director::getInstance()->pushScene(TransitionCrossFade::create(0.5f, OptionScene::createScene()));
    }
    else if(item->getTag() == 1001) //Main
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, SelectScene::createScene()));
    }
    else if(item->getTag() == 1002) //Quit
    {
        exit(0);
    }
    else if(item->getTag() == 1003) //Resume
    {
        showPause(false);
    }
}

void GameScene::scoring()
{
    if (m_gameoptions->isMultiPlayerMode()) {
        m_gameoptions->setFirstMatches(m_firstMatches);
        m_gameoptions->setSecondMatches(m_secondMatches);
    }else
    {
        int tile_count = m_nH * m_nW;
        int flip_count = m_gameoptions->getFirstUserFlips();
        int game_time = m_nTime;
        
        float accuracy = (float)tile_count * 100 / (float)(flip_count * 2);
        float time_score = (float)tile_count / (float)game_time * (float)tile_count * 100;
        float accu_score = (float)tile_count / ((float)flip_count * 2) * ((float)tile_count * 200);
        float tile_score = (float)tile_count * 100;
        int total_score = time_score + accu_score + tile_score;
        
        m_gameoptions->setFirstAccuracy(accuracy);
        m_gameoptions->setGameTime(m_lTime->getString());
        m_gameoptions->setFirstPlayerScore(total_score);
        m_gameoptions->setHighScore(total_score);
    }
    
}

void GameScene::flipCard(cocos2d::Sprite *card)
{
    
    m_org_cardScaleX = card->getScaleY();
    m_org_cardScaleY = card->getScaleX();
    card->runAction(Sequence::create(
                                     ScaleTo::create(0.1f, 0, m_org_cardScaleY),
                                     CallFunc::create([&]{
                                                            card->setVisible(false);
                                                            card->setScaleX(m_org_cardScaleX);
                                                     }),
                                     NULL)
                    );

}

void GameScene::unflipCard(cocos2d::Sprite *card)
{
    card->setVisible(true);
    card->runAction(ScaleTo::create(0.1f, m_org_cardScaleX, m_org_cardScaleY));
}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent){
   
    Point touchLocation=touches[0]->getLocation();
    if(m_bIsPaused)
        return;
    
    //Check Touch
    for(int i = 0; i < m_nH * m_nW; i++)
    {
        if(m_bCanTouch && m_sTile[i]->getBoundingBox().containsPoint(touchLocation) && m_nOpen1 != i && ((m_gameoptions->getShowImageOption() && m_sItem[i]->getOpacity() == 255)? true : m_sTile[i]->isVisible()))
        {
            m_lTileName->setString(g_sAnimalNames[m_nPack][m_nTileInfo[i]]); // Added by Fredric animal name to image
            
            this->stopActionByTag(tHideNameAction);
            
            m_nTileNumber = m_nTileInfo[i];     // Added by Fredric to play animal soundeffect
            float delay_tile;
            if (m_gameoptions->getTileSoundEffectOption()) {
                delay_tile = 0.5f;
            }else{
                delay_tile = 0.0f;
            }
            runAction(Sequence::create(CallFunc::create([&] {
                                                                if (m_gameoptions->getTileSoundEffectOption()) {
                                                                    SoundEngine::getInstance()->playFlipEffect();
                                                                }
                                                            }),
                                       DelayTime::create(delay_tile),
                                       CallFunc::create([&] {
                                                                if (m_gameoptions->getAnimalSoundEffectOption()) {
                                                                    SoundEngine::getInstance()->playItemSoundEffect(m_nPack, m_nTileNumber);
                                                                }
                                                            }),
                                       NULL));
            flip_card_index = i;
            m_flipcard = m_sTile[i];
            m_sTile[i]->runAction(Sequence::create(ScaleTo::create(0.1f, 0, m_org_cardScaleY),
                                                   CallFunc::create([&]{
                                                                        m_flipcard->setVisible(false);
                                                                        m_flipcard->setScaleX(m_org_cardScaleX);
                                                                        }),
                                                   NULL) );
            
            if(m_nOpen1 == -1)
            {
                m_bCanTouch = true;
                m_nOpen1 = i;
                
                this->stopActionByTag(tCoverAction);
                
                if (!m_gameoptions->getShowImageOption() && prev_open1 >= 0 && prev_open2 >= 0) {
                    if (i != prev_open1)
                    {
                        m_sTile[prev_open1]->setVisible(true);
                        m_sTile[prev_open1]->runAction(ScaleTo::create(0.1f, m_org_cardScaleX, m_org_cardScaleY));
                    }
                    if (i != prev_open2) {
                        m_sTile[prev_open2]->setVisible(true);
                        m_sTile[prev_open2]->runAction(ScaleTo::create(0.1f, m_org_cardScaleX, m_org_cardScaleY));
                    }
                }
            }
            else
            {
                m_nFlipped++;
                setFlippedText(m_nFlipped);
                if (m_gameoptions->isMultiPlayerMode()) {
                    if (isSecondPlayer) {
                        m_gameoptions->setFirstPlayerFlips(m_nFlipped);
                        m_userName->setString(m_gameoptions->getFirstUserName().c_str());
                        m_nFlipped = m_gameoptions->getSecondUserFlips();
                    }else
                    {
                        m_gameoptions->setSecondPlayerFlips(m_nFlipped);
                        m_userName->setString(m_gameoptions->getSecondUserName().c_str());
                        m_nFlipped = m_gameoptions->getFirstUserFlips();
                    }
                    isSecondPlayer = !isSecondPlayer;
                }else{
                    m_gameoptions->setFirstPlayerFlips(m_nFlipped);
                }
                setFlippedText(m_nFlipped);
                
                
                //Check Pair
                if(m_nTileInfo[m_nOpen1] == m_nTileInfo[i]) //Pair matched
                {
                    m_bCanTouch = true;
                    m_sItem[m_nOpen1]->setTag(tMatchedState);   // Mark Item as matched
                    m_sItem[i]->setTag(tMatchedState);          // Mark Item as matched
                    
                    setMatchLeftText();
                    
                    if (m_gameoptions->isMultiPlayerMode()) {
                        if (!isSecondPlayer) {
                            m_secondMatches++;
                        }else
                        {
                            m_firstMatches++;
                        }
                    }
                    
                    float delay_matchEffect;
                    delay_matchEffect = delay_tile;
                    if (m_gameoptions->getAnimalSoundEffectOption()) {
                        delay_matchEffect += 1.0f;
                    }
                    runAction(Sequence::create(DelayTime::create(delay_matchEffect),
                                               CallFunc::create([&]{
                                                                        if (m_gameoptions->getTileSoundEffectOption()) {
                                                                            SoundEngine::getInstance()->playMatchEffect();
                                                                        }
                                                                    }),
                                               NULL));
                    m_sItem[m_nOpen1]->setOpacity(254);
                    m_sItem[i]->setOpacity(254);
                    m_sItem[m_nOpen1]->runAction(Sequence::create(DelayTime::create(delay_matchEffect), FadeOut::create(0.75f), NULL));
                    m_sItem[i]->runAction(Sequence::create(DelayTime::create(delay_matchEffect), FadeOut::create(0.75f), NULL));
                    
//                    if (!m_gameoptions->getShowImageOption()) {
                        Sequence* seq_hideName = Sequence::create(DelayTime::create(delay_matchEffect + 0.75), CallFunc::create([&]{m_lTileName->setString("");}), NULL);
                        seq_hideName->setTag(tHideNameAction);
                        this->runAction(seq_hideName);
//                    }                    
                    
                    m_nOpen1 = m_nOpen2 = -1;
                    prev_open1 = -1;        // Added by fredric to init select tile
                    prev_open2 = -1;        // Added by fredric to init select tile
                    
                    if(getMatchLeft() == 0) // All animals are matched
                    {
                        unschedule(schedule_selector(GameScene::onTimer));
                        float delay_done;
                        delay_done = delay_matchEffect + 1.0f;
                        float delay_replace;
                        if (m_gameoptions->getTileSoundEffectOption()) {
                            delay_replace = 1.0;
                        }else
                        {
                            delay_replace = 0.0;
                        }
                        runAction(Sequence::create(DelayTime::create(delay_done),
                                                   CallFunc::create([&]{
                                                                            if (m_gameoptions->getTileSoundEffectOption()) {
                                                                                SoundEngine::getInstance()->playDoneEffect();
                                                                            }
                                                                        }),
                                                   DelayTime::create(1.0f),
                                                   CallFunc::create([&]{
                                                                            scoring();
                                                                            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, ScoreScene::createScene()));
                                                                        }),
                                                   NULL));
                        
                    }

                }
                else //Pair doesn't match
                {
                    m_nOpen2 = i;
                    
                    prev_open1 = m_nOpen1;
                    prev_open2 = m_nOpen2;
                    
                    m_nOpen1 = m_nOpen2 = -1;
                    
                    Sequence* action_seq = Sequence::create(DelayTime::create(m_gameoptions->getTimerIndicate()),
                                                            CallFunc::create([&]{
                                                                                    m_bCanTouch = true;
                                                                                    if (!m_gameoptions->getShowImageOption()) {
                                                                                            m_sTile[prev_open1]->setVisible(true);
                                                                                            m_sTile[prev_open1]->setScaleX(0);
                                                                                            m_sTile[prev_open1]->runAction(ScaleTo::create(0.1f, m_org_cardScaleX, m_org_cardScaleY));
                                                                                            m_sTile[prev_open2]->setVisible(true);
                                                                                            m_sTile[prev_open2]->setScaleX(0);
                                                                                            m_sTile[prev_open2]->runAction(ScaleTo::create(0.1f, m_org_cardScaleX, m_org_cardScaleY));
                                                                                    }
                                                                            }),
                                                            CallFunc::create([&]{if (!m_gameoptions->getShowImageOption()) m_lTileName->setString("");}),
                                                            NULL);
                    action_seq->setTag(tCoverAction);
                    runAction(action_seq);
                }
            }
        }
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent){
    
}
void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent){
    
}

void GameScene::onEnterTransitionDidFinish()
{
    //    Layer::onEnterTransitionDidFinish();
    CCLOG("----- Game Scene onEnter -----");
    if (m_bIsPaused)
    {
        Director::getInstance()->pause();
    }
}
