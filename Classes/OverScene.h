#ifndef __OVER_SCENE_GAME_H__
#define __OVER_SCENE_GAME_H__

#include "cocos2d.h" 
USING_NS_CC;

class OverScene : public cocos2d::Layer
{
public:
	static Scene* scene(RenderTexture* sqr,bool isFlip);
	virtual bool init();
	CREATE_FUNC(OverScene);
	void menuExitCallback(Ref* pSender);
	void menuReplayCallback(Ref* pSender);
	void menuNextCallback(Ref* pSender); 
	 
};
#endif
