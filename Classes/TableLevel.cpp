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
    tableSize = this->getContentSize();
    
    
    tableSize = Size(winSize.width*0.75,winSize.height*0.85);
    
    
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
    auto rotate = RotateBy::create(0.1f, Vec3(-10, 0, 0));
    if(cell->getIdx() != LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber))
    {
        cell->runAction(Sequence::create(rotate,callFunc,NULL));
        cell->runAction(action);
    }
}

Size TableLevel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(cellSize.width,cellSize.height *0.80);
}

TableViewCell* TableLevel::tableCellAtIndex(TableView *table, ssize_t idx)
{
    int id = static_cast<int>(idx);
    
    cocos2d::__String *string;
    if(idx == LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber))//Empty Block
    {
        string = String::createWithFormat("*_*\nCongrats");
    }
    else
    {
        string = String::createWithFormat("%s\n%s",Util::to_roman(id+1).c_str(), LevelXML::getLevelNameAt(static_cast<int>(idx)).c_str());
    }
    

    
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new TableViewCell(); //Can Be Customized, refer to TestCpp
        cell->autorelease();
        Sprite* sprite = Sprite::create(IMG_CIRCLE_WHITE);
        Size temp = sprite->getBoundingBox().size;
        sprite->setScale(cellSize.height/temp.height);//for new UI, Overlapping
        cell->setAnchorPoint(Point(0.5,0.5));
        sprite->setTag(111);
        cell->addChild(sprite);
        
        auto label = Label::createWithTTF(string->getCString(), Constants::fontName, Constants::fontSize*0.70);
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setDimensions(cellSize.width*0.60,0);
        label->setPosition(Point(temp.width/2,temp.height/2));
        label->setColor(RGB_COLOR6);
		label->setAnchorPoint(Point(0.5,0.5));
        label->setTag(123);
        sprite->addChild(label);
        
        
        
        /* Repeat of else{}, for bug */
        switch (idx%2) {
            case 0:
                sprite->setPositionX(sprite->getBoundingBox().size.width/2);
                break;
            case 1:
                sprite->setPositionX(sprite->getBoundingBox().size.width*0.60 + (sprite->getBoundingBox().size.width/2));
                break;
            default:
                break;
        }
        if(LevelXML::getDidCompleteLevelAt(id) == true)
        {
            auto c = LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber);
            sprite->setColor(c);
        }
        else
        {
            sprite->setColor(RGB_COLOR8);
        }
        /*End*/
    }
    else
    {
        auto sprite = cell->getChildByTag(111);
        switch (idx%2) {
            case 0:
                sprite->setPositionX(sprite->getBoundingBox().size.width/2);
                break;
            case 1:
                sprite->setPositionX(sprite->getBoundingBox().size.width*0.60 + (sprite->getBoundingBox().size.width/2));
                break;
            default:
                break;
        }
        if(LevelXML::getDidCompleteLevelAt(id) == true)
        {
            auto c = LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber);
            sprite->setColor(c);
        }
        else
        {
            sprite->setColor(RGB_COLOR8);
        }
        auto label = (Label*)sprite->getChildByTag(123);
        label->setString(string->getCString());
    }

    
    return cell;
}

ssize_t TableLevel::numberOfCellsInTableView(TableView *table)
{
    return LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber) + 1;//Empty Block
}

Size TableLevel::getCellSize()
{
    return cellSize;
}
