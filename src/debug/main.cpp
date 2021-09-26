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

    sf::Color background = sf::Color(150, 220, 255); // Window background color

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
    text.setFillColor(sf::Color::White);

    // Map
    int mapWidth = 20;
    int mapHeight = 20;

    sf::Vector2f mapTileSize(24.f, 24.f);

    sf::RectangleShape map[mapWidth][mapHeight];

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            map[x][y].setSize(mapTileSize);
            map[x][y].setOutlineThickness(1.f);
            map[x][y].setOutlineColor(sf::Color(0, 0, 0));
            map[x][y].setPosition(sf::Vector2f(((rootWin.getSize().x / 2) - (mapWidth * mapTileSize.x / 2)) + (x * mapTileSize.x), (((rootWin.getSize().y / 2) - (mapHeight * mapTileSize.y / 2))) + (y * mapTileSize.y)));

            //walls
            map[0][y].setFillColor(sf::Color::Red);
            map[x][0].setFillColor(sf::Color::Red);
            map[mapWidth - 1][y].setFillColor(sf::Color::Red);
            map[x][mapHeight - 1].setFillColor(sf::Color::Red);
        }
    }

    int headPosX = 0;
    int headPosY = 0;

    //set walls
    // for(int x = 0; x < mapWidth; x++)
    // {
    //     for(int y = 0; y < mapHeight; y++)
    //     {
    //         map[0][y].setFillColor(sf::Color::Red);
    //     }
    // }

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

    // for (int i = 0; i < snake.size(); i++)
    // {
    //     //snake.at(i).setPosition(sf::Vector2f((rootWin.getSize().x / 2) - (snake[i].getTexture()->getSize().x / 2), (rootWin.getSize().y / 2) - (snake[i].getTexture()->getSize().y / 2)));
    //     snake.at(i).setPosition(map[1][1].getPosition());
    // }

    snake.at(0).setPosition(map[1][1].getPosition());

    char myDir = 'N';

    while (rootWin.isOpen())
    {
        headPosX = (snake.at(0).getPosition().x - map[0][0].getPosition().x) / mapTileSize.x;
        headPosY = (snake.at(0).getPosition().y - map[0][0].getPosition().y) / mapTileSize.y;

        // std::cout << "X: " << headPosX << "\n";
        // std::cout << "Y: " << headPosY << "\n";

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

        if (elapsed.asMilliseconds() >= 200)
        {

            for (int i = 0; i < snake.size(); i++)
            {
                if (i > 0)
                {
                    snake.at(snake.size() - i).setPosition(snake.at(snake.size() - (i + 1)).getPosition());
                }
            }

            snake.at(0).move(snakeVelocityX, snakeVelocityY);
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
                    snake.at(0).setPosition(map[1][1].getPosition());
                    snakeVelocityX = 0;
                    snakeVelocityY = 0;
                }
                break;

                case (sf::Keyboard::Space):
                {
                    // snake[0].getTexture()->getSize().x += 1;
                    // snake[0].getTexture()->getSize().y += 1;

                    // snake.at(0).setSize(squareSize);
                    snakeVelocityX = 0;
                    snakeVelocityY = 0;
                }
                break;

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
                    if ((elapsedInput.asMilliseconds() >= 200))
                    {
                        snake.push_back(snakeTile);
                        snake.at(snake.size() - 1).setPosition(snake.at(0).getPosition());
                        clock1.restart();
                    }
                }
                break;

                case (sf::Keyboard::Right):
                {
                    //snake.at(0).setFillColor(sf::Color::Red);
                    if ((snakeVelocityX != -snakeVelocity) && (elapsedInput.asMilliseconds() >= 101) && myDir != 'L') // Check if snake.at(0) isn't goin the opposite direction so you don't eat yourself
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
                    if (snakeVelocityX != snakeVelocity && (elapsedInput.asMilliseconds() >= 101) && myDir != 'R')
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
                    if (snakeVelocityY != snakeVelocity && (elapsedInput.asMilliseconds() >= 101) && myDir != 'D')
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
                    if (snakeVelocityY != -snakeVelocity && (elapsedInput.asMilliseconds() >= 101) && myDir != 'U')
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

        for (int i = 0; i < mapWidth; i++)
        {
            for (int j = 0; j < mapHeight; j++)
            {
                rootWin.draw(map[i][j]);
            }
        }

        for (int i = 0; i < snake.size(); i++)
        {
            rootWin.draw(snake.at(i));
        }

        rootWin.draw(text);
        rootWin.display();
    }
    return 0;
}