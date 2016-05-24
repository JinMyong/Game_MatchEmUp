//
//  LoadingScene.cpp
//  MatchEmUp
//
//  Created by PAK on 4/4/16.
//
//

#include "LoadingScene.hpp"
#include "GameSettings.h"
#include "MainScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    m_count = 0;
    createBG();
    runAction(Sequence::create(DelayTime::create(4.0f),
                               CallFunc::create([&]{onFinishLoad(NULL);}),
                               NULL));
    return true;
}

void LoadingScene::createBG()
{
    newSprite("load_bg", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, this, 1, RATIO_XY);
    newSprite("load_logo", G_SWIDTH * 0.5, G_SHEIGHT * 0.5, this, 1, RATIO_O);
}

void LoadingScene::loadResources()
{
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/g_blackoverlay.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/g_snake.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/g_title.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    string filename;
    // Backgrounds
    for (int index = 0 ; index < 12; index++) {
        filename = StringUtils::format("res/images/backgrounds/bkg_%d.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
    }
    
    // Game Scene
    for (int index = 0 ; index < 12; index++) {
        filename = StringUtils::format("res/images/gamescene/cover/card_%d.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
    }
    
    for (int pack = 1; pack < 7; pack++) {
        for (int index = 1; index < 25; index++) {
            filename = StringUtils::format("res/images/gamescene/img/img%d_%d.png", pack, index);
            Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
        }
    }
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/animal_name.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/btn_pause.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/btn_pmain.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/btn_poption.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/btn_pquit.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/btn_presume.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/pausepopup.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/t_flipped.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/t_matches.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/t_timer.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/tiles.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/gamescene/timer.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    // Main Scene
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_change.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_go.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_no.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_options.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_play.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/btn_yes.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/editback.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/hipposcape_logo.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/main_bg.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/mainscene/maintitle.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    // Name popup
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_change.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_create.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_delete.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_go.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_no.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_select.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/btn_yes.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/delete_name_box.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/players_list_box.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/namepopup/welcome_box.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    // Option Scene
    for (int index = 0 ; index < 12; index++) {
        filename = StringUtils::format("res/images/optionscene/backgroudchange/bkg_%d_off.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
        filename = StringUtils::format("res/images/optionscene/backgroudchange/bkg_%d_on.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
    }
    for (int index = 0 ; index < 12; index++) {
        filename = StringUtils::format("res/images/optionscene/tilecoverchange/card_%d_off.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
        filename = StringUtils::format("res/images/optionscene/tilecoverchange/card_%d_on.png", index);
        Director::getInstance()->getTextureCache()->addImageAsync(filename.c_str(), CC_CALLBACK_1(LoadingScene::onLoad, this));
    }
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/arrow_left.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/arrow_right.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_back.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_change_name.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_changebg.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_changetile.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_leaderboard.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_play.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_switch_off.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/btn_switch_on.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/check_no.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/check_yes.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/checkbox.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/optionbox.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/page_off.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/page_on.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/pointer.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/snake.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/timelabel.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/timercounter.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/optionscene/unlock_box.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    // Score Scene
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/bg_score.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/btn_mainmenu.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/btn_playagain.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/highscore.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/score_log_2.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/score_log.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/score_stones_2.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/score_stones.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/total_score.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/winner_log.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/scorescene/woodpecker.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    
    // Select Scene
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/bonus.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/box.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_2players.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_level_l.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_level_r.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_options.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_settile.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_start.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/btn_unlock.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/level_l_h.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/level_r_h.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv1.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv2.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv3.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv4.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv5.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/lv6.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack1.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack2.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack3.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack4.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack5.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/pack6.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/settile_h.png", CC_CALLBACK_1(LoadingScene::onLoad, this));
    Director::getInstance()->getTextureCache()->addImageAsync("res/images/selectscene/shop_popup_box.png", CC_CALLBACK_1(LoadingScene::onFinishLoad, this));
    
}

void LoadingScene::onLoad(Ref *sender)
{
    CCLOG("%d images Loaded", ++m_count);
}

void LoadingScene::onFinishLoad(Ref *sender)
{
    Director::getInstance()->replaceScene(MainScene::createScene());
}