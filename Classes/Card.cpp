//
//  Card.cpp
//  2048
//
//  Created by dzzhyk on 2019/11/21.
//

#include "Card.h"
#include "cocos2d.h"
using namespace cocos2d;

Card* Card::createCard(int number, int width, int height, float x, float y){
    
    auto enemy = new Card();
    if (enemy && enemy->init()) {
        enemy->autorelease();
        enemy->enemyInit(number, width, height, x, y);  // 调用私有的初始化方法来进行初始化
        
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

bool Card::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    
    
    return true;
}

int Card::getNumber(){
    return number;
}

void Card::setNumber(int x){
    number = x;
    // 更新显示的数字
    if (number > 0) {
        // 根据不同的数字显示不同的颜色的字体大小
        switch (number) {
            case 2:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(233, 221, 209));
                numberLabel->setColor(Color3B(99, 91, 82));
                break;
            case 4:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(232, 217, 187));
                numberLabel->setColor(Color3B(99, 91, 82));
                break;
            case 8:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(235, 160, 99));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 16:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(237, 128, 78));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 32:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(237, 100, 75));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 64:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(60);
                layerBGColor->setColor(Color3B(236, 69, 43));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 128:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(50);
                layerBGColor->setColor(Color3B(231, 197, 90));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 256:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(50);
                layerBGColor->setColor(Color3B(231, 193, 72));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 512:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(50);
                layerBGColor->setColor(Color3B(232, 197, 66));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 1024:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(38);
                layerBGColor->setColor(Color3B(232, 194, 46));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 2048:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(38);
                layerBGColor->setColor(Color3B(233, 191, 24));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 4096:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(38);
                layerBGColor->setColor(Color3B(53, 51, 44));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            case 8192:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(38);
                layerBGColor->setColor(Color3B(216, 96, 187));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
            default:
                numberLabel->setString(__String::createWithFormat("%d", number)->getCString());
                numberLabel->setSystemFontSize(30);
                layerBGColor->setColor(Color3B(244, 0, 22));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
        }
    }else{
        // 否则设置为空，还原为默认底色
        numberLabel->setString("");
        layerBGColor->setColor(Color3B(197, 183, 169));
    }
}

void Card::enemyInit(int _number, int width, int height, float x, float y){
    number = _number;
    
    // 设置游戏卡片的背景颜色
    layerBGColor = LayerColor::create(Color4B(197, 183, 169, 255), width-10, height-10);
    layerBGColor->setPosition(Point(x, y));
    
    if (_number <= 0) {
        numberLabel = Label::createWithSystemFont("", "HiraKakuProN-W6", 60);
        numberLabel->setAnchorPoint(Point(0.5, 0.5));
        numberLabel->setPosition(Point(x+width/2-4, y+height/2-20));
    }else{
        switch (_number) {
            case 2:
                numberLabel= Label::createWithSystemFont(__String::createWithFormat("%d", _number)->getCString(), "HiraKakuProN-W6", 60);
                layerBGColor->setColor(Color3B(233, 221, 209));
                numberLabel->setColor(Color3B(99, 91, 82));
                break;
            case 4:
                numberLabel= Label::createWithSystemFont(__String::createWithFormat("%d", _number)->getCString(), "HiraKakuProN-W6", 60);
                layerBGColor->setColor(Color3B(232, 217, 187));
                numberLabel->setColor(Color3B(99, 91, 82));
                break;
            default:
                numberLabel= Label::createWithSystemFont(__String::createWithFormat("%d", _number)->getCString(), "HiraKakuProN-W6", 30);
                layerBGColor->setColor(Color3B(244, 0, 22));
                numberLabel->setColor(Color3B(247, 244, 239));
                break;
        }
        numberLabel->setAnchorPoint(Point(0.5, 0.5));
        numberLabel->setPosition(Point(x+width/2-4, y+height/2-20));
    }
    this->addChild(layerBGColor);
    this->addChild(numberLabel);
}
