//
//  Player.h
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#ifndef __roundels__Player__
#define __roundels__Player__

#include <iostream>
#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:
    int x;
    int y;
    Player(const char* image);
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* innerSprite;
    int totalElements;
    int capturedElements;
    
    
    virtual bool init();
    static Player* create(const char* image);
    void setScale(float);
    void setTotalElements(int);
    bool capture(int type,float animationDelta);
};
#endif /* defined(__roundels__Player__) */
