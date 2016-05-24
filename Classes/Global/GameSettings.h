//
//  GameSettings.h
//  MatchEmUp
//
//  Created by Mary Rowe on 2015-12-10.
//
//

#ifndef __GameSettings__
#define __GameSettings__
#include "GameConfig.h"

#define G_OWIDTH (2048.0f)
#define G_OHEIGHT (2732.0f)

#define G_SWIDTH    (Director::getInstance()->getVisibleSize().width)  //Screen width
#define G_SHEIGHT   (Director::getInstance()->getVisibleSize().height)   //Screen height

#define G_SCALEX    (G_SWIDTH / G_OWIDTH)
#define G_SCALEY    (G_SHEIGHT / G_OHEIGHT)
#define G_SCALEO    (G_SCALEX<G_SCALEY?G_SCALEX:G_SCALEY)
#define G_SCALEM    (G_SCALEX>G_SCALEY?G_SCALEX:G_SCALEY)

#define DISX(X)  ((X) * (G_SCALEX))
#define DISY(Y)  ((Y) * (G_SCALEY))
#define DISO(O)  ((O) * (G_SCALEO))

#define TABLE_CELL_WIDTH G_SWIDTH
#define TABLE_CELL_HEIGHT DISX(150)

typedef enum
{
    RATIO_XY = 0,
    RATIO_X,
    RATIO_Y,
    RATIO_O,
    RATIO_1,
    RATIO_2
}Ratio;

float getX(int x);
float getY(int y);

Sprite *newSprite(const char *sName, float x, float y, Node* target, int zOrder, Ratio nRatio);

MenuItemImage *newButtonGrow(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio);
MenuItemImage *newButton(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio);
MenuItemImage *newButtonOn(const char* fileName, float x, float y, ccMenuCallback target, Ratio nRatio);

MenuItemToggle *newToggleButton(const char *btnNameNormal,const char *btnNameSelect, float x, float y, ccMenuCallback target, Ratio nRatio);

Label* newLabel(const char* txt, const char* fontName,float size, float x, float y, Node* target, int zOrder,Ratio nRatio);


void setScale(Node *node, Ratio nRatio);
ParticleSystemQuad* showParticle(const char *filename, Node *target, Point pos, int zOrder, Ratio nRatio);


#endif
