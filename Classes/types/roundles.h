//
//  Radio.h
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#ifndef __roundels__Roundles__
#define __roundels__Roundles__

#include <iostream>
#include "cocos2d.h"


class Roundles : public cocos2d::MenuItem
{
    cocos2d::Label* lblHeading;
    cocos2d::Label* lblText;
    cocos2d::Sprite* circleLeft;
    cocos2d::Sprite* circleRight;
    cocos2d::Sprite* bar;
    float _originalScale;
    cocos2d::Point _originalPosition;
    
public:
    Roundles(std::string heading,std::string message);
    static Roundles* create(std::string heading,std::string message);
    virtual void selected();
    virtual void unselected();
};

#endif /* defined(__roundels__Roundles__) */
