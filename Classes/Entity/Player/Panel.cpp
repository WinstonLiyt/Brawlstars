//���� : ����
//���� : 2022-5-18
#include "Panel.h"

USING_NS_CC;

/****************************
* Name ��Panel::init
* Summary ����ʼ�����
* return ��
****************************/
void Panel::init(int& maxHealthPoint, int& attack, int& defence, float& skillAttackRate, float& attackRate)
{
	_maxHealthPoint = maxHealthPoint;
	_healthPoint = maxHealthPoint;
	_attack = attack % (PANEL_MAX_ATTACK + 1);
	_defence = defence % (PANEL_MAX_DEFENCE + 1);
	_skillAttackRate = skillAttackRate;
	_attackRate = attackRate;

	_survive = true;
	_canBeSeen = true;
}

/*===============================================================================*/
/*============================����������ֱ�Ӷ�ȡ===============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::getHealthPoint()const
* Summary ����ȡ��ǰѪ��
* return ��Ѫ��
****************************/
int Panel::getHealthPoint()const
{
	return _healthPoint;
}
/****************************
* Name ��Panel::getMaxHealthPoint()const
* Summary ����ȡ���Ѫ��
* return �����Ѫ��
****************************/
int Panel::getMaxHealthPoint()const
{
	return _maxHealthPoint;
}
/****************************
* Name ��Panel::getSkillAttackRate()const
* Summary ����ȡ���ܱ���
* return �����ܱ���
****************************/
float Panel::getSkillAttackRate()const
{
	return _skillAttackRate;
}
/****************************
* Name ��Panel::getAttackRate()const
* Summary ����ȡ�չ�����
* return ���չ�����
****************************/
float Panel::getAttackRate()const
{
	return _attackRate;
}
/****************************
* Name ��Panel::getAttack()const
* Summary ����ȡ������
* return ��������
****************************/
int Panel::getAttack()const
{
	return _attack;
}
/****************************
* Name ��Panel::getDefence()const
* Summary ����ȡ������
* return ��������
****************************/
int Panel::getDefence()const
{
	return _defence;
}
/****************************
* Name ��getIsSurvive()const
* Summary ����ȡ�Ƿ��� 
* return ��true ���, false δ��� 
****************************/
bool Panel::getIsSurvive()const
{
	return _survive;
}
/****************************
* Name ��getCanBeSeen()const
* Summary ����ȡ�Ƿ���� 
* return ��true ����, false ������ 
****************************/
bool Panel::getCanBeSeen()const
{
	return _canBeSeen;
}

/*===============================================================================*/
/*============================����������ֱ������===============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::setHealthPoint
* Summary �����õ�ǰѪ��
* return ��
****************************/
void Panel::setHealthPoint(int& healthPoint)
{
	_healthPoint = healthPoint;
}
/****************************
* Name ��Panel::setAttack
* Summary �����ù�����
* return ��
****************************/
void Panel::setAttack(int& attack)
{
	_attack = attack % (PANEL_MAX_ATTACK + 1);
}
/****************************
* Name ��Panel::setDefence
* Summary �����÷�����
* return ��
****************************/
void Panel::setDefence(int& defence)
{
	_defence = defence % (PANEL_MAX_DEFENCE + 1);
}
/****************************
* Name ��setIsSurvive
* Summary �������Ƿ��� 
* return ��
****************************/
void Panel::setIsSurvive(bool survive)
{
	_survive = survive;
}
/****************************
* Name ��setCanBeSeen
* Summary �������Ƿ�ɼ� 
* return ��
****************************/
void Panel::setCanBeSeen(bool canBeSeen)
{
	_canBeSeen = canBeSeen;
}

/*===============================================================================*/
/*=========================�����Ƿ��𹥻����˺��Ľ���============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::doAttack()
* Summary �������չ��˺�
* return ���չ��˺�
****************************/
int Panel::doAttack()
{
	return int(_attack * _attackRate);
}
/****************************
* Name ��Panel::doSkillAttack()
* Summary �����㼼���˺�
* return �������˺�
****************************/
int Panel::doSkillAttack()
{
	return int(_attack * _skillAttackRate);
}

/*===============================================================================*/
/*=========================�������ܹ����������ƵĽ���============================*/
/*===============================================================================*/

/****************************
* Name ��Panel::hit
* Summary ���ܹ���
* return �����ս�����˺�ֵ
****************************/
int Panel::hit(int& attack)
{
	//����������Ч��ʽΪ�ٷֱȼ���
	int hitPoint = attack * (1.0f - _defence / PANEL_MAX_DEFENCE);
	_healthPoint -= hitPoint;
	if (_healthPoint <= 0) {//�˺�������ɱ
		_healthPoint = 0;
		_survive = false;
	}
	return hitPoint;//�����˺���� Ҳֱ�ӷ�����ɵ��˺�
}
/****************************
* Name ��Panel::treat
* Summary ��������
* return ����������
****************************/
int Panel::treat(int& healthPoint)
{
	_healthPoint += healthPoint;
	_healthPoint %= (_maxHealthPoint + 1);//�������
	return healthPoint;//����������
}