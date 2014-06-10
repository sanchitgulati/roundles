#include "MainMenuScene.h"
#include "OptionMenu.h"
#include "LevelMenu.h"

USING_NS_CC;

enum btnId
{
    bSetting,
    bTutorial,
    bPlay
};

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /* Touch Dispatcher */
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainMenu::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MainMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* End */

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    fontSize = Constants::defaultFontSize*(winSize.width/480);
    Constants::fontSize = this->fontSize;
    Constants::vEdgeMargin = winSize.width/20.0f;
    
    /*Initiations Of Array */
    arrBundle = new ccArray;
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    auto btnSetting = Button::create("Setting",IMG_BUTTON_MENU,RGB_COLOR2);
    btnSetting->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*0.85 ));
    btnSetting->setCallback(CC_CALLBACK_1(MainMenu::menuCallback, this));
    btnSetting->setTag(bSetting);
    
    
    auto btnTutorial = Button::create("Tutorial",IMG_BUTTON_TUTORIAL,RGB_COLOR2);
    btnTutorial->setCallback(CC_CALLBACK_1(MainMenu::menuCallback, this));
    btnTutorial->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*0.85 ));
    btnTutorial->setTag(bTutorial);
    
    /* Object Placement and other settings */
    
    auto btnPlay = Rectton::create("PLAY ROUNDELS", RGB_COLOR2);
    btnPlay->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.30));
    btnPlay->setTag(bPlay);
    
    auto lblGameName = Label::create("ROUNDELS",Constants::fontName,fontSize);
    auto gameTitle = MenuItemLabel::create(lblGameName, CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    bundleNode = Node::create();
    
    gameTitle->setEnabled(false);
    gameTitle->setColor(RGB_COLOR3);
    gameTitle->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.85 ));
    
    
    //Read XML and draw Bundle Circle
    const int bundleSize = LevelXML::getTotalBundlesSize();
    
    int r = winSize.width*0.45;
    step = 2*PI/bundleSize;
    float theta= PI*0.5;
    
    for(int i=0; i < bundleSize;i++,theta+=step)
    {
        
        auto bundle = Rotator::create(LevelXML::getBundleColorOuterAt(i), LevelXML::getBundleColorInnerAt(i));
        /* Calculations for x and y */
//        float deltaEclipse = bundle->getBoundingBox().size.width*0.20; //to be saved
//        float x = (r+deltaEclipse)*cos(theta); //to be saved
        float x = r*cos(theta);
        float y = r*sin(theta);
        /* End */
        
        
        //Transferring Values
        bundle->setPosition(Point(x,y));
        bundleNode->addChild(bundle,bundleSize-i);
    }
    //End
    
    bundleNode->setPosition(Point(origin.x + visibleSize.width*(0.50),origin.y + visibleSize.height*0.30 ));
    this->addChild(bundleNode,zReloader);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(btnPlay, btnSetting,btnTutorial,gameTitle, NULL);

    menu->setPosition(Point::ZERO);
    this->addChild(menu, zMenu);
    
    //Temp
    Layer *primLayer = PrimitivesClass::create();
    this->addChild(primLayer, zPrimatives);

    
    //schedule update
    this->scheduleUpdate();
    return true;
}

void MainMenu::update(float dt)
{
    
}


void MainMenu::menuCallback(Ref* pSender)
{
    auto obj = (Node*)pSender;
    log("Reached menuCallback from %d",obj->getTag());
    
    switch (obj->getTag()) {
        case bPlay:
            break;
        case bSetting:
        {
            auto s = (Scene*)OptionMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
        }
            break;
        case bTutorial:
        {
            auto s = (Scene*)LevelMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
        }
            break;
        default:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
            Director::getInstance()->end();
            break;
    }


}


bool MainMenu::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
    touchStart = touch->getLocation();
    return true;
};

void MainMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location = touch->getLocation();
    if(touchStart != Point::ZERO)
    {
        //right left
        if( touchStart.x - location.x  > SWIPE_THRESHOLD)
        {swipeLeft(location);touchStart = Point::ZERO;}
        else if(location.x - touchStart.x > SWIPE_THRESHOLD)
        {swipeRight(location);touchStart = Point::ZERO;}
        //up down
        else if(touchStart.y - location.y > SWIPE_THRESHOLD)
        {swipeDown(location);touchStart = Point::ZERO;}
        else if (location.y - touchStart.y > SWIPE_THRESHOLD)
        {swipeUp(location);touchStart = Point::ZERO;}
    }
}

void MainMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void MainMenu::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void MainMenu::swipeLeft(Point location)
{
    int multipler = (location.y > bundleNode->getPositionY() ? 1 : -1);
    if(bundleNode->getNumberOfRunningActions() == 0 )
        bundleNode->runAction(RotateBy::create(0.5, -1*multipler*step*(180.0/PI)));
    log("left");
}
void MainMenu::swipeRight(Point location)
{
    int multipler = (location.y > bundleNode->getPositionY() ? 1 : -1);
    if(bundleNode->getNumberOfRunningActions() == 0 )
        bundleNode->runAction(RotateBy::create(0.5, multipler*step*(180.0/PI)));
    log("right");
}
void MainMenu::swipeUp(Point location)
{log("up");}
void MainMenu::swipeDown(Point location)
{log("down");}



//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//


/* Primitive Class To Test Things */

bool PrimitivesClass::init()
{
    winSize = Director::getInstance()->getWinSize();
    
    return true;
}

void PrimitivesClass::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(PrimitivesClass::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void PrimitivesClass::onDraw(const kmMat4 &transform, bool transformUpdated)
{
//    drawPolygon();
//    drawCircle();
}

void PrimitivesClass::drawCircle()
{
    int cx = winSize.width*0.50;
    int cy = winSize.height*0.50;
    int r = winSize.width*0.40;
    float step = 0.1;
    int pointSize = 5;
    
    DrawPrimitives::setDrawColor4B(0,0,255,128);
    for(float theta = 0; theta < 2*PI;theta += step)
    {
        float x =  cx + (r+ 50)*cos(theta);
        float y = cy + r*sin(theta);
        DrawPrimitives::setPointSize(pointSize);
        DrawPrimitives::drawPoint(Point(x, y) );
    }

}

void PrimitivesClass::drawPolygon()
{
    glLineWidth(1);
    DrawPrimitives::setDrawColor4B(255,255,255,255);
    DrawPrimitives::setPointSize(1);
    
    // Anti-Aliased
//    glEnable(GL_LINE_SMOOTH);
    
    // filled poly
    glLineWidth(1);
    Point filledVertices[] = { Point(10,120), Point(50,120), Point(50,170), Point(25,200), Point(10,170) };
    DrawPrimitives::drawSolidPoly(filledVertices, 5, Color4F(0.5f, 0.5f, 1, 1 ) );
}
