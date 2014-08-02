//
//  Rotator.h
//  roundels ,bool
//
//  Created by Sanchit Gulati on 10/06/14.
//
//

#ifndef __roundels__Rotator__
#define __roundels__Rotator__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"


class Rotator : public cocos2d::Node
{
    cocos2d::ProgressTimer* outer;
    cocos2d::Sprite* inner;
    
public:
    Rotator(cocos2d::Color3B color,std::string text,float percentage,bool locked);
    static Rotator* create(cocos2d::Color3B color,std::string text,float percentage,bool locked = true);
    virtual cocos2d::Rect getBoundingBox();
    void animateRotation(float val,float time = VFX_CONSTANT);
    void setRotation(float val);
};
#endif /* defined(__roundels__Rotator__) */
