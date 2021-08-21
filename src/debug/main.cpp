#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    int pressed = 0;

    sf::RenderWindow rootWin(sf::VideoMode(800, 800), "Poop", sf::Style::Titlebar | sf::Style::Close);

    sf::Vector2u oldRootWinSize;

    sf::Color background = sf::Color(0, 0, 0); // Window background color

    sf::Font font;

    sf::Text text;

    sf::Vector2f squareSize = {20.f, 20.f};

    std::vector<sf::RectangleShape> snake = {sf::RectangleShape(squareSize)};

    //sf::RectangleShape snake[1] = {sf::RectangleShape(squareSize)};

    sf::Clock clock;

    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "Couldn't load font arial.ttf";
    }

    float snakeVelocity = squareSize.x;
    float snakeVelocityX = 0.f;
    float snakeVelocityY = 0.f;

    snake.at(0).setPosition(sf::Vector2f((rootWin.getSize().x / 2) - (squareSize.x / 2), (rootWin.getSize().y / 2) - (squareSize.y / 2)));
    snake.at(0).setFillColor(sf::Color::Green);

    while (rootWin.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();

        //std::cout << elapsed.asMilliseconds() << "\n";

        if(elapsed.asMilliseconds() == 100)
        {
            snake.at(0).move(snakeVelocityX, snakeVelocityY);
            clock.restart();
        }

        //snake.at(0).move(snakeVelocityX, snakeVelocityY);
        

        sf::Event event;

        while (rootWin.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                rootWin.close();
                std::cout << "closed"
                          << "\n";
                break;

            case sf::Event::Resized:
                std::cout << event.size.width << "x" << event.size.height << "\n";
                break;

            case sf::Event::KeyPressed: // Get input
                std::cout << event.key.code << "\n";

                switch (event.key.code) // Get input value
                {
                case (sf::Keyboard::F): // If F pressed then set Fullscreen
                {
                    sf::Vector2u fullScreen = {2560, 1440};

                    if (rootWin.getSize() != fullScreen)
                    {
                        oldRootWinSize = rootWin.getSize();
                        rootWin.setSize(fullScreen);
                        rootWin.setPosition(sf::Vector2i(0, 0));
                        std::cout << "X: " << rootWin.getPosition().x << "|Y: " << rootWin.getPosition().y << "\n";

                        // Make sure we refresh the screen to scale graphics
                        // rootWin.clear(background);
                        // rootWin.draw(text);
                        // rootWin.display();
                    }

                    else
                    {
                        rootWin.setSize(oldRootWinSize);
                        std::cout << "X: " << rootWin.getPosition().x << "|Y: " << rootWin.getPosition().y << "\n";

                        // Make sure we refresh the screen to scale graphics
                        // rootWin.clear(background);
                        // rootWin.draw(text);
                        // rootWin.display();
                    }
                    text.setCharacterSize(24); // in pixels, not points!
                }
                break;

                case (sf::Keyboard::Space):
                {
                    squareSize.x += 1;
                    squareSize.y += 1;

                    snake.at(0).setSize(squareSize);
                }
                break;

                case (sf::Keyboard::Backspace):
                {
                    if (squareSize.x > 0 || squareSize.y > 0)
                    {
                        squareSize.x -= 1;
                        squareSize.y -= 1;
                    }

                    snake.at(0).setSize(squareSize);
                }
                break;

                case (sf::Keyboard::Right):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityX != -snakeVelocity) // Check if snake.at(0) isn't goin the opposite direction so you don't eat yourself
                    {
                        snakeVelocityX = snakeVelocity;
                        snakeVelocityY = 0.0f;
                    }
                }
                break;

                case (sf::Keyboard::Left):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityX != snakeVelocity)
                    {
                        snakeVelocityX = -snakeVelocity;
                        snakeVelocityY = 0.0f;
                    }
                }
                break;

                case (sf::Keyboard::Up):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityY != snakeVelocity)
                    {
                        snakeVelocityX = 0.0f;
                        snakeVelocityY = -snakeVelocity;
                    }
                }
                break;

                case (sf::Keyboard::Down):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityY != -snakeVelocity)
                    {
                        snakeVelocityX = 0.0f;
                        snakeVelocityY = snakeVelocity;
                    }
                }
                break;

                default:
                    break;
                }
                break;

                // case(sf::Event::KeyReleased):
                // {
                //     switch (event.key.code)
                //     {
                //     case (sf::Keyboard::Right):
                //     {
                //             snake.at(0).setFillColor(sf::Color::Green);
                //     }break;

                //     case (sf::Keyboard::Left):
                //     {
                //             snake.at(0).setFillColor(sf::Color::Green);
                //     }break;

                //     case (sf::Keyboard::Up):
                //     {
                //             snake.at(0).setFillColor(sf::Color::Green);
                //     }break;

                //     case (sf::Keyboard::Down):
                //     {
                //             snake.at(0).setFillColor(sf::Color::Green);
                //     }break;

                //     default:
                //         break;
                //     }
                // }

            default:
                break;
            }
        }

        rootWin.clear(background);
        for (int i = 0; i < snake.size(); i++)
        {
            rootWin.draw(snake.at(i));
        }
        rootWin.display();
    }

    return 0;
}