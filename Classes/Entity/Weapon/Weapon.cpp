//���� : ����
//���� : 2022-5-20
#include "Weapon.h"

USING_NS_CC;

/****************************
* Name ��Weapon::create
* Summary ��������ʼ��
* return ������ָ��
****************************/
Weapon* Weapon::create(const std::string& filename)
{
	Weapon* weapon = new (std::nothrow) Weapon();
	if (weapon && weapon->initWithFile(filename))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}
/****************************
* Name ��Weapon::getWeapon()
* Summary ����ȡ����ָ��
* return ������ָ��
****************************/
Weapon* Weapon::getWeapon()
{
	return this;
}

/****************************
* Name ��Weapon::launchAnAttack()
* Summary �����𹥻�
* return ��
****************************/
void Weapon::launchAnAttack(int attack)
{

}

/****************************
* Name ��Weapon::launchAnSkill()
* Summary �������ܹ���
* return ��
****************************/
void Weapon::launchAnSkill(int attack)
{

}