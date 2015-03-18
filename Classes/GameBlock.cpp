//
//  Block.cpp
//  WhiteBlock
//
//  Created by plter on 14-5-4.
//
//

#include "GameBlock.h"

Vector<GameBlock*> * GameBlock::blocks = new Vector<GameBlock*>();

Vector<GameBlock*> * GameBlock::getBlocks(){
    return GameBlock::blocks;
}

void GameBlock::removeAllBlocks(){
    
    while (getBlocks()->size()) {
        getBlocks()->back()->removeFromParent();
        getBlocks()->popBack();
    }
}
Animate* GameBlock::getFly()
{
	auto cache = SpriteFrameCache::getInstance();
	Animation* an = Animation::create();
	for(int i=1;i<=9;i++){
		char temp[20];
		sprintf(temp,"fly_%d.png",i);
		  
		//an->addSpriteFrameWithFile(temp);
		//auto sp = cache->getSpriteFrameByName(temp);
		auto sp =   cache->getSpriteFrameByName(temp);
		if(sp != NULL){
			 
			an->addSpriteFrame(sp);
		}
	}
	an->setDelayPerUnit(1.0f/8.0f);
	an->setLoops(1);
	 
	return Animate::create(an);
}

GameBlock* GameBlock::createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor,boolean isFly){
    
    auto b = new GameBlock();
    b->initWithArgs(color,size,label,fontSize,textColor,isFly);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
}


bool GameBlock::initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor,boolean isFly){
    
    Sprite::init();
    
    lineIndex = 0;
    
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
	//setAnchorPoint(Point(-size.width/2,-size.height/2));
    //setTextureRect(Rect(0, 0, size.width, size.height));
    //setColor(color);
    
	auto shit = Sprite::create("shit.png");
	this->addChild(shit);
	shit->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);

    auto l = Label::create();
    
    l->setString(label);
	l->setName("num");
    l->setSystemFontSize(fontSize);
    l->setTextColor(textColor);
    addChild(l);
    l->setPosition(size.width/2,size.height/2);
    if(isFly){
		auto tmp_sp = Sprite::createWithSpriteFrameName("fly_1.png");
		tmp_sp->setPosition(Point(this->getContentSize().width/2,this->getContentSize().height/2));
		tmp_sp->setLocalZOrder(-100);
		this->addChild(tmp_sp);
		tmp_sp->runAction(RepeatForever::create(this->getFly()));
	}
    return true;
}


void GameBlock::removeBlock(){
//    auto c = getColor();
//    log("Remove block,color is (%d,%d,%d)",c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}


void GameBlock::setLineIndex(int v){
    this->lineIndex = v;
}


int GameBlock::getLineIndex(){
    return this->lineIndex;
}

void GameBlock::moveDown(){
    
    this->lineIndex--;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
     
    //runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
	runAction(Sequence::create( 
                               CallFunc::create([this](){
        
        if (lineIndex<0) {
			log(">>> removeBlock");
            this->removeBlock();
        }
        
    }), NULL));
    
}
void GameBlock::moveByDirection(char dir){
    
     
    Size visibleSize = Director::getInstance()->getVisibleSize();
     
	if(getNumberOfRunningActions()!=0){
		return;
	}
	float x = visibleSize.width/4;
	float y = this->getContentSize().height/2+5;
	log("moveByDirection:%c",dir);
	if(dir=='l'){
		x=this->getPosition().x-visibleSize.width/4;
		x=x<=this->getContentSize().width/2?x=this->getContentSize().width/2:x;
	}else{
		float temp = visibleSize.width - this->getContentSize().width/2; 
		x=this->getPosition().x+visibleSize.width/4;
		x=x>temp?temp:x;
	}
    runAction(Sequence::create(MoveTo::create(0.1f, Point(x, y))  , NULL));
    
}


