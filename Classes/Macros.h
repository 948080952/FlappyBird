//
//  Macros.h
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/29.
//
//

#ifndef Macros_h
#define Macros_h

#define VisibleSize     Director::getInstance()->getVisibleSize()
#define VisibleWidth    Director::getInstance()->getVisibleSize().width
#define VisibleHeight   Director::getInstance()->getVisibleSize().height
#define Origin          Director::getInstance()->getVisibleOrigin()
#define OriginX         Director::getInstance()->getVisibleOrigin().x
#define OriginY         Director::getInstance()->getVisibleOrigin().y

#define WIDTH(node)     node->getContentSize().width * SCALE(node)
#define HEIGHT(node)    node->getContentSize().height * SCALE(node)
#define SIZE(node)      node->getContentSize()
#define POSITIONX(node) node->getPositionX()
#define POSITIONY(node) node->getPositionY()
#define SCALE(node)     node->getScale()


#endif /* Macros_h */
