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

enum {
    eNull,
    eStart,
    eSingle
};

typedef struct {
    int x, y;
} iPoint;

struct LevelElement
{
    int type;
    int x;
    int y;
    cocos2d::Node* ccElement;
    LevelElement()
    {
        type = eNull;
        x = 0;
        y = 0;
    }
};

class LevelXML
{
public:
    static pugi::xml_document doc;
    static pugi::xml_node curBundle;
    static pugi::xml_node curLevel;
    static int curBundleNumber;
    static int curLevelNumber;
    
    static bool init();
    static void traverse();
    
    static int getTotalBundlesSize();
    static int getTotalLevelsInBundle(int);
    
    static std::string getBundleNameAt(int);
    static Color3B getBundleColorInnerAt(int);
    static Color3B getBundleColorOuterAt(int);
    
    static bool setCurrentBundleId(int);
    static bool setCurrentLevelId(int);
    
    static std::string getLevelNameAt(int);
    static float getDidCompleteLevelAt(int);
    static bool setLevelCompletedAt(int);
    
    static int getGridSizeX();
    static int getGridSizeY();
    static int getLevelId();
    
    static std::vector<LevelElement> getCurrentLevel();
};

#endif /* defined(__OneClosedLoop__LevelXML__) */
