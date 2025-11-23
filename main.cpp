// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	 // Create a video mode object
	 VideoMode vm(1280, 800);

	 // Create and open a window for the game
	 RenderWindow window(vm, "Chaos Game!!", Style::Default);
	 vector<Vector2f> vertices;
	 vector<Vector2f> points;
	 
	 bool readingTheInput = true;
	 bool continueReadingVertices = true;
	 while (readingTheInput)
	 {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			
			if (Keyboard::isKeyPressed(Keyboard::Enter) && vertices.size() > 2) continueReadingVertices = false;

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					if(vertices.size() < 10 && continueReadingVertices)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if(points.size() == 0)
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						readingTheInput = false;
					}
				}
			}
			
			window.clear();
			 
			for(int i = 0; i < vertices.size(); i++)
			{
				RectangleShape rect(Vector2f(7,7));
				rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
				rect.setFillColor(Color::Red);
				window.draw(rect);
			}

			window.display();
		}
		
	}
	
	int previousVertex = -1;
	float r = 0.5;
	if(vertices.size() == 5) r = 0.618;
	else if(vertices.size() == 6) r = 0.667;
	else if(vertices.size() == 7) r = 0.692;
	else if(vertices.size() == 8) r = 0.707;
	else if(vertices.size() == 9) r = 0.742;
	else if(vertices.size() == 10) r = 0.764;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}

		/*
		****************************************
		Update
		****************************************
		*/

			
		if(points.size() > 0 && vertices.size() == 3)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			Vector2f p = points[points.size() - 1];
			Vector2f v = vertices[rand() % vertices.size()];
			Vector2f newPoint((p.x + v.x) * r, (p.y + v.y) * r);
			points.push_back(newPoint);
		}
		else if(points.size() > 0)
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

		/*
		****************************************
		Draw
		****************************************
		*/
			
		
		 
		window.clear();
		 
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
