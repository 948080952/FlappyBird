//
//  DPMarioNode.hpp
//  FlappyBird
//
//  Created by Dai Pei on 2016/9/29.
//
//

#ifndef DPMarioNode_hpp
#define DPMarioNode_hpp

#include "cocos2d.h"

class DPMarioNode : public cocos2d::Sprite
{
public:
    
    cocos2d::Action *flap;
    
    static DPMarioNode* create();
    
    virtual bool init();
    
    void startPlaying();
    
    void fly();
    
private:
    
    
};

#endif /* DPMarioNode_hpp */
