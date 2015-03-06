#ifndef __MAIN_SCENE_GAME_H__
#define __MAIN_SCENE_GAME_H__

#include "cocos2d.h" 

class MainScene : public cocos2d::Layer
{
public:
	 
	virtual bool init();
	CREATE_FUNC(MainScene);
	void menuMenuCallback(Ref* pSender);
	void menuReplayCallback(Ref* pSender);
	void menuNextCallback(Ref* pSender); 
	 
};
#endif
