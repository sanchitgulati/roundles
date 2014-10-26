//
//  TableLevel.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#include "TableLevel.h"
#include "Util.h"
#include "LevelXML.h"
#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool TableLevel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    tableSize = Size(winSize.width,winSize.height*0.80);
    
    
    auto calcTemp = tableSize.height/4.0f;
    cellSize = Size(tableSize.width*0.75,calcTemp); //for new UI, Overlapping
    
    
	TableView* tableView = TableView::create(this,Size(tableSize.width,tableSize.height));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(Point(0,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
    
    return true;
}

void TableLevel::tableCellTouched(TableView* table, TableViewCell* cell)
{
    LevelXML::setCurrentLevelId(static_cast<int>(cell->getIdx()));
    auto callFunc = CallFunc::create([this]()
    {
        auto s = (Scene*)GameScene::create();
        Director::getInstance()->replaceScene(TransitionFade::create(VFX_CONSTANT, s,RGB_COLOR1));
    });
    auto action = MoveBy::create(0.1f, Point(0,-5));
    if(cell->getIdx() != LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber))
    {
        cell->runAction(Sequence::create(callFunc,NULL));
        cell->runAction(action);
    }
}

Size TableLevel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(cellSize.width,cellSize.height);
//    return Size(cellSize.width,cellSize.height *0.80);
}

TableViewCell* TableLevel::tableCellAtIndex(TableView *table, ssize_t idx)
{
    int id = static_cast<int>(idx);
    
    cocos2d::__String *string;
    string = String::createWithFormat("%s %s",Util::to_roman(id+1).c_str(), LevelXML::getLevelNameAt(static_cast<int>(idx)).c_str());
    

    
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new TableViewCell(); //Can Be Customized, refer to TestCpp
        cell->autorelease();
        auto img_str = StringUtils::format("images/%s",LevelXML::getLevelImage());
        Sprite* sprite = Sprite::create(img_str.c_str());
        Size temp = sprite->getBoundingBox().size;
        sprite->setScale(cellSize.height/temp.height);
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setTag(111);
        cell->addChild(sprite);
        
        auto label = Label::createWithTTF(string->getCString(), Constants::fontNameBold, Constants::fontSize*0.70);
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setDimensions(cellSize.width*0.60,0);
        label->setPosition(Point(temp.width/2,temp.height/2));
        label->setColor(RGB_COLOR1);
		label->setAnchorPoint(Point(0.5,0.5));
        label->setTag(123);
        sprite->addChild(label);
        
        
        
        /* Repeat of else{}, for bug */
        switch (idx%2) {
            case 0:
                sprite->setPositionX(winSize.width/2 - sprite->getBoundingBox().size.width);
                break;
            case 1:
                sprite->setPositionX(winSize.width/2 );
                break;
            default:
                break;
        }
        if(LevelXML::getDidCompleteLevelAt(id) == true)
        {
            auto c = LevelXML::getBundleColorAt(LevelXML::curBundleNumber);
//            sprite->setColor(c);
        }
        else
        {
            auto c = LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber);
//            sprite->setColor(c);
        }
        /*End*/
    }
    else
    {
        auto sprite = cell->getChildByTag(111);
        
        /* Repeat of else{}, for bug */
        switch (idx%2) {
            case 0:
                sprite->setPositionX(winSize.width/2 - sprite->getBoundingBox().size.width);
                break;
            case 1:
                sprite->setPositionX(winSize.width/2 );
                break;
            default:
                break;
        }
        if(LevelXML::getDidCompleteLevelAt(id) == true)
        {
            auto c = LevelXML::getBundleColorAt(LevelXML::curBundleNumber);
//            sprite->setColor(c);
        }
        else
        {
            auto c = LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber);
//            sprite->setColor(c);
        }
        /*End*/
        
        auto label = (Label*)sprite->getChildByTag(123);
        label->setString(string->getCString());
    }

    
    return cell;
}

ssize_t TableLevel::numberOfCellsInTableView(TableView *table)
{
    return LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber);
}

Size TableLevel::getCellSize()
{
    return cellSize;
}
