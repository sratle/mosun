#pragma once
#include "keyhouse.h"
//�ӵ���image32*32
class Shot
{
public:
	int flag;//�Ƿ����
	void draw();
	Shot(int,int);//id,rotate
	void set_pos(int, int);//��Ⱦ����x,y
	int get_x();
	int get_y();
	void set_r(int);
	int get_r();
	void set_id(int);
	int get_id();
	~Shot() {};

private:
	int x;//plane�и����������ݣ�ע��˴�����Ⱦ���꣬���ǵ���x+16��y+16
	int y;
	int id;//�ӵ�id
	int rotate;//0~6�����ϣ�7~14������
	void put_bk_image(int, int, IMAGE);
};

