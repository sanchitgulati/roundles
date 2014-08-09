//
//  Dialog.h
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#ifndef __roundels__Dialog__
#define __roundels__Dialog__

#include <iostream>
#include "cocos2d.h"


class Dialog : public cocos2d::Node
{
    cocos2d::Sprite* box;
    cocos2d::Label* lblText;
    cocos2d::Ref* mTarget;
    cocos2d::SEL_CallFunc mFunctionSelector;
public:
    static Dialog* create(std::string text);
    Dialog(std::string text);
    void setCallback(cocos2d::Ref* target);
};

#endif /* defined(__roundels__Dialog__) */
