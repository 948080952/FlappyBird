//
//  MainScene.cpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/26.
//
//

#include "MainScene.hpp"
#include "DPScrollingNode.hpp"

#define VisibleSize     Director::getInstance()->getVisibleSize()
#define VisibleWidth    Director::getInstance()->getVisibleSize().width
#define VisibleHeight   Director::getInstance()->getVisibleSize().height
#define Origin          Director::getInstance()->getVisibleOrigin()
#define OriginX         Director::getInstance()->getVisibleOrigin().x
#define OriginY         Director::getInstance()->getVisibleOrigin().y

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->createBackground();
    this->createFloor();
    
    return true;
}

#pragma mark - Privite Method

void MainScene::createBackground()
{
    auto backgroundNode = DPScrollingNode::create("res/back.png", Size(VisibleWidth, VisibleHeight - 80));
    backgroundNode->setAnchorPoint(Vec2(0, 0));
    backgroundNode->setPosition(OriginX, OriginY + 80);
    backgroundNode->scrollSpeed = 1;
    this->addChild(backgroundNode);
}

void MainScene::createFloor()
{
    auto floorNode = DPScrollingNode::create("res/floor.png", Size(VisibleWidth, 80));
    floorNode->setPosition(Vec2(0, 0));
    floorNode->setPosition(OriginX, OriginY);
    floorNode->scrollSpeed = 2;
    this->addChild(floorNode);
}

void menuCloseCallBack(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainScene::update(float delta)
{
    printf("update");
}

