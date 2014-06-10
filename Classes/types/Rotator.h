//
//  Rotator.h
//  roundels
//
//  Created by Sanchit Gulati on 10/06/14.
//
//

#ifndef __roundels__Rotator__
#define __roundels__Rotator__

#include <iostream>
#include "cocos2d.h"


class Rotator : public cocos2d::Node
{
    cocos2d::Sprite* outer;
    cocos2d::Sprite* inner;
    
public:
    Rotator(cocos2d::Color3B outerColor,cocos2d::Color3B innerColor);
    static Rotator* create(cocos2d::Color3B outerColor,cocos2d::Color3B innerColor);
    virtual cocos2d::Rect getBoundingBox();
};
#endif /* defined(__roundels__Rotator__) */
