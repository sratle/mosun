#pragma once
#include "main.h"
//��save������Ҫ�浵��
//�ؼ����ݴ洢���У�ע������಻��Խ��Խӷ�ף���Ҫ�����߼����ʵ��ذ�һЩ���ݷ�װ�����е�������
class keyhouse
{
public:
	//��ԴԤ����
	vector<IMAGE> sakuya;
	vector<IMAGE> plane_image;
	vector<IMAGE> enemy_image;
	//һ��ͼƬ����ʮ�ĴΣ�-30��-20��-10��0��10��20��30��150��160��170��180��190��200��210��
	//1��6��10�ȣ�1��3��20�ȣ�1��2��30��
	vector<IMAGE> shots_image;
	//��������
	vector<BYTE> key_any;//condition0
	vector<BYTE> key_num;//condition1
	int key_move;//condition2
	int key_card;//condition2
	//�����ñ���
	int condition;//���������״̬������0��������ģʽ��1���˵�ģʽ��2��ս��ģʽ
	int timer;//ȫ�ּ�ʱ��
	int get_flag(int pos);//0:CapsLock�Ƿ��� 1:�ؿ�1�ж�ʱ�� 
	int get_flag_size();
	void set_flag(int pos, int val);
	int level;//�ؿ�
	//������Դ
	int star_value;//save
	int anu;//save
	int isthar;//save
	//��������,���ǵ�ǰ�ķɻ����ݼ��ص����ʵʱ�仯����
	int plane_id;//��ui.planes_data�м��ض�Ӧid
	int mp;
	int hp;
	int attack;
	int shield;
	int strike;//����
	vector<int> plane_level{ 0,0,0,0 };//save �洢���ֻ���ĵ�ǰ�ȼ�
	int plane_unlock;//save ˳��������� 1~3

	keyhouse();
	void load();//���浵����
	void save();//�浵

private:
	vector<int> desigh_flags;
	void load_shots(LPCTSTR);
};

