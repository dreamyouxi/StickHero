#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

#define  HEIGHT Director::getInstance()->getVisibleSize().height


class logo : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(logo);
};






class HelloWorld : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	void call(Ref* pSender);
	CREATE_FUNC(HelloWorld);
};




class Hero
{
public:
	Sprite*sprite;
	Hero()
	{
		sprite = Sprite::createWithSpriteFrameName("d0001.png");

	}

	void runActionWalk()
	{
		sprite->stopAllActions();

		Animation*s = Animation::create();
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0001.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0002.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0003.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0004.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0005.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0006.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0007.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0008.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("z0009.png"));

		s->setDelayPerUnit(0.05);
		s->setLoops(-1);
		sprite->runAction(Animate::create(s));

	}
	void runActionStand()
	{
		sprite->stopAllActions();

		Animation*s = Animation::create();
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0001.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0002.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0003.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0004.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0005.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0006.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0007.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0008.png"));
		s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0009.png"));

		s->setDelayPerUnit(0.1);
		s->setLoops(-1);
		sprite->runAction(Animate::create(s));


	}


};


class Dark;


class Stick;


class gameaScene : public Layer
{
public:
	int score;
	int best;


	void incScore()
	{

		sprintf(str, "%d", ++score);
		label->setString(str);

		if (score >= 1)
		{
			text->setVisible(false);
		}

		if (score >= best)
		{
			UserDefault::getInstance()->setIntegerForKey("best", best);
			best = score;
			SimpleAudioEngine::getInstance()->playEffect("perfect.mp3");

		}
		else

		SimpleAudioEngine::getInstance()->playEffect("score.mp3");


	}



	void showFalse()
	{

		SimpleAudioEngine::getInstance()->playEffect("fall.wav");
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);


		auto menu1111 = MenuItemImage::create("d.png", "d.png", "", [=](Ref*){});
		menu1111->setPosition(640 / 2, HEIGHT / 2);
		menu1111->setOpacity(99);
		menu1111->setScale(55);



		auto menu11111111 = MenuItemImage::create("1.png", "1.png", "", [=](Ref*)
		{
			this->removeAllChildrenWithCleanup(true);
			delete dark[0];
			delete dark[1];
			delete hero;
			delete stick;
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");

			Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, gameaScene::createScene()));

		});
		menu11111111->setPosition(640 / 2 + 200, HEIGHT / 2 - 300);


		auto menu1111111111111 = MenuItemImage::create("2.png", "2.png", "", [=](Ref*)
		{
			this->removeAllChildrenWithCleanup(true);
			delete dark[0];
			delete dark[1];
			delete hero;
			delete stick;
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");

			Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::createScene()));

		});
		menu1111111111111->setPosition(640 / 2 - 200, HEIGHT / 2 - 300);


		auto menu = Menu::create(menu1111, menu11111111, menu1111111111111, nullptr);
		menu->setPosition(0, 0);
		this->addChild(menu);


		menu11111111->setScale(1.5);
		menu1111111111111->setScale(1.5);


		Sequence* ss = Sequence::create(MoveBy::create(1.5, Vec2(0, 10)), MoveBy::create(1.5, Vec2(0, -10)), nullptr);
		menu11111111->runAction(RepeatForever::create(ss));


		Sequence* ss1 = Sequence::create(MoveBy::create(1.5, Vec2(0, -10)), MoveBy::create(1.5, Vec2(0, 10)), nullptr);
		menu1111111111111->runAction(RepeatForever::create(ss1));





		auto	label1 = Label::create("Game Over!", "Arial", 100);
		this->addChild(label1);
		label1->setPosition(640 / 2, HEIGHT / 2 + 400);



		Sprite*q = Sprite::create("q.png");

		this->addChild(q);
		q->setPosition(640 / 2, HEIGHT / 2 + 100);




		auto label2 = Label::create("Score", "Arial", 50);
		this->addChild(label2);
		label2->setPosition(640 / 2 - 100, HEIGHT / 2 + 170);
		label2->setColor(Color3B(0, 0, 0));


		sprintf(str, "%d", score);
		auto label4 = Label::create(str, "Arial", 50);
		this->addChild(label4);
		label4->setPosition(640 / 2 + 100, HEIGHT / 2 + 170);
		label4->setColor(Color3B(0, 0, 0));




		auto label3 = Label::create("Best", "Arial", 50);
		this->addChild(label3);
		label3->setPosition(640 / 2 - 100, HEIGHT / 2 + 30);
		label3->setColor(Color3B(0, 0, 0));


		sprintf(str, "%d", best);
		auto label41 = Label::create(str, "Arial", 50);
		this->addChild(label41);
		label41->setPosition(640 / 2 + 100, HEIGHT / 2 + 30);
		label41->setColor(Color3B(0, 0, 0));



	}


	EventListenerTouchOneByOne*listener;

	Label*label;

	Stick*stick;
	Dark*dark[2];
	Hero*hero;
	void doNext();
	Sprite*text;
	char str[100];

	static Scene* createScene();

	virtual bool init();
	void call(Ref* pSender);
	CREATE_FUNC(gameaScene);
};


class Dark
{
public:
	Sprite*sprite;
	int width;

	Dark(gameaScene*p, int w = 0)
	{

		srand(time(0));
		if (w){ width = w; }
		else
			width = 48 + rand() % 52;

		sprite = Sprite::create("d.png", Rect(0, 0, width, 500));

		p->addChild(sprite);
		sprite->setPosition(640 + width / 2, HEIGHT / 2 - 460);


	}

	void runActionMoveToLeft()
	{
		sprite->runAction(MoveTo::create(1.0, Vec2(width / 2, HEIGHT / 2 - 460)));

	}

	void MoveToLeft()
	{
		sprite->setPosition(width / 2, HEIGHT / 2 - 460);

	}


};

class Stick
{
public:
	Sprite*sprite;


	int height;
	Stick(gameaScene*p)
	{
		height = 0;
		sprite = Sprite::create("stick.png");
		p->addChild(sprite);

		sprite->setAnchorPoint(Vec2(0.5, 0));

		sprite->setPositionY(HEIGHT / 2 - 210);

		sprite->setPositionX(500);


		sprite->setTextureRect(Rect(0, 0, 5, 0));


	}

	void doTouchBegin()
	{
		sprite->stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("stick_grow_loop.mp3");


		sprite->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.002), CallFunc::create([=]()
		{
			height += 5;



			if (height >= 850)return;
			sprite->setTextureRect(Rect(0, 0, 5, height));
			log("%d", height);

		}), nullptr)));
	}

	void doTouchEnd()
	{
		sprite->stopAllActions();
		sprite->runAction(RotateBy::create(0.5, 90));

	}



	void reset()
	{
		height = 0;
		sprite->setTextureRect(Rect(0, 0, 5, height));
		sprite->setRotation(0);
		sprite->setPositionY(HEIGHT / 2 - 210);

		//sprite->setPositionX(500);

	}

	void setPosX(int x)
	{
		x -= 1;

		sprite->setPositionX(x);

	}

};


#endif // __HELLOWORLD_SCENE_H__
