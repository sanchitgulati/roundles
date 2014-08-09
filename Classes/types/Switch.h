//
//  Switch.h
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#ifndef __roundels__Switch__
#define __roundels__Switch__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Util.h"


class Switch : public MenuItem
{
    cocos2d::Label* lblText;
    cocos2d::extension::ControlSwitch* btnSwitch;
    
public:
    void setOn(bool val);
    Switch(std::string text,bool toggle);
    static Switch* create(std::string text,bool toggle = true);
    void addTargetWithActionForControlEvents(Ref* target, cocos2d::extension::Control::Handler action, cocos2d::extension::Control::EventType controlEvents);
    
};

#endif /* defined(__roundels__Switch__) */
