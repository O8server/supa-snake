#include <iostream>
#include <SFML/Graphics.hpp>

void updateSnake()
{
    // Define this later
}

int main()
{
    sf::RenderWindow rootWin(sf::VideoMode(800, 800), "Poop", sf::Style::Titlebar | sf::Style::Close);

    sf::Vector2u oldRootWinSize;

    sf::Color background = sf::Color(0, 0, 0); // Window background color

    sf::Font font;

    sf::Text text;

    sf::Vector2f squareSize = {20.f, 20.f};

    //sf::snakeTileShape snake[1] = {sf::snakeTileShape(squareSize)};

    sf::Clock clock;
    sf::Clock clock1;

    sf::Time elapsed;
    sf::Time elapsedInput;

    sf::Event event;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // Map


    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "Couldn't load font arial.ttf";
    }

    sf::Texture texture;
    if (!texture.loadFromFile("resources/snaketile.png"))
    {
        std::cout << "Couldn't load font texture";
    }

    sf::Sprite snakeTile;
    snakeTile.setTexture(texture);
    std::vector<sf::Sprite> snake = {snakeTile};

    

    float snakeVelocity = 0;

    float snakeVelocityX = 0.f;
    float snakeVelocityY = 0.f;

    for (int i = 0; i < snake.size(); i++)
    {
        snake.at(i).setPosition(sf::Vector2f((rootWin.getSize().x / 2) - (snake[i].getTexture()->getSize().x / 2), (rootWin.getSize().y / 2) - (snake[i].getTexture()->getSize().y / 2)));
    }

    char myDir = 'N';

    while (rootWin.isOpen())
    {
        // std::cout << texture.getSize().x;
        // std::cout << texture.getSize().y;

        text.setString("Snake size: " + std::to_string(snake.size()));

        elapsed = clock.getElapsedTime();
        elapsedInput = clock1.getElapsedTime();

        //std::cout << elapsed.asMilliseconds() << "\n";
        for (int i = 0; i < snake.size(); i++)
        {
            snakeVelocity = snake[i].getTexture()->getSize().x;
        }

        if(elapsed.asMilliseconds() >= 100)
        {           
            for (int i = 0; i < snake.size(); i++)
            {
                snake.at(i).move(snakeVelocityX, snakeVelocityY);
            }

            clock.restart();
        }

        //snake.at(0).move(snakeVelocityX, snakeVelocityY);       

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

                case (sf::Keyboard::C):
                {
                    snake.at(0).setPosition(sf::Vector2f((rootWin.getSize().x / 2) - (snake[0].getTexture()->getSize().x / 2), (rootWin.getSize().y / 2) - (snake[0].getTexture()->getSize().y / 2)));
                }
                break;

                // case (sf::Keyboard::Space):
                // {
                //     snake[0].getTexture()->getSize().x += 1;
                //     snake[0].getTexture()->getSize().y += 1;

                //     snake.at(0).setSize(squareSize);
                // }
                // break;

                // case (sf::Keyboard::Backspace):
                // {
                //     if (snake[0].getTexture()->getSize().x > 0 || snake[0].getTexture()->getSize().y > 0)
                //     {
                //         snake[0].getTexture()->getSize().x -= 1;
                //         snake[0].getTexture()->getSize().y -= 1;
                //     }

                //     snake.at(0).setSize(squareSize);
                // }
                // break;

                case (sf::Keyboard::Enter):
                {
                    snake.push_back(snakeTile);
                }
                break;

                case (sf::Keyboard::Right):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if ((snakeVelocityX != -snakeVelocity) && (elapsedInput.asMilliseconds() >= 101))// Check if snake.at(0) isn't goin the opposite direction so you don't eat yourself
                    {
                        snakeVelocityX = snakeVelocity;
                        snakeVelocityY = 0.0f;
                        myDir = 'R';
                        clock1.restart();
                    }
                }
                break;

                case (sf::Keyboard::Left):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityX != snakeVelocity && (elapsedInput.asMilliseconds() >= 101))
                    {
                        snakeVelocityX = -snakeVelocity;
                        snakeVelocityY = 0.0f;
                        myDir = 'L';
                        clock1.restart();

                    }
                }
                break;

                case (sf::Keyboard::Up):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityY != snakeVelocity && (elapsedInput.asMilliseconds() >= 101))
                    {
                        snakeVelocityX = 0.0f;
                        snakeVelocityY = -snakeVelocity;
                        myDir = 'U';
                        clock1.restart();

                    }
                }
                break;

                case (sf::Keyboard::Down):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if (snakeVelocityY != -snakeVelocity && (elapsedInput.asMilliseconds() >= 101))
                    {
                        snakeVelocityX = 0.0f;
                        snakeVelocityY = snakeVelocity;
                        myDir = 'D';
                        clock1.restart();
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
        rootWin.draw(text);
        rootWin.display();
    }
    return 0;
}