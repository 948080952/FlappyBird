//
//  DPMarioNode.cpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/29.
//
//

#include "DPMarioNode.hpp"
#include "Constants.h"
#include "Macros.h"

USING_NS_CC;

DPMarioNode* DPMarioNode::create()
{
    DPMarioNode *pRet = new DPMarioNode();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool DPMarioNode::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    this->setTexture("res/bird_3.png");
    float width = WIDTH(this);
    float height = HEIGHT(this);
    this->setScale(1.5, 1.5);
    
    
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(3);
    animFrames.pushBack(SpriteFrame::create("res/bird_1.png", Rect(0, 0, width, height)));
    animFrames.pushBack(SpriteFrame::create("res/bird_2.png", Rect(0, 0, width, height)));
    animFrames.pushBack(SpriteFrame::create("res/bird_3.png", Rect(0, 0, width, height)));
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.f, 1);
    auto animate = Animate::create(animation);
    
    this->flap = animate;
    CC_SAFE_RETAIN(flap);
    
    return true;
}

void DPMarioNode::startPlaying()
{
    auto body = PhysicsBody::createBox(this->getContentSize());
    body->setMass(0.1);
    body->setCategoryBitmask(birdBitMask);
    body->setContactTestBitmask(blockBitMask);
    body->setMoment(1.f);
    this->setPhysicsBody(body);
}


void DPMarioNode::fly()
{
    this->getPhysicsBody()->setVelocity(Vec2(0, 0));
    this->getPhysicsBody()->applyImpulse(Vec2(0, 30));
    
    
//    auto fadeout = FadeOut::create(0.5);
//    auto fadein = FadeIn::create(0.5);
//    
//    auto seq = Sequence::create(fadeout, fadein, NULL);
    
    float width = WIDTH(this) / SCALE(this);
    float height = HEIGHT(this) / SCALE(this);
    
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(3);
    animFrames.pushBack(SpriteFrame::create("res/bird_1.png", Rect(0, 0, width, height)));
    animFrames.pushBack(SpriteFrame::create("res/bird_2.png", Rect(0, 0, width, height)));
    animFrames.pushBack(SpriteFrame::create("res/bird_3.png", Rect(0, 0, width, height)));
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f, 1);
    auto animate = Animate::create(animation);
    
    this->runAction(animate);
}

