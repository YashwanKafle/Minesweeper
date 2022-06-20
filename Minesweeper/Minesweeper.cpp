#include "Minesweeper.h"


Minesweeper::Minesweeper(int width, int height) {
	
	srand(time(&time_rand));
	Height = height;
	Width = width;

	box_size = width / level;
	


	showgrid.resize(level +2);
	hidegrid.resize(level +2);
	

	font.loadFromFile("Fonts/times.ttf");

	t.setFillColor(sf::Color::Black);


	t.setFont(font);
	
	t.setCharacterSize(25);


	 zero.loadFromFile("images/0.png");
	 one.loadFromFile("images/1.png");
	 two.loadFromFile("images/2.png");
	 three.loadFromFile("images/3.png");
	 four.loadFromFile("images/4.png");
	 five.loadFromFile("images/5.png");
	 six.loadFromFile("images/6.png");
	 seven.loadFromFile("images/7.png");
	 eight.loadFromFile("images/8.png");
	 facingdown.loadFromFile("images/facingDown.png");
	 flag.loadFromFile("images/flagged.png");
	 bombtexture.loadFromFile("images/bomb.png");

	create_grid();
	create_bomb();
}

void Minesweeper::create_grid() {
	
	for (int i = 0; i < level+2; i++) {
		for (int j = 0; j < level +2; j++) {
			sf::Sprite s;

			s.setTexture(facingdown);
			s.setPosition((i - 1) * box_size, (j - 1) * box_size);
			s.setScale(box_size*scale, box_size*scale);
			

			hidegrid[i].push_back(make_pair(s, 0));
			showgrid[i].push_back(make_pair(s, false));
			
		}
	}


}

void Minesweeper::create_bomb() {
	srand(time(NULL));

	while (bomb.size() < bomb_number) {
		int a = 1 + rand() % level;
		int b = 1 + rand() % level;

		bomb_set.insert(make_pair(a, b));
		if (bomb_set.size() > bomb.size()) {
			bomb.push_back(make_pair(a, b));
		}
	}
	bomb_value();
}

void Minesweeper::bomb_value() {
	for (int i = 0; i < bomb.size(); i++) {


		sf::Sprite s;

		s.setTexture(bombtexture);

		s.setPosition(hidegrid[bomb[i].first][bomb[i].second].first.getPosition());
		s.setScale(box_size * bomb_scale, box_size * bomb_scale);

		hidegrid[bomb[i].first][bomb[i].second] = make_pair(s,-1);
		
	}


	for (int i = 1; i <= level; i++) {
		for (int j = 1; j <= level; j++) {

			int n = 0;

			if (hidegrid[i][j].second == -1 )  continue;
			if (hidegrid[i-1][j-1].second == -1)  n++;
			if (hidegrid[i-1][j].second == -1)  n++;
			if (hidegrid[i-1][j+1].second == -1)  n++;
			if (hidegrid[i][j-1].second == -1)  n++;
			if (hidegrid[i][j+1].second == -1)  n++;
			if (hidegrid[i+1][j-1].second == -1)  n++;
			if (hidegrid[i+1][j].second == -1)  n++;
			if (hidegrid[i+1][j+1].second == -1)  n++;
			
			hidegrid[i][j].second = n;


			sf::Sprite s;
			s.setScale(box_size * scale, box_size * scale);
			s.setPosition(hidegrid[i][j].first.getPosition());

			if (hidegrid[i][j].second == 0) s.setTexture(zero);
			if (hidegrid[i][j].second == 1) s.setTexture(one);
			if (hidegrid[i][j].second == 2) s.setTexture(two);
			if (hidegrid[i][j].second == 3) s.setTexture(three);
			if (hidegrid[i][j].second == 4) s.setTexture(four);
			if (hidegrid[i][j].second == 5) s.setTexture(five);
			if (hidegrid[i][j].second == 6) s.setTexture(six);
			if (hidegrid[i][j].second == 7) s.setTexture(seven);
			if (hidegrid[i][j].second == 8) s.setTexture(eight);

			hidegrid[i][j].first = s;
			
		}
	}
}


int Minesweeper::left_mouse_clicked(int x, int y) {
	if (game_start == false) {
		winclock.restart();
		game_start = true;
	}

	if (clock.getElapsedTime().asMilliseconds() > 200) {
		for (int i = 1; i <=level; i++) {
			for (int j = 1; j <= level; j++) {

				sf::FloatRect sprite1 = showgrid[i][j].first.getGlobalBounds();
				
				if (sprite1.contains(sf::Vector2f(x, y))) {
					
					if (showgrid[i][j].second == false) {

						if (hidegrid[i][j].second == -1) {
							display_all();
							
							return -1;
						}
						 return display_number(i, j);
						 
					}
					else {
						if (count_flag(i, j) == hidegrid[i][j].second) {
							
							if (clearing_boundary(i, j) == -1) {
								display_all();
								return -1;
							}
							else {
								clearing_boundary(i,j);
							}
						}

					}
				}
				
			}
			
		}
		
		clock.restart();
	}
}

int Minesweeper::count_flag(int i, int j) {
	
	if (i > 0 && i <= level && j > 0 && j <= level) {
		int n = 0;

		if (showgrid[i-1][j-1].first.getTexture() == &flag) n++;
		if (showgrid[i-1][j].first.getTexture() == &flag) n++;
		if (showgrid[i-1][j+1].first.getTexture() == &flag) n++;
		if (showgrid[i][j-1].first.getTexture() == &flag) n++;
		if (showgrid[i][j+1].first.getTexture() == &flag) n++;
		if (showgrid[i+1][j-1].first.getTexture() == &flag) n++;
		if (showgrid[i+1][j].first.getTexture() == &flag) n++;
		if (showgrid[i+1][j+1].first.getTexture() == &flag) n++;

		

		return n;
	}
	
}

void Minesweeper::right_mouse_clicked(int x, int y) {
	if (game_start == false) {
		winclock.restart();
		game_start = true;
	}
	if (clock.getElapsedTime().asMilliseconds() > 200) {
		for (int i = 1; i <= level; i++) {
			for (int j = 1; j <= level; j++) {

				sf::FloatRect sprite1 = showgrid[i][j].first.getGlobalBounds();

				if (sprite1.contains(sf::Vector2f(x, y))) {
				
					if(showgrid[i][j].second == false){
						sf::Sprite s;
						s.setTexture(flag);
						s.setScale(box_size * scale, box_size * scale);
						s.setPosition(showgrid[i][j].first.getPosition());

						showgrid[i][j].first = s;

						showgrid[i][j].second = true;
					}
					else {
						if (showgrid[i][j].first.getTexture() == &flag) {
							sf::Sprite s;
							s.setTexture(facingdown);
							s.setScale(box_size * scale, box_size * scale);
							s.setPosition(showgrid[i][j].first.getPosition());

							showgrid[i][j].first = s;
							showgrid[i][j].second = false;
						}
					}
				}
			}

		}
		
		clock.restart();
	}
}


int  Minesweeper::display_number(int x, int y) {
	if(x > 0 && x <=level && y >0 && y<=level){
		if (showgrid[x][y].second == false) {
			showgrid[x][y].first = hidegrid[x][y].first;
			showgrid[x][y].second = true;
			if (hidegrid[x][y].second == -1) {
				return -1;
			}
			if (hidegrid[x][y].second == 0) {
				return clearing_boundary(x, y);
			}
		}
		return 0;
	}
}

void Minesweeper::display_game_over(sf::RenderWindow& window) {
	sf::Text t;
	sf::Font font;

	stringstream ss;
	font.loadFromFile("Fonts/times.ttf");

	ss << "You Win !!" << endl << "Your time was : " <<(int)winclock.getElapsedTime().asSeconds() <<"seconds"<<endl;
	t.setFont(font);
	t.setFillColor(sf::Color::Black);
	t.setCharacterSize(30);
	t.setString(ss.str());
	t.setPosition(Width / 2 - 100, Height / 2-50);
	window.draw(t);
}

int Minesweeper::clearing_boundary(int x, int y) {
	if(display_number(x - 1, y - 1) == -1  && (showgrid[x - 1][y - 1].first.getTexture() != &flag)) return -1;
	if(display_number(x - 1, y) == -1 && (showgrid[x - 1][y].first.getTexture() != &flag)) return -1;
	if(display_number(x - 1, y + 1) == -1 && (showgrid[x - 1][y + 1].first.getTexture() != &flag)) return -1;
	if(display_number(x, y - 1) == -1 && (showgrid[x][y - 1].first.getTexture() != &flag)) return -1;
	if(display_number(x, y + 1) == -1 && (showgrid[x][y + 1].first.getTexture() != &flag)) return -1;
	if(display_number(x + 1, y - 1) == -1 && (showgrid[x + 1][y - 1].first.getTexture() != &flag)) return -1;
	if(display_number(x + 1, y) == -1 && (showgrid[x + 1][y].first.getTexture() != &flag)) return -1;
	if(display_number(x + 1, y + 1) == -1 && (showgrid[x + 1][y + 1].first.getTexture() != &flag)) return -1;
}

void Minesweeper::display_all() {
	for (int i = 1; i <= level; i++) {
		for (int j = 1; j <= level; j++) {
			if (hidegrid[i][j].second == -1) {
				showgrid[i][j].first = hidegrid[i][j].first;
				showgrid[i][j].second = true;
			}
		}

	}
}

bool Minesweeper::game_over() {
	int truecount = 0;

	for (int i = 1; i <= level; i++) {
		for (int j = 1; j <= level; j++) {
			
			if (showgrid[i][j].second == true) {
				if (showgrid[i][j].first.getTexture() == &flag) {
					if (hidegrid[i][j].first.getTexture() == &bombtexture) {
						truecount++;
					}
				}
				else {
					truecount++;
				}

			}
		}

	}
	
	if (truecount == level * level) {
		return true;
	}
	return false;
}

void Minesweeper::draw(sf::RenderWindow& window) {
	int truecount = 0;

	for (int i = 1; i <= level; i++) {
		for (int j = 1; j <= level; j++) {
			window.draw(showgrid[i][j].first);
			
		}
	}
}

