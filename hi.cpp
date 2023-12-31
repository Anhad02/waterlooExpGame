#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow& window) : window(window) {}

    void run() {
        while (window.isOpen()) {
            handleEvents();
            draw();
        }
    }

    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text level1Text;
    sf::Text level2Text;
    sf::Text level3Text;

    void setup() {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
            return;
        }

        titleText.setFont(font);
        titleText.setString("Game Menu");
        titleText.setCharacterSize(40);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(150.f, 50.f);

        level1Text.setFont(font);
        level1Text.setString("Level 1");
        level1Text.setCharacterSize(30);
        level1Text.setFillColor(sf::Color::White);
        level1Text.setPosition(200.f, 150.f);

        level2Text.setFont(font);
        level2Text.setString("Level 2");
        level2Text.setCharacterSize(30);
        level2Text.setFillColor(sf::Color::White);
        level2Text.setPosition(200.f, 200.f);

        level3Text.setFont(font);
        level3Text.setString("Level 3");
        level3Text.setCharacterSize(30);
        level3Text.setFillColor(sf::Color::White);
        level3Text.setPosition(200.f, 250.f);
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
    }

    void handleMouseClick(int x, int y) {
        if (level1Text.getGlobalBounds().contains(x, y)) {
            std::cout << "Level 1 selected\n";
            // Add code to start Level 1
        } else if (level2Text.getGlobalBounds().contains(x, y)) {
            std::cout << "Level 2 selected\n";
            // Add code to start Level 2
        } else if (level3Text.getGlobalBounds().contains(x, y)) {
            std::cout << "Level 3 selected\n";
            // Add code to start Level 3
        }
    }

    void draw() {
        window.clear();

        window.draw(titleText);
        window.draw(level1Text);
        window.draw(level2Text);
        window.draw(level3Text);

        window.display();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu");

    Menu menu(window);
    menu.setup();
    menu.run();

    return 0;
}
