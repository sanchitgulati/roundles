//
//  LevelXML.h
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#ifndef __OneClosedLoop__LevelXML__
#define __OneClosedLoop__LevelXML__

#include <iostream>
#include "cocos2d.h"
#include "pugixml.hpp"

USING_NS_CC;

class LevelXML
{
public:
    static pugi::xml_document doc;
    static pugi::xml_document curBundle;
    static pugi::xml_document curLevel;
    static bool init();
    static void traverse();
    
    static int getTotalBundlesSize();
    static std::string getBundleNameAt(int);
    static Color3B getBundleColorInnerAt(int);
    static Color3B getBundleColorOuterAt(int);
    
};

#endif /* defined(__OneClosedLoop__LevelXML__) */
