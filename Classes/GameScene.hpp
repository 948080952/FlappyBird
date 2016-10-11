//
//  GameScene.hpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/28.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "DPScrollingNode.hpp"
#include "DPMarioNode.hpp"

class GameScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    
    virtual void update(float delta);
    
    CREATE_FUNC(GameScene);
    
private:
    
    DPMarioNode *mario;
    
    cocos2d::Layer *layer;
    
    DPScrollingNode *backgroundNode;
    
    DPScrollingNode *floorNode;
    
    cocos2d::Vector<cocos2d::Sprite*> bottomPipes;
    
    cocos2d::Vector<cocos2d::Sprite*> topPipes;
    
    cocos2d::Label *scoreLabel;
    
    bool wasted;
    
    bool started;
    
    int obstacleNum;
    
    int score;
    
    void startGame();
    
    void createNumLabel();
    
    void createBackground();
    
    void createFloor();
    
    void createSprite();
    
    void createObstacles();
    
    void updateObstacles();
    
    void updateScore();
    
    void placePipe(cocos2d::Sprite *bottomPipe, cocos2d::Sprite *topPipe, float positionX);
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
};

#endif /* GameScene_hpp */
