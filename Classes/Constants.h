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

#define RGBA_COLOR1 Color4B(255,255,255,255) // was bg //(237,237,237)
#define RGB_COLOR1 Color3B(255,255,255)     // is bg

#define RGBA_COLOR2 Color4B(240,201,74,255) //was logo //(128,215,232)
#define RGB_COLOR2 Color3B(240,201,74)      //Menu Item

#define RGBA_COLOR3 Color4B(51,113,126,255) //was inner logo  //(83,190,230)
#define RGB_COLOR3 Color3B(51,113,126)      // Heading

#define RGBA_COLOR4 Color4B(235,239,242,255) // was heading  //(79,79,79)
#define RGB_COLOR4 Color3B(235,239,242)      // is highlight

#define RGBA_COLOR5 Color4B(83,190,230,255)
#define RGB_COLOR5 Color3B(83,190,230)    //is text against bg

#define RGBA_COLOR6 Color4B(255,255,255,255)
#define RGB_COLOR6 Color3B(255,255,255) //is text against Menu Item

#define RGB_COLOR7 Color3B(83,101,121)
#define RGBA_COLOR7 Color4B(83,101,121,255)  // is black

#define SFX_BTN_CLICKED "sfx/btn_Clicked.wav"
#define SFX_POSITIVE "sfx/btn_Postive.wav"
#define SFX_NEGATIVE "sfx/btn_Negation.wav"
#define SFX_MUSIC "sfx/caribbean_lobby-rick_dickert.mp3"

#define GAME_OPACITY 220.0

#define SWIPE_THRESHOLD 100.0

#define ANIMATION_CONSTANT 0.10

#define MENU_HEIGHT 0.90


#define IMG_BLUR "images/blur.png"

#define IMG_CIRCLE_BTN "images/circleBtn.png"
#define IMG_CIRCLE_OBJECT "images/circleBtn.png"
#define IMG_CIRCLE_MM "images/circleMM.png"
#define IMG_CIRCLE_SHADOW "images/circleShadow.png"
#define IMG_CIRCLE_LIGHT "images/circleGameOuter.png"

#define IMG_CIRCLE_TWITTER "images/twitter.png"
#define IMG_CIRCLE_WHITE "images/circleWhiteHiRes.png"
#define IMG_CIRCLE_WHITE_BORDER "images/circleWhiteBorder.png"
#define IMG_RECT_WHITE "images/rectWhite.png"
#define IMG_BUTTON_WHITE "images/btnWhiteFlat.png"


#define IMG_BUTTON_MENU "images/btnMenu.png"
#define IMG_BUTTON_LEVEL "images/btnWhiteFlat.png"
#define IMG_BUTTON_HINT "images/btnHint.png"
#define IMG_BUTTON_RESTART "images/btnRestart.png"
#define IMG_BUTTON_UNDO "images/btnUndo.png"

#define IMG_BUTTON_TUTORIAL "images/btnTut.png"
#define IMG_BUTTON_ACHIEVE "images/btnAchieve.png"

#define IMG_BUTTON_BACK "images/btnBack.png"
#define IMG_BUTTON_OPTION "images/btnOption.png"
#define IMG_TICK_GREEN "images/btnTick.png"
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
