//
//  OptButton.h
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#ifndef __roundels__OptButton__
#define __roundels__OptButton__

#include <iostream>
#include "cocos2d.h"

#endif /* defined(__roundels__OptButton__) */

class OptButton : public cocos2d::MenuItemFont
{
    cocos2d::Label* lblText;
    float _originalScale;
    cocos2d::Point _originalPosition;
public:
    OptButton(std::string text);
    static OptButton* create(std::string text);
    virtual void selected();
    virtual void unselected();
    void setScale(float val);
};