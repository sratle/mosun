#include "Ui.h"
extern keyhouse keys;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0), plane(nullptr)
{
}

void Ui::init()
{
	initgraph(width, height);

	//����ҳ��
	IMAGE* page_1 = new IMAGE(width, height);
	loadimage(page_1, L"assets/main_test.png");//��ʼ����
	add_page(page_1);

	IMAGE* page_2 = new IMAGE(width, height);
	loadimage(page_2, L"assets/mune.jpg");//�˵�����
	add_page(page_2);

	IMAGE* page_3 = new IMAGE(width, height);
	loadimage(page_3, L"assets/attack01.png");//ս����һ����
	add_page(page_3);
}

void Ui::run()
{
	ExMessage msg;
	BeginBatchDraw();
	draw_control();
	FlushBatchDraw();
	//��¼ÿһ֡ʹ�õ�ʱ��
	double start = 0;
	double end = 0;

	while (true)
	{
		start = clock();
		if (peekmessage(&msg))//�������Ϣ
		{//��������ģ��
			if (msg.message == WM_KEYDOWN && keys.condition == 0)
			{
				keys.key_any.push_back(msg.vkcode);
			}
			else if (msg.message == WM_KEYDOWN && keys.condition == 1)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num.push_back(msg.vkcode);
				}
			}
			else if (msg.message == WM_KEYDOWN && keys.condition == 2)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num.push_back(msg.vkcode);
				}
				else if (msg.vkcode == 65 || msg.vkcode == 68 || msg.vkcode == 83 || msg.vkcode == 87)//ADSW
				{
					keys.key_move = msg.vkcode;
				}
				else if (msg.vkcode == 20 || msg.vkcode == 74 || msg.vkcode == 75)//CapsLock,J,K
				{
					keys.key_card = msg.vkcode;
				}
			}
		}
		while (peekmessage(&msg)) {}//msg���жѻ���Ӱ�찴���ж�

		draw_control();//������Ⱦ���ƺ���
		FlushBatchDraw();
		end = clock();
		Sleep(DWORD(1000.0 / FPS + start - end));//����֡��
		keys.timer++;
		if (keys.timer > FPS * 30000)
		{
			keys.timer = 0;
		}
	}
	EndBatchDraw();
}

void Ui::close()
{
	closegraph();
	exit(0);
}

//������ҳ����Ⱦ����������������
void Ui::draw_control()
{
	if (current_index < 0 || current_index > pages.size())//ȷ������
		return;
	//��Ⱦ����ͼ
	putimage(0, 0, pages[current_index]);
	if (current_index == 0)
	{
		//���������Ľ���Ч����������������
		double cps = keys.timer / 10.0;
		COLORREF color = RGB(200 * abs(sin(cps)), 200 * abs(sin(cps)), 80);
		settextcolor(color);
		setbkmode(TRANSPARENT);
		settextstyle(140, 0, _T("�����п�"));
		outtextxy(100, 100, L"Moon Sun");
		settextstyle(60, 0, _T("����"));
		outtextxy(200, 800, L"�����������");

		note(100, 10, 100, 50, 30, 0, L"0:�˳�");
		//ȷ�ϲ��񰴼�0��ִ���˳�
		if (keys.condition == 0 && (!keys.key_any.empty()) && keys.key_any.back() == 48)
		{
			close();
		}//������������ⰴ���ͽ���
		else if (keys.condition == 0 && (!keys.key_any.empty()))
		{
			keys.key_any.clear();
			set_current_index(1);
			keys.condition = 1;//�ð��������ģʽת����1ģʽ���˵�ģʽ
		}
	}
	else if (current_index == 1)
	{
		note(10, 10, 100, 50, 30, 1, L"0:�˳�");
		note(10, 200, 300, 70, 50, 1, L"1:̤���ó�");
		//�˵������·���sakuya
		put_bk_image(350 + int(300 * sin(keys.timer / 30.0)), 800, keys.sakuya[keys.timer / 10 % 3]);
		//����0�����ؿ�ʼ����
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
		{
			keys.key_num.clear();
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			set_current_index(0);
			keys.condition = 0;
		}
		//����1������ս������
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 49)
		{
			keys.key_num.clear();
			set_current_index(2);
			keys.condition = 2;
			//��ʼ����ս������ս���ĳ�ʼ��
			switch (keys.plane_id)
			{
			case 0:
				plane = new ur;
				break;
			case 1:
				plane = new nanna;
				break;
			case 2:
				plane = new ea;
				break;
			case 3:
				plane = new enlil;
				break;
			}
			plane->upgrade();//�������ݵ�keys��
			plane->set_stage(1);
			//init end
		}
		//����2�������޾�
		//����3���������
		//����4�������ƿ�
		//����5����������
	}
	else if (current_index == 2)
	{
		note(10, 10, 100, 50, 30, 1, L"0:�˳�");
		//���ز˵�
		if (keys.condition == 2 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
		{
			keys.key_num.clear();
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			set_current_index(1);
			keys.condition = 1;
			//����flags�����ڹؿ���flags
			for (int i = 0; i < keys.get_flag_size(); i++)
				keys.set_flag(i, 0);
			delete plane;
			plane = nullptr;
			//����defeatĿ������
			defeat_target.clear();
			//�ڴ����
			if (enemys.empty())
				return;
			for (auto enemy : enemys)
				delete enemy;
			enemys.clear();
			return;
		}
		//����
		if (keys.hp <= 0) {
			note(180, 300, 360, 120, 80, 1, L"YOU DIED");
			return;
		}
		//������ص���Ⱦ,�󲿷���Ⱦ�߼���װ��plane��
		plane->draw();
		switch (keys.level)
		{
		case 0:
			level_1();
			break;
		}
		for (auto ene : enemys) {
			ene->draw();
		}
		judge();//�ж�
	}
}

void Ui::level_1()
{
	//ʹ��flag��defeatĿ����ж��գ���д�ؿ���һ���׶ε�ʱ����Ҫ��target_numֵ�ֶ���һ
	static int target_num = 4;

	static int target = 0;
	if (defeat_target.empty())
		for (int i = 0; i <= target_num; i++)
			defeat_target.push_back(0);
	int i = 0;
	//ģ��start
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		//���enemy,���޸�
		enemys.push_back(new simple_enemy(240, 150, 1));//�ֱ���x��y�����group������group���ǹؿ�id
		enemys.push_back(new simple_enemy(480, 150, 1));
		//�������仰���ø�
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	//end
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		//���enemy
		enemys.push_back(new simple_enemy(220, 150, 1));
		enemys.push_back(new lock_simple(360, 250, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_enemy(500, 150, 1));
		//�������仰���ø�
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new lock_simple(160, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(360, 150, 1));
		enemys.push_back(new lock_simple(560, 300, 1, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new simple_three(260, 150, 1));
		enemys.push_back(new lock_simple(120, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new lock_simple(600, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(460, 150, 1));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
}

void Ui::judge()//�ж�����
{
	//�ж������ӵ��Եл����˺�
	for (auto shot : plane->shots)
	{
		for (auto enemy : enemys)
		{
			if (enemy->state)
				continue;//�л��Ѿ����˾Ͳ������ж�
			//������
			if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - enemy->position[2]), 2) + pow(abs(shot->get_y() + 16 - enemy->position[3]), 2)) < 24)
			{
				enemy->hp -= keys.attack * (1 + (rand() < keys.strike));
				shot->flag = 1;
			}
		}
	}
	//�ж��л��ӵ��Լ������˺�
	for (auto enemy : enemys)
	{
		if (enemy->state)
			continue;//�л��Ѿ����˾Ͳ������ж�
		for (auto shot : enemy->shots)
		{
			if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - plane->position[2]), 2) + pow(abs(shot->get_y() + 16 - plane->position[3]), 2)) < 8)
			{
				keys.hp -= enemy->attack;
				shot->flag = 1;
			}
		}
	}
}

//����enemys��,�ڴ����
void Ui::enemys_reset()
{
	if (enemys.empty())
		return;
	for (auto enemy : enemys)
		delete enemy;
	enemys.clear();
}

//��ָ��λ����Ⱦһ����ʾ�򣬲���Ϊ��x���꣬y���꣬��ȣ��߶ȣ������С���Ƿ񺬱���������
void Ui::note(int x, int y, int width, int height, int font, int bg, const wstring& text)
{
	if (bg == 1)
	{
		fillrectangle(x, y, x + width, y + height);
	}
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(font, 0, _T("����"));
	int textX = x + (width - textwidth(text.c_str())) / 2;
	int textY = y + (height - textheight(_T("����"))) / 2;
	outtextxy(textX, textY, text.c_str());
}

//�趨��ǰҳ���id
void Ui::set_current_index(int index)
{
	if (index >= 0 && index < pages.size())
	{
		current_index = index;
	}
}

//����һ��ҳ��
void Ui::add_page(IMAGE* page)
{
	pages.push_back(page);
}

//�ú���������ָ��λ����ȾͼƬ��ע����Ⱦ������ͼƬ���Ͻ�
void Ui::put_bk_image(int x, int y, IMAGE img)
{
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03)
		{
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE))
		{
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
}

