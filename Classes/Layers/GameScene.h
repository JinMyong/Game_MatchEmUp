//
//  GameScene.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#ifndef __GameScene__
#define __GameScene__

#include "cocos2d.h"
#include "GameOptions.h"

#define tUnMatchedState     0
#define tFlipState          1
#define tMatchedState       2

#define tCoverAction        10
#define tHideNameAction     200

using namespace cocos2d;
class GameScene : public Layer{
    
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    static Scene* createScene();
    
private:
    void createBg();
    void createBtn();
    void createLabel();
    void onMenu(Ref *sender);
    void createPause();
    void showPause(bool bIsShow);
    
    void initGame();
    int getMatchLeft();
    void setFlippedText(int value);
    void setMatchLeftText();
    void setTimerText();
    void onTimer(float dt);
    
    GameOptions* m_gameoptions;     // Added by Fredric to got game setting.
    int m_nTileNumber;              // Added by Fredric to play animal sound effect.
    Sprite* m_tileNameBoard;        // Added by Fredric to show tile name.
    Label* m_lTileName;             // Added by Fredric to show tile name.
    int prev_open1, prev_open2;     // Added by Fredric to save previous tile number.
    Label* m_userName;              // Added by Fredric to show player name.
    bool isSecondPlayer;            // Added by Fredric to show player name.
    int m_firstMatches;             // Added by Fredric for multiplayer
    int m_secondMatches;            // Added by Fredric for multiplayer
    float m_org_cardScaleX;
    float m_org_cardScaleY;
    CallFunc* hideTileName;
    
    int flip_card_index;
    Sprite* m_flipcard;
    
    void flipCard(Sprite* card);    // Added by Fredric to flip Scard
    void unflipCard(Sprite* card);
    
    //Tiles & Layout
    int m_nW, m_nH;
    int m_nPack;
    Sprite *m_sItem[48], *m_sTile[48];
    int m_nTileInfo[48];
    
    //Game Info
    int m_nTime, m_nFlipped;
    Label *m_lTime, *m_lFlipped, *m_lMatchLeft;
    
    //Game Play
    int m_nOpen1, m_nOpen2;
    bool m_bCanTouch;
    //Pause
    Sprite *m_sBOverlay, *m_sPause;
    Menu *m_mMain, *m_mPause;

    bool m_bIsPaused;
    
    void onEnterTransitionDidFinish() override;
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent)  override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent)  override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent)  override;
    
    void scoring();
};

#endif
