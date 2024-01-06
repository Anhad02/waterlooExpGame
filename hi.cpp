#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Move Object Equal Time");

    sf::CircleShape object(20); // Example object (circle)

    sf::Vector2f pointA(100, 100); // Starting point
    sf::Vector2f pointB(500, 300); // Ending point

    float speed = 7.5f; // Fixed speed of the movement (pixels per second)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Calculate direction from A to B
        sf::Vector2f direction = pointB - pointA;

        // Normalize the direction (make it a unit vector)
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f normalizedDirection = direction / length;

        // Calculate the movement based on fixed speed and elapsed time
        float deltaTime = 1.0f / 60.0f; // Assuming 60 frames per second
        sf::Vector2f movement = speed * normalizedDirection * deltaTime;

        // Update object position
        object.move(movement);

        window.clear();
        window.draw(object);
        window.display();
    }

    return 0;
}
