#pragma once

#include<SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include<set>
#include<ctime>
#include<sstream>

using namespace std;
class Minesweeper {

public:
	Minesweeper(int width, int height);
	void draw(sf::RenderWindow& window);
	void create_bomb();
	int left_mouse_clicked(int x, int y);
	void right_mouse_clicked(int x, int y);
	int display_number(int x, int y);
	void display_all();
	int count_flag(int i, int j);
	int clearing_boundary(int x, int y);
	void display_game_over(sf::RenderWindow& window);
	void bomb_value();
	void create_grid();
	bool game_over();

private:

	sf::Texture zero;
	sf::Texture one;
	sf::Texture two;
	sf::Texture three;
	sf::Texture four;
	sf::Texture five;
	sf::Texture six;
	sf::Texture seven;
	sf::Texture eight;
	sf::Texture facingdown;
	sf::Texture flag;
	sf::Texture bombtexture;

	sf::Texture s;
	
	
	vector<vector<pair<sf::Sprite,bool>>> showgrid;
	vector<vector<pair<sf::Sprite, int>>> hidegrid;

	set<pair<int, int>> bomb_set;
	vector<pair<int, int>> bomb;




	sf::Font font;
	sf::Text t;

	sf::Clock clock;

	time_t time_rand;

	int Height;
	int Width;
	int box_size;
	float scale = 0.005;
	float bomb_scale = 0.023;

	int level = 16;
	int bomb_number = 40;

	bool game_start = false;
	sf::Time wintime;
	sf::Clock winclock;
};





