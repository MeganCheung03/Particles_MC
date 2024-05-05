#include "Engine.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

Engine::Engine()
{
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;

	VideoMode vm(pixelWidth, pixelHeight);
	m_Window.create(vm, "Particles");
}

void Engine::run()
{
	Clock c;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	//end of unit tests

	while (m_Window.isOpen())
	{
		Time t = c.restart();
		float seconds = t.asSeconds();
		input();
		update(seconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			//handles event to close window
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			for (int i = 0; i < 5; ++i)
			{
				int numPoints = rand() % 26 + 25;
				Vector2i mousePos = Mouse::getPosition(m_Window);
				//using Particle::Particle(...) function
				m_particles.emplace_back(m_Window, numPoints, mousePos);
			}
		} 
	}
}

void Engine::update(float dtAsSeconds)
{
	vector<Particle> p = m_particles.begin();

	while (p != m_particles.end())
	{
		if (p->getTTL() > 0.0)
		{
			p->update(dtAsSeconds);
			++p;
		}
		else
		{
			p = m_particles.erase(p);
		}
	}

}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); ++i)
	{
		m_Window.draw(i);
	}
	m_Window.display();
}