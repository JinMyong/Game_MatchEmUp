//
//  OptionScene.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-14.
//
//

#include "ScoreScene.h"
#include "GameSettings.h"
#include "GameScene.h"
#include "MainScene.h"
#include "SelectScene.h"
#include "SoundEngine.hpp"

Scene* ScoreScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ScoreScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ScoreScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_gameoptions = GameOptions::getInstance();
    
    createBg();
    createLabel();
    createBtn();
    
    return true;
}

void ScoreScene::createBg()
{
    newSprite("scorescene/bg_score", G_SWIDTH/2, G_SHEIGHT/2, this, 0, RATIO_XY);
    m_score_title = newSprite("scorescene/winner_log", getX(1040), getY(385), this, 0, RATIO_O);
    
    if (m_gameoptions->isMultiPlayerMode()) {
        m_score_log = newSprite("scorescene/score_log_2", getX(1015), getY(1200), this, 0, RATIO_O);
        newSprite("scorescene/score_stones_2", getX(1024), getY(2090), this, 0, RATIO_O);
    }else
    {
        m_score_log = newSprite("scorescene/score_log", getX(1015), getY(1060), this, 0, RATIO_O);
        m_total = newSprite("scorescene/total_score", getX(1015), m_score_log->getPositionY() - m_score_log->getContentSize().height * m_score_log->getScaleY() * 0.5 - DISY(120), this, 0, RATIO_O);
        newSprite("scorescene/highscore", getX(1020), getY(1715), this, 0, RATIO_O);
        newSprite("scorescene/score_stones", getX(1024), getY(2090), this, 0, RATIO_O);
    }
//    m_sPecker = newSprite("scorescene/woodpecker", getX(560), m_score_log->getPositionY() + m_score_log->getContentSize().height * m_score_log->getScaleY() * 0.5 - 50 * G_SCALEY, this, 1, RATIO_O);
    m_score_title->setAnchorPoint(Vec2(0.5, 0));
    m_score_title->setPositionY(m_score_log->getPositionY() + m_score_log->getContentSize().height * m_score_log->getScaleY() * 0.5 + 100 * G_SCALEY);
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("res/images/animation/woodpecker_animation.plist");
    Sprite* character = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("woodpecker-animation-01.png"));
    character->setScale(G_SCALEO * 2);
    character->setPosition(Vec2(G_SWIDTH * 0.5 - DISX(50), m_score_log->getPositionY() + m_score_log->getContentSize().height * m_score_log->getScaleY() * 0.5 + 100 * G_SCALEY));
    this->addChild(character, 3);
    
    float frameRate = 0.05;
    Vector<AnimationFrame*> animationFrames;
    for (int index = 1; index <= 95; index++) {
        char frameName[50];
        sprintf(frameName, "woodpecker-animation-%02d.png", index);
        SpriteFrame* frame = frameCache->getSpriteFrameByName(frameName);
        auto animFrame = AnimationFrame::create(frame, 1, ValueMap());
        animationFrames.pushBack(animFrame);
    }
    Animation* characterAnimation = Animation::create(animationFrames, frameRate);
    Animate* animate = Animate::create(characterAnimation);
    character->runAction(animate);
    this->runAction(Sequence::create(DelayTime::create(frameRate * 8),
                                     CallFunc::create([&]{
                                                            SoundEngine::getInstance()->playWoodPeckerEffect();
                                                          }),
                                     DelayTime::create(frameRate * 70),
                                     CallFunc::create([&]{
                                                            SoundEngine::getInstance()->stopWoodPeckerEffect();
                                                          }),
                                     NULL));
}

void ScoreScene::createLabel()
{
    if (m_gameoptions->isMultiPlayerMode()) {
        int firstMatches = m_gameoptions->getFirstMatches();
        int secondMatches = m_gameoptions->getSecondMatches();
        
        string score_str;
        string winner_name;
        if (firstMatches > secondMatches) {
            score_str = StringUtils::format("Player 1 wins\n%d matches\nto\n%d matches", firstMatches, secondMatches);
            winner_name = m_gameoptions->getFirstUserName();
        }else if (firstMatches < secondMatches)
        {
            score_str = StringUtils::format("Player 2 wins\n%d matches\nto\n%d matches", secondMatches, firstMatches);
            winner_name = m_gameoptions->getSecondUserName();
        }else if (firstMatches == secondMatches)
        {
            score_str = StringUtils::format("Players tied\n%d matches\neach", firstMatches);
            winner_name = "";
        }
        // Show Winner Name.
        Label* lbl_name = newLabel(winner_name.c_str(), "fonts/GROBOLD.ttf", DISO(150), getX(1250), getY(550), this, 2, RATIO_1);
        lbl_name->setColor(Color3B(249, 235, 17));
        
        // Show game result.
        Label* lbl_result = newLabel(score_str.c_str(), "fonts/GROBOLD.ttf", DISO(75), getX(1015), getY(1230), this, 2, RATIO_1);
        lbl_result->setColor(cocos2d::Color3B::BLACK);
        lbl_result->setAlignment(cocos2d::TextHAlignment::CENTER);
    }else
    {
        // Show player Name
        string playername = m_gameoptions->getFirstUserName();
        Label* lbl_name = newLabel(playername.c_str(), "fonts/GROBOLD.ttf", DISO(150), getX(1250), getY(550), this, 1, RATIO_1);
        lbl_name->setPositionY(m_score_title->getPositionY() + m_score_title->getContentSize().height * m_score_title->getScaleY() * 0.5 + DISY(50));
        lbl_name->setColor(Color3B(249, 235, 17));
        
        // Show player game time.
        Label* lbl_time = newLabel("Time", "fonts/GROBOLD.ttf", DISO(70), getX(560), getY(1140), this, 2, RATIO_1);
        lbl_time->setColor(cocos2d::Color3B::BLACK);
        lbl_time->setAnchorPoint(Vec2(0, 0.5));
        m_time = newLabel(m_gameoptions->getGameTime().c_str(), "fonts/GROBOLD.ttf", DISO(70), getX(1432), lbl_time->getPositionY(), this, 2, RATIO_1);
        m_time->setColor(cocos2d::Color3B::BLACK);
        m_time->setAnchorPoint(Vec2(1, 0.5));
        
        // show player game accuracy.
        Label* lbl_accur = newLabel("Accuracy", "fonts/GROBOLD.ttf", DISO(70), getX(560), getY(1215), this, 2, RATIO_1);
        lbl_accur->setColor(cocos2d::Color3B::BLACK);
        lbl_accur->setAnchorPoint(Vec2(0, 0.5));
        string accuracy = StringUtils::format("%d%%", (int)m_gameoptions->getFirstAccuracy());
        m_accur = newLabel(accuracy.c_str(), "fonts/GROBOLD.ttf", DISO(70), getX(1432), lbl_accur->getPositionY(), this, 2, RATIO_1);
        m_accur->setColor(cocos2d::Color3B::BLACK);
        m_accur->setAnchorPoint(Vec2(1, 0.5));
        
        // show game difficulty.
        Label* lbl_diff = newLabel("Difficulty", "fonts/GROBOLD.ttf", DISO(70), getX(560), getY(1290), this, 2, RATIO_1);
        lbl_diff->setColor(cocos2d::Color3B::BLACK);
        lbl_diff->setAnchorPoint(Vec2(0, 0.5));
        string tiles = StringUtils::format("%d tiles", m_gameoptions->getGameDifficulty());
        m_diff = newLabel(tiles.c_str(), "fonts/GROBOLD.ttf", DISO(70), getX(1432), lbl_diff->getPositionY(), this, 2, RATIO_1);
        m_diff->setColor(cocos2d::Color3B::BLACK);
        m_diff->setAnchorPoint(Vec2(1, 0.5));
        
        // show total score.
        string total_score_str = StringUtils::format("TOTAL SCORE : %s", formatNumber(m_gameoptions->getFirstPlayerScore()).c_str());
        m_totalScore = newLabel(total_score_str.c_str(), "fonts/GROBOLD.ttf", DISO(85), getX(1015), m_total->getPositionY() + DISY(10), this, 2, RATIO_1);
        m_totalScore->setColor(Color3B(249, 235, 17));
        
        // get player high scores.
        int* playerHighScores;
        int* allHighScores;
        playerHighScores = m_gameoptions->getPlayerHighScores();
        allHighScores = m_gameoptions->getAllHighScores();
        
        // show player high score
        string highScore = StringUtils::format("HIGH SCORE : %s", formatNumber(playerHighScores[0]).c_str());
        m_highScore = newLabel(highScore.c_str(), "fonts/GROBOLD.ttf", DISO(85), getX(1024), getY(1725), this, 2, RATIO_1);
        m_highScore->setColor(Color3B(249, 235, 17));
        
        // show player top 3 high scores
        Label* lbl_yourscore = newLabel("Your Scores", "fonts/GROBOLD.ttf",  DISO(65), getX(612), getY(1975), this, 2, RATIO_1);
        lbl_yourscore->setColor(cocos2d::Color3B::BLACK);
        for (int index = 0; index < SCORECOUNT; index++) {
            string score_str = StringUtils::format("%d) %s", index + 1, formatNumber(playerHighScores[index]).c_str());
            Label* lbl_playerscore = newLabel(score_str.c_str(), "fonts/GROBOLD.ttf", DISO(65), getX(462), getY(1985 + 65 * (index + 1)), this, 2, RATIO_1);
            lbl_playerscore->setColor(cocos2d::Color3B::BLACK);
            lbl_playerscore->setAnchorPoint(Vec2(0, 0.5));
        }
        
        // Show all top 3 high scores.
        Label* lbl_alltimescore = newLabel("High Scores", "fonts/GROBOLD.ttf",  DISO(65), getX(1395), getY(1975), this, 2, RATIO_1);
        lbl_alltimescore->setColor(cocos2d::Color3B::BLACK);
        for (int index = 0; index < SCORECOUNT; index++) {
            string score_str = StringUtils::format("%d) %s", index + 1, formatNumber(allHighScores[index]).c_str());
            Label* lbl_allscore = newLabel(score_str.c_str(), "fonts/GROBOLD.ttf", DISO(65), getX(1250), getY(1985 + 65 * (index + 1)), this, 2, RATIO_1);
            lbl_allscore->setColor(cocos2d::Color3B::BLACK);
            lbl_allscore->setAnchorPoint(Vec2(0, 0.5));
        }
    }
    
}

void ScoreScene::createBtn()
{
    MenuItemImage *iPlayAgain = newButton("scorescene/btn_playagain", getX(796), getY(2515), CC_CALLBACK_1(ScoreScene::onMenu, this), RATIO_O);
    iPlayAgain->setTag(1000);
    MenuItemImage *iMain = newButton("scorescene/btn_mainmenu", getX(1264), getY(2515), CC_CALLBACK_1(ScoreScene::onMenu, this), RATIO_O);
    iMain->setTag(1001);
    
    m_mMain = Menu::create(iPlayAgain, iMain, NULL);
    m_mMain->setPosition(Point(0, 0));
    addChild(m_mMain, 1);
}

void ScoreScene::onMenu(Ref *sender)
{
    MenuItemImage *item = (MenuItemImage *)sender;
    SoundEngine::getInstance()->stopWoodPeckerEffect();
    this->removeAllChildrenWithCleanup(true);
    this->stopAllActions();
    if(item->getTag() == 1000) //Play Again
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
    }
    else if(item->getTag() == 1001) //Main
    {
//        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, MainScene::createScene()));
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, SelectScene::createScene()));
    }
}

string ScoreScene::formatNumber(int value)
{
    string retval;
    string buf_str = StringUtils::format("%d", value);
    int dis = 0;
    
    for (int i = (int)buf_str.length() - 1; i >= 0; i--) {
        retval = buf_str.at(i) + retval;
        dis++;
        if (dis >= 3 && i != 0) {
            dis = 0;
            retval = "," + retval;
        }
    }
    return retval;
}