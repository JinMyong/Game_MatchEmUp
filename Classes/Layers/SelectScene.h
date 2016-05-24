//
//  GameScene.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#ifndef __SelectScene__
#define __SelectScene__

#include "cocos2d.h"
#include "NamePopUpLayer.hpp"
#include "GameOptions.h"

#include "PluginIAP/PluginIAP.h"

using namespace cocos2d;
class SelectScene : public Layer, public sdkbox::IAPListener
{
    
    enum{
        TAG_OPTIONS = 1200,
        TAG_START,
        TAG_2PLAYER,
        TAG_UNLOCK,
        TAG_BTN_UNLOCKBACK,
        TAG_BTN_RESTORE
    };
    
public:
    virtual bool init() override;
    CREATE_FUNC(SelectScene);
    static Scene* createScene();
    
    Menu* m_button_menu;
    Menu* m_btn_pop;
    
private:
    void createBg();
    void createLabel();
    void createBtn();
    void onMenu(Ref *sender);
    void setLevelHL(int nLevel);
    
    void unlockAnimalSet(int animalset);
    void purchaseAnimalSet(int animalset);
    void showAnimalUnlockPopUp(int animalset);
    
    void setAnimalSet(int animalset);
    
    Layer* popupLayer;
    
    void updateIAP(const std::vector<sdkbox::Product>& products);
    
    virtual void onInitialized(bool ok) override;
    
    virtual void onSuccess(sdkbox::Product const& p) override;
    
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    
    virtual void onCanceled(sdkbox::Product const& p) override;
    
    virtual void onRestored(sdkbox::Product const& p) override;
    
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    
    virtual void onProductRequestFailure(const std::string &msg) override;
    
    void onRestoreComplete(bool ok, const std::string &msg) override;
    
    void onEnterTransitionDidFinish() override;
    
private:
    int m_nPlayerCnt;
    int m_nSelPack, m_nSelLevel;
    int m_nUnlockIndex;
    Sprite *m_sPackHL, *m_sLevelL_HL, *m_sLevelR_HL;
    Label *m_lPlayerCnt;
    MenuItemImage *m_iPacks[6], *m_iLevels[6];    
    NamePopUpLayer* m_namepopup;
    GameOptions* m_gameoptions;
    int purchase_animalPack;
    Sprite* m_snake[6];
};

#endif
