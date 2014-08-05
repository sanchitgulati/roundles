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
#include "Util.h"

class Single : public cocos2d::Node
{
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* dot;
public:
    Single();
    virtual bool init();
    static Single* create();
    void setScale(float);
};

#endif /* defined(__roundels__Single__) */
