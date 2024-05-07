#include "Engine.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cstdlib>
#include <ctime>

Engine::Engine()
{
	//creating the window
	VideoMode customMode(1440, 1080);
	m_Window.create(customMode, "Particles");
}

void Engine::run()
{
	//construct a local Clock object to track time per frame
	Clock c;
	
	//run unit tests
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		//restart the clock
		sf::Time t = c.restart();
		input();
		//call update with clock time converted to seconds
		update(t.asSeconds());
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_Window.close();
		}

		std::vector<Particle> new_particle;

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_Window);

			for (int i = 0; i < 5; i++)
			{
				//numPoints determines the number of vertices in each particle
				int numPoints = rand() % 26 + 25;
				//pass mouse click position into Particle to give starting position
				new_particle.push_back(Particle(m_Window, numPoints, mousePosition));
			}
		}
		//put the new_particle into m_particles
		m_particles.insert(m_particles.begin(), new_particle.begin(), new_particle.end());
	}
}

void Engine::update(float dtAsSeconds)
{
	//iterator based for loop
	std::vector<Particle>::iterator it; 

	for (it = m_particles.begin(); it != m_particles.end();)
	{ 
		if (it->getTTL() > 0.0)
		{ 
			it->update(dtAsSeconds);
			it++;
		}
		else
		{
			//erase the element the iterator points to
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();

	std::vector<Particle>::iterator it;

	//use polymorphism to create the particles
	for (it = m_particles.begin(); it != m_particles.end(); it++)
	{ 
		m_Window.draw(*it);
	}

	m_Window.display();
}