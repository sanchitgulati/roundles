//
//  Util.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#include "Util.h"

float Util::getScreenRatio(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    if(winSize.width > winSize.height)
    {
        return (winSize.height/obj->getBoundingBox().size.height);
    }
    else
    {
        return (winSize.width/obj->getBoundingBox().size.width);
    }
}

float Util::getScreenRatioWidth(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    return (winSize.width/obj->getBoundingBox().size.width);

}

float Util::getScreenRatioHeight(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    return (winSize.height/obj->getBoundingBox().size.height);
}

Color3B Util::randomBrightColor()
{
    while (true) {
        float requiredBrightness = 192;
        Color3B c = Color3B(arc4random() % 255,arc4random() % 255,arc4random() % 255);
        if (    c.r > requiredBrightness
            ||  c.g > requiredBrightness
            ||  c.b > requiredBrightness)
        {
            return c;
        }
    }
}
