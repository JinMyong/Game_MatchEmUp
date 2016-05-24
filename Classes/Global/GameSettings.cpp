//
//  GameSettings.cpp
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#include "GameSettings.h"

float getX(int x)
{
    float fx=0;
    
    fx = G_SCALEX * x ;
    return fx;
}

float getY(int y)
{
    float fy=0;
    fy = G_SHEIGHT - G_SCALEY * y ;
    fy = (G_OHEIGHT - y) * G_SCALEY;
    return fy;
}

Sprite *newSprite(const char *sName, float x, float y,Node *target, int zOrder, Ratio nRatio)
{
    Sprite *sprite = Sprite::create(StringUtils::format("res/images/%s.png",sName).c_str());
    setScale(sprite, nRatio);
    
    sprite->setPosition(Point(x, y));
    target->addChild(sprite ,zOrder);
    return sprite;
}



MenuItemImage *newButtonGrow(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio)
{
    MenuItemImage *item;
    
    item =MenuItemImage::create(StringUtils::format("res/images/%s.png", fileName).c_str(), StringUtils::format("res/images/%s.png", fileName).c_str(),StringUtils::format("%s.png", fileName).c_str(), target);
    
    setScale(item, nRatio);
    item->setPosition(Point(x, y));
    
    return item;
}

MenuItemImage *newButton(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio)
{
    MenuItemImage *item;
    
    item =MenuItemImage::create(StringUtils::format("res/images/%s.png", fileName).c_str() ,StringUtils::format("res/images/%s.png", fileName).c_str(), StringUtils::format("res/images/%s.png", fileName).c_str(), target);
    
    /*item->getSelectedImage()->setColor(Color3B(item->getNormalImage()->getColor().r-100,item->getNormalImage()->getColor().g-100,item->getNormalImage()->getColor().b-100));
    item->getDisabledImage()->setColor(Color3B(item->getNormalImage()->getColor().r-100,item->getNormalImage()->getColor().g-100,item->getNormalImage()->getColor().b-100));*/
    
    setScale(item, nRatio);
    item->setPosition(Point(x, y));
    
    return item;
}

MenuItemImage *newButtonOn(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio)
{
    MenuItemImage *item;
    
    item =MenuItemImage::create(StringUtils::format("res/images/%s.png", fileName).c_str(), StringUtils::format("res/images/%s_on.png", fileName).c_str(), StringUtils::format("res/images/%s_on.png", fileName).c_str(),target);
    
    setScale(item, nRatio);
    item->setPosition(Point(x, y));
    
    return item;
}



MenuItemToggle *newToggleButton(const char *btnNameNormal,const char *btnNameSelect, float x, float y, ccMenuCallback target, Ratio nRatio)
{
    MenuItemToggle *item;
    MenuItemImage *itemOn, *itemOff;
    itemOn = MenuItemImage::create(StringUtils::format("res/images/%s.png", btnNameNormal).c_str(),StringUtils::format("res/images/%s.png", btnNameNormal).c_str());
    
    //itemOn->getSelectedImage()->setColor(Color3B(itemOn->getNormalImage()->getColor().r-100,itemOn->getNormalImage()->getColor().g-100,itemOn->getNormalImage()->getColor().b-100));
    
    itemOff = MenuItemImage::create(StringUtils::format("res/images/%s.png", btnNameSelect).c_str(), StringUtils::format("res/images/%s.png", btnNameSelect).c_str());
    //itemOff->getSelectedImage()->setColor(Color3B(itemOff->getNormalImage()->getColor().r-100,itemOff->getNormalImage()->getColor().g-100,itemOff->getNormalImage()->getColor().b-100));
    
    item = MenuItemToggle::createWithCallback(target,itemOn, itemOff, NULL);
    setScale(item, nRatio);
    item->setPosition(Point(x, y));
    return item;
}

Label* newLabel(const char* txt, const char* fontName, float size, float x, float y, Node* target, int zOrder,Ratio nRatio){
    
    Label* label=Label::createWithTTF(txt, fontName, size);
    label->setPosition(Point(x, y));
    target->addChild(label, zOrder);
    setScale(label, nRatio);
    
    return label;
}

void setScale(Node *node, Ratio nRatio)
{
    if(nRatio == RATIO_XY)
    {
        node->setScaleX(G_SCALEX);
        node->setScaleY(G_SCALEY);
    }
    else if(nRatio == RATIO_X)
        node->setScale (G_SCALEX);
    else if(nRatio == RATIO_Y)
        node->setScale(G_SCALEY);
    else if(nRatio == RATIO_O)
        node->setScale(G_SCALEO);
    else if(nRatio == RATIO_2)
        node->setScale(G_SCALEM);
}

ParticleSystemQuad * showParticle(const char *filename, Node *target, Point pos, int zOrder, Ratio nRatio)
{
    ParticleSystemQuad *particle =ParticleSystemQuad::create(filename);
    particle->setPosition(pos);
    setScale(particle,nRatio);
    target->addChild(particle,zOrder);
    return particle;
}