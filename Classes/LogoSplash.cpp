//
//  LogoSplash.cpp
//  roundels
//
//  Created by Sanchit Gulati on 02/08/14.
//
//

#include "LogoSplash.h"
#include "MainMenuScene.h"
#include "Constants.h"

using namespace cocos2d;

std::string LogoSplash::tips[TOTAL_TIPS] =
{
    "Change to your favorite language from setting menu",
    "Sharing On Twitter and Facebook have perks",
    "Hints replenish themselves every 6 hours",
    "Score more with faster moves and avoiding illegal moves",
    "Spread the love"
};

LogoSplash::LogoSplash() {
    
}

LogoSplash::~LogoSplash() {
    
}

bool LogoSplash::init() {
    bool bRet = false;
    
    do {
        
        CC_BREAK_IF(! LayerColor::init());
        
        
        auto touchListener = EventListenerTouchAllAtOnce::create();
        touchListener->onTouchesEnded = CC_CALLBACK_2(LogoSplash::onTouchesEnded, this);
        touchListener->onTouchesBegan = CC_CALLBACK_2(LogoSplash::onTouchesBegan, this);
        
        this->setColor(Color3B(RGB_COLOR1));
        this->setOpacity(255);
        
        Size screenSize = Director::getInstance()->getWinSize();
        
        logoSprite = CCSprite::create("images/logo.png");
        float logoWidth = logoSprite->boundingBox().size.width;
        logoSprite->setScale(clampf(screenSize.width/logoWidth*0.8,0,1));
        
        this->addChild(logoSprite);
        logoSprite->setPosition(Point(screenSize.width/2,screenSize.height/2));
        logoSprite->setOpacity(0);
        
        auto dice = arc4random_uniform(TOTAL_TIPS);
        
        auto tipsString = StringUtils::format("%s : %s",LocalizedString::localizedString("TIP")->getCString(),
                                              LocalizedString::localizedString(tips[dice].c_str())->getCString());
        
        labelHint = Label::create(tipsString, Constants::fontName, Constants::fontSize*0.50);
        labelHint->setDimensions(screenSize.width*0.70,0);
        labelHint->setColor(RGB_COLOR7);
        labelHint->setAnchorPoint(Point(0.5, 0.5));
        labelHint->setHorizontalAlignment(TextHAlignment::CENTER);
        labelHint->setPosition(Point(screenSize.width/2,screenSize.height*0.30));
        labelHint->setOpacity(0);
        this->addChild(labelHint);
        
        bRet = true;
    } while(0);
    
    
    this->scheduleUpdate();
    
    return bRet;
}


void LogoSplash::onEnter() {
    
    Layer::onEnter();
    
    auto nextSceneFunc = CallFuncN::create(CC_CALLBACK_1(LogoSplash::nextScene,this));
    
    
    ActionInterval* pFadeIn = FadeIn::create(1.0f);
    ActionInterval* pFadeOut = FadeOut::create(1.0f);
    //    ActionInterval* pFadeOut = MoveTo::create(3.0, Point(0,0));
    DelayTime* delayTimeShort = DelayTime::create(1.0f);
    
    FiniteTimeAction* pSeq = CCSequence::create(pFadeIn, delayTimeShort, pFadeOut,nextSceneFunc, NULL );
    
    logoSprite->runAction(pSeq);
    labelHint->runAction(pSeq->clone());
}

void LogoSplash::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    this->nextScene(this);
}


void LogoSplash::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{}



void LogoSplash::onExit() {
    Layer::onExit();
}

void LogoSplash::nextScene(Node *)
{
    Scene* scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
}

void LogoSplash::update(float delta)
{
    //    log("Get Position %f %f",logoSprite->getPositionX(),logoSprite->getPositionY());
    
}