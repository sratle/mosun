#pragma once
#include "Card.h"
#include "Drop.h"
#include "Enemy.h"
#include "Tool.h"
#include "main.h"
#include "Plane.h"
#include "keyhouse.h"

//����UI��ƣ�������Ŀ��������꣬ȫ���̲ٿ�
class Ui
{
private:
	int width;//���ڳ���
	int height;
	int current_index;//��ǰҳ��id
	int music_id;//���Ƶ�ǰ���ŵ���Ч
	int bgm_id;//���Ƶ�ǰ���ŵ�bgm
	vector<IMAGE*> pages;//ҳ�汳����ͼƬָ��
	void add_page(IMAGE*);
	void set_current_index(int);
	void draw_control();
	void note(int, int, int, int, int, int, COLORREF, COLORREF, const wstring&);
	void judge();//�ж��ú���
	void level_1();//�ؿ�1�����������Ϊ�����׶�
	void enemys_reset();//���õл�
	void card_control();//����Ч��
	void plane_house();//���⺯��
	vector<int> defeat_target;//Ŀ����ܵ���������Ҫ�����Զ���ͳ�Ƶл���������ɹؿ��ƽ�

public:
	void music_control();//���Ƶ�ǰ����Ч
	void bgm_control();//���Ƶ�ǰ��bgm
	void input();//����
	Ui(int, int);//���볤��
	~Ui() {};
	void init();
	void run();//ִ��ѭ��
	void close();
	void put_bk_image(int, int, IMAGE);

	Plane* plane;//�Լ��ķɻ���ÿ�ν���ս��֮ǰ������������
	vector<Enemy*> enemys;//�л�������BOSS����ͨ�ɻ�
	vector<Tool*> tools;//һЩС�����Ķ����������
	vector<Card*> card_select;//ÿ��ս������ѡ�����ſ�������ѹ������,id��ʶ0~15
	vector<int> card_now;//����ͬʱӵ�еĿ��������ţ����Դ�����е�һ�ţ����ڶ�ʱ֮��ˢ�£���ʶcard_Select�е�pos,��id
	vector<Drop*> drops;//������
};