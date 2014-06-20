//
//  Single.h
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#ifndef __roundels__Single__
#define __roundels__Single__

#include <iostream>
#include "cocos2d.h"

class Single : public cocos2d::Node
{
public:
    Single(const char* image);
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* light;
    virtual bool init();
    static Single* create(const char* image);
    void setScale(float);
};

#endif /* defined(__roundels__Single__) */
