#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameBlock.h"

using namespace std;
class HelloWorld : public cocos2d::Layer
{
private: 
	Point beginPoint;
    Node *gameLayer;
    int linesCount;
	GameBlock *flyShit;

public:

	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
     
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void addNormalLine(int lineIndex);
    void addFlyShit();
	void addEdges();
	void dropShit(float dt);

	bool onContactBegin(    PhysicsContact& contact);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
