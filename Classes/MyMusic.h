//
//  MyMusic.h
//  2048
//
//  Created by dzzhyk on 2019/11/22.
//

#ifndef MyMusic_h
#define MyMusic_h
#include <map>
class MyMusic{

private:
    
    std::map<char*, int> manager;
    
public:
    MyMusic();
    ~MyMusic();
    int getEffectID(char*);
    void setEffectID(char*, int);
    void preLoadMusicSources();
    void playBGM(char*, bool);
    void stopBGM();
    void playEffect(char*, bool);
    void pauseBGM();
    void pauseEffect(char*);
    void pauseAllEffect();
    void pauseAllMusic();
    void resumeBGM();
    void resumeEffect(char*);
    void resumeAllEffect();
    void resumeAllMusic();  // 恢复所有音乐
    void stopEffect(char*);
    void stopAllEffect();
    void destroyMusicEngine();
};

#endif /* MyMusic_h */
