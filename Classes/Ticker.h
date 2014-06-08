#include "cocos2d.h"

class Ticker : public cocos2d::Node
{
    std::string *_messageArray;
    int _size;
    float _delay;
    int ctr;
    cocos2d::Label *lblTicker;
  Ticker(std::string *messageArray, int size, const char* fontName, int fontSize, float delay);
public:
    static Ticker* create(std::string *messageArray, int size, const char* fontName, int fontSize, float delay = 2);
    void updateTicker(float);
    void updateString();
    virtual void setAnchorPoint(cocos2d::Point);
    virtual void setColor(cocos2d::Color3B);
    virtual void setVisible(bool);
};