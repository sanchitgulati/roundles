#ifndef __LOGOSPLASH_SCENE_H__
#define __LOGOSPLASH_SCENE_H__

#include "cocos2d.h"
#define TOTAL_TIPS 5

class LogoSplash : public cocos2d::LayerColor
{
public:
	LogoSplash();
	~LogoSplash();
    virtual bool init();
    void onEnter();
    void onExit();
    
    void nextScene(Node *);
    void update(float delta);
    
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    static std::string tips[TOTAL_TIPS];
    
    cocos2d::Sprite *logoSprite;
    cocos2d::Label *labelHint;
    
    CREATE_FUNC(LogoSplash);
};

#endif