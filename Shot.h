#pragma once
#include "keyhouse.h"
//�ӵ���image32*32
class Shot
{
public:
	int flag;//�Ƿ����,�ж�����
	void draw();
	Shot(int, int, int, int);//id,rotate,x,y
	void set_pos(double, double);//��Ⱦ����x,y
	double get_x();
	double get_y();
	void set_r(int);
	int get_r();
	void set_id(int);
	int get_id();
	void set_dpos(double,double);
	double get_dx();
	double get_dy();
	~Shot() {};

private:
	double x;//plane�и����������ݣ�ע��˴�����Ⱦ���꣬���ǵ���x+16��y+16
	double y;
	double dx;
	double dy;
	int id;//�ӵ�id
	int rotate;//0~6�����ϣ�7~14������
	void put_bk_image(int, int, IMAGE);
};

