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
	 VideoMode mode = VideoMode::getDesktopMode();
	 cout << "Resolution read: " << mode.width << ' ' << mode.height << endl;
	 VideoMode vm(mode.width, mode.height);

	 // Create and open a window for the game
	 RenderWindow window(vm, "Chaos Game!!", Style::Default);
	 vector<Vector2f> vertices;
	 vector<Vector2f> points;
	 
	 Font font;
	 font.loadFromFile("dejavu/DejaVuSansMono.ttf");
	 Text text;
	 text.setFont(font);
	 text.setString("Choose three or more points (up to 10).");
	 text.setCharacterSize(24);
	 text.setFillColor(Color::White);
	 text.setPosition(60, 50);
	 
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
			if (Keyboard::isKeyPressed(Keyboard::Enter) && vertices.size() < 3) text.setString("You need to have at least 3 points.");
			
			if (!continueReadingVertices) text.setString("Click anywhere to start generating the fractal.");

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (text.getString() == "You need to have at least 3 points.") text.setString("Press Enter when you're done with vertecies.");
					if (text.getString() == "Choose three or more points (up to 10).") text.setString("Press Enter when you're done with vertecies.");
					
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
			 
			window.draw(text);
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
	text.setString("Generating" + dots);
	text.setCharacterSize(15);
	text.setPosition(20, 30);
	int textTimer = -50;
	
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
		
		textTimer++;
		if (textTimer > 100) { dots += '.'; textTimer = 0; }
		if (dots.size() > 3) dots = "";
		text.setString("Generating" + dots);
		
		
		window.draw(text);
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
