//
//  GameScene.h
//  2048
//
//  Created by dzzhyk on 2019/11/21.
//

#ifndef GameScene_h
#define GameScene_h
#include "cocos2d.h"
#include "Card.h"
#include "MyMusic.h"

class GameScene : public cocos2d::Layer {
private:
    
    int score;  // 当前分数
    int highscore;   // 记录的最高分
    Card *table[4][4];    // 二维矩阵
    Label *scoreBoard;  // 记分板
    Label *highScoreBoard;  // 最高分记分板
    MyMusic musicManager;   // 音乐管理器
    
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    int getCurrentScore();
    void setCurrentScore(int);
    int getHighScore();
    void setHighScore(int);
    
    // 移动处理
    virtual bool onTouchBegan(cocos2d::Touch *t, cocos2d::Event *e);
    virtual void onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e);
    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();
    
    
private:
    int firstX, firstY, endX, endY;
    // 创建卡片
    void initCard(cocos2d::Size size);
    // 创建背景
    void initBackGround(cocos2d::Size size);
    // 随机卡片生成
    void createNumberRandomly();
    // 结束判断
    void checkGameOver();
    // 刷新记分板
    void flushScoreBoard(int x);
    // 播放成功合并音效
    void playCombinedEffect();
    // 写入文件记录最高分
    void recordHighScore();
    // 读取文件获取记录的最高分来替换最高分
    void getRecordHighScore();
};

#endif /* GameScene_h */

