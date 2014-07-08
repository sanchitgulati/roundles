//
//  Ice.h
//  roundels
//
//  Created by Sanchit Gulati on 06/07/14.
//
//

#ifndef __roundels__Ice__
#define __roundels__Ice__

#include <iostream>
#include "cocos2d.h"

class Ice : public cocos2d::Node
{
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* dot;
public:
    Ice();
    virtual bool init();
    static Ice* create();
    void setScale(float);
    void setActive(bool);
};

#endif /* defined(__roundels__Ice__) */
