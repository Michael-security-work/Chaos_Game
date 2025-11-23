// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	 srand(time(NULL));
	 
	 // Create a video mode object
	 VideoMode mode = VideoMode::getDesktopMode();
	 cout << "Resolution read: " << mode.width << ' ' << mode.height << endl;
	 VideoMode vm(mode.width, mode.height);

	 // Create and open a window for the game
	 RenderWindow window(vm, "Chaos Game!!", Style::Default);
	 vector<Vector2f> vertices;
	 vector<Vector2f> points;
	 
	 Font font;
	 font.loadFromFile("fonts/DejaVuSansMono.ttf");
	 
	 Text text;
	 text.setFont(font);
	 text.setFillColor(Color::White);
	 
	 Text exit;
	 exit.setFont(font);
	 exit.setFillColor(Color::White);
	 
	 string textInit = "Leftclick to choose three or more points for vertives (up to 10).";
	 string text1 = "Rightclick anywhere to start generating the fractal.";
	 string textWarning = "You need to have at least 3 vertices.";
	 string textWarning2 = "You've hit 10 points, leftclick to start generating";
	 
	 string exit1 = "Press esc to quit.";
	 string exit2 = "Press esc to start a new shape.";
	 
	 while (window.isOpen())
	 {
		 
		 text.setString(textInit);
		 text.setCharacterSize(24);
		 text.setPosition(60, 50);
		 
		 
		 exit.setString(exit1);
		 exit.setCharacterSize(24);
		 exit.setPosition(60, 20);
		 
		 bool readingTheInput = true;
		 bool continueReadingVertices = true;
		 while (readingTheInput && window.isOpen())
		 {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
				if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
				
				if (!continueReadingVertices) text.setString(text1);

				if (event.type == Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						if (text.getString() == textWarning) text.setString(text1);
						if (text.getString() == textInit) text.setString(text1);
						if(vertices.size() > 9) text.setString(textWarning2);
						
						std::cout << "the left button was pressed" << std::endl;
						std::cout << "mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "mouse y: " << event.mouseButton.y << std::endl;
						if(vertices.size() < 10 && continueReadingVertices)
						{
							vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						}
					}
					if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (vertices.size() > 2) continueReadingVertices = false;
						if (vertices.size() < 3) text.setString(textWarning);
						else if(points.size() == 0 && vertices.size() > 2)
						{
							points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
							readingTheInput = false;
						}
					}
				}
				
				window.clear();
				 
				window.draw(text);
				window.draw(exit);
				for(int i = 0; i < vertices.size(); i++)
				{
					RectangleShape rect(Vector2f(7,7));
					rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
					rect.setFillColor(Color::Red);
					window.draw(rect);
				}
				
				for (int i = 0; i < points.size(); i++)
				{
					RectangleShape rect(Vector2f(1,1));
					rect.setPosition(Vector2f(points[i].x, points[i].y));
					rect.setFillColor(Color::Blue);
					window.draw(rect);
				}

				window.display();
			}
			
		}
		
		string dots = "";
		text.setString("Genarating" + dots);
		text.setCharacterSize(15);
		text.setPosition(20, 30);
		int textTimer = -50;
		
		exit.setString(exit2);
		exit.setCharacterSize(15);
		exit.setPosition(mode.width - 300, 30);
		
		float r = 0.5;
		switch(vertices.size())
		{
			case 5: r = 0.618; break;
			case 6: r = 0.667; break;
			case 7: r = 0.692; break;
			case 8: r = 0.707; break;
			case 9: r = 0.742; break;
			case 10: r = 0.764; break;
		}
		
		int previousVertex = -1;
		
		bool generating = true;
		while (generating && window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
				if (Keyboard::isKeyPressed(Keyboard::Escape)) 
				{
					sleep(milliseconds(100));
					generating = false;
					vertices.clear();
					points.clear();
				}
			}

			/*
			****************************************
			Update
			****************************************
			*/
				
			if(points.size() > 0 && vertices.size() == 4)
			{
				Vector2f p = points[points.size() - 1];
				Vector2f v;
				while(true)
				{
					int ran = rand() % vertices.size();
					if(ran != previousVertex)
					{
						v = vertices[ran];
						previousVertex = ran;
						break;
					}
				}
				Vector2f newPoint((v.x - p.x) * r + p.x, (v.y - p.y) * r + p.y);
				points.push_back(newPoint);
			}
			else if(points.size() > 0)
			{
				Vector2f p = points[points.size() - 1];
				Vector2f v = vertices[rand() % vertices.size()];
				Vector2f newPoint((v.x - p.x) * r + p.x, (v.y - p.y) * r + p.y);
				points.push_back(newPoint);
			}
			
			textTimer++;
			if (textTimer > 100) { dots += '.'; textTimer = 0; }
			if (dots.size() > 3) dots = "";
			text.setString("Generating" + dots);
			
			/*
			****************************************
			Draw
			****************************************
			*/
			
			window.clear();
			
			window.draw(text);
			window.draw(exit);
			for(int i = 0; i < vertices.size(); i++)
			{
				RectangleShape rect(Vector2f(3,3));
				rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
				rect.setFillColor(Color::Red);
				window.draw(rect);
			}

			for (int i = 0; i < points.size(); i++)
			{
				RectangleShape rect(Vector2f(1,1));
				rect.setPosition(Vector2f(points[i].x, points[i].y));
				rect.setFillColor(Color::Blue);
				window.draw(rect);
			}

			window.display();
		}
	}
}
