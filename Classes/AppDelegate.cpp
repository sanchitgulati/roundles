#include "AppDelegate.h"
#include "LogoSplash.h"
#include "Constants.h"
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
    auto valM = UserDefault::getInstance()->getBoolForKey("music", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(valM*SOUND_MAX);
    
    
    auto valS = UserDefault::getInstance()->getBoolForKey("sound", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(valS*MUSIC_MAX);
    
    
    //Unlock First Bundle Pernamently
    UserDefault::getInstance()->setBoolForKey("unlocked-0", true);
    UserDefault::getInstance()->flush();
    
    //Play Playholder Music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(SFX_MUSIC,true);

    
    //Loading default from static file
    LevelXML::curBundleNumber = UserDefault::getInstance()->getIntegerForKey("curBundleNumber", 0);
    
    // create a scene. it's an autorelease object
    
    auto scene = Scene::create();
    scene->addChild(LogoSplash::create());

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
