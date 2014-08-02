//
//  Header.h
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#ifndef __roundels__Header__
#define __roundels__Header__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "Util.h"

class Header : public cocos2d::MenuItem
{
    cocos2d::Label* lblText;
public:
    Header(std::string text);
    static Header* create(std::string text);
    
};

#endif /* defined(__roundels__Header__) */
