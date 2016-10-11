//
//  GameScene.cpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/28.
//
//

#include "GameScene.hpp"
#include "Macros.h"
#include "Constants.h"
#include "base/ccRandom.h"

#define FLOOR_SCROLLING_SPEED 3

#define FIRST_OBSTACLE_PADDING      80
#define OBSTACLES_INTERVAL_SPACE    120
#define VERTICAL_GAP_SIZE           100
#define OBSTACLE_MIN_HEIGHT         60

USING_NS_CC;

bool GameScene::init()
{
    if (!Scene::initWithPhysics()) {
        return false;
    }
    
    this->layer = Layer::create();
    this->addChild(this->layer);
    this->getPhysicsWorld()->setGravity(Vec2(0.0f, -980.0f));
    
    this->wasted = false;
    this->startGame();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        
        if (wasted) {
            this->startGame();
        }else {
            if (!started) {
                this->mario->startPlaying();
                this->started = true;
            }
            this->mario->fly();
        }
        return true;
    };
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void GameScene::update(float delta)
{
    if (wasted) {
        return ;
    }
    
    if (started) {
        this->backgroundNode->updateNode();
        this->floorNode->updateNode();
        this->updateObstacles();
        this->updateScore();
    }
}


bool GameScene::onContactBegin(PhysicsContact& contact)
{
    this->wasted = true;
    this->started = false;
    return true;
}


#pragma mark - Privite Method

void GameScene::startGame()
{
    this->wasted = false;
    
    this->layer->removeAllChildren();
    
    this->createBackground();
    this->createObstacles();
    this->createFloor();
    this->createSprite();
    this->createNumLabel();
}

void GameScene::createNumLabel()
{
    auto numLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
    numLabel->setAnchorPoint(Vec2(0, 0));
    numLabel->setPosition(OriginX, OriginY + VisibleHeight - HEIGHT(numLabel));
    this->layer->addChild(numLabel);
    this->scoreLabel = numLabel;
    score = 0;
}

void GameScene::createSprite()
{
    auto mario = DPMarioNode::create();
    mario->setAnchorPoint(Vec2(0.5, 0.5));
    mario->setPosition(OriginX + VisibleWidth / 3, OriginY + VisibleHeight / 2);
    this->layer->addChild(mario);
    this->mario = mario;
}

void GameScene::createBackground()
{
    auto backgroundNode = DPScrollingNode::create("res/back.png", Size(VisibleWidth, VisibleHeight - 80));
    backgroundNode->setAnchorPoint(Vec2(0, 0));
    backgroundNode->setPosition(OriginX, OriginY + 80);
    auto body = PhysicsBody::createEdgeBox(Size(VisibleWidth, VisibleHeight - 80));
    body->setDynamic(false);
    body->setCategoryBitmask(backBitMask);
    body->setContactTestBitmask(birdBitMask);
    body->setCollisionBitmask(birdBitMask);
    backgroundNode->setPhysicsBody(body);
    backgroundNode->scrollSpeed = 1;
    this->layer->addChild(backgroundNode);
    this->backgroundNode = backgroundNode;
}

void GameScene::createFloor()
{
    auto floorNode = DPScrollingNode::create("res/floor.png", Size(VisibleWidth, 80));
    floorNode->setAnchorPoint(Vec2(0, 0));
    floorNode->setPosition(OriginX, OriginY);
    floorNode->scrollSpeed = 3;
    auto body = PhysicsBody::createEdgeBox(Size(VisibleWidth, 80));
    body->setDynamic(false);
    body->setCategoryBitmask(floorBitMask);
    body->setContactTestBitmask(birdBitMask);
    body->setCollisionBitmask(birdBitMask);
    floorNode->addComponent(body);
    this->layer->addChild(floorNode);
    this->floorNode = floorNode;
}

void GameScene::createObstacles()
{
    obstacleNum = ceil(VisibleWidth / OBSTACLES_INTERVAL_SPACE);
    
    //caculate the scale
    Sprite *pipe = Sprite::create("res/pipe_top.png");
    float obstacleScale = (float)VisibleHeight / (float)HEIGHT(pipe);
    pipe = Sprite::create("res/pipe_bottom.png");
    obstacleScale = (obstacleScale > (HEIGHT(pipe) / VisibleHeight)) ? obstacleScale : (HEIGHT(pipe) / VisibleHeight);
    pipe = nullptr;
    obstacleScale = (obstacleScale > 1) ? obstacleScale : 1;
    
    
    float lastBlockPosX = 0;
    this->topPipes.reserve(obstacleNum);
    this->bottomPipes.reserve(obstacleNum);
    
    for (int i = 0; i < obstacleNum; i++) {
        
        Sprite *topPipe = Sprite::create("res/pipe_top.png");
        topPipe->setScale(obstacleScale, obstacleScale);
        topPipe->setAnchorPoint(Vec2(0, 0));
        auto topBody = PhysicsBody::createBox(SIZE(topPipe));
        topBody->setCategoryBitmask(blockBitMask);
        topBody->setContactTestBitmask(birdBitMask);
        topBody->setCollisionBitmask(birdBitMask);
        topBody->setDynamic(false);
        topPipe->setPhysicsBody(topBody);
        this->layer->addChild(topPipe);
        topPipes.insert(i, topPipe);
        
        Sprite *bottomPipe = Sprite::create("res/pipe_bottom.png");
        bottomPipe->setScale(obstacleScale, obstacleScale);
        bottomPipe->setAnchorPoint(Vec2(0, 0));
        auto bottomBody = PhysicsBody::createBox(SIZE(bottomPipe));
        bottomBody->setCategoryBitmask(blockBitMask);
        bottomBody->setContactTestBitmask(birdBitMask);
        bottomBody->setCollisionBitmask(birdBitMask);
        bottomBody->setDynamic(false);
        bottomPipe->setPhysicsBody(bottomBody);
        this->layer->addChild(bottomPipe);
        bottomPipes.insert(i, bottomPipe);
        
        if (i == 0)
        {
            this->placePipe(bottomPipe, topPipe, VisibleWidth + FIRST_OBSTACLE_PADDING);
        }
        else
        {
            this->placePipe(bottomPipe, topPipe, lastBlockPosX + WIDTH(bottomPipe) + OBSTACLES_INTERVAL_SPACE);
        }
        lastBlockPosX = POSITIONX(topPipe);
    }
}

void GameScene::updateScore()
{
    for (int i = 0; i < obstacleNum; i++) {
        Sprite *topPipe = this->topPipes.at(i);
        if (POSITIONX(topPipe) + WIDTH(topPipe) > POSITIONX(mario) &&
            POSITIONX(topPipe) + WIDTH(topPipe) < POSITIONX(mario) + FLOOR_SCROLLING_SPEED) {
            score++;
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "%d", score);
            std::string scoreStr = buffer;
            this->scoreLabel->setString(scoreStr);
        }
    }
}

void GameScene::updateObstacles()
{
    for (int i = 0; i < obstacleNum; i++) {
        Sprite *topPipe = topPipes.at(i);
        Sprite *bottomPipe = bottomPipes.at(i);
        
        if (POSITIONX(topPipe) <  OriginX-WIDTH(topPipe)) {
            Sprite *rightMostPipe = topPipes.at((i + obstacleNum - 1) % obstacleNum);
            this->placePipe(bottomPipe, topPipe, POSITIONX(rightMostPipe) + WIDTH(topPipe) + OBSTACLES_INTERVAL_SPACE);
        }
        
        topPipe->setPosition(POSITIONX(topPipe) - FLOOR_SCROLLING_SPEED, POSITIONY(topPipe));
        bottomPipe->setPosition(POSITIONX(bottomPipe) - FLOOR_SCROLLING_SPEED, POSITIONY(bottomPipe));
    }
}

void GameScene::placePipe(cocos2d::Sprite *bottomPipe, cocos2d::Sprite *topPipe, float positionX)
{
    
    float availableHeight = HEIGHT(this->backgroundNode);
    float maxVariance = availableHeight - (2 * OBSTACLE_MIN_HEIGHT) - VERTICAL_GAP_SIZE;
    float variance = random(0.f, maxVariance);
    
    float bottomPipeOriginY = POSITIONY(backgroundNode) - HEIGHT(bottomPipe) + OBSTACLE_MIN_HEIGHT;
    float bottomPipePosY = bottomPipeOriginY + variance;
    
    bottomPipe->setPosition(positionX, bottomPipePosY);
    
    topPipe->setPosition(positionX, bottomPipePosY + HEIGHT(bottomPipe) + VERTICAL_GAP_SIZE);
    
}

