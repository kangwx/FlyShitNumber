#ifndef __PAUSE_SCENE_GAME_H__
#define __PAUSE_SCENE_GAME_H__

#include "cocos2d.h" 
USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
	static Scene* scene(RenderTexture* sqr,bool isFlip);
	virtual bool init();
	CREATE_FUNC(PauseScene);
	void menuMenuCallback(Ref* pSender);
	void menuReplayCallback(Ref* pSender);
	void menuNextCallback(Ref* pSender); 
	 
};
#endif
