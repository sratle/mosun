#pragma once
#include "main.h"
//��save������Ҫ�浵��
//�ؼ����ݴ洢���У�ע������಻��Խ��Խӷ�ף���Ҫ�����߼����ʵ��ذ�һЩ���ݷ�װ�����е�������
class keyhouse
{
public:
	//��ԴԤ����
	vector<IMAGE> sakuya;//0
	vector<IMAGE> plane_image;//1
	vector<IMAGE> enemy_image;//2
	vector<IMAGE> drop_image;//3
	vector<IMAGE> boom_image;//4
	vector<IMAGE> card_image;//5
	vector<IMAGE> other_image;//6
	//һ��ͼƬ����ʮ�ĴΣ�-30��-20��-10��0��10��20��30��150��160��170��180��190��200��210��
	//1��6��10�ȣ�1��3��20�ȣ�1��2��30��
	vector<IMAGE> shots_image;
	//��������
	int key_any;//condition0
	int key_num;//condition1
	int key_card;//condition2
	vector<int> move{ 360,932 };
	//�����ñ���
	int condition;//���������״̬������0��������ģʽ��1���˵�ģʽ��2��ս��ģʽ
	int timer;//ȫ�ּ�ʱ��
	int get_flag(int pos);//0:���������ˢ���� 1:���ڹؿ�1���ж���2�����ڹؿ�2���ж���3�����ڹؿ�3���ж���4���޾����ж�
	int get_flag_size();
	void set_flag(int pos, int val);
	int stage;//�ؿ�
	//������Դ
	int star_value;//save
	int sun;//save
	int moon;//save
	vector<int> plane_level{ 0,0,0,0 };//save �洢���ֻ���ĵ�ǰ�ȼ�
	vector<int> cards_unlock{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//save 16�ſ��Ľ������
	int plane_unlock;//save �������
	int max_score;//save
	int score;
	//��������,���ǵ�ǰ�ķɻ����ݼ��ص����ʵʱ�仯����
	int plane_id;//��ui.planes_data�м��ض�Ӧid
	int mp;
	int hp;
	int attack;
	int shield;
	int strike;//����

	keyhouse();
	void load();//���浵����
	void save();//�浵
	void reset_save();

private:
	vector<int> desigh_flags;
	void load_shots(LPCTSTR);
	void load_image_asset(LPCTSTR, int);
};

