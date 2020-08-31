//
//  MyMusic.cpp
//  2048
//
//  Created by dzzhyk on 2019/11/22.
//

#include "MyMusic.h"
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

void MyMusic::preLoadMusicSources(){
    // 预加载音效
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("button.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("eliminate.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("generate.wav");
}

MyMusic::MyMusic(){
    manager.clear();
}

MyMusic::~MyMusic(){
    manager.clear();
}

void MyMusic::playBGM(char *name, bool loop){
    SimpleAudioEngine::getInstance()->playBackgroundMusic(name, loop);
}

void MyMusic::stopBGM(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void MyMusic::playEffect(char *name, bool loop){
    manager.insert(std::pair<char*, int>(name, SimpleAudioEngine::getInstance()->playEffect(name, loop)));
}

void MyMusic::stopEffect(char *name){
    SimpleAudioEngine::getInstance()->stopEffect(manager[name]);
}

void MyMusic::stopAllEffect(){
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void MyMusic::destroyMusicEngine(){
    SimpleAudioEngine::end();
    manager.clear();
}

void MyMusic::pauseBGM(){
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void MyMusic::pauseAllEffect(){
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void MyMusic::pauseAllMusic(){
    pauseBGM();
    pauseAllEffect();
}

void MyMusic::resumeBGM(){
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void MyMusic::resumeAllEffect(){
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void MyMusic::resumeAllMusic(){
    resumeBGM();
    resumeAllEffect();
}

int MyMusic::getEffectID(char *name){
    return manager[name];
}

void MyMusic::setEffectID(char *name, int id){
    manager[name] = id;
}

void MyMusic::pauseEffect(char *name){
    SimpleAudioEngine::getInstance()->pauseEffect(manager[name]);
}

void MyMusic::resumeEffect(char *name){
    SimpleAudioEngine::getInstance()->resumeEffect(manager[name]);
}
