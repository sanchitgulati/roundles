//
//  Sideton.h
//  roundels
//
//  Created by Sanchit Gulati on 21/06/14.
//
//

#ifndef __roundels__Sideton__
#define __roundels__Sideton__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;

class Sideton : public cocos2d::MenuItem
{
    cocos2d::Sprite* backSprite;
    cocos2d::Sprite* foreSprite;
    float _originalScale;
    Point _originalPosition;
public:
    Sideton(std::string text,std::string image,Color3B color);
    static Sideton* create(std::string text,std::string image,Color3B color);
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool);
    
};

#endif /* defined(__roundels__Sideton__) */
