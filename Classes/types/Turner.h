//
//  Turner.h
//  roundels
//
//  Created by Sanchit Gulati on 06/07/14.
//
//

#ifndef __roundels__Turner__
#define __roundels__Turner__

#include <iostream>
#include "cocos2d.h"

class Turner : public cocos2d::Node
{
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* dot;
public:
    Turner();
    virtual bool init();
    static Turner* create();
    void setScale(float);
};
#endif /* defined(__roundels__Turner__) */
