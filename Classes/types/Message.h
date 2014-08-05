//
//  Message.h
//  roundels
//
//  Created by Sanchit Gulati on 11/06/14.
//
//

#ifndef __roundels__Message__
#define __roundels__Message__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "Util.h"


class Message : public cocos2d::Node
{
    cocos2d::Label* lblText;
    
public:
    Message(std::string text);
    static Message* create(std::string text);
};

#endif /* defined(__roundels__Message__) */
