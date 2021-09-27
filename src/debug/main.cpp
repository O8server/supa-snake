#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


void updateSnake()
{
    // Define this later
}

int main()
{
    bool gameOver = false;

    sf::RenderWindow rootWin(sf::VideoMode(800, 800), "Poop", sf::Style::Titlebar | sf::Style::Close);

    sf::Vector2u oldRootWinSize;

    sf::Color background = sf::Color(150, 220, 255); // Window background color

    sf::Font font;

    sf::Text text;

    //sf::snakeTileShape snake[1] = {sf::snakeTileShape(squareSize)};

    sf::Clock clock;
    sf::Clock clock1;

    sf::Time elapsed;
    sf::Time elapsedInput;

    sf::Event event;

    sf::SoundBuffer buffer;

    sf::Sound gwa;

    sf::Music music;

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
            map[x][y].setPosition(sf::Vector2f(((rootWin.getSize().x / 2) - (mapWidth * mapTileSize.x / 2)) + (x * mapTileSize.x), (((rootWin.getSize().y / 2) - (mapHeight * mapTileSize.y / 2))) + (y * mapTileSize.y)));
            map[x][y].setFillColor(sf::Color::Transparent);

            // Show grid (tile outlines)
            // map[x][y].setOutlineThickness(1.f);
            // map[x][y].setOutlineColor(sf::Color(0, 0, 0));
        }
    }
    // Wall colors
    for (int x = 0; x < (mapWidth - mapWidth / 2); x++)
    {
        for (int y = 0; y < (mapHeight - mapHeight / 2); y++)
        {
            map[mapWidth - 1][y + y].setFillColor(sf::Color::Yellow);
            map[mapWidth - 1][y + y + 1].setFillColor(sf::Color::Black);
            map[x + x][mapHeight - 1].setFillColor(sf::Color::Yellow);
            map[x + x + 1][mapHeight - 1].setFillColor(sf::Color::Black);

            map[0][y + y].setFillColor(sf::Color::Black);
            map[0][y + y + 1].setFillColor(sf::Color::Yellow);
            map[x + x][0].setFillColor(sf::Color::Black);
            map[x + x + 1][0].setFillColor(sf::Color::Yellow);
        }
    }

    int headPosX = 0;
    int headPosY = 0;

    int applePosX = 0;
    int applePosY = 0;

    //set walls
    // for(int x = 0; x < mapWidth; x++)
    // {
    //     for(int y = 0; y < mapHeight; y++)
    //     {
    //         map[0][y].setFillColor(sf::Color::Red);
    //     }
    // }

    if (!music.openFromFile("resources/ZULUL.wav"))
    return -1; // error
    music.play();

    if (!buffer.loadFromFile("resources/gwa.wav"))
    {
        std::cout << "Couldn't play gwa.wav";
        return -1;
    }

    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "Couldn't load font arial.ttf";
    }

    sf::Texture texture;
    if (!texture.loadFromFile("resources/snaketile.png"))
    {
        std::cout << "Couldn't load snaketile.png";
    }

    sf::Texture appleTexture;
    if (!appleTexture.loadFromFile("resources/zulul.png"))
    {
        std::cout << "Couldn't load font zulul.png";
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resources/forsenLevel2.png"))
    {
        std::cout << "Couldn't load font metal.png";
    }

    sf::Texture pagman;
    if (!pagman.loadFromFile("resources/pagman.png"))
    {
        std::cout << "Couldn't load font pagman.png";
    }

    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("resources/gameover.jpeg"))
    {
        std::cout << "Couldn't load font gameover.jpeg";
    }

    sf::RectangleShape gameOverImage(sf::Vector2f(rootWin.getSize().x, rootWin.getSize().y));
    gameOverImage.setTexture(&gameOverTexture);
    gameOverImage.setFillColor(sf::Color::Transparent);

    sf::RectangleShape backgroundMap(sf::Vector2f(mapTileSize.x * mapWidth - mapTileSize.x * 2, mapTileSize.y * mapHeight - mapTileSize.y * 2));
    backgroundMap.setTexture(&backgroundTexture);
    backgroundMap.setPosition(map[0][0].getPosition().x + mapTileSize.x * 1, map[0][0].getPosition().y + mapTileSize.y * 1);

    sf::RectangleShape apple(mapTileSize);
    std::vector <sf::RectangleShape> apples {apple};
    apples.at(0).setTexture(&appleTexture);

    sf::Sprite snakeTile;
    snakeTile.setTexture(texture);
    std::vector<sf::Sprite> snake = {snakeTile};

    snake.at(0).setTexture(pagman);

    float snakeVelocity = 0;

    float snakeVelocityX = 0.f;
    float snakeVelocityY = 0.f;

    // for (int i = 0; i < snake.size(); i++)
    // {
    //     //snake.at(i).setPosition(sf::Vector2f((rootWin.getSize().x / 2) - (snake[i].getTexture()->getSize().x / 2), (rootWin.getSize().y / 2) - (snake[i].getTexture()->getSize().y / 2)));
    //     snake.at(i).setPosition(map[1][1].getPosition());
    // }

    snake.at(0).setPosition(map[1][1].getPosition());

    int snakeMoveDelay = 200;

    char myDir = 'N';

    // Set random apple position
    apples.at(0).setPosition(map[0][0].getPosition().x + 4 * mapTileSize.x, map[0][0].getPosition().y + 4 * mapTileSize.y);

    while (rootWin.isOpen())
    {
        if(gameOver)
        {
            gameOverImage.setFillColor(sf::Color::White);
        }

        headPosX = (snake.at(0).getPosition().x - map[0][0].getPosition().x) / mapTileSize.x;
        headPosY = (snake.at(0).getPosition().y - map[0][0].getPosition().y) / mapTileSize.y;

        applePosX = (apples.at(0).getPosition().x - map[0][0].getPosition().x) / mapTileSize.x;
        applePosY = (apples.at(0).getPosition().y - map[0][0].getPosition().y) / mapTileSize.y;

        //colission checks
        if (headPosX <= 0 || headPosX >= (mapWidth - 1) || headPosY <= 0 || headPosY >= (mapHeight - 1))
        {
            snakeVelocityX = 0;
            snakeVelocityY = 0;
            gameOver = true;
        }

        if (headPosX == applePosX && headPosY == applePosY)
        {
            
            //Play sound
            gwa.setBuffer(buffer);
            gwa.play();

            snake.push_back(snakeTile);
            snake.at(snake.size() - 1).setPosition(snake.at(0).getPosition());
            apples.pop_back();
            apples.push_back(apple);
            apples.at(0).setTexture(&appleTexture); // Reaply texture because the apple is a new element in the vector
            //generate random numbers
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distrX(1, mapWidth - 2); // define the range
            std::uniform_int_distribution<> distrY(1, mapHeight - 2); // define the range

            apples.at(0).setPosition(map[0][0].getPosition().x + distrX(gen) * mapTileSize.x, map[0][0].getPosition().y + distrY(gen) * mapTileSize.y);
        }

        // std::cout << "X: " << applePosX << "\n";
        // std::cout << "Y: " << applePosY << "\n";

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

        if (elapsed.asMilliseconds() >= snakeMoveDelay)
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
                    gameOver = false;
                    gameOverImage.setFillColor(sf::Color::Transparent);
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
                    // if ((elapsedInput.asMilliseconds() >= snakeMoveDelay))
                    // {
                    snake.push_back(snakeTile);
                    snake.at(snake.size() - 1).setPosition(snake.at(0).getPosition());
                    //clock1.restart();
                    //
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

        rootWin.draw(backgroundMap);

        for (int i = 0; i < mapWidth; i++)
        {
            for (int j = 0; j < mapHeight; j++)
            {
                rootWin.draw(map[i][j]);
            }
        }

        rootWin.draw(apples.at(0));

        for (int i = 0; i < snake.size(); i++)
        {
            rootWin.draw(snake.at(i));
        }

        rootWin.draw(text);

        rootWin.draw(gameOverImage);

        rootWin.display();
    }
    return 0;
}