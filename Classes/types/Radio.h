//
//  Radio.h
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#ifndef __roundels__Radio__
#define __roundels__Radio__

#include <iostream>
#include "cocos2d.h"


class Radio : public cocos2d::MenuItemToggle
{
    cocos2d::Label* lblText;
    cocos2d::Sprite* circle;
    cocos2d::Sprite* bar;
    cocos2d::MenuItem* on;
    cocos2d::MenuItem* off;
    
public:
    Radio(std::string text);
    static Radio* create(std::string text);
    bool init();
};

#endif /* defined(__roundels__Radio__) */
