//
//  Util.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#include "Util.h"
#include "LevelXML.h"

float Util::getScreenRatio(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    if(winSize.width > winSize.height)
    {
        return (winSize.height/obj->getBoundingBox().size.height);
    }
    else
    {
        return (winSize.width/obj->getBoundingBox().size.width);
    }
}

float Util::getScreenRatioWidth(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    return (winSize.width/obj->getBoundingBox().size.width);

}

float Util::getScreenRatioHeight(Node* obj)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    return (winSize.height/obj->getBoundingBox().size.height);
}

Color3B Util::randomBrightColor()
{
    while (true) {
        float requiredBrightness = 192;
        Color3B c = Color3B(arc4random() % 255,arc4random() % 255,arc4random() % 255);
        if (    c.r > requiredBrightness
            ||  c.g > requiredBrightness
            ||  c.b > requiredBrightness)
        {
            return c;
        }
    }
}

void Util::loadParticleDefaults(cocos2d::ParticleSystemQuad *emitter)
{
    Size winSize = Director::getInstance()->getWinSize();
    emitter->setBlendAdditive(false);
    emitter->setSourcePosition(Point(winSize.width/2, winSize.height/2.0f));
    emitter->setPosVar(Point(winSize.width/2.0f, winSize.height/2.0f));
//    emitter->setOpacity(0);
//    auto fadeIn = FadeIn::create(1.0f);
//    auto delay = DelayTime::create(1.0f);
//    emitter->runAction(Sequence::create(delay,fadeIn,NULL));
    
    try
    {
        Color4F colorInner = Color4F(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber));
        colorInner.a = 0.5;
        emitter->setStartColor(colorInner);
    }
    catch(std::exception e)
    {
        log("Unable to setStartColor to particle emitter");
    }
}

std::string Util::to_roman(unsigned int value)
{
    struct romandata_t { unsigned int value; char const* numeral; };
    const struct romandata_t romandata[] =
    {
        {1000, "M"}, {900, "CM"},
        {500, "D"}, {400, "CD"},
        {100, "C"}, { 90, "XC"},
        { 50, "L"}, { 40, "XL"},
        { 10, "X"}, { 9, "IX"},
        { 5, "V"}, { 4, "IV"},
        { 1, "I"},
        { 0, NULL} // end marker
    };
    
    std::string result;
    for (const romandata_t* current = romandata; current->value > 0; ++current)
    {
        while (value >= current->value)
        {
            result += current->numeral;
            value -= current->value;
        }
    }
    return result;
}