#include "MainMenuScene.h"

USING_NS_CC;

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
    Constants::vEdgeMargin = winSize.width/20.0f;
    
    /*Initiations Of Array */
    arrBundle = new ccArray;
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(Color4B(BG_RGBA), visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    auto lblPlayButton = Label::create("Play Game", Constants::fontName, fontSize);
    
    auto playItem = MenuItemLabel::create(lblPlayButton, CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    playItem->setColor(Color3B(LOGO_RGB)); //todo //del //temp
    
    auto settingButton = MenuItemImage::create("whiteCircle.png", "whiteCircle.png", CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    
    auto tutorialButton = MenuItemImage::create("whiteCircle.png", "whiteCircle.png", CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    auto lblGameName = Label::create("ROUNDELS",Constants::fontName,fontSize);
    auto gameTitle = MenuItemLabel::create(lblGameName, CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    bundleNode = Node::create();
    
        /* Object Placement and other settings */
    
    closeItem->setAnchorPoint(Point(1, 0));
	closeItem->setPosition(Point(origin.x + visibleSize.width - Constants::vEdgeMargin,
                                 origin.y + Constants::vEdgeMargin));
    
    playItem->setPosition(Point(origin.x + visibleSize.width/2 , visibleSize.height/4));
    
    settingButton->setColor(Color3B(LOGO_RGB));
    settingButton->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*0.85 ));
    settingButton->setScale(Util::getScreenRatio(settingButton)*0.2);
    
    
    tutorialButton->setColor(Color3B(LOGO_RGB));
    tutorialButton->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*0.85 ));
    tutorialButton->setScale(Util::getScreenRatio(tutorialButton)*0.2);
    
    gameTitle->setEnabled(false);
    gameTitle->setColor(Color3B(INNER_LOGO_RGB));
    gameTitle->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.85 ));
    
    
    //Read XML and draw Bundle Circle
    const int bundleSize = LevelXML::getTotalBundlesSize();
    
    int r = winSize.width*0.4;
    step = 2*PI/bundleSize;
    float theta= PI*0.5;
    
    for(int i=0; i < bundleSize;i++,theta+=step)
    {
         /* {
            log("Name for %d bundle %s",i,LevelXML::getBundleNameAt(i).c_str());
            log("Color.Red for %d bundle %d",i,LevelXML::getBundleColorInnerAt(i).r);
            log("Color.Green for %d bundle %d",i,LevelXML::getBundleColorInnerAt(i).g);
            log("Color.Blue for %d bundle %d",i,LevelXML::getBundleColorInnerAt(i).b);
            log("Color.Red for %d bundle %d",i,LevelXML::getBundleColorOuterAt(i).r);
            log("Color.Green for %d bundle %d",i,LevelXML::getBundleColorOuterAt(i).g);
            log("Color.Blue for %d bundle %d",i,LevelXML::getBundleColorOuterAt(i).b);
        } */  //Hidden Log // Delete in release
        auto iBundle = Sprite::create("whiteCircle.png");
        iBundle->setColor(LevelXML::getBundleColorInnerAt(i));
        iBundle->setAnchorPoint(Point(0.5,0.5));
//        float deltaEclipse = iBundle->getBoundingBox().size.width*0.20; //to be saved
        iBundle->setScale(Util::getScreenRatioWidth(iBundle)*0.75);
        iBundle->setOpacity(GAME_OPACITY);
//        float x = (r+deltaEclipse)*cos(theta); //to be saved
        float x = r*cos(theta);
        float y = r*sin(theta);
        iBundle->setPosition(Point(x,y));
        
        /* Complicated Script */
        iBundle->runAction( RepeatForever::create(
                                                  Sequence::create(
                                                                   ScaleBy::create(3,1.1),
                                                                   ScaleBy::create(3,1.1)->reverse(),
                                                                   NULL)
                                                  ));

        
        auto oBundle = Sprite::create("whiteCircle.png");
        oBundle->setColor(LevelXML::getBundleColorOuterAt(i));
        oBundle->setAnchorPoint(Point(0.5, 0.5));
        oBundle->setScale(iBundle->getScale()*0.30);
        oBundle->setOpacity(GAME_OPACITY);
        oBundle->setPosition(Point(x,y));
        
        /* Complicated Script */
        oBundle->runAction( RepeatForever::create(
                                                Sequence::create(
                                                                 ScaleBy::create(3,1.5),
                                                                 ScaleBy::create(3,1.5)->reverse(),
                                                                 NULL)
                                                ));
        
        //Add Text
        int lengthOfBundleName = std::strlen(LevelXML::getBundleNameAt(i).c_str());
        auto lblBundleName = LabelBMFont::create(LevelXML::getBundleNameAt(i), Constants::bitmapFontName);
        lblBundleName->setScale(Util::getScreenRatio(lblBundleName)*0.1);
        lblBundleName->setPosition(Point(x, y));
        int circumfence = oBundle->getBoundingBox().size.width;
        
        /* Fancy Curved Bundle Name */
        int tR = circumfence;
        float tStep = (PI*0.4)/lengthOfBundleName;
        float tTheta= 0;
        for(int j =0; j < lengthOfBundleName;j++,tTheta+=tStep)
        {
            Sprite * tempSprite = lblBundleName->getLetter(lengthOfBundleName-j-1);
            float tX = tR*cos(tTheta);
            float tY = tR*sin(tTheta);
            tempSprite->setAnchorPoint(Point(0.5,0));
            tempSprite->setPosition(Point(tX,tY));
            tempSprite->setRotation(90 - tTheta*(180.0/PI));
            
        }
        
        bundleNode->addChild(oBundle,bundleSize-i);
        bundleNode->addChild(iBundle,bundleSize-i);
        bundleNode->addChild(lblBundleName,bundleSize-i);
    }
    //End
    
    bundleNode->setPosition(Point(origin.x + visibleSize.width*(0.50),origin.y + visibleSize.height*0.30 ));
    this->addChild(bundleNode,zReloader);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, settingButton,tutorialButton,gameTitle, NULL);
#else
    auto menu = Menu::create(playItem, settingButton, tutorialButton,gameTitle, closeItem, NULL);
#endif
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
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
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
        {swipeLeft();touchStart = Point::ZERO;}
        else if(location.x - touchStart.x > SWIPE_THRESHOLD)
        {swipeRight();touchStart = Point::ZERO;}
        //up down
        else if(touchStart.y - location.y > SWIPE_THRESHOLD)
        {swipeDown();touchStart = Point::ZERO;}
        else if (location.y - touchStart.y > SWIPE_THRESHOLD)
        {swipeUp();touchStart = Point::ZERO;}
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

void MainMenu::swipeLeft()
{
    
    bundleNode->runAction(RotateBy::create(2.0, -1*step*(180.0/PI)));
    log("left");
}
void MainMenu::swipeRight()
{
    bundleNode->runAction(RotateBy::create(2.0, step*(180.0/PI)));
    log("right");
}
void MainMenu::swipeUp()
{log("up");}
void MainMenu::swipeDown()
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
