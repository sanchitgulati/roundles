//
//  TableLevel.h
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#ifndef __OneClosedLoop__TableLevel__
#define __OneClosedLoop__TableLevel__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Constants.h"
#include "Util.h"




USING_NS_CC;


class TableLevel :public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
    
    
public:
    virtual bool init();
    Size winSize;
    Size tableSize;
    Size cellSize;
    
    CREATE_FUNC(TableLevel);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
};

#endif /* defined(__OneClosedLoop__TableLevel__) */
