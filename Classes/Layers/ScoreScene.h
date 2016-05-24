//
//  OptionScene.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-14.
//
//

#ifndef ScoreScene_h
#define ScoreScene_h

#include "cocos2d.h"
#include "GameOptions.h"
#include "stdio.h"

using namespace cocos2d;
using namespace std;

class ScoreScene : public Layer{
    
public:
    virtual bool init();
    CREATE_FUNC(ScoreScene);
    static Scene* createScene();

private:    
    void createBg();
    void createLabel();
    void createBtn();
    void onMenu(Ref *sender);
    
private:
    Sprite *m_sPecker;
    Menu *m_mMain;
    
    Sprite* m_score_title;
    Sprite* m_score_log;
    Sprite* m_total;
    
    Label* m_time;
    Label* m_accur;
    Label* m_diff;
    Label* m_totalScore;
    Label* m_highScore;
    
    GameOptions* m_gameoptions;
    
    string formatNumber(int value);
};

#endif /* ScoreScene_h */
