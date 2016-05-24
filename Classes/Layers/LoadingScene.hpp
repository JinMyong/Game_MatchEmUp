//
//  LoadingScene.hpp
//  MatchEmUp
//
//  Created by PAK on 4/4/16.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class LoadingScene : public Layer
{
public:
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(LoadingScene);
    
private:
    int m_count;
    void createBG();
    void loadResources();
    void onLoad(Ref* sender);
    void onFinishLoad(Ref* sender);
};

#endif /* LoadingScene_hpp */
