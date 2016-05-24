//
//  MainScene.hpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-13.
//
//

#ifndef MainScene_h
#define MainScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NamePopUpLayer.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

class MainScene : public Layer, public ui::EditBoxDelegate{
    
public:
    virtual bool init();
    CREATE_FUNC(MainScene);
    static Scene* createScene();
    void gotoSelectScene();

private:
    void createBg();
    void createLabel();
    void createBtn();
    void createPopup();
    void showPopup(bool bIsShow);
    void onMenu(Ref *sender);
    
    //void editBoxEditingDidBegin(EditBox* editBox);
    //void editBoxEditingDidEnd(EditBox* editBox);
    //void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);

private:
    Sprite *m_sBOverlay, *m_sPopup;//, *m_sPContent;
    Label *m_lPopup;
    Menu *m_mMain, *m_mPopup;
    EditBox *m_editName;
    
    NamePopUpLayer* m_popup;
};

#endif /* MainScene_h*/
