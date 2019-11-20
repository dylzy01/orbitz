// System includes
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <math.h>

// SFML includes
#include <SFML/Graphics.hpp>

sf::CircleShape ORBIT_ONE(25.f);
sf::CircleShape AURA_ONE(125.f);
sf::CircleShape ORBIT_TWO(25.f);
sf::CircleShape AURA_TWO(125.f);
sf::CircleShape PLANET(25.f);	sf::Vector2f PLANETVel{ 0.f, 0.f }; float acceleration = 0.005;	float maxVel = 0.1f;
sf::Transform transform;
float angle = 0.f, pi = 3.14159265359;
sf::Vector2f ORBIT_ONE_POS, ORBIT_TWO_POS, PlayerPos;
sf::CircleShape Player(25);

bool orbit_1 = false, orbit_2 = false;

void Orbit(sf::Vector2f orbitPosition, sf::Vector2f orbitPositionNormal, sf::Vector2f planetPosition)
{
	float dot = ((orbitPositionNormal.x * planetPosition.x) + (orbitPositionNormal.y * planetPosition.y));
	angle = acos(dot);
	transform.rotate(angle, orbitPosition);
	///Player.rotate(angle);
}

bool Collision(sf::CircleShape* one, sf::CircleShape* two)
{
	float Xdist = pow((one->getPosition().x - two->getPosition().x), 2);
	float Ydist = pow((one->getPosition().y - two->getPosition().y), 2);
	float Xsum = (one->getPosition().x - two->getPosition().x) - Xdist;
	float Ysum = (one->getPosition().y - two->getPosition().y) - Ydist;
	float normal = (Xdist - Ydist) / (Xsum - Ysum);

	if (sqrt(Xdist + Ydist) >= one->getRadius() + two->getRadius())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void MovePLANET()
{
	// X
	/*PLANETVel.x -= acceleration;
	if (PLANETVel.x > maxVel)
	{
		PLANETVel.x = maxVel;
	}
	else if (PLANETVel.x < -maxVel)
	{
		PLANETVel.x = -maxVel;
	}
	PLANET.setPosition(PLANET.getPosition() + PLANETVel);*/

	// Y
	PLANETVel.y -= acceleration;
	if (PLANETVel.y > maxVel)
	{
		PLANETVel.y = maxVel;
	}
	else if (PLANETVel.y < -maxVel)
	{
		PLANETVel.y = -maxVel;
	}
	PLANET.setPosition(PLANET.getPosition() + PLANETVel);
}

sf::Vector2f Normalize(const sf::Vector2f& vector)
{
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if (length != 0)
	{
		return sf::Vector2f(vector.x / length, vector.y / length);
	}
	else
	{
		return vector;
	}
}

void Update(float deltaTime)
{
	// ORBIT ONE
	/*if (Collision(&Player, &AURA_ONE))
	{
		///if (orbit_2)
		{
			orbit_2 = false;
		}

		orbit_1 = true;
	}*/
	
	// ORBIT TWO
	/*if (Collision(&Player, &AURA_TWO))
	{
		///if (orbit_1)
		{
			orbit_1 = false;
		}

		orbit_2 = true;
	}*/
	
	// Movement
	/*if ((!orbit_1) && (!orbit_2))
	{
		MovePLANET();
	}
	else if (orbit_1)
	{
		Orbit(ORBIT_ONE.getPosition(), ORBIT_ONE_POS, PLANET_POS);
	}
	else if (orbit_2)
	{
		Orbit(ORBIT_TWO.getPosition(), ORBIT_TWO_POS, PLANET_POS);
	}*/


}

void Render(sf::RenderWindow* window)
{
	window->clear(sf::Color::Black);
	window->draw(AURA_ONE);
	window->draw(AURA_TWO);
	window->draw(ORBIT_ONE);
	window->draw(ORBIT_TWO);
	///window->draw(PLANET, transform);
	window->draw(Player, transform);
	window->display();
}

int main()
{
	sf::Clock clock;
	float deltaTime = clock.getElapsedTime().asSeconds();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Orbitz");

	ORBIT_ONE.setFillColor(sf::Color::Yellow);
	ORBIT_ONE.setPosition(550, 350);
	ORBIT_ONE.setOrigin(25, 25);
	ORBIT_ONE_POS = ORBIT_ONE.getPosition();
	ORBIT_ONE_POS = Normalize(ORBIT_ONE_POS);
	AURA_ONE.setFillColor(sf::Color::Green);
	AURA_ONE.setPosition(ORBIT_ONE.getPosition());
	AURA_ONE.setOrigin(125, 125);

	ORBIT_TWO.setFillColor(sf::Color::Yellow);
	ORBIT_TWO.setPosition(350, 250);
	ORBIT_TWO.setOrigin(25, 25);
	ORBIT_TWO_POS = ORBIT_TWO.getPosition();
	ORBIT_TWO_POS = Normalize(ORBIT_TWO_POS);
	AURA_TWO.setFillColor(sf::Color::Red);
	AURA_TWO.setPosition(ORBIT_TWO.getPosition());
	AURA_TWO.setOrigin(125, 125);

	PLANET.setFillColor(sf::Color::Blue);
	PLANET.setPosition(550, 450);
	PLANET.setOrigin(12.5, 12.5);

	sf::Texture texture; texture.loadFromFile("../Resources/spaceship.png");
	Player.setTexture(&texture);
	Player.setPosition(100, 450);
	Player.setOrigin(sf::Vector2f(12.5f, 12.5f));
	PlayerPos = Player.getPosition();
	PlayerPos = Normalize(PlayerPos);
	sf::Vector2f PlayerVelocity{ 0.f, 0.f }; 
	float PlayerAcceleration = 0.005;	
	float PlayerVelocityMAX = 0.1f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Update
		{
			// https://en.sfml-dev.org/forums/index.php?topic=4951.0
			float PlayerAngleRadians = ((pi / 180)*(Player.getRotation()));
			float PlayerX = (0.01f*cos(PlayerAngleRadians));
			float PlayerY = (0.01f*sin(PlayerAngleRadians));
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					Player.move(PlayerX, PlayerY);
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					Player.rotate(0.03f);
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					Player.rotate(-0.03f);
				}
			}

			// Movement
			if (!orbit_1 && !orbit_2)
			{
				PlayerVelocity.x += PlayerAcceleration;
				if (PlayerVelocity.x > PlayerVelocityMAX)
				{
					PlayerVelocity.x = PlayerVelocityMAX;
				}
				else if (PLANETVel.x < -PlayerVelocityMAX)
				{
					PlayerVelocity.x = -PlayerVelocityMAX;
				}
				Player.setPosition(Player.getPosition() + PlayerVelocity);
			}
			///Player.move(PlayerX, PlayerY);

			// Collision
			if (Collision(&Player, &AURA_ONE))
			{
				orbit_1 = true;
				orbit_2 = false;
				///Orbit(ORBIT_ONE.getPosition(), ORBIT_ONE_POS, PlayerPos);
			}

			if (Collision(&Player, &AURA_TWO))
			{
				orbit_1 = false;
				orbit_2 = true;
				///Orbit(ORBIT_TWO.getPosition(), ORBIT_TWO_POS, PlayerPos);
			}

			if (orbit_1)
			{
				Orbit(ORBIT_ONE.getPosition(), ORBIT_ONE_POS, PlayerPos);
			}
			else if (orbit_2)
			{
				Orbit(ORBIT_TWO.getPosition(), ORBIT_TWO_POS, PlayerPos);
			}

			///Update(deltaTime);
		}

		// Render
		{
			Render(&window);
		}

		///std::cout << "ANGLE:" << std::to_string(angle) << std::endl;
		/*if (Collision(&PLANET, &AURA_ONE))
		{
			std::cout << "COLLISION: AURA ONE" << std::endl;
		}*/
		if (Collision(&PLANET, &AURA_TWO))
		{
			std::cout << "COLLISION: AURA TWO" << std::endl;
		}
	}

	return 0;
}