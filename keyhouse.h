#pragma once
#include "main.h"
#include "Card.h"
class keyhouse
{
public:
	//��ԴԤ����
	vector<IMAGE> sakuya;
	vector<IMAGE> plane_image;
	vector<IMAGE> enemy_image;
	vector<IMAGE> shots_image;//һ��ͼƬ�����ߴΣ�-30��-20��-10��0��10��20��30��
	void load_shots(LPCTSTR);
	//��������
	vector<BYTE> key_any;//condition0
	vector<BYTE> key_num;//condition1
	int key_move;//condition2
	int key_card;//condition2
	//��������
	vector<vector<int>> shot_self;
	vector<vector<int>> shot_enemy;
	vector<vector<int>> plane_enemy;
	vector<int> plane_self;
	//��Ƭ����
	vector<Card> card_all;
	vector<Card> card_select;
	vector<Card> card_now;
	//�����ñ���
	int condition;
	int move_flag;
	int timer;
	int plane_time;
	int shot_time;
	int level;
	//������Դ
	int star_value;//save
	int anu;//save
	int isthar;//save
	//��������
	int plane_id;//��ui.planes_data�м��ض�Ӧid
	int mp;
	int hp;
	int attack;
	int shield;
	int strike;
	vector<int> plane_level{ 0,0,0,0 };//save �洢���ֻ���ĵ�ǰ�ȼ�
	int plane_unlock;//˳����� 1~3

	keyhouse();
	void load();//���浵����
	void save();//�浵
};

