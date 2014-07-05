//
//  Dingle.h
//  roundels
//
//  Created by Sanchit Gulati on 05/07/14.
//
//

#ifndef __roundels__Dingle__
#define __roundels__Dingle__

#include <iostream>

#include "cocos2d.h"

class Dingle : public cocos2d::Node
{
    int _hp;
public:
    Dingle(const char* image);
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* light;
    cocos2d::Sprite* dot;
    virtual bool init();
    static Dingle* create(const char* image);
    void setScale(float);
    int getHP();
};


#endif /* defined(__roundels__Dingle__) */