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
    
    auto calcTemp = (winSize.height*0.70)/5.5f;
    
    cellSize = Size(tableSize.width - 2*Constants::vEdgeMargin,calcTemp);
    tableSize = Size(winSize.width,winSize.height*0.70);
    
    
	TableView* tableView = TableView::create(this,Size(tableSize.width,tableSize.height));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setAnchorPoint(Point(0,0));
    tableView->setPosition(Point(Constants::vEdgeMargin,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
    
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
    cell->runAction(Sequence::create(RotateBy::create(0.1f, Vertex3F(0, 10, 0)),callFunc,NULL));
}

Size TableLevel::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSize;
}

TableViewCell* TableLevel::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%s", LevelXML::getLevelNameAt(static_cast<int>(idx)).c_str());
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new TableViewCell(); //Can Be Customized, refer to TestCpp
        cell->autorelease();
        Sprite* sprite = Sprite::create(IMG_BUTTON_LEVEL);
        Size temp = sprite->getBoundingBox().size;
        sprite->setScale((cellSize.width/temp.width),1);
        
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
        
        
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(0, 0));
        sprite->setTag(111);
        cell->addChild(sprite);
        
        auto label = LabelTTF::create(string->getCString(), Constants::fontName, Constants::defaultFontSize);
        label->setPosition(Point(Constants::vEdgeMargin, cellSize.height - Constants::vEdgeMargin));
        label->setColor(Color3B::WHITE);
		label->setAnchorPoint(Point(0,1));
        label->setTag(123);
        cell->addChild(label);
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
    }

    
    return cell;
}

ssize_t TableLevel::numberOfCellsInTableView(TableView *table)
{
    return LevelXML::getTotalLevelsInBundle(LevelXML::curBundleNumber);
}
