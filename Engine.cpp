#include <Engine.h>

using namespace sf;
using namespace std;

Engine::Engine()
{
	create(m_Window);
	VideoMode::getDesktopMode();
}

void Engine::run()
{
	Clock c;
	Particle p;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	//end of unit tests

	while (m_Window.open() == true)
	{
		c.restart();
		//convert time to seconds
		input();
		update();
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			//handles event to close window
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				while (numPoints < 5)
				{
					//pass position of mouse click into Particle
					Particle p = /*smth*/
				}
			}
		} 
	}
}

void Engine::update(float dtAsSeconds)
{
	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (dtAsSeconds == 0)
		{
			m_particles.erase(i);
		}
		if (getTTL() > 0.0)
		{
			update(i);
			++i;
		}
		else
		{
			if (i == m_particles.size())
			{
				return end(i);
			}
			else
			{
				m_particles.erase(i);
				return (i + 1);
			}
			
		}
	}

}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_Particles.size(); ++i)
	{
		m_Window.draw(i);
		m_Window.display();
	}
}