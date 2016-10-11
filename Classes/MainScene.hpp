//
//  MainScene.hpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/26.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    
    cocos2d::Layer testLayer;
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallBack(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainScene);
    
    virtual void update(float delta);
    
private:
    void createBackground();
    
    void createFloor();
    
};


#endif /* MainScene_hpp */
