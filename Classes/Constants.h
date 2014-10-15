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

//BG
#define RGBA_COLOR1 Color4B(251,251,255,255)
#define RGB_COLOR1 Color3B(251,251,255)


//MENU_ITEMS
#define RGBA_COLOR2 Color4B(240,201,74,255)
#define RGB_COLOR2 Color3B(240,201,74)


//HEADING
#define RGBA_COLOR3 Color4B(51,113,126,255)
#define RGB_COLOR3 Color3B(51,113,126)

//IS HIGHLIGHT
#define RGBA_COLOR4 Color4B(225,229,232,255)
#define RGB_COLOR4 Color3B(225,229,232)


//IS TEXT AGAINST BG
//LAST VAL 82,190,230
#define RGBA_COLOR5 Color4B(42,91,121,255)
#define RGB_COLOR5 Color3B(42,91,121)


//IS TEXT AGAINST MENU_ITEM
#define RGBA_COLOR6 Color4B(255,255,255,255)
#define RGB_COLOR6 Color3B(255,255,255)


//BLACK TEXT
#define RGB_COLOR7 Color3B(83,101,121)
#define RGBA_COLOR7 Color4B(83,101,121,255)


//ART_GREEN_UNLOCKED
#define RGB_COLOR8 Color3B(218,240,123)
#define RGBA_COLOR8 Color4B(218,240,123,255)


#define SFX_BTN_CLICKED "sfx/btn_Clicked.wav"
#define SFX_POSITIVE "sfx/btn_Postive.wav"
#define SFX_NEGATIVE "sfx/btn_Negation.wav"
#define SFX_MUSIC "sfx/caribbean_lobby-rick_dickert.mp3"

#define GAME_OPACITY 128.0

#define SWIPE_THRESHOLD 100.0

#define ANIMATION_CONSTANT 0.3

#define MENU_HEIGHT 0.90


#define IMG_LOCK "images/lock.png"

#define IMG_CIRCLE_BORDER "images/btnCircle.png"
#define IMG_CIRCLE_WHITE "images/circleWhiteLoRes.png"
#define IMG_CIRCLE_NO_BORDER "images/circleWhiteLoResNoBorder.png"

#define IMG_RABBIT "images/charRabbit.png"

#define IMG_CIRCLE_TWITTER "images/twitter.png"

#define IMG_RECT_WHITE "images/rectWhite.png"
#define IMG_BUTTON_WHITE "images/btnRectangle.png"


#define IMG_BUTTON_MENU "images/btnMenu.png"
#define IMG_BUTTON_LEVEL "images/btnWhiteFlat.png"
#define IMG_BUTTON_HINT "images/btnHint.png"
#define IMG_BUTTON_RESTART "images/btnRestart.png"
#define IMG_BUTTON_UNDO "images/btnUndo.png"

#define IMG_BUTTON_TUTORIAL "images/btnTut.png"
#define IMG_BUTTON_ACHIEVE "images/btnAchieve.png"

#define IMG_BUTTON_BACK "images/btnBack.png"
#define IMG_ARROW "images/arrowPlayer.png"

#define IMG_SANCHIT "images/sanchit.png"
#define IMG_RADHIKA "images/radhika.png"


#define MUSIC_MAX 0.50
#define SOUND_MAX 1.00

#define VFX_CONSTANT 0.50

enum zindex
{
    zBg,
    zReloader,
    zMenu,
    zLogo,
    zGame,
    zGameFront,
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
