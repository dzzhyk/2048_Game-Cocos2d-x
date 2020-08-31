//
//  MainMenu.cpp
//  2048
//
//  Created by dzzhyk on 2019/11/22.
//

#include "MainMenu.h"
#include "GameScene.h"


cocos2d::Scene* MainMenu::createMainMenu(){
    auto scene = cocos2d::Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init(){
    if (!cocos2d::Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    layerBGColor = LayerColor::create(Color4B(249, 246, 235, 255));
    this->addChild(layerBGColor);
    
    startClassicalBTN = Label::createWithSystemFont("经典模式", "HiraKakuProN-W6", 50);
    startClassicalBTN->setAnchorPoint(Point(0.5, 0.5));
    startClassicalBTN->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    startClassicalBTN->setColor(Color3B(172, 157, 142));
    this->addChild(startClassicalBTN);
    
    
    auto BTN_listener_classical = EventListenerTouchOneByOne::create();
    BTN_listener_classical->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBeganClassicalBTN, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BTN_listener_classical, startClassicalBTN);
    
    
    
    musicManager.playBGM((char*)"bgm.wav", true);
    
    return true;
}


bool MainMenu::onTouchBeganClassicalBTN(cocos2d::Touch *t, cocos2d::Event *e){
    if (startClassicalBTN->getBoundingBox().containsPoint(t->getLocation())) {
        musicManager.playEffect((char*)"button.wav", false);
        // 切换场景
        auto classicalMode = GameScene::createScene();
        Director::getInstance()->pushScene(TransitionFade::create(1.5, classicalMode));
    }
    return false;
}
