//
//  NamePopUpLayer.hpp
//  MatchEmUp
//
//  Created by Fredric on 3/6/16.
//
//

#ifndef NamePopUpLayer_hpp
#define NamePopUpLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameOptions.h"

#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;

enum
{
    TAG_GO_BTN = 1000,
    TAG_YES_BTN,
    TAG_NO_BTN,
    TAG_CHANGE_BTN,
    TAG_DELETE_BTN,
    TAG_CREATE_BTN,
    TAG_SELECT_BTN,
    TAG_PLAY_BTN, // GO BUTTON ON LASTNAME POPUP
    TAG_CELL_BG,
    TAG_BACK_BTN,
    TAG_MAX
};
enum
{
    Z_BG = 10,
    Z_BOX,
    Z_LABEL,
    Z_ITEM,
    Z_BUTTON,
    Z_LAYER,
    Z_ACTIVE
};

class NamePopUpLayer : public Layer, public ui::EditBoxDelegate, public TableViewDataSource, public TableViewDelegate
{
public:
    virtual bool init();
    static Scene* createScene();
    
    void createBackground();
    void createNameCreateLayer();
    void createDeleteNameLayer();
    void createSelectNameLayer();
    void createLastNameLayer();
    void onMenu(Ref* pSender);
    void editBoxReturn(EditBox* editBox);
    
    void showCreateNameBox();
    void showDeleteNameBox();
    void showSelectNameBox();
    void showLastNameBox();
    
    void hideCreateNameBox();
    void hideDeleteNameBox();
    void hideSelectNameBox();
    void hideLastNameBox();
    
    void selectNamme();
    void deleteName();
    void createName();
    void sortName();
    void removeFirstUserNameFromNameList();
    
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    CREATE_FUNC(NamePopUpLayer);
    
    Menu* m_delete_menu;
    Menu* m_change_menu;
    Menu* m_select_menu;
    Menu* m_go_menu;
    Label* m_lastname_label;
    
    TableView* m_tableview;
    
    bool m_isSelectSecondPlayer;
    void setGotoAfterSelect(bool value);
    
private:
    void creatBackground();
    Layer* m_nameCreateLayer;
    Layer* m_nameSelectLayer;
    Layer* m_nameDeleteLayer;
    Layer* m_lastNameLayer;
    EditBox *m_editName;
    GameOptions* m_gameoptions;
    std::vector<std::string> nameList;
    int selectedIndex;
    bool m_gotoAfterSelect;
};

#endif /* NamePopUpLayer_hpp */
