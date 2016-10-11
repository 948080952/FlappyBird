//
//  DPScrollingNode.hpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/27.
//
//

#ifndef DPScrollingNode_hpp
#define DPScrollingNode_hpp

#include "cocos2d.h"

class DPScrollingNode : public cocos2d::Sprite
{
public:
    
    float scrollSpeed;
    
    static DPScrollingNode* create(const std::string& imageName, const cocos2d::Size& nodeSize);
    
    CREATE_FUNC(DPScrollingNode);
    
    void updateNode();
    
};


#endif /* DPScrollingNode_hpp */
