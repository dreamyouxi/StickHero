#include "HelloWorldScene.h"





Scene* logo::createScene()
{
	auto scene = Scene::create();
	auto layer = logo::create();
	scene->addChild(layer);
	return scene;
}


bool logo::init()
{
	Layer::init();


	Sprite*bg = Sprite::create("logo.png");

	bg->setPosition(640 / 2, HEIGHT / 2);
	this->addChild(bg);

	this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=]{

		Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::createScene()));



	}), nullptr));

	
	return true;
}

































Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}


bool HelloWorld::init()
{
	Layer::init();


	char str[100];
	srand(time(0));



	int a = rand() % 4;

	switch (a)
	{
	case 0:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_city.mp3", true); break;
	case 1:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_country.mp3", true); break;
	case 2:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_snow.mp3", true); break;
	case 3:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_sea.mp3", true); break;
	default:
		break;
	}





	sprintf(str, "background%d.png", a);

	Sprite*bg = Sprite::create(str);

	bg->setPosition(640 / 2, HEIGHT / 2);
	this->addChild(bg);


	Sprite *l = Sprite::create("d.png");
	this->addChild(l);
	l->setPosition(640 / 2, 0);

	l->setScaleX(0.3);



	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("yao.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("walk.plist");





	Sprite *hero = Sprite::createWithSpriteFrameName("d0001.png");
	this->addChild(hero);
	hero->setPosition(640 / 2, l->getPositionY() + 280);

	Animation*s = Animation::create();
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0001.png"));
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0002.png"));
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0003.png"));
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0004.png"));
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0005.png"));
	s->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("d0006.png"));





	s->setDelayPerUnit(0.1);
	s->setLoops(-1);

	hero->runAction(Animate::create(s));


	auto menu_play_ = MenuItemImage::create("start_normal.png", "start_select.png", "", this, menu_selector(HelloWorld::call));

	menu_play_->setPosition(640 / 2, HEIGHT / 2);

	auto menu_play = Menu::create(menu_play_, nullptr);
	menu_play->setPosition(0, 0);
	this->addChild(menu_play);

	Sequence* ss = Sequence::create(MoveBy::create(1.5, Vec2(0, 20)), MoveBy::create(1.5, Vec2(0, -20)), nullptr);
	menu_play_->runAction(RepeatForever::create(ss));



	auto	label1 = Label::create("Stick Hero", "Arial", 100);
	this->addChild(label1);
	label1->setPosition(640 / 2, HEIGHT / 2 + 400);

	label1->setColor(Color3B(255,0,0));

	return true;
}

void HelloWorld::call(Ref* p)
{
	SimpleAudioEngine::getInstance()->playEffect("button.mp3");

	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, gameaScene::createScene()));

}








Scene* gameaScene::createScene()
{
	auto scene = Scene::create();
	auto layer = gameaScene::create();
	scene->addChild(layer);
	return scene;
}


bool gameaScene::init()
{
	Layer::init();


	srand(time(0));


	int a = rand() % 4;

	switch (a)
	{
	case 0:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_city.mp3", true); break;
	case 1:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_country.mp3", true); break;
	case 2:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_snow.mp3", true); break;
	case 3:SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_sea.mp3", true); break;
	default:
		break;
	}




	sprintf(str, "background%d.png", a);





	Sprite*bg = Sprite::create(str);

	bg->setPosition(640 / 2, HEIGHT / 2);
	this->addChild(bg);


	text = Sprite::create("text.png");

	text->setPosition(640 / 2, HEIGHT / 2 + 300);
	this->addChild(text);

	score = 0;
	best = 0;

	best = UserDefault::getInstance()->getIntegerForKey("best");



	Sprite*ss = Sprite::create("ss.png");

	this->addChild(ss);
	ss->setPosition(640 / 2, HEIGHT / 2 + 400);

	ss->setOpacity(99);

	label = Label::create("0", "Arial", 50);
	this->addChild(label);
	label->setPosition(640 / 2, HEIGHT / 2 + 400);







	hero = new Hero;

	dark[0] = new Dark(this);
	dark[0]->MoveToLeft();


	dark[1] = new Dark(this, 100);


	dark[1]->sprite->setPositionX(500);


	this->addChild(hero->sprite);
	hero->sprite->setPosition(dark[0]->width - 30, HEIGHT / 2 - 460 + 280);

	hero->runActionStand();




	stick = new Stick(this);

	stick->setPosX(dark[0]->width);



	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch*touch, Event*event)
	{
		hero->runActionStand();
		stick->doTouchBegin();
		return true;
	};


	listener->onTouchEnded = [=](Touch*touch, Event*event)
	{

		listener->setEnabled(false);


		stick->doTouchEnd();

		if (
			((stick->sprite->getPositionX() + stick->height) > (dark[1]->sprite->getPositionX() - dark[1]->width / 2)) &&

			((stick->sprite->getPositionX() + stick->height) < (dark[1]->sprite->getPositionX() + dark[1]->width / 2))

			)
		{
			this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=]()
			{
				SimpleAudioEngine::getInstance()->playEffect("stick_fallen.wav");

				hero->runActionWalk();
				hero->sprite->runAction(MoveTo::create(stick->height*0.005, Vec2(dark[1]->sprite->getPositionX() + dark[1]->width / 2 - 30, hero->sprite->getPositionY())));

			}), DelayTime::create(stick->height*0.005 + 0.1), CallFunc::create([=]()
			{
				//移动完成 过关
				hero->runActionStand();
				doNext();

			


			}), nullptr));

		}
		else
		{
			this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=]()
			{
				hero->runActionWalk();
				SimpleAudioEngine::getInstance()->playEffect("stick_fallen.wav");

				hero->sprite->runAction(MoveTo::create(stick->height*0.005, Vec2(stick->sprite->getPositionX() + stick->height, hero->sprite->getPositionY())));

			}), DelayTime::create(stick->height*0.005 + 0.1), CallFunc::create([=]()
			{
				//移动完成 不过关
				hero->runActionStand();

				SimpleAudioEngine::getInstance()->playEffect("dead.wav");

				hero->sprite->runAction(MoveBy::create(0.3, Vec2(0, -500)));
				stick->sprite->runAction(RotateBy::create(0.3, 90));

			}), DelayTime::create(0.4), CallFunc::create([=]()
			{

				this->runAction(Repeat::create(Sequence::create(MoveBy::create(0.01, Vec2(5, 5)), MoveBy::create(0.01, Vec2(-5, -5)), nullptr), 10));


			}), DelayTime::create(1.0), CallFunc::create([=]
			{
				listener->setEnabled(true);

				showFalse();


			}), nullptr));

		}


	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
}

void gameaScene::call(Ref* p)
{
	exit(0);
}


void   gameaScene::doNext()
{
	int movebyX = dark[1]->sprite->getPositionX();
	movebyX = -movebyX + dark[1]->width / 2;
	dark[1]->sprite->runAction(MoveBy::create(0.5, Vec2(movebyX, 0)));
	dark[0]->sprite->runAction(MoveBy::create(0.5, Vec2(movebyX, 0)));
	hero->sprite->runAction(MoveBy::create(0.5, Vec2(movebyX, 0)));

	stick->sprite->runAction(MoveBy::create(0.5, Vec2(movebyX, 0)));
	this->runAction(Sequence::create(DelayTime::create(0.6), CallFunc::create([=]()
	{
		stick->reset();
		stick->setPosX(dark[1]->width);

		this->removeChild(dark[0]->sprite);

		delete	dark[0];

		dark[0] = dark[1];

		dark[1] = new Dark(this);


		dark[1]->sprite->setPositionX(dark[0]->width + rand() % (640 - dark[0]->width - dark[1]->width) + dark[1]->width);

		incScore();

		listener->setEnabled(true);


	}), nullptr));


}
