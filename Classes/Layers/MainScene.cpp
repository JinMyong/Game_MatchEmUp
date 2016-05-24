//
//  MainScene.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-13.
//
//

#include "MainScene.h"
#include "GameSettings.h"
#include "SelectScene.h"
#include "OptionScene.h"
#include "ui/CocosGUI.h"

#include "SoundEngine.hpp"
#include "GameOptions.h"

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    g_optionScenebackisMain = true;
    
    SoundEngine::getInstance()->playBackgroundMusic(); // Added by Fredric To play background music.
    if (GameOptions::getInstance()->getBackgroundMusicOption()) {
        SoundEngine::getInstance()->unMuteBackgoundMusic();
    }else
    {
        SoundEngine::getInstance()->muteBackgroundMusic();
    }
    
    GameOptions::getInstance()->setSecondPlayerName("");
    
    createBg();
    createLabel();
    createBtn();
    createPopup();
    
    return true;
}

void MainScene::createBg()
{
    newSprite("mainscene/main_bg", G_SWIDTH/2, G_SHEIGHT/2, this, 0, RATIO_XY);
    Sprite* title = newSprite("mainscene/maintitle", getX(950), getY(665), this, 1, RATIO_O);
    title->setAnchorPoint(Vec2(0.5, 1));
    title->setPosition(Vec2(G_SWIDTH * 0.5, G_SHEIGHT));
// Added by fredric for Logo
    Sprite* logo = newSprite("mainscene/hipposcape_logo", getX(1910), getY(2595), this, 1, RATIO_O);
    logo->setAnchorPoint(Vec2(1, 0));
}

void MainScene::createLabel()
{

}

void MainScene::createBtn()
{
    MenuItemImage *iPlay = newButton("mainscene/btn_play", getX(960), getY(2440), CC_CALLBACK_1(MainScene::onMenu, this), RATIO_O);
    iPlay->setAnchorPoint(Vec2(0.5, 0));
    iPlay->setTag(1000);
    MenuItemImage *iOptions = newButton("mainscene/btn_options", getX(1045), iPlay->getPositionY() + DISY(60), CC_CALLBACK_1(MainScene::onMenu, this), RATIO_O);
    iOptions->setAnchorPoint(Vec2(0.5, 1));
    iOptions->setTag(1001);
    
    m_mMain = Menu::create(iPlay, iOptions, NULL);
    m_mMain->setPosition(Point(0, 0));
    addChild(m_mMain, 1);
}

void MainScene::createPopup()
{
    m_popup = NamePopUpLayer::create();
    this->addChild(m_popup, 10);
    showPopup(false);
}

void MainScene::showPopup(bool bIsShow)
{
    m_popup->setVisible(bIsShow);    
}

void MainScene::editBoxReturn(EditBox* editBox)
{
    
}

void MainScene::onMenu(Ref *sender)
{
    MenuItemImage *item = (MenuItemImage *)sender;
    if(item->getTag() == 1000) //Play
    {
        if (GameOptions::getInstance()->getNameCount() == 0) {
            m_popup->showCreateNameBox();
        }else
        {
            m_popup->showLastNameBox();
        }
        showPopup(true);
    }
    else if(item->getTag() == 1001) //Options
    {
        Director::getInstance()->pushScene(TransitionCrossFade::create(0.5f, OptionScene::createScene()));
//        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, OptionScene::createScene()));
    }
    else if(item->getTag() == 1002) //Popup No
    {
        showPopup(false);
    }
    else if(item->getTag() == 1003) //Popup Yes
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, SelectScene::createScene()));
    }
}

void MainScene::gotoSelectScene()
{
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, SelectScene::createScene()));
}
