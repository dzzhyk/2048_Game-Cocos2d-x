//
//  Card.h
//  2048
//
//  Created by dzzhyk on 2019/11/21.
//

#ifndef Card_h
#define Card_h
#include "cocos2d.h"
using namespace cocos2d;

class Card : public Sprite {
private:
    
    int number;
    void enemyInit(int number, int width, int height, float x, float y);   // 私有的初始化方法
    
    // 显示数字的控件
    cocos2d::Label *numberLabel;
    
    // 背景控件
    cocos2d::LayerColor *layerBGColor;
    
public:
    virtual bool init();
    static Card* createCard(int _number, int width, int height, float x, float y);   // 外部调用的初始化方法
    CREATE_FUNC(Card);
    int getNumber();
    void setNumber(int);
};


#endif /* Card_h */
