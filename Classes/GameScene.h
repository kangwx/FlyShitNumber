#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameBlock.h"
#include "PauseScene.h"
#include "OverScene.h"
#include <sstream>
#include <string>

using namespace std;
class GameScene : public cocos2d::Layer
{
private: 
	Point beginPoint;
    Node *gameLayer;
    int linesCount;
	GameBlock *flyShit;
	Label *score;

public:

	int flyNumber ;
    int scoreNum  ;
    int shitCount ;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
     
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void addNormalLine(int lineIndex);
	void addDropShit(float dt);
    void addFlyShit();
	void addEdges();
	void dropShit(float dt);
	string num2str(double i);

	bool onContactBegin(    PhysicsContact& contact);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__