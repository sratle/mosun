#include<bits/stdc++.h>
#include<fstream>
using namespace std;
 
struct Player{
    int gold, maxHP, HP;
    string name;
}player;
void saveGame(){
    ofstream file("game.dat", ios::out|ios::binary);
    file.write((char*)&player, sizeof(player));
    file.close();
}
void readGame(){
	ifstream file("game.dat", ios::in|ios::binary);
	if(!file){
		cout << "error" << endl;
		return ;
	}
	file.read((char*)&player, sizeof(player));
	file.close();
}
 
int main()
{
	player.gold = 0;
	player.HP = 100;
	player.maxHP = 100;
	player.name = "0D00";
	saveGame();
	cout << player.gold << ' ' << player.HP << ' ' << player.maxHP << endl;
	cout << player.name << endl;
	return 0;
}