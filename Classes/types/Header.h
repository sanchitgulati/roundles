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
    cocos2d::Sprite* backSprite;
    cocos2d::Sprite* foreSprite;
    cocos2d::Label* lblText;
public:
    Header(std::string text,std::string image,Color3B color);
    static Header* create(std::string text,std::string image,Color3B color);
    
};

#endif /* defined(__roundels__Header__) */
