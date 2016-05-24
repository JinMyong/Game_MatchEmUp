//
//  GameScene.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#include "SelectScene.h"
#include "GameSettings.h"
#include "GameScene.h"
#include "OptionScene.h"

using namespace sdkbox;

Scene* SelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool SelectScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    IAP::setDebug(true);
    IAP::setListener(this);
    
    g_optionScenebackisMain = false;
    
    m_nPlayerCnt = 1;
    m_gameoptions = GameOptions::getInstance();
    m_nSelPack = m_gameoptions->getAnimalPack();
    m_nSelLevel = m_gameoptions->getGameLevel();
    
// added by Fredric to select second player.
    
    m_namepopup = NamePopUpLayer::create();
    m_namepopup->setVisible(false);
    addChild(m_namepopup, 100);
    
// add end
    
    createBg();
    createLabel();
    createBtn();

    m_sPackHL = newSprite("selectscene/settile_h", m_iPacks[m_nSelPack]->getPositionX(), m_iPacks[m_nSelPack]->getPositionY(), this, 1, RATIO_XY);
    m_sLevelL_HL = newSprite("selectscene/level_l_h", m_iLevels[m_nSelLevel]->getPositionX(), m_iLevels[m_nSelLevel]->getPositionY(), this, 1, RATIO_XY);
    m_sLevelR_HL = newSprite("selectscene/level_r_h", m_iLevels[m_nSelLevel]->getPositionX(), m_iLevels[m_nSelLevel]->getPositionY(), this, 1, RATIO_XY);
    
    setLevelHL(m_nSelLevel);
    return true;
}

void SelectScene::createBg()
{
    string bg_name = StringUtils::format("backgrounds/bkg_%d", m_gameoptions->getBackgroundIndex());
    newSprite(bg_name.c_str(), G_SWIDTH/2, G_SHEIGHT/2, this, 0, RATIO_XY);
    //newSprite("g_boxcontent", getX(1045), getY(1380), this, 0, RATIO_XY);
    newSprite("selectscene/box", getX(985), getY(1415), this, 0, RATIO_XY);
    newSprite("g_title", getX(1000), getY(275), this, 1, RATIO_XY);
}

void SelectScene::createLabel()
{
//    Label *lChooseMany = newLabel(Txt_SELECTPLAYERS, "fonts/GROBOLD.ttf", DISO(75), getX(1035), getY(1630), this, 1, RATIO_1);
//    lChooseMany->setColor(TEXT_BROWNCOLOR);
    
    Label *lChooseLevel = newLabel(Txt_SELECTDIFFICULTY, "fonts/GROBOLD.ttf", DISO(75), getX(1035), getY(1800), this, 1, RATIO_1);
    lChooseLevel->setColor(TEXT_BROWNCOLOR);
}

void SelectScene::createBtn()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            int index = i*3 + j;
            m_iPacks[index]= newButton("selectscene/btn_settile", getX(610 + 435 * j), getY(795 + i * 435), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
            m_iPacks[i * 3 + j]->setTag(1000 + index);
            
            newSprite(StringUtils::format("selectscene/pack%d", index + 1).c_str(), m_iPacks[index]->getPositionX(), m_iPacks[index]->getPositionY() - DISY(30), this, 2, RATIO_O);
            if (!m_gameoptions->getPurchased() && index != 0) {
                Sprite* lock_snake = newSprite("g_snake", m_iPacks[index]->getPositionX() - DISX(20), m_iPacks[index]->getPositionY() - DISY(0), this, 2, RATIO_O);
                m_snake[index] = lock_snake;
                lock_snake->setTag(2000 + index);
            }
        }
    }
    
    int nPos[6][2] = {{475, 2005}, {705, 2095}, {960, 1995}, {1150, 2135}, {1345, 1965}, {1545, 2135}};
    for(int i = 0; i < 6; i++)
    {
        if(i%2 == 0)
            m_iLevels[i] = newButton("selectscene/btn_level_l", getX(nPos[i][0]), getY(nPos[i][1]), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
        else
            m_iLevels[i] = newButton("selectscene/btn_level_r", getX(nPos[i][0]), getY(nPos[i][1]), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
        
        m_iLevels[i]->setTag(1100 + i);
        newSprite(StringUtils::format("selectscene/lv%d", i+1).c_str(), m_iLevels[i]->getPositionX() + DISX(40), m_iLevels[i]->getPositionY() - DISY(40), this, 2, RATIO_XY);
    }
    
    
    MenuItemImage *iOptions = newButton("selectscene/btn_options", getX(600), getY(2415), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
    iOptions->setTag(TAG_OPTIONS);
    MenuItemImage *iStart = newButton("selectscene/btn_start", getX(1335), getY(2420), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
    iStart->setTag(TAG_START);
    
    MenuItemImage* iRestore = newButton("selectscene/btn_restore", G_SWIDTH * 0.5, getY(1550), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_XY);
    iRestore->setTag(TAG_BTN_RESTORE);
    
//    MenuItemImage* player_2 = newButton("selectscene/btn_2players", G_SWIDTH * 0.5, getY(1740), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_O);
//    player_2->setTag(TAG_2PLAYER);
    
    m_button_menu = Menu::create(m_iPacks[0], m_iPacks[1], m_iPacks[2], m_iPacks[3], m_iPacks[4], m_iPacks[5], m_iLevels[0], m_iLevels[1], m_iLevels[2], m_iLevels[3], m_iLevels[4], m_iLevels[5], iRestore, iOptions, iStart, /*player_2,*/ NULL);
    m_button_menu->setPosition(Point(0,0));
    addChild(m_button_menu, 1);
}

void SelectScene::setLevelHL(int nLevel)
{
    bool bIsLeft = false;
    if(nLevel % 2 == 0) //Left
        bIsLeft = true;
    else //Right
        bIsLeft = false;
    
    m_sLevelL_HL->setPosition(m_iLevels[nLevel]->getPosition());
    m_sLevelR_HL->setPosition(m_iLevels[nLevel]->getPosition());
    
    m_sLevelL_HL->setVisible(bIsLeft);
    m_sLevelR_HL->setVisible(!bIsLeft);
}

void SelectScene::onMenu(Ref *sender)
{
    MenuItemImage *item = (MenuItemImage *)sender;
    if(item->getTag() >= 1000 && item->getTag() < 1006) //Pack
    {
        int animal_pack = item->getTag() - 1000;
        if (m_gameoptions->getPurchased() || animal_pack == 0) {
            m_nSelPack = item->getTag() - 1000;
            setAnimalSet(m_nSelPack);
        }else
        {
            m_button_menu->setEnabled(false);
            showAnimalUnlockPopUp(animal_pack);
        }
    }
    else if(item->getTag() >= 1100 && item->getTag() < 1106) //Level
    {
        int level_count = item->getTag() - 1100;
//        if (m_gameoptions->isPurchasedCount(level_count) && level_count == 0) {
            m_nSelLevel = level_count;
            setLevelHL(m_nSelLevel);
            m_gameoptions->setGameLevel(m_nSelLevel);
//        }else
//        {
//            
//        }
    }
    else if(item->getTag() == TAG_OPTIONS) //Option
    {
//        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, OptionScene::createScene()));
        Director::getInstance()->pushScene(TransitionCrossFade::create(0.5f, OptionScene::createScene()));
    }
    else if(item->getTag() == TAG_START) //Start
    {
        g_nPack = m_nSelPack;
        g_nLevel = m_nSelLevel;
        
        int tiles = g_llGame[g_nLevel].nW * g_llGame[g_nLevel].nH;
        m_gameoptions->setGameDifficulty(tiles);
        
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
    }
    else if(item->getTag() == TAG_2PLAYER) // 2 Player
    {
        m_button_menu->setEnabled(false);
        m_namepopup->removeFirstUserNameFromNameList();
        m_namepopup->showSelectNameBox();
        m_namepopup->setVisible(true);
    }else if (item->getTag() == TAG_UNLOCK)
    {
        m_button_menu->setEnabled(true);
        popupLayer->removeFromParent();
        purchaseAnimalSet(purchase_animalPack);
    }else if (item->getTag() == TAG_BTN_UNLOCKBACK)
    {
        m_button_menu->setEnabled(true);
        popupLayer->removeFromParent();
    }else if (item->getTag() == TAG_BTN_RESTORE)
    {
        IAP::restore();
    }
}

void SelectScene::purchaseAnimalSet(int animalset)
{
   
    CCLOG("Start IAP %s", "unlock_res");
    IAP::purchase("unlock_res");
    m_nUnlockIndex = animalset;
//
}

void SelectScene::unlockAnimalSet(int animalset)
{
    m_nSelPack = animalset;
    m_gameoptions->setPurchased(true);
    setAnimalSet(animalset);
    
    for (int i = 0 ; i < 6; i++) {
        if (m_snake[i] != NULL) {
            m_snake[i]->setVisible(false);
        }
    }
}

void SelectScene::showAnimalUnlockPopUp(int animalset)
{
    purchase_animalPack = animalset;
    
    popupLayer = Layer::create();
    newSprite("g_blackoverlay", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, popupLayer, 10, RATIO_XY);
    Sprite* spt_box = newSprite("selectscene/shop_popup_box", G_SWIDTH * 0.5, getY(1405), popupLayer, 11, RATIO_2);
    
    Sprite* spt_tile = newSprite("selectscene/btn_settile", G_SWIDTH * 0.5, getY(1200), popupLayer, 11, RATIO_2);
    newSprite(StringUtils::format("selectscene/pack%d", animalset + 1).c_str(), spt_tile->getPositionX(), spt_tile->getPositionY() - DISY(30), popupLayer, 11, RATIO_2);
    newSprite("g_snake", spt_tile->getPositionX() - DISX(20), spt_tile->getPositionY() - DISY(30), popupLayer, 11, RATIO_2);
    
    string price_str = StringUtils::format("Unlock Animal Set %d\nMore Tiles\nMore Backgrounds\nMore Animals!", animalset);
    Label* txt_price = newLabel(price_str.c_str(), "fonts/GROBOLD.ttf", DISO(65), G_SWIDTH * 0.5 - DISX(10), getY(1709), popupLayer, 11, RATIO_1);
    txt_price->setAlignment(cocos2d::TextHAlignment::CENTER);
    txt_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    txt_price->setLineHeight(DISY(80));
    txt_price->setColor(TEXT_BROWNCOLOR);
    
    MenuItem* btn_unlock = newButton("selectscene/btn_unlock", getX(1234), getY(2024), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_O);
    btn_unlock->setPositionY(spt_box->getPositionY() - spt_box->getContentSize().height * spt_box->getScaleY() * 0.5 + DISY(200));
    btn_unlock->setTag(TAG_UNLOCK);
    
    MenuItem* btn_back = newButton("optionscene/btn_back", getX(750), getY(2024), CC_CALLBACK_1(SelectScene::onMenu, this), RATIO_O);
    btn_back->setTag(TAG_BTN_UNLOCKBACK);
    btn_back->setPositionY(btn_unlock->getPositionY());
    
    m_btn_pop = Menu::create(btn_unlock, btn_back, NULL);
    m_btn_pop->setPosition(Vec2::ZERO);
    popupLayer->addChild(m_btn_pop, 12);
    this->addChild(popupLayer, 10);
}

void SelectScene::setAnimalSet(int animalset)
{
    m_gameoptions->setAnimalPack(animalset);
    m_sPackHL->setPosition(m_iPacks[animalset]->getPosition());
}

void SelectScene::updateIAP(const std::vector<sdkbox::Product> &products)
{
    
}

void SelectScene::onInitialized(bool ok)
{
    CCLOG("IAP >> Initialized : %s", ok?"true":"false");
}

void SelectScene::onSuccess(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Success: %s", p.name.c_str());
    unlockAnimalSet(m_nUnlockIndex);
}

void SelectScene::onFailure(const sdkbox::Product &p, const std::string &msg)
{
    CCLOG("IAP >> Purchase Failed: %s", p.name.c_str());
}

void SelectScene::onCanceled(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Canceled: %s", p.name.c_str());
}

void SelectScene::onRestored(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Restored: %s", p.name.c_str());
    m_gameoptions->setPurchased(true);
    for (int index = 0; index < 6; index++) {
        if (m_snake[index] != NULL) {
            m_snake[index]->setVisible(false);
        }
    }
}

void SelectScene::onRestoreComplete(bool ok, const std::string &msg)
{
    
}

void SelectScene::onProductRequestSuccess(const std::vector<sdkbox::Product> &products)
{
    CCLOG("IAP >> ProductRequestSuccess >> count : %lu", products.size());
}

void SelectScene::onProductRequestFailure(const std::string &msg)
{
    CCLOG("IAP >> ProductRequestFailure >> %s", msg.c_str());
}

void SelectScene::onEnterTransitionDidFinish()
{
//    Layer::onEnterTransitionDidFinish();
    CCLOG("----- Select Scene onEnter -----");
    if (m_gameoptions->getPurchased())
    {
        for (int i = 0 ; i < 6; i++) {
            if (m_snake[i] != NULL) {
                m_snake[i]->setVisible(false);
            }
        }
    }
}

