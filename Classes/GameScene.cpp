//
//  GameScene.cpp
//  2048
//
//  Created by dzzhyk on 2019/11/21.
//

#include <iostream>
#include "GameScene.h"
#include "cocos2d.h"
#include "Card.h"
using namespace cocos2d;

cocos2d::Scene* GameScene::createScene(){
    auto scene = cocos2d::Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    if (!cocos2d::Layer::init()) {
        return false;
    }
    
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//    Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    // 单点触摸事件侦听器
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    // 绑定事件侦听器
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // 读取记录的最高分
    getRecordHighScore();
    // 初始化背景
    initBackGround(visibleSize);
    // 初始化卡片
    initCard(visibleSize);  // 传入可视区域的size
    // 初始随机生成2个卡片
    createNumberRandomly();
    createNumberRandomly();
    
    
    return true;
}


int GameScene::getCurrentScore(){
    return score;
}

void GameScene::setCurrentScore(int x){
    score = x;
}

bool GameScene::onTouchBegan(cocos2d::Touch *t, cocos2d::Event *e){
    cocos2d::Point p = t->getLocation();
    firstX = p.x;
    firstY = p.y;
    return true;
}
void GameScene::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e){
    cocos2d::Point p = t->getLocation();
    endX = firstX - p.x;
    endY = firstY - p.y;
    
    if (abs(endX) > abs(endY)) {
        // 左右移动
        if (endX+50 > 0) {
            // 移动结束之后如果发生了移动就刷出随机数
            if (doLeft()) {
                createNumberRandomly();
                checkGameOver();
            }
        }else{
            if (doRight()){
                createNumberRandomly();
                checkGameOver();
            }
        }
    }else{
        // 上下移动
        if (endY+50 > 0) {
            if (doDown()) {
                createNumberRandomly();
                checkGameOver();
            }
        }else{
            if (doUp()) {
                createNumberRandomly();
                checkGameOver();
            }
        }
    }
}

bool GameScene::doUp(){
    bool isdo = false;
    
    for (int i=0; i<4; i++) {
        for (int j=3; j>=0; j--) {
            
            for (int pos=j-1; pos >= 0; pos--) {
                if (table[pos][i]->getNumber() > 0) {   // 判断当前位置上面一列是否有数字
                    if (table[j][i]->getNumber() <= 0) {    // 如果当前的位置没有数字
                        table[j][i]->setNumber(table[pos][i]->getNumber());
                        table[pos][i]->setNumber(0);
                        
                        j++;    // j++ 来继续检测这一列
                        isdo = true;
                    }else if (table[j][i]->getNumber() == table[pos][i]->getNumber()) {
                        table[j][i]->setNumber(2*table[j][i]->getNumber());
                        table[pos][i]->setNumber(0);
                        
                        // 合并音效
                        playCombinedEffect();
                        // 得分:
                        flushScoreBoard(table[j][i]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool GameScene::doDown(){
    bool isdo = false;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            
            for (int pos=j+1; pos < 4; pos++) {
                if (table[pos][i]->getNumber() > 0) {   // 判断当前位置上面一列是否有数字
                    if (table[j][i]->getNumber() <= 0) {    // 如果当前的位置没有数字
                        table[j][i]->setNumber(table[pos][i]->getNumber());
                        table[pos][i]->setNumber(0);
                        
                        j--;    // j-- 来继续检测这一列
                        isdo = true;
                    }else if (table[j][i]->getNumber() == table[pos][i]->getNumber()) {
                        table[j][i]->setNumber(2*table[j][i]->getNumber());
                        table[pos][i]->setNumber(0);
                        
                        // 合并音效
                        playCombinedEffect();
                        // 得分:
                        flushScoreBoard(table[j][i]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isdo;
}
bool GameScene::doLeft(){
    bool isdo = false;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            
            for (int pos=j+1; pos < 4; pos++) {
                if (table[i][pos]->getNumber() > 0) {   // 判断当前位置上面一列是否有数字
                    if (table[i][j]->getNumber() <= 0) {    // 如果当前的位置没有数字
                        table[i][j]->setNumber(table[i][pos]->getNumber());
                        table[i][pos]->setNumber(0);
                        
                        j--;    // j-- 来继续检测这一行
                        isdo = true;
                    }else if (table[i][j]->getNumber() == table[i][pos]->getNumber()) {
                        table[i][j]->setNumber(2*table[i][j]->getNumber());
                        table[i][pos]->setNumber(0);
                        
                        // 合并音效
                        playCombinedEffect();
                        // 得分:
                        flushScoreBoard(table[i][j]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool GameScene::doRight(){
    bool isdo = false;
    for (int i=0; i<4; i++) {
        for (int j=3; j>=0; j--) {
            
            for (int pos=j-1; pos >= 0; pos--) {
                if (table[i][pos]->getNumber() > 0) {   // 判断当前位置上面一列是否有数字
                    if (table[i][j]->getNumber() <= 0) {    // 如果当前的位置没有数字
                        table[i][j]->setNumber(table[i][pos]->getNumber());
                        table[i][pos]->setNumber(0);
                        
                        j++;    // j++ 来继续检测这一行
                        isdo = true;
                    }else if (table[i][j]->getNumber() == table[i][pos]->getNumber()) {
                        table[i][j]->setNumber(2*table[i][j]->getNumber());
                        table[i][pos]->setNumber(0);
                        
                        // 合并音效
                        playCombinedEffect();
                        // 得分:
                        flushScoreBoard(table[i][j]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}

void GameScene::initCard(cocos2d::Size size){
    
    // 计算单元格的宽度和高度
    int len = (size.width-2*45-5*10)/4;  // 有四张卡片就除以4
    
    float saveX, saveY;
    saveX = 52;
    saveY = size.height/6;
    
#if 0
    int a = 2;
#endif
    
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (j==0) {
                table[i][j] = Card::createCard(0, len, len, saveX, saveY + i*(14+len));
//                card->setAnchorPoint(Point(0.5, 0.5));
                this->addChild(table[i][j]);
            }else{
                table[i][j] = Card::createCard(0, len, len, saveX + j*(14+len), saveY + i*(14+len));
//                card->setAnchorPoint(Point(0.5, 0.5));
                this->addChild(table[i][j]);
            }
        }
//        a *= 2;
    }
}

void GameScene::initBackGround(cocos2d::Size size){
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto background = LayerColor::create(Color4B(249, 246, 235, 255));
    addChild(background);
    
    float saveX, saveY;
    saveX = 32;
    saveY = size.height/6-20;
    // 4*4底部棕色色块
    auto background_card = LayerColor::create(Color4B(172, 157, 142, 255), size.width-5*10-20, size.width-5*10-20);
    background_card->setPosition(Point(saveX, saveY));
    addChild(background_card);
    // 记分板和最高分底部的色块以及文字
    auto background_score = LayerColor::create(Color4B(172, 157, 142, 255), 180, 150);
    background_score->setPosition(Point(size.width/2-80, size.height/4*3+90));
    addChild(background_score);
    auto background_highscore = LayerColor::create(Color4B(172, 157, 142, 255), 180, 150);
    background_highscore->setPosition(Point(size.width/2+110, size.height/4*3+90));
    addChild(background_highscore);
    auto background_title = LayerColor::create(Color4B(233, 191, 24, 255), 200, 200);
    background_title->setPosition(Point(size.width/2-300, size.height/4*3+40));
    addChild(background_title);
    auto labelScore = Label::createWithTTF("得分", "test.ttf", 46);
    labelScore->setPosition(Point(size.width/2+10, size.height/4*3+190));
    auto labelHighScore = Label::createWithTTF("最高分", "test.ttf", 46);
    labelHighScore->setPosition(Point(size.width/2+200, size.height/4*3+190));
    auto labelTitle = Label::createWithTTF("2048", "test.ttf", 68);
    labelTitle->setPosition(Point(size.width/2-200, size.height/4*3+120));
    auto labelRules = Label::createWithTTF("合并数字以得到2048方块！", "test.ttf", 40);
    labelRules->setAnchorPoint(Point(0, 0));
    labelRules->setPosition(Point(size.width/2-280, size.height/4*3-80));
    labelRules->setTextColor(Color4B(172, 157, 142, 255));
    addChild(labelScore);
    addChild(labelHighScore);
    addChild(labelTitle);
    addChild(labelRules);
    // 添加分数
    scoreBoard = Label::createWithTTF(__String::createWithFormat("%d", 0)->getCString(), "test.ttf", 46);
    scoreBoard->setPosition(Point(size.width/2+10, labelScore->getPositionY()-70));
    scoreBoard->setColor(Color3B(247, 244, 239));
    addChild(scoreBoard);
    // 添加最高分
    highScoreBoard = Label::createWithTTF(__String::createWithFormat("%d", highscore)->getCString(), "test.ttf", 46);
    highScoreBoard->setPosition(Point(size.width/2+200, labelScore->getPositionY()-70));
    highScoreBoard->setColor(Color3B(247, 244, 239));
    addChild(highScoreBoard);
}

// 随机生成卡片
void GameScene::createNumberRandomly(){
    int x = CCRANDOM_0_1()*4;   // 获取0-3的随机数
    int y = CCRANDOM_0_1()*4;
    
    // 判断位置(x, y)是否为空
    if (table[x][y]->getNumber() <= 0) {
        // 为空
        table[x][y]->setNumber(CCRANDOM_0_1()*10<1?4:2);    // 10%的几率为4， 90%的几率为2
        musicManager.playEffect((char*)"generate.wav", false);
    }else{
        // 不为空
        createNumberRandomly();
    }
}

void GameScene::checkGameOver(){
    bool isGameOver = true;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (table[i][j]->getNumber()==0||
                (i>0 && table[i][j]->getNumber()==table[i-1][j]->getNumber())||
                (i<3 && table[i][j]->getNumber()==table[i+1][j]->getNumber())||
                (j>0 && table[i][j]->getNumber()==table[i][j-1]->getNumber())||
                (j<3 && table[i][j]->getNumber()==table[i][j+1]->getNumber())) {
                isGameOver = false;
            }
        }
    }
    if (isGameOver) {
        // 记录最高分
        recordHighScore();
        // 重新开始
        Director::getInstance()->replaceScene(TransitionFade::create(1.5, GameScene::createScene()));
    }
}

void GameScene::flushScoreBoard(int x){
    score += x;
    scoreBoard->setString(__String::createWithFormat("%d", score)->getCString());
    // 替换最高分
    if (score > highscore) {
        highscore = score;
        highScoreBoard->setString(__String::createWithFormat("%d", highscore)->getCString());
    }
    // 这里根据数字宽度设置字体大小
    if (score > 9999 && score <= 99999) {
        scoreBoard->setSystemFontSize(40);
    }else if(score > 100000){
        scoreBoard->setSystemFontSize(30);
    }
    if (highscore > 9999 && highscore <= 99999) {
        highScoreBoard->setSystemFontSize(40);
    }else if(highscore > 100000){
        highScoreBoard->setSystemFontSize(30);
    }
}

void GameScene::playCombinedEffect(){
    musicManager.playEffect((char*)"eliminate.wav", false);
}

void GameScene::setHighScore(int score){
    highscore = score;
}

int GameScene::getHighScore(){
    return highscore;
}

void GameScene::recordHighScore(){
    UserDefault::getInstance()->setIntegerForKey("highScoreRecord_classical", highscore);
}

void GameScene::getRecordHighScore(){
    highscore = UserDefault::getInstance()->getIntegerForKey("highScoreRecord_classical", 0);
}
