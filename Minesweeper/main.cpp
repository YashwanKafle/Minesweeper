#include<SFML/Graphics.hpp>
#include "Minesweeper.h"
#include <Windows.h>


int main() {

	

	
		int box_dimension = 30;

		sf::RenderWindow window(sf::VideoMode(16 * box_dimension, 16 * box_dimension), "MineSweeper");


		Minesweeper game(box_dimension * 16, box_dimension * 16);

		
		while (window.isOpen()) {
			sf::Event event;



			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
					
				}
			}


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				if (game.left_mouse_clicked(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) == -1) {

					window.clear(sf::Color::White);
					game.draw(window);
					window.display();

					Sleep(3000);
					window.close();
					
				}

			}
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

				game.right_mouse_clicked(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);


			}

			if (game.game_over()) {
				window.clear(sf::Color::White);
				game.draw(window);
				game.display_game_over(window);
				window.display();

				Sleep(5000);
				window.close();
			}

			window.clear(sf::Color::White);
			game.draw(window);
			
			window.display();


		}
	

}