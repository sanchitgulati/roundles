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
    
    
    tableSize = Size(winSize.width,winSize.height*0.75);
    auto calcTemp = (winSize.height*0.75)/5.0f;
    cellSize = Size(tableSize.width - 2*Constants::vEdgeMargin,calcTemp);
    
    
	TableView* tableView = TableView::create(this,Size(tableSize.width,tableSize.height));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setAnchorPoint(Point(0,0));
    tableView->setPosition(Point(Constants::vEdgeMargin,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
    
    auto blur = Sprite::create(IMG_BLUR);
    blur->setPosition(Point(0, tableSize.height));
    blur->setAnchorPoint(Point(0,1));
    blur->setScaleX(Util::getScreenRatioWidth(blur));
    this->addChild(blur);
    
    auto blur1 = Sprite::create(IMG_BLUR);
    blur1->setPosition(Point(0, tableSize.height));
    blur1->setAnchorPoint(Point(0,0));
    blur1->setFlippedY(true);
    blur1->setScaleX(Util::getScreenRatioWidth(blur1));
    this->addChild(blur1);
    
    auto blur2 = Sprite::create(IMG_BLUR);
    blur2->setPosition(Point(0, 0));
    blur2->setAnchorPoint(Point(0,0));
    blur2->setFlippedY(true);
    blur2->setScaleX(Util::getScreenRatioWidth(blur2));
    this->addChild(blur2);
    
    return true;
}

void TableLevel::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
    LevelXML::setCurrentLevelId(static_cast<int>(cell->getIdx()));
    auto callFunc = CallFunc::create([this]()
    {
        auto s = (Scene*)GameScene::create();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
    });
    auto action = MoveBy::create(0.1f, Point(0,-5));
    auto rotate = RotateBy::create(0.1f, Vertex3F(-10, 0, 0));
    cell->runAction(Sequence::create(rotate,callFunc,NULL));
    cell->runAction(action);
}

Size TableLevel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSize;
}

TableViewCell* TableLevel::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%s : %s",Util::to_roman(idx+1).c_str(), LevelXML::getLevelNameAt(static_cast<int>(idx)).c_str());
    
    std::string stringMore = "Tap To Play";
    if(LevelXML::getDidCompleteLevelAt(idx));
    {
        stringMore = "Level Completed";
    }
    
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new TableViewCell(); //Can Be Customized, refer to TestCpp
        cell->autorelease();
        Sprite* sprite = Sprite::create(IMG_BUTTON_LEVEL);
        Size temp = sprite->getBoundingBox().size;
        sprite->setScale((cellSize.width/temp.width));
        
        switch (idx%2) {
            case 0:
                sprite->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber)) ;
                break;
            case 1:
                sprite->setColor(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber)) ;
                break;
            default:
                break;
        }
        cell->setAnchorPoint(Point(0.5, 0.5));
        
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(0, 0));
        sprite->setTag(111);
        cell->addChild(sprite);
        
        auto label = LabelTTF::create(string->getCString(), Constants::fontName, Constants::defaultFontSize);
        label->setPosition(Point(Constants::vEdgeMargin, cellSize.height - 2*Constants::vEdgeMargin));
        label->setColor(RGB_COLOR6);
		label->setAnchorPoint(Point(0,1));
        label->setTag(123);
        cell->addChild(label);
        
        auto labelMore = Label::create(stringMore.c_str(),Constants::fontName, Constants::defaultFontSize*0.5);
        auto labelSize = label->getBoundingBox().size;
        labelMore->setPosition(Point(Constants::vEdgeMargin, cellSize.height - 2*Constants::vEdgeMargin - labelSize.height));
        labelMore->setColor(RGB_COLOR6);
		labelMore->setAnchorPoint(Point(0,1));
        labelMore->setTag(124);
        cell->addChild(labelMore);
        
    }
    else
    {
        auto sprite = cell->getChildByTag(111);
        switch (idx%2) {
            case 0:
                sprite->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber)) ;
                break;
            case 1:
                sprite->setColor(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber)) ;
                break;
            default:
                break;
        }
        
        auto label = (LabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
        auto labelMore = (LabelTTF*)cell->getChildByTag(124);
        labelMore->setString(stringMore.c_str());
    }

    
    return cell;
}

ssize_t TableLevel::numberOfCellsInTableView(TableView *table)
{
    return LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber);
}
