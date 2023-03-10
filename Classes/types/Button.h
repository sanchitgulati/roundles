//
//  Button.h
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#ifndef __roundels__Button__
#define __roundels__Button__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;

class Button : public cocos2d::MenuItem
{
    cocos2d::Sprite* backSprite;
    cocos2d::Sprite* foreSprite;
    cocos2d::Label* lblText;
    float _originalScale;
    Point _originalPosition;
public:
    Button(std::string text,std::string image,Color3B color);
    static Button* create(std::string text,std::string image,Color3B color);
    virtual void selected();
    virtual void unselected();
    void setScale(float val);
    
};

#endif /* defined(__roundels__Button__) */
