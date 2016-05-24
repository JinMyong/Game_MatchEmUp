//
//  NamePopUpLayer.cpp
//  MatchEmUp
//
//  Created by PAK on 3/10/16.
//
//

#include "NamePopUpLayer.hpp"
#include "GameSettings.h"
#include "Const.h"

#include "SelectScene.h"
#include "OptionScene.h"
#include "MainScene.h"

#define CELL_HEIGHT     DISY(80)
#define CELL_WIDTH      DISX(975)
#define TABLE_HEIGHT    DISY(420)

#pragma mark - Initial Layer

Scene* NamePopUpLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NamePopUpLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool NamePopUpLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    m_gameoptions = GameOptions::getInstance();
    nameList = m_gameoptions->getNameList();
    selectedIndex = 0;
    m_isSelectSecondPlayer = false;
    m_gotoAfterSelect = false;
    
    createBackground();
    
    m_nameCreateLayer = Layer::create();
    m_nameDeleteLayer = Layer::create();
    m_nameSelectLayer = Layer::create();
    m_lastNameLayer = Layer::create();
    
    createNameCreateLayer();
    createDeleteNameLayer();
    createSelectNameLayer();
    createLastNameLayer();
    
    m_nameCreateLayer->setVisible(false);
    m_nameDeleteLayer->setVisible(false);
    m_nameSelectLayer->setVisible(false);
    m_lastNameLayer->setVisible(false);
    
    return true;
}

void NamePopUpLayer::createBackground()
{
    newSprite("g_blackoverlay", G_SWIDTH/2, G_SHEIGHT/2, this, Z_BG, RATIO_XY);
}

void NamePopUpLayer::createNameCreateLayer()
{
    Sprite* box = newSprite("namepopup/welcome_box", getX(1025), getY(1220), m_nameCreateLayer, Z_BOX, RATIO_O);
    box->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5);
    
    float button_posY = box->getPositionY() - box->getContentSize().height * box->getScaleY() * 0.5 + 100 * G_SCALEY;
    
    Label* lbl_createName = newLabel("Create your username", "fonts/GROBOLD.ttf", DISO(65), getX(1030), getY(1225), m_nameCreateLayer, Z_LABEL, RATIO_1);
    lbl_createName->setColor(TEXT_BROWNCOLOR);
    lbl_createName->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5 + 50 * G_SCALEY);
    lbl_createName->setAlignment(TextHAlignment::CENTER);
    
    MenuItemImage *iGo = newButton("mainscene/btn_go", getX(1235), getY(1550), CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iGo->setAnchorPoint(Vec2(0.5, 0.5));
    iGo->setPositionY(button_posY);
    iGo->setTag(TAG_GO_BTN);
    
    m_go_menu = Menu::create(iGo, NULL);
    m_go_menu->setPosition(Vec2::ZERO);
    m_nameCreateLayer->addChild(m_go_menu, Z_BUTTON);
    
    m_editName = EditBox::create(Size(650 * G_SCALEX, 100 * G_SCALEY), ui::Scale9Sprite::create("res/images/mainscene/editback.png"));
    m_editName->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT * 0.5 - 50 * G_SCALEY));
    m_editName->setMaxLength(14);
    m_editName->setFontSize(DISO(100));
    m_editName->setFontName("fonts/GROBOLD.ttf");
    m_editName->setFontColor(TEXT_BROWNCOLOR);
    m_editName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    m_editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    m_editName->setColor(Color3B::BLUE);
    m_editName->setDelegate(this);
    m_editName->setText("");
    m_editName->setPlaceHolder("-----------");
    m_editName->setPlaceholderFontColor(TEXT_BROWNCOLOR);
    m_nameCreateLayer->addChild(m_editName, Z_ITEM);
    
    this->addChild(m_nameCreateLayer, Z_LAYER);
}


void NamePopUpLayer::createDeleteNameLayer()
{
    Sprite* box = newSprite("namepopup/delete_name_box", getX(1025), getY(1220), m_nameDeleteLayer, Z_BOX, RATIO_O);
    box->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5);
    
    float button_posY = box->getPositionY() - box->getContentSize().height * box->getScaleY() * 0.5 + 120 * G_SCALEY;
    
    Label* lbl_deleteName = newLabel(Txt_DELETENAME, "fonts/GROBOLD.ttf", DISO(70), getX(1025), getY(1620), m_nameDeleteLayer, Z_LABEL, RATIO_1);
    lbl_deleteName->setPositionY(G_SHEIGHT * 0.5);
    lbl_deleteName->setColor(TEXT_BROWNCOLOR);
    lbl_deleteName->setAlignment(TextHAlignment::CENTER);
//    lbl_deleteName->setDimensions(820 * G_SCALEX, DISO(65) * 5);
    
    MenuItemImage* iYes = newButton("namepopup/btn_yes", getX(1230), getY(1500), CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iYes->setPositionY(button_posY);
    iYes->setTag(TAG_YES_BTN);
    
    MenuItemImage* iNo = newButton("namepopup/btn_no", getX(805), getY(1500), CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iNo->setPositionY(button_posY);
    iNo->setTag(TAG_NO_BTN);
    
    m_delete_menu = Menu::create(iYes, iNo, NULL);
    m_delete_menu->setPosition(Vec2::ZERO);
    m_nameDeleteLayer->addChild(m_delete_menu, Z_BUTTON);
    
    this->addChild(m_nameDeleteLayer, Z_LAYER);
}

void NamePopUpLayer::createLastNameLayer()
{
    Sprite* box = newSprite("namepopup/welcome_box", getX(1025), getY(1220), m_lastNameLayer, Z_BG, RATIO_O);
    box->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5);
    
    float button_posY = box->getPositionY() - box->getContentSize().height * box->getScaleY() * 0.5 + DISY(150);
    
    m_lastname_label = newLabel(m_gameoptions->getLastUsedName().c_str(), "fonts/GROBOLD.ttf", DISO(70), getX(1030), getY(1225), m_lastNameLayer, Z_LABEL, RATIO_1);
    m_lastname_label->setColor(TEXT_BROWNCOLOR);
    m_lastname_label->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5);
    m_lastname_label->setAlignment(TextHAlignment::CENTER);
    
    MenuItemImage *iChange = newButton("mainscene/btn_change", getX(805), getY(1550), CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iChange->setPositionY(button_posY);
    iChange->setTag(TAG_CHANGE_BTN);
    
    MenuItemImage *iGo = newButton("mainscene/btn_go", getX(1355), getY(1550), CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iGo->setPositionY(button_posY);
    iGo->setTag(TAG_PLAY_BTN);
    
    m_change_menu = Menu::create(iChange, iGo, NULL);
    m_change_menu->setPosition(Vec2::ZERO);
    m_lastNameLayer->addChild(m_change_menu, Z_BUTTON);
    
    this->addChild(m_lastNameLayer, Z_LAYER);
}

void NamePopUpLayer::createSelectNameLayer()
{
    Sprite* box = newSprite("namepopup/players_list_box", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, m_nameSelectLayer, Z_BOX, RATIO_O);
    box->setPosition(G_SWIDTH * 0.5, G_SHEIGHT * 0.5);
    
    float button_posY = box->getPositionY() - box->getContentSize().height * box->getScaleY() * 0.5 + 150 * G_SCALEY;
    
    MenuItemImage* iBack = newButton("namepopup/btn_back", getX(421), button_posY, CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iBack->setTag(TAG_BACK_BTN);
    
    MenuItemImage* iDelete = newButton("namepopup/btn_delete", getX(821), button_posY, CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iDelete->setTag(TAG_DELETE_BTN);
    
    MenuItemImage* iCreate = newButton("namepopup/btn_create", getX(1288), button_posY, CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iCreate->setTag(TAG_CREATE_BTN);
    
    MenuItemImage* iSelect = newButton("namepopup/btn_select", getX(1688), button_posY, CC_CALLBACK_1(NamePopUpLayer::onMenu, this), RATIO_O);
    iSelect->setTag(TAG_SELECT_BTN);
    
    m_select_menu = Menu::create(iBack, iDelete, iCreate, iSelect, NULL);
    m_select_menu->setPosition(Vec2::ZERO);
    m_nameSelectLayer->addChild(m_select_menu, Z_BUTTON);
    
    Size winsize = Director::getInstance()->getWinSize();
    
    m_tableview = TableView::create(this, Size(CELL_WIDTH, TABLE_HEIGHT));
    m_tableview->setDirection(TableView::Direction::VERTICAL);
    m_tableview->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_tableview->setAnchorPoint(Vec2(0.5, 0.5));
    m_tableview->setPosition(Vec2(G_SWIDTH * 0.5 - CELL_WIDTH * 0.5, G_SHEIGHT * 0.5 - TABLE_HEIGHT * 0.5 - DISY(20)));
    m_tableview->setDelegate(this);
    m_nameSelectLayer->addChild(m_tableview, Z_ITEM);
    
    this->addChild(m_nameSelectLayer, Z_LAYER);
}

#pragma mark - Show Methods for Every Dialog

void NamePopUpLayer::showCreateNameBox()
{
    m_editName->setText("");
    m_editName->setFocusEnabled(true);
    m_editName->setFocused(true);
    
    m_nameCreateLayer->setLocalZOrder(Z_ACTIVE);
    m_nameCreateLayer->setVisible(true);
}

void NamePopUpLayer::showDeleteNameBox()
{
    m_select_menu->setEnabled(false);
    m_nameDeleteLayer->setLocalZOrder(Z_ACTIVE);
    m_nameDeleteLayer->setVisible(true);
}

void NamePopUpLayer::showLastNameBox()
{
    m_lastNameLayer->setLocalZOrder(Z_ACTIVE);
    m_lastNameLayer->setVisible(true);
}

void NamePopUpLayer::showSelectNameBox()
{
    m_tableview->reloadData();
    m_nameSelectLayer->setLocalZOrder(Z_ACTIVE);
    m_nameSelectLayer->setVisible(true);
}

void NamePopUpLayer::hideCreateNameBox()
{
    m_nameCreateLayer->setLocalZOrder(Z_LAYER);
    m_nameCreateLayer->setVisible(false);
}

void NamePopUpLayer::hideDeleteNameBox()
{
    m_select_menu->setEnabled(true);
    m_nameDeleteLayer->setLocalZOrder(Z_LAYER);
    m_nameDeleteLayer->setVisible(false);
}

void NamePopUpLayer::hideLastNameBox()
{
    m_lastNameLayer->setLocalZOrder(Z_LAYER);
    m_lastNameLayer->setVisible(false);
}

void NamePopUpLayer::hideSelectNameBox()
{
    auto parent = this->getParent();
    if (dynamic_cast<OptionScene*>(parent)) {
        // if this dialog shows on option scene, enable buttons of option scene and hide dialog.
        ((OptionScene*)parent)->m_mMain->setEnabled(true);
        if (nameList.size() > 0) {
            m_gameoptions->setFirstUserName(nameList.at(selectedIndex).c_str());
            this->setVisible(false);
        }else
        {
            this->setVisible(false);
        }
    }else if (dynamic_cast<MainScene*>(parent) && m_lastNameLayer->isVisible())
    {
        // if this dialog shows with last name dialog, enable buttons of last name dialog and update last name label.
        
        if (m_gameoptions->getNameCount() == 0) {
            m_lastNameLayer->setVisible(false);
            showCreateNameBox();
        }else{
            m_change_menu->setEnabled(true);
        }
    }else if (dynamic_cast<SelectScene*>(parent) && nameList.size() > 0)
    {
        // if this dialog shows on select scene, enable buttons of select scene, set select name to second player name and hid dialog
        ((SelectScene*)parent)->m_button_menu->setEnabled(true);
        this->setVisible(false);
    }
    m_nameSelectLayer->setLocalZOrder(Z_LAYER);
    m_nameSelectLayer->setVisible(false);
}

#pragma mark - Button Process

void NamePopUpLayer::onMenu(cocos2d::Ref *pSender)
{
    int item_tag = ((MenuItem*)pSender)->getTag();
    switch (item_tag) {
        case TAG_GO_BTN:
            log("Go button pressed");
            createName();
            break;
        case TAG_YES_BTN:
            log("Delete Yes button pressed '%s'", nameList.at(selectedIndex).c_str());
            deleteName();
            break;
        case TAG_NO_BTN:
            log("Delete No button pressed");
            hideDeleteNameBox();
            break;
        case TAG_CHANGE_BTN:
            log("Change button pressed");
            m_change_menu->setEnabled(false);
            showSelectNameBox();
            break;
        case TAG_CREATE_BTN:
            log("Create button pressed");
            m_select_menu->setEnabled(false);
            showCreateNameBox();
            break;
        case TAG_DELETE_BTN:
            log("Delete button pressed");
            if(nameList.size() > 0)
            {
                showDeleteNameBox();
            }
            break;
        case TAG_SELECT_BTN:
            if (nameList.size() > 0) {
                log("Select button pressed '%s'",nameList.at(selectedIndex).c_str());
                m_gameoptions->setLastUsedName(nameList.at(selectedIndex).c_str());
                selectNamme();
                hideSelectNameBox();
            }
            break;
        case TAG_PLAY_BTN:
            log("Play button pressed");
            m_gameoptions->setFirstUserName(m_lastname_label->getString().c_str());
            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, SelectScene::createScene()));
            break;
        case TAG_BACK_BTN:
            m_change_menu->setEnabled(true);
            hideSelectNameBox();
            break;
        default:
            break;
    }
}

#pragma mark - TextEdit Delegate

void NamePopUpLayer::editBoxReturn(EditBox* editBox)
{
    
}

#pragma mark - TableView Call Back Function

Size NamePopUpLayer::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Size(CELL_WIDTH, CELL_HEIGHT);
}

ssize_t NamePopUpLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    if (m_isSelectSecondPlayer) {
        return nameList.size() - 1;
    }else
    {
        return nameList.size();
    }
}

void NamePopUpLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    for (int i = 0; i < nameList.size(); i++) {
        auto bg = cell->getChildByTag(TAG_CELL_BG);
        if (i == cell->getIdx()) {
            bg->setVisible(true);
        }else
        {
            bg->setOpacity(false);
        }
    }
    selectedIndex = (int)cell->getIdx();
    Vec2 offset = table->getContentOffset();
    log("Cell %zd",cell->getIdx());
    table->reloadData();
    table->setContentOffset(offset);
    offset = table->getContentOffset();

    
//    table->reloadData();
    
}

TableViewCell* NamePopUpLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    auto background_color = Color3B(1, 235, 100);
    
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0,CELL_WIDTH, CELL_HEIGHT));
    bg->setColor(background_color);
    bg->setTag(TAG_CELL_BG);
    if (selectedIndex == idx) {
        bg->setVisible(true);
    }else
    {
        bg->setVisible(false);
    }
    
    cell->addChild(bg);
    
    auto text = nameList.at(idx);
    auto label = Label::createWithTTF(text.c_str(), "fonts/GROBOLD.ttf", DISO(65));
    label->setAnchorPoint(Vec2(0.5, 0.5));
    label->setPosition(Vec2(CELL_WIDTH * 0.5, CELL_HEIGHT * 0.5));
    label->setColor(TEXT_BROWNCOLOR);
    label->setAlignment(TextHAlignment::CENTER);
    cell->addChild(label);
    
    return cell;
}

#pragma mark -

void NamePopUpLayer::selectNamme()
{
    auto parent = this->getParent();
    if (dynamic_cast<OptionScene*>(parent)) {
        // if this dialog shows on option scene, enable buttons of option scene and hide dialog.
        ((OptionScene*)parent)->m_mMain->setEnabled(true);
        m_gameoptions->setFirstUserName(nameList.at(selectedIndex).c_str());
        this->setVisible(false);
        if (m_gotoAfterSelect) {
            ((OptionScene*)parent)->gotoSelectScene();
        }
    }else if (dynamic_cast<MainScene*>(parent) && m_lastNameLayer->isVisible() && nameList.size() > 0)
    {
        // if this dialog shows with last name dialog, enable buttons of last name dialog and update last name label.
        m_change_menu->setEnabled(true);
        m_lastname_label->setString(nameList.at(selectedIndex).c_str());
    }else if (dynamic_cast<SelectScene*>(parent) && nameList.size() > 0)
    {
        // if this dialog shows on select scene, enable buttons of select scene, set select name to second player name and hid dialog
        ((SelectScene*)parent)->m_button_menu->setEnabled(true);
        m_gameoptions->setSecondPlayerName(nameList.at(selectedIndex).c_str());
        this->setVisible(false);
    }
}

void NamePopUpLayer::deleteName()
{
    if(nameList.size() == 0)
    {
        return;
    }
    m_gameoptions->removeUserName(selectedIndex);       // remove name from option name list
    m_select_menu->setEnabled(true);                // the buttons('Delete', 'Create', 'Select') enable.
    nameList = m_gameoptions->getNameList();            // Update new name list.
    selectedIndex = 0;                              // Select the first item on table.
    m_tableview->reloadData();                      // Update the table.
    
    hideDeleteNameBox();                            // Hide 'Delete' Dialog.
}

void NamePopUpLayer::createName()
{
    string name = m_editName->getText();
    if (name.length() == 0) {
        return;
    }
    
    if (m_gameoptions->isDuplicateName(name.c_str())) {
        MessageBox(Txt_DUPLICATENAME, "");;
    }else
    {
        m_gameoptions->addUserName(m_editName->getText());
        m_nameCreateLayer->setVisible(false);
        m_nameCreateLayer->setLocalZOrder(Z_LAYER);
        
        m_select_menu->setEnabled(true);
        
        editBoxReturn(m_editName);
        
        nameList = m_gameoptions->getNameList();
        
        selectedIndex = 0;
        m_tableview->reloadData();
        
        auto parent = this->getParent();
        if (dynamic_cast<MainScene*>(parent) && !m_nameSelectLayer->isVisible()) {
            if (!m_nameCreateLayer->isVisible()) {
                m_gameoptions->setFirstUserName(m_editName->getText());
                ((MainScene*)parent)->gotoSelectScene();
            }
        }
        if (dynamic_cast<OptionScene*>(parent) && !m_nameSelectLayer->isVisible()) {
            if (!m_nameCreateLayer->isVisible()) {
                m_gameoptions->setFirstUserName(m_editName->getText());
                ((OptionScene*)parent)->gotoSelectScene();
            }
        }
    }
    
}

void NamePopUpLayer::sortName()
{
    std::sort(nameList.begin(), nameList.end());
    
    for (int idx_f = 0; idx_f < nameList.size() - 1; idx_f++) {
        for (int idx_s = 1; idx_s < nameList.size(); idx_s++) {
            string first_name = nameList[idx_f];
            string second_name = nameList[idx_s];
            if (first_name.compare(second_name) > 0) {
                //                nameList.swap(first_name, second_name);
                string tmp = nameList[idx_f];
                nameList[idx_f] = nameList[idx_s];
                nameList[idx_s] = tmp;
            }
        }
    }
//    for (int idx_f = 0; idx_f < nameList.size() - 1; idx_f++) {
//        for (int idx_s = 1; idx_s < nameList.size(); idx_s++) {
//            string first_name = nameList.at(idx_f);
//            string second_name = nameList.at(idx_s);
//            if (first_name.compare(second_name.c_str()) > 0) {
//                nameList.swap(idx_f, idx_s);
//            }
//        }
//    }
}

void NamePopUpLayer::removeFirstUserNameFromNameList()
{
    
    string firstplayer = m_gameoptions->getFirstUserName();
    for (int index = 0; index < nameList.size(); index++) {
        string nameitem = nameList.at(index).c_str();
        if (nameitem.compare(firstplayer) == 0) {
//            nameList.erase(index);
            string removeitem = nameList[index];
            vector<string>::iterator result = find(nameList.begin(), nameList.end(), removeitem);
            nameList.erase(result);
            
            break;
        }
    }
}

void NamePopUpLayer::setGotoAfterSelect(bool value)
{
    m_gotoAfterSelect = value;
}