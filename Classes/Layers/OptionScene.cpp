//
//  OptionScene.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-14.
//
//

#include "OptionScene.h"
#include "GameSettings.h"
#include "GameScene.h"
#include "Const.h"
#include "SelectScene.h"
#include "MainScene.h"

#define TimerTileUnit   0.5

using namespace sdkbox;

Scene* OptionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionScene::create();
    layer->setTag(tLAYER);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool OptionScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_gameoptions = GameOptions::getInstance();

    IAP::setDebug(true);
    IAP::setListener(this);
    IAP::init();
    
    createBg();
    createLabel();
    createBtn();
    
// Added by Fredric for namepopup
    namepopup = NamePopUpLayer::create();
    namepopup->setVisible(false);
    addChild(namepopup, 100);
// Add End
    
    return true;
}

void OptionScene::createBg()
{
    string bg_name = StringUtils::format("backgrounds/bkg_%d", m_gameoptions->getBackgroundIndex());
    m_bg = newSprite(bg_name.c_str(), G_SWIDTH/2, G_SHEIGHT/2, this, 0, RATIO_XY);
    newSprite("g_title", getX(1000), getY(275), this, 1, RATIO_XY);
    newSprite("optionscene/optionbox", getX(985), getY(1415), this, 0, RATIO_XY);
//    newSprite("optionscene/timercounter", getX(1030), getY(1290), this, 1, RATIO_XY);
//    newSprite("optionscene/timelabel", getX(1120), getY(1420), this, 1, RATIO_XY);
    
    newSprite("optionscene/checkbox", getX(1530), getY(1525), this, 1, RATIO_XY);
    
    // Added by Fredric for chameleon animation.
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("res/images/animation/chameleon.plist");
    Sprite* character = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("chameleon-01.png"));
    character->setScale(G_SCALEO);
    character->setPosition(Vec2(getX(1775), getY(1950)));
    this->addChild(character, 2);
    
    Vector<AnimationFrame*> animationFrames;
    for (int index = 1; index <= 31; index++) {
        char frameName[20];
        sprintf(frameName, "chameleon-%02d.png", index);
        SpriteFrame* frame = frameCache->getSpriteFrameByName(frameName);
        auto animFrame = AnimationFrame::create(frame, 1, ValueMap());
        animationFrames.pushBack(animFrame);
    }
    Animation* characterAnimation = Animation::create(animationFrames, 0.15);
    Animate* animate = Animate::create(characterAnimation);
    RepeatForever* runAni = RepeatForever::create(animate);
    character->runAction(runAni);
    
    // Add End
    
    // Added by Fredric to show time indicator.
//    m_sTimerIndicator = newSprite("optionscene/pointer", getX(588.5 + m_gameoptions->getTimerIndicate() * 88.3), getY(1315), this, 1, RATIO_XY);
}

void OptionScene::createLabel()
{
    newLabel("SOUND EFFECTS",   "fonts/GROBOLD.ttf", DISO(90), getX(850), getY(750),  this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
    newLabel("Tiles",           "fonts/GROBOLD.ttf", DISO(75),  getX(700), getY(950),  this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
    newLabel("Animals",         "fonts/GROBOLD.ttf", DISO(75),  getX(700), getY(1065), this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
    newLabel("MUSIC",           "fonts/GROBOLD.ttf", DISO(75),  getX(700), getY(1180), this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
    newLabel("TILE NAME",       "fonts/GROBOLD.ttf", DISO(75),  getX(700), getY(1295), this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
//    newLabel("TIMER TILES", "fonts/GROBOLD.ttf", DISO(75), getX(730), getY(1175), this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
    newLabel("Show image after flip : ", "fonts/GROBOLD.ttf", DISO(75), getX(920), getY(1525), this, 1, RATIO_1)->setColor(TEXT_BROWNCOLOR);
}

void OptionScene::createBtn()
{
    MenuItemImage *iBack = newButton("optionscene/btn_back", getX(550), getY(2415), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iBack->setTag(TAG_BTN_BACK);
    MenuItemImage *iLeaderboard = newButton("optionscene/btn_leaderboard", getX(1015), getY(2415), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
    iLeaderboard->setTag(TAG_BTN_LEADERBOARD);
    MenuItemImage *iPlay = newButton("optionscene/btn_play", getX(1505), getY(2415), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iPlay->setTag(TAG_BTN_PLAY);
    
//    MenuItemImage *iLeft = newButton("optionscene/arrow_left", getX(455), getY(1290), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
//    iLeft->setTag(TAG_BTN_LEFT);
//    MenuItemImage *iRight = newButton("optionscene/arrow_right", getX(1605), getY(1290), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
//    iRight->setTag(TAG_BTN_RIGHT);

    MenuItemToggle *iTiles = newToggleButton("optionscene/btn_switch_on", "optionscene/btn_switch_off", getX(1360), getY(950), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iTiles->setTag(TAG_BTN_TILES);
    
    MenuItemToggle *iAnimals = newToggleButton("optionscene/btn_switch_on", "optionscene/btn_switch_off", getX(1360), getY(1065), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iAnimals->setTag(TAG_BTN_ANIMAL);
    
    MenuItemToggle *iMusic = newToggleButton("optionscene/btn_switch_on", "optionscene/btn_switch_off", getX(1360), getY(1180), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iMusic->setTag(TAG_BTN_MUSIC);
    
    MenuItemToggle *iTilename = newToggleButton("optionscene/btn_switch_on", "optionscene/btn_switch_off", getX(1360), getY(1295), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iTilename->setTag(TAG_BTN_TILENAME);

    MenuItemToggle *iFlip = newToggleButton("optionscene/check_yes", "optionscene/check_no", getX(1550), getY(1485), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    iFlip->setTag(TAG_BTN_FLIP);
    
    MenuItemImage* iChangeName = newButton("optionscene/btn_change_name", getX(1030), getY(1680),  CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
    iChangeName->setTag(TAG_BTN_CHANGENAME);
    
    MenuItemImage *iChangeTile = newButton("optionscene/btn_changetile", getX(700), getY(1945), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
    iChangeTile->setTag(TAG_BTN_CHANGETILE);
    MenuItemImage *iChangeBG = newButton("optionscene/btn_changebg", getX(1345), getY(1945), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
    iChangeBG->setTag(TAG_BTN_CHANGEBG);
    
    MenuItemImage* iRestore = newButton("optionscene/btn_restore", getX(1030), getY(2200), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_XY);
    iRestore->setTag(TAG_BTN_RESTORE);
   
    m_mMain = Menu::create(iBack, /*iLeaderboard,*/ iPlay, iTiles, iAnimals, iMusic, /*iLeft, iRight,*/ iTilename, iFlip, iChangeName, iChangeTile, iChangeBG, iRestore, NULL);
    m_mMain->setPosition(Point(0, 0));
    addChild(m_mMain, 1);
    
// Added by Fredric to update toggle item status
    
    // Play Tile Flip Sound Effect
    if (m_gameoptions->getTileSoundEffectOption()) {
        iTiles->setSelectedIndex(0);
    }else
    {
        iTiles->setSelectedIndex(1);
    }
    
    // Play Animal Sound Effect
    if (m_gameoptions->getAnimalSoundEffectOption()) {
        iAnimals->setSelectedIndex(0);
    }else
    {
        iAnimals->setSelectedIndex(1);
    }
    
    // Play Background Music
    if (m_gameoptions->getBackgroundMusicOption()) {
        iMusic->setSelectedIndex(0);
    }else
    {
        iMusic->setSelectedIndex(1);
    }
    
    // Show Image After Flip
    if (m_gameoptions->getShowImageOption())
    {
        iFlip->setSelectedIndex(0);
    }else
    {
        iFlip->setSelectedIndex(1);
    }
    
    // Show Tile Name
    if (m_gameoptions->getTileNameOption()) {
        iTilename->setSelectedIndex(0);
    }else
    {
        iTilename->setSelectedIndex(1);
    }
    
// Add end
}

void OptionScene::onMenu(Ref *sender)
{
//    int nIndicatorPos[] = {};
    MenuItem *item = (MenuItem *)sender;
    int nTag = item->getTag();
    
    switch (nTag) {
        case TAG_BTN_BACK:
            Director::getInstance()->popScene();
            break;
        case TAG_BTN_LEADERBOARD:
            break;
        case TAG_BTN_PLAY:
            if (m_gameoptions->getFirstUserName().compare("") == 0) {
                if (m_gameoptions->getNameCount() == 0) {
                    namepopup->setVisible(true);
                    namepopup->showCreateNameBox();
                    m_mMain->setEnabled(false);
                }else
                {
                    namepopup->setVisible(true);
                    namepopup->showSelectNameBox();
                    namepopup->setGotoAfterSelect(true);
                    m_mMain->setEnabled(false);
                }
            }else
            {
                gotoSelectScene();
            }            
            break;
        case TAG_BTN_LEFT:
            if (m_gameoptions->getTimerIndicate() > TimerTileUnit) {
                m_gameoptions->setTimerInstance(m_gameoptions->getTimerIndicate() - TimerTileUnit);
                m_sTimerIndicator->setPosition(Vec2(m_sTimerIndicator->getPositionX() - getX(88.3) * TimerTileUnit, m_sTimerIndicator->getPositionY()));
            }
            break;
        case TAG_BTN_RIGHT:
            if (m_gameoptions->getTimerIndicate() < 10) {
                m_gameoptions->setTimerInstance(m_gameoptions->getTimerIndicate() + TimerTileUnit);
                m_sTimerIndicator->setPosition(Vec2(m_sTimerIndicator->getPositionX() + getX(88.3) * TimerTileUnit, m_sTimerIndicator->getPositionY()));
            }
            break;
        case TAG_BTN_CHANGETILE:
            m_mMain->setEnabled(false);
            showChangePopup(false);
            break;
        case TAG_BTN_CHANGEBG:
            m_mMain->setEnabled(false);
            showChangePopup(true);
            break;
        case TAG_BTN_RESTORE:
            IAP::restore();
            break;
        case TAG_BTN_TILES:
            m_gameoptions->setTileSoundEffectOption(!m_gameoptions->getTileSoundEffectOption());
            break;
        case TAG_BTN_ANIMAL:
            m_gameoptions->setAnimalSoundEffectOption(!m_gameoptions->getAnimalSoundEffectOption());
            break;
        case TAG_BTN_MUSIC:
            m_gameoptions->setBackgroundMusicOption(!m_gameoptions->getBackgroundMusicOption());
            break;
        case TAG_BTN_FLIP:
            m_gameoptions->setShowImageOption(!m_gameoptions->getShowImageOption());
            break;
        case TAG_BTN_TILENAME:
            m_gameoptions->setTileNameOption(!m_gameoptions->getTileNameOption());
            break;
        case TAG_BTN_CHANGENAME:
            namepopup->setVisible(true);
            namepopup->showSelectNameBox();
            m_mMain->setEnabled(false);
            break;
        case TAG_BTN_SHOWBACK:
            m_mMain->setEnabled(true);
            m_changePopUp->removeFromParent();
            break;
        case TAG_BTN_PREV:
                if (m_currentPage > 0) {
                    m_currentPage--;
                    showChangePopupPage(m_currentPage);
                }
            break;
        case TAG_BTN_NEXT:
                if (m_currentPage < 2) {
                    m_currentPage++;
                    showChangePopupPage(m_currentPage);
                }
            break;
        default:
            break;
    }
}

void OptionScene::gotoSelectScene()
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->removeSpriteFrames();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
}

void OptionScene::onChange(Ref* sender)
{
    MenuItemToggle *item = (MenuItemToggle *)sender;
    item->setSelectedIndex(0);
    int index = item->getTag() - 1000;

    m_currentUnlockIndex = index;
    if (!m_gameoptions->getPurchased() && index != 0) {
        m_showMenu->setEnabled(false);
        showUnlockPopup(index);
    }else
    {
        if (m_currentShowChangeBG) {
            setBackground(index);
        }else{
            setTileCover(index);
        }
        
    }
    
}

void OptionScene::showChangePopup(bool isBackground)
{
    // Init visible variables.
    m_currentShowChangeBG = isBackground;
    m_currentPage = m_gameoptions->getBackgroundIndex() / 4;
    
    m_changePopUp = Layer::create();
    this->addChild(m_changePopUp, 10);
    
//    Sprite* spt_title = newSprite("g_title", G_SWIDTH * 0.5, G_SHEIGHT, m_unlockPopUp, 10, RATIO_O);
//    spt_title->setAnchorPoint(Vec2(0.5, 1));
    newSprite("g_blackoverlay", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, m_changePopUp, 10, RATIO_XY);
    Sprite* chg_box = newSprite("optionscene/unlock_box", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, m_changePopUp, 10, RATIO_XY);
    
    // Add back button
    MenuItemImage *btn_back = newButton("optionscene/btn_back", getX(550), chg_box->getPositionY() - chg_box->getContentSize().height * 0.5 * chg_box->getScaleY() + DISY(300), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    btn_back->setTag(TAG_BTN_SHOWBACK);
    m_showMenu = Menu::create(btn_back, NULL);
    m_showMenu->setPosition(Vec2::ZERO);
    m_changePopUp->addChild(m_showMenu, 11);
    
    // Add previous and next page button
    MenuItemImage* btn_prev = newButton("optionscene/arrow_left", getX(730), chg_box->getPositionY() - chg_box->getContentSize().height * 0.5 * chg_box->getScaleY() + DISY(500), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    btn_prev->setTag(TAG_BTN_PREV);
    m_showMenu->addChild(btn_prev);
    
    MenuItemImage* btn_next = newButton("optionscene/arrow_right", getX(1410), btn_prev->getPositionY(), CC_CALLBACK_1(OptionScene::onMenu, this), RATIO_O);
    btn_next->setTag(TAG_BTN_NEXT);
    m_showMenu->addChild(btn_next);
    
    // Show "Change Backgrounds" Title.
    Label* lbl_title;
    if (m_currentShowChangeBG) {
        lbl_title = newLabel(Txt_CHANGEBACKGROUNDS, "fonts/GROBOLD.ttf", DISO(85), G_SWIDTH * 0.5, getY(650), m_changePopUp, 11, RATIO_1);
    }else{
        lbl_title = newLabel(Txt_CHANGETILECOVERS, "fonts/GROBOLD.ttf", DISO(85), G_SWIDTH * 0.5, getY(650), m_changePopUp, 11, RATIO_1);
    }
    lbl_title->setColor(TEXT_BROWNCOLOR);
    lbl_title->setAlignment(cocos2d::TextHAlignment::CENTER);
    
    // Add Background Packs.
    for (int page = 0; page < 3; page++) {
        for (int y_index = 0; y_index < 2; y_index++) {
            for (int x_index = 0; x_index < 2; x_index++) {
                int index = page * 4 + y_index * 2 + x_index;
                string normal;
                string select;
                if (isBackground) {
                    normal = StringUtils::format("optionscene/backgroudchange/bkg_%d_off", index);
                    select = StringUtils::format("optionscene/backgroudchange/bkg_%d_on", index);
                }else
                {
                    normal = StringUtils::format("optionscene/tilecoverchange/card_%d_off", index);
                    select = StringUtils::format("optionscene/tilecoverchange/card_%d_on", index);
                }
                m_unlockItem[index] = newToggleButton(normal.c_str(), select.c_str(), getX(750 + 680 * x_index), getY(1100 + 610 * y_index), CC_CALLBACK_1(OptionScene::onChange, this), RATIO_O);
                m_unlockItem[index]->setTag(1000 + index);
                m_unlockItem[index]->setVisible(false);
                
                if (index != 0) {
                    m_snake[index] = newSprite("optionscene/snake", m_unlockItem[index]->getPositionX() - DISX(20), m_unlockItem[index]->getPositionY() - DISY(30), m_changePopUp, 12, RATIO_O);
                    if (!m_gameoptions->getPurchased())
                    {
                        m_snake[index]->setVisible(false);
                    }
                }
                m_showMenu->addChild(m_unlockItem[index]);
            }
        }
    }
    
    // Add page dots
    for (int i = 0 ; i < 3; i++) {
        m_offSprite[i] = newSprite("optionscene/page_off", getX(900 + 170 * i), btn_prev->getPositionY(), m_changePopUp, 11, RATIO_O);
    }
    
    m_onSprite = newSprite("optionscene/page_off", getX(850 + 220 * m_currentPage), btn_prev->getPositionY(), m_changePopUp, 11, RATIO_O);
    
    // Set high light
    if (m_unlockItem[m_gameoptions->getBackgroundIndex()] != NULL) {
        m_unlockItem[m_gameoptions->getBackgroundIndex()]->setSelectedIndex(1);
    }
    
    // show background page.
    showChangePopupPage(m_currentPage);
}

void OptionScene::showChangePopupPage(int page)
{
    for (int i = 0 ; i < 12; i++) {
        m_unlockItem[i]->setVisible(false);
        if (m_snake[i] != NULL) {
            m_snake[i]->setVisible(false);
        }
    }
    
    m_onSprite->setPositionX(getX(900 + 170 * page));
    
    for (int i = 0 ; i < 4; i++) {
        int index = page * 4 + i;
        m_unlockItem[index]->setVisible(true);
        if (m_snake[index] != NULL && !m_gameoptions->getPurchased() && index != 0) {
            m_snake[index]->setVisible(true);
        }
    }
}

void OptionScene::showUnlockPopup(int index)
{
    m_unlockPopUp = Layer::create();
    this->addChild(m_unlockPopUp, 20);
    // add unlock box
    Sprite* spt_box = newSprite("selectscene/shop_popup_box", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, m_unlockPopUp, 21, RATIO_2);
    // add unlock background
    string str_img;
    if (m_currentShowChangeBG) {
        str_img = StringUtils::format("optionscene/backgroudchange/bkg_%d_off", index);
    }else
    {
        str_img = StringUtils::format("optionscene/tilecoverchange/card_%d_off", index);
    }
    
    Sprite* spt_tile = newSprite(str_img.c_str(), G_SWIDTH * 0.5, getY(1200), m_unlockPopUp, 21, RATIO_O);
    float currentScale = spt_tile->getScale();
    spt_tile->setScale(currentScale * 0.8);
    Sprite* spt_snake = newSprite("optionscene/snake", spt_tile->getPositionX() - DISX(20), spt_tile->getPositionY() - DISY(30), m_unlockPopUp, 21, RATIO_O);
    currentScale = spt_snake->getScale();
    spt_snake->setScale(currentScale * 0.8);
    
    string price_str;
    if (m_currentShowChangeBG) {
        price_str = StringUtils::format("Unlock Background %d\nMore Tiles\nMore Backgrounds\nMore Animals!", index);
        // Unlock Animal Set 1 - More Tiles, More Backgrounds, More Animals and Sounds!
    }else
    {
        price_str = StringUtils::format("Unlock Tile %d\nMore Tiles\nMore Backgrounds\nMore Animals!", index);
    }
    Label* txt_price = newLabel(price_str.c_str(), "fonts/GROBOLD.ttf", DISO(65), G_SWIDTH * 0.5, getY(1709), m_unlockPopUp, 21, RATIO_1);
    txt_price->setAlignment(cocos2d::TextHAlignment::CENTER);
    txt_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    txt_price->setLineHeight(DISY(80));
    txt_price->setColor(TEXT_BROWNCOLOR);
    
    MenuItem* btn_unlock = newButton("selectscene/btn_unlock", getX(1184), getY(2024), CC_CALLBACK_1(OptionScene::onUnlock, this), RATIO_O);
    btn_unlock->setPositionY(spt_box->getPositionY() - spt_box->getContentSize().height * spt_box->getScaleY() * 0.5 + DISY(150));
    btn_unlock->setTag(TAG_BTN_UNLOCK);
    
    MenuItem* btn_back = newButton("optionscene/btn_back", getX(750), getY(2024), CC_CALLBACK_1(OptionScene::onUnlock, this), RATIO_O);
    btn_back->setTag(TAG_BTN_UNLOCKBACK);
    btn_back->setPositionY(btn_unlock->getPositionY());
    m_unlockMenu = Menu::create(btn_unlock, btn_back, NULL);
    m_unlockMenu->setPosition(Vec2::ZERO);
    m_unlockPopUp->addChild(m_unlockMenu, 21);
}

void OptionScene::onUnlock(cocos2d::Ref *sender)
{
    MenuItem *item = (MenuItem *)sender;
    int nTag = item->getTag();
    
    if (nTag == TAG_BTN_UNLOCK) {
//        if (m_currentShowChangeBG) {
//            unlockBackgrounds(m_currentUnlockIndex);
//        }else
//        {
//            unlockTileCovers(m_currentUnlockIndex);
//        }
        m_unlockPopUp->removeFromParent();
        m_showMenu->setEnabled(true);
        IAP::purchase("unlock_res");
    }else if (nTag == TAG_BTN_UNLOCKBACK)
    {
        m_unlockPopUp->removeFromParent();
        m_showMenu->setEnabled(true);
    }
}

void OptionScene::unlockBackgrounds(int index)
{
    m_gameoptions->setPurchased(true);
    setBackground(index);
    string bg_name = StringUtils::format("res/images/backgrounds/bkg_%d.png", m_gameoptions->getBackgroundIndex());
    m_bg->setTexture(bg_name);
    for (int i = 0; i < 12; i++) {
        if (m_snake[i] != NULL) {
            m_snake[i]->setVisible(false);
        }
    }
}

void OptionScene::unlockTileCovers(int index)
{
    m_gameoptions->setPurchased(true);
    setTileCover(index);
    for (int i = 0; i < 12; i++) {
        if (m_snake[i] != NULL) {
            m_snake[i]->setVisible(false);
        }
    }
}

void OptionScene::setBackground(int index)
{
    m_gameoptions->setBackgroundIndex(index);
    string bg_name = StringUtils::format("res/images/backgrounds/bkg_%d.png", m_gameoptions->getBackgroundIndex());
    m_bg->setTexture(bg_name);
    for (int i = 0; i < 12; i++) {
        if (m_unlockItem[i] != NULL && i != index) {
            m_unlockItem[i]->setSelectedIndex(0);
        }else
        {
            m_unlockItem[i]->setSelectedIndex(1);
        }
    }
}

void OptionScene::setTileCover(int index)
{
    m_gameoptions->setTileCoverIndex(index);
    for (int i = 0; i < 12; i++) {
        if (m_unlockItem[i] != NULL && i != index) {
            m_unlockItem[i]->setSelectedIndex(0);
        }else
        {
            m_unlockItem[i]->setSelectedIndex(1);
        }
    }
}

void OptionScene::updateIAP(const std::vector<sdkbox::Product> &products)
{
    
}

void OptionScene::onInitialized(bool ok)
{
    
}

void OptionScene::onSuccess(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Success: %s", p.name.c_str());
    if (m_currentShowChangeBG) {
        unlockBackgrounds(m_currentUnlockIndex);
    }else
    {
        unlockTileCovers(m_currentUnlockIndex);
    }
}

void OptionScene::onFailure(const sdkbox::Product &p, const std::string &msg)
{
    CCLOG("IAP >> Purchase Failed: %s", p.name.c_str());
}

void OptionScene::onCanceled(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Canceled: %s", p.name.c_str());
}

void OptionScene::onRestored(const sdkbox::Product &p)
{
    CCLOG("IAP >> Purchase Restored: %s", p.name.c_str());
    m_gameoptions->setPurchased(true);
}

void OptionScene::onRestoreComplete(bool ok, const std::string &msg)
{
    CCLOG("IAP >> Purchase Restore Completed: %s", msg.c_str());
}

void OptionScene::onProductRequestSuccess(const std::vector<sdkbox::Product> &products)
{
    
}

void OptionScene::onProductRequestFailure(const std::string &msg)
{
    
}


