//
//  OptionScene.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-14.
//
//

#ifndef OptionScene_h
#define OptionScene_h

#include "cocos2d.h"
#include "GameOptions.h"
#include "NamePopUpLayer.hpp"

#include "PluginIAP/PluginIAP.h"

using namespace cocos2d;



class OptionScene : public Layer, public sdkbox::IAPListener
{
enum
{
    TAG_BTN_BACK = 1000,
    TAG_BTN_LEADERBOARD,
    TAG_BTN_PLAY,
    TAG_BTN_LEFT,
    TAG_BTN_RIGHT,
    TAG_BTN_CHANGETILE,
    TAG_BTN_CHANGEBG,
    TAG_BTN_TILES,
    TAG_BTN_ANIMAL,
    TAG_BTN_MUSIC,
    TAG_BTN_FLIP,
    TAG_BTN_TILENAME,
    TAG_BTN_CHANGENAME,
    TAG_BTN_SHOWBACK,
    TAG_BTN_PREV,
    TAG_BTN_NEXT,
    TAG_BTN_UNLOCK,
    TAG_BTN_UNLOCKBACK,
    TAG_BTN_RESTORE
};
    
public:
    virtual bool init() override;
    CREATE_FUNC(OptionScene);
    static Scene* createScene();
    GameOptions* m_gameoptions;
    
    Menu* m_mMain;
    Menu* m_showMenu;
    Menu* m_unlockMenu;
    
    void gotoSelectScene();

private:    
    void createBg();
    void createLabel();
    void createBtn();
    void onMenu(Ref *sender);
    void onChange(Ref *sender);
    void onUnlock(Ref *sender);
    
    void showChangePopup(bool isBackground);
    void showChangePopupPage(int page);
    void showUnlockPopup(int index);
    
    void unlockBackgrounds(int index);    
    void unlockTileCovers(int index);
    
    void setBackground(int index);
    void setTileCover(int index);
    
    
    void updateIAP(const std::vector<sdkbox::Product>& products);
    
    virtual void onInitialized(bool ok) override;
    
    virtual void onSuccess(sdkbox::Product const& p) override;
    
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    
    virtual void onCanceled(sdkbox::Product const& p) override;
    
    virtual void onRestored(sdkbox::Product const& p) override;
    
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    
    virtual void onProductRequestFailure(const std::string &msg) override;
    
    void onRestoreComplete(bool ok, const std::string &msg) override;
    
    
    Sprite* m_sTimerIndicator;
    Sprite* m_bg;
    NamePopUpLayer* namepopup;
    Layer* m_changePopUp;
    Layer* m_unlockPopUp;
    
    MenuItemToggle* m_unlockItem[12];
    MenuItemToggle* m_tileItem[12];
    
    bool m_currentShowChangeBG;
    int m_currentPage;
    int m_currentUnlockIndex;
    
    Sprite* m_offSprite[3];
    Sprite* m_onSprite;
    Sprite* m_snake[12];
};

#endif /* OptionScene_h */
