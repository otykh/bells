#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#define SCREEN_HEIGHT 300
#define SCREEN_WIDTH 300
#define BALL_SIZE 4

std::vector<sf::CircleShape> ball_shape;
std::vector<float> ball_speed;
std::vector<sf::Vector2f> ball_direction;
std::vector<sf::Sound> ball_sound;
//float ball_speed = 1000;

//sf::Vector2f ball_direction(0.1f, -1.f);

float getRandomUnitFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
void normalize(sf::Vector2f& source)
{
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
	{
        source = sf::Vector2f(source.x / length, source.y / length);
	}
}

int main()
{
	srand(time(0));

	sf::SoundBuffer chimeBuffer;
    if (!chimeBuffer.loadFromFile("sound.wav"))
        return -1;

	std::cout << "Welcome to the chime creator, please input the ball speed, direction and pitch" << std::endl;
	for(;;)
	{
		std::cout << "Add a new ball" << std::endl;

		float newSpeed;
		float newX;
		float newY;
		float newPitch;
		std::cout << "Speed: ";
		std::cin >> newSpeed;
		std::cout << "Now x dir: ";
		std::cin >> newX;
		std::cout << "Now y dir: ";
		std::cin >> newY;
		std::cout << "New pitch: ";
		std::cin >> newPitch;

		std::cout << "You want to create a new ball with these properties?" << std::endl;

		char c;
		std::cout << "add? (y/n)";
		std::cin >> c;
		if(c == 'y')
		{
			sf::CircleShape shape(BALL_SIZE);
			shape.setPosition(sf::Vector2f(0,0));

			sf::Sound chime;
			chime.setBuffer(chimeBuffer);
			chime.setPitch(newPitch);

			ball_shape.push_back(shape);
			ball_speed.push_back(newSpeed);
			ball_direction.push_back(sf::Vector2f(newX, newY));
			ball_sound.push_back(chime);

			std::cout << "added" << std::endl;
			std::cout << "wanna continue? (y/n)";
			std::cin >> c;
			if(c == 'n')
			{
				std::cout << "creating the simulation" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "alright, try again" << std::endl;
		}
	}


	sf::Sound chime;
	chime.setBuffer(chimeBuffer);
	chime.play();

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "COOL SOUND");

    //sf::CircleShape ball(4.f);

	//ball.setPosition(0, 0);

    //ball.setFillColor(sf::Color::Green);

	sf::Clock clock;
    while (window.isOpen())
    {
		sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

		for(int i = 0; i < ball_shape.size(); i++)
		{
			ball_shape[i].move(ball_direction[i] * ball_speed[i] * elapsed.asSeconds());

			//simple wall collision detection
			sf::Vector2f ball_position = ball_shape[i].getPosition();
			if(ball_position.x + BALL_SIZE > SCREEN_WIDTH || ball_position.x < 0)
			{
				// left and right wall
				ball_direction[i].x *= -1;
				if(ball_position.x < 0)
				{
					// on the left, account for the distance that was lost
					ball_shape[i].setPosition(0 - ball_position.x, ball_position.y);
				}
				else
				{
					// on the right, account for the distance that was lost
					ball_shape[i].setPosition(SCREEN_WIDTH - (SCREEN_WIDTH - ball_position.x + BALL_SIZE), ball_position.y);
				}
				ball_position = ball_shape[i].getPosition(); // update the position for the collision on y axis
				//ball_direction.x += getRandomUnitFloat() - 0.5f;
				//ball_direction.y += getRandomUnitFloat() - 0.5f;
				//normalize(ball_direction);

				ball_sound[i].play();
			}
			if(ball_position.y < 0 || ball_position.y + BALL_SIZE > SCREEN_HEIGHT)
			{
				// south and north wall
				ball_direction[i].y *= -1;
				if(ball_position.y < 0)
				{
					// on the left, account for the distance that was lost
					ball_shape[i].setPosition(ball_position.x, 0 - ball_position.y);
				}
				else
				{
					// on the right, account for the distance that was lost
					ball_shape[i].setPosition(ball_position.x, SCREEN_HEIGHT - (SCREEN_HEIGHT - ball_position.y + BALL_SIZE));
				}
				//ball_direction.x += getRandomUnitFloat() - 0.5f;
				//ball_direction.y += getRandomUnitFloat() - 0.5f;
				//normalize(ball_direction);

				ball_sound[i].play();
			}

			window.draw(ball_shape[i]);
		}

        window.display();
    }

    return 0;
}
