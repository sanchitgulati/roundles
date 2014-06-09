//
//  Constants.h
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 22/03/14.
//
//

#ifndef __OneClosedLoop__Constants__
#define __OneClosedLoop__Constants__

#include <iostream>
#include "cocos2d.h"

#define PI 3.14

#define RGBA_BG Color4B(237,237,237,255)
#define RGB_BG Color3B(237,237,237)

#define LOGO_RGBA 128,215,232,255
#define LOGO_RGB 128,215,232

#define INNER_LOGO_RGBA 83,190,230,255
#define INNER_LOGO_RGB 83,190,230

#define H1_LABEL_RGBA 79,79,79,255
#define H1_LABEL_RGB 79,79,79

#define GAME_OPACITY 220.0

#define SWIPE_THRESHOLD 100.0


#define IMG_CIRCLE_WHITE "images/whiteCircle.png"
#define IMG_RECT_WHITE "images/whiteRect.png"
#define IMG_BUTTON_WHITE "images/whiteButton.png"


#define IMG_BUTTON_MENU "images/btnMenu.png"
#define IMG_BUTTON_TUTORIAL "images/btnTut.png"
#define IMG_BUTTON_BACK "images/btnBack.png"
#define IMG_BUTTON_OPTION "images/btnOption.png"
#define IMG_TICK_GREEN "images/btnTick.png"

enum zindex
{
    zBg,
    zReloader,
    zMenu,
    zLogo,
    zPrimatives
    
};

enum gamestate
{
    gsMenu,
};




class Constants
{
public:
    static std::string fontName;
    static std::string fontNameBold;
    static std::string fontNameLight;
    static std::string bitmapFontName;
    static int defaultFontSize;
    static int fontSize;
    
    
    //Variables
    static float vEdgeMargin;
};

#endif /* defined(__OneClosedLoop__Constants__) */
