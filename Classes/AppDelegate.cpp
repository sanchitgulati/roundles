#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "LevelXML.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //read from level file
    LevelXML::init();
    
    // preload background music and effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic( SFX_MUSIC );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( SFX_BTN_CLICKED );
    
    // set default volume
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.50);
    
    //Play Playholder Music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(SFX_MUSIC,true);

    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
