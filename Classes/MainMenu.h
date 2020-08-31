//
//  MainMenu.h
//  2048
//
//  Created by dzzhyk on 2019/11/22.
//

#ifndef MainMenu_h
#define MainMenu_h
#include "cocos2d.h"
#include "MyMusic.h"
using namespace cocos2d;

// 主界面基类
class MainMenu : public cocos2d::Layer{
private:
    MyMusic musicManager;
    // 开始游戏按钮
    Label * startClassicalBTN;
    // 背景颜色
    LayerColor *layerBGColor;
    
public:
    virtual bool init();
    static cocos2d::Scene* createMainMenu();
    CREATE_FUNC(MainMenu);
    virtual bool onTouchBeganClassicalBTN(cocos2d::Touch *t, cocos2d::Event *e);
};
#endif /* MainMenu_h */
