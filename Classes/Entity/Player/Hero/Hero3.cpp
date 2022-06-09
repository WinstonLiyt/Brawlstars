//作者 : 王鹏
//日期 : 2022-6-2

//修改 : 束赫
//日期 : 2022-6-3
//实现 : 人物动画功能函数接口

#include "Hero1.h"
#include "Hero2.h"
#include "Hero3.h"
#include "Hero4.h"
//#include "Entity/Weapon/Weapon.h"
USING_NS_CC;
using namespace CocosDenshion;

/*===============================================================================*/
/*=============================以下是创建与初始化================================*/
/*===============================================================================*/

/****************************
* Name ：create
* Summary ：创建
* return ：hero指针
****************************/
Hero3* Hero3::create(const std::string& filename)
{
	Hero3* player = new (std::nothrow) Hero3();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}
/****************************
* Name ：create
* Summary ：创建
* return ：hero指针
****************************/
Hero3* Hero3::create(const std::string& filename, const Rect& rect)
{
	Hero3* player = new (std::nothrow) Hero3();
	if (player && player->initWithFile(filename, rect))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}
/****************************
* Name ：initPlayer
* Summary ：自定义值初始化
* return ：
****************************/
void Hero3::initPlayer(int maxHealthPoint, int attack, int defence, float skillAttackRate, float attackRate)
{
	//初始化面板
	_panel.init(maxHealthPoint, attack, defence, skillAttackRate, attackRate);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}
/****************************
* Name ：initPlayer
* Summary ：按默认值初始化
* return ：
****************************/
void Hero3::initPlayer()
{
	//初始化面板
	_panel.init(HERO3_INIT_MAXHEALTHPOINT, HERO3_INIT_ATTACK, HERO3_INIT_DEFENCE, HERO3_INIT_SKILLRATE, HERO3_INIT_ATTACKRATE);
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

/*===============================================================================*/
/*=======================以下是UI、武器等的位置保持跟随==========================*/
/*===============================================================================*/

/****************************
* Name ：keepHealthBar
* Summary ：保持血条位置
* return ：
****************************/
void Hero3::keepHealthBar(Slider* healthBar)
{
	/*healthBar->setPosition(HERO3_HEALTHBAR_POSITION);*/
	//_healthBar->setPosition(position);
	float x = this->getPosition().x;
	float y = this->getPosition().y + 30;

	healthBar->setPosition(Vec2::Vec2(x, y));
}
/****************************
* Name ：keepMagicBar
* Summary ：保持蓝条位置
* return ：
****************************/
void Hero3::keepMagicBar(Slider* magicBar)
{
	//magicBar->setPosition(HERO3_MAGICBAR_POSITION);
	float x = this->getPosition().x;
	float y = this->getPosition().y + 25;

	magicBar->setPosition(Vec2::Vec2(x, y));
}
/****************************
* Name ：keepWeapon
* Summary ：保持武器位置
* return ：
****************************/
void Hero3::keepWeapon(Weapon* weapon)
{
	weapon->setPosition(HERO3_WEAPON_POSITION_X, HERO3_WEAPON_POSITION_Y);
}
/****************************
* Name ：keepLevelText
* Summary ：保持等级位置
* return ：
****************************/
void Hero3::keepLevelText(cocos2d::Label* levelText, Slider* bar)
{
	//levelText->setPosition(HERO3_LEVELTEXT_POSITION);
	float x = this->getPosition().x;
	float y = this->getPosition().y + 35;

	levelText->setPosition(Vec2::Vec2(x, y));
}
/****************************
* Name ：runFlipxWithWeapon
* Summary ：带着武器翻转
* return ：
****************************/
void Hero3::runFlipxWithWeapon(bool flipx, Weapon* weapon)
{

	_weaponAnchorPositionX = (flipx ?
		HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_LEFT :
		HERO3_WEAPON_ANCHOR_POSITION_X_WHEN_RIGHT);
	_direct = (flipx ? -1.0f : 1.0f);

	weapon->setAnchorPoint(Vec2(_weaponAnchorPositionX, _weaponAnchorPositionY));
	keepWeapon(weapon);

	this->runAction(FlipX::create(flipx));
	weapon->runAction(FlipX::create(flipx));
}
/****************************
* Name ：setPositionWithAll
* Summary ：整体移动
* return ：
****************************/
void Hero3::setPositionWithAll(cocos2d::Vec2& position, Weapon* weapon, Slider* healthBar, Slider* magicBar, cocos2d::Label* levelText)
{
	this->setPosition(position);
	this->keepWeapon(weapon);
	this->refreshHealthBar(healthBar);
	this->refreshMagicBar(magicBar);
	this->keepLevelText(levelText, magicBar);
}

/*===============================================================================*/
/*==================================以下是升级===================================*/
/*===============================================================================*/

/****************************
* Name ：Hero3::upgrade()
* Summary ：人物升级
* return ：
****************************/
void Hero3::upgrade(cocos2d::Label* levelText, Slider* bar)
{
	if (_level < PLAYER_MAX_GRADE) {
		_level++;
		levelText->setString((std::string("Lv.") + std::to_string(_level)));
		_panel.setMaxHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getMaxHealthPoint());
		_panel.setAttack(HERO3_INIT_ATTACK / 10 + _panel.getAttack());
		_panel.setDefence(HERO3_INIT_DEFENCE / 10 + _panel.getDefence());
		_panel.setAttackRate(0.1f + _panel.getAttackRate());
		_panel.setSkillRate(0.1f + _panel.getSkillRate());
		_panel.setHealthPoint(HERO3_INIT_MAXHEALTHPOINT / 10 + _panel.getHealthPoint());
		_panel.treat(HERO3_INIT_MAXHEALTHPOINT / 2);
		this->keepLevelText(levelText, bar);
	}
}

bool Hero3::initWalkAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Run.plist", "Character/Hero3/hero3_Run.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 6; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Run-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);

	this->setWalkAction(RepeatForever::create(Animate::create(animation)));

	if (_walkAction != nullptr)
		return true;
	else
		return false;


}

bool Hero3::initNormalAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Start.plist", "Character/Hero3/hero3_Start.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 6; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Idle3-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 9.0);
	this->setNormalAction(RepeatForever::create(Animate::create(animation)));

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

bool Hero3::initAttackAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Attack.plist", "Character/Hero3/hero3_Attack.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 0; i < 8; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("Attack2-%d.png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
	animation->setLoops(1);
	auto* animate = Animate::create(animation);
	this->setAttackAction(animate);

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

bool Hero3::initSkillAction()
{
	auto* frameCache = CCSpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Character/Hero3/hero3_Skill.plist", "Character/Hero3/hero3_Skill.png");

	Vector<CCSpriteFrame*> playerFrameArray;
	for (int i = 1; i < 9; i++)
	{
		auto frame = frameCache->getSpriteFrameByName(String::createWithFormat("skill1- (%d).png", i)->getCString());
		playerFrameArray.pushBack(frame);
	}

	auto* animation = Animation::createWithSpriteFrames(playerFrameArray, 1.0 / 12.0);
	auto* animate = Animate::create(animation);
	this->setSkillAction(animate);

	if (_normalAction != nullptr)
		return true;
	else
		return false;
}

bool Hero3::playerCollisionTest1(Player* target, Weapon* weapon)
{
	if (target == nullptr)
		return false;
	_targetX = target->getPosition().x;                           //目标位置X
	_targetY = target->getPosition().y;                           //目标位置Y
	_targetWidth = target->_width;                                //目标的宽度
	_targetHeight = target->_height;                              //目标的高度
	_weaponWidth = weapon->getContentSize().width;                //攻击范围的宽度
	_weaponHeight = weapon->getContentSize().height;              //攻击范围的高度

	_thisX = this->getPosition().x;
	_thisY = this->getPosition().y;

	if (_direct == 1)
	{
		if ((_targetX - _thisX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) <= 0)
		{           //范围判定
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
	}
	if (_direct == -1)
	{
		if ((_thisX - _targetX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) >= 0)
		{           //范围判定
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_2.mp3");
				return true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/knife_attack_1.mp3");
			return false;
		}
	}
}

bool Hero3::playerCollisionTest2(Player* target, Weapon* weapon)
{
	_targetX = target->getPosition().x;                           //目标位置X
	_targetY = target->getPosition().y;                           //目标位置Y
	_targetWidth = target->_width;         //目标的宽度
	_targetHeight = target->_height;        //目标的高度
	_weaponWidth = weapon->getContentSize().width;                //攻击范围的宽度
	_weaponHeight = weapon->getContentSize().height;              //攻击范围的高度

	_thisX = this->getPosition().x;
	_thisY = this->getPosition().y;

	if (_direct == 1)
	{
		if ((_targetX - _thisX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) <= 0)
		{           //范围判定
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	if (_direct == -1)
	{
		if ((_thisX - _targetX) < (_weaponWidth + _targetWidth / 2) && (_thisX - _targetX) >= 0)
		{           //范围判定
			if (fabs(_thisY - _targetY) < (_weaponHeight / 2 + _targetHeight / 2))
			{
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
}

int Hero3::getID()
{
	return ID;
}