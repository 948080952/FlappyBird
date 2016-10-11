//
//  DPScrollingNode.cpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/27.
//
//

#include "DPScrollingNode.hpp"
#include "cocos2d.h"
#include "Macros.h"

USING_NS_CC;


DPScrollingNode* DPScrollingNode::create(const std::string& imageName, const cocos2d::Size& nodeSize)
{
    DPScrollingNode* node = DPScrollingNode::create();
    node->setContentSize(nodeSize);
    node->scrollSpeed = 1;
    
    Sprite* tmp = Sprite::create(imageName);
    float width = tmp->getContentSize().width;
    float height = tmp->getContentSize().height;
    
    float total = 0;
    float scaleRate = nodeSize.height / height;
    width = width * scaleRate;
    height = nodeSize.height;
    
    while (total < (nodeSize.width + width)) {
        Sprite* child = Sprite::create(imageName);
        child->setScale(scaleRate, scaleRate);
        child->setAnchorPoint(Vec2(0, 0));
        child->setPosition(total, 0);
        node->addChild(child);
        total += width;
    }
    
    return node;
}

void DPScrollingNode::updateNode()
{
    Vector<Sprite *>& childVector = (Vector<Sprite *>&)this->getChildren();
    for (int i = 0; i < childVector.size(); i++) {
        Sprite* child = childVector.at(i);
        child->setPosition(POSITIONX(child) - scrollSpeed, POSITIONY(child));
        if (POSITIONX(child) <= -(WIDTH(child))) {
            child->setPosition(WIDTH(child) * childVector.size() + POSITIONX(child), POSITIONY(child));
        }
    }
}



