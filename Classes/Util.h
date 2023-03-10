//
//  Util.h
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#ifndef __OneClosedLoop__Util__
#define __OneClosedLoop__Util__

#include <iostream>
#include "cocos2d.h"
#include "LocalizedString.h"

USING_NS_CC;
using namespace std;



class Util
{
public:
    static float getScreenRatio(Node*);
    static float getScreenRatioWidth(Node*);
    static float getScreenRatioHeight(Node*);
    static Color3B randomBrightColor();
    static std::string to_roman(unsigned int value);
};
#endif /* defined(__OneClosedLoop__Util__) */
