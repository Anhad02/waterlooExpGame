#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Sprite Map Outline Example");

    // Load sprite map texture from PNG file
    sf::Texture spriteMapTexture;
    if (!spriteMapTexture.loadFromFile("Charactervector.png")) {
        // Print an error message
        return -1;
    }

    // Create sprite for the entire sprite map
    sf::Sprite spriteMap(spriteMapTexture);

    // Define the region (rectangle) of the sprite map for the specific sprite you want
    sf::IntRect spriteRect(0, 0, 5, 5); // Adjust the coordinates and dimensions based on your sprite map

    // Set the texture rectangle for the specific sprite
    spriteMap.setTextureRect(spriteRect);

    // Create an image to store the alpha mask
    sf::Image alphaMask = spriteMapTexture.copyToImage();
    alphaMask.createMaskFromColor(sf::Color::Transparent, 0); // Create a mask based on transparency

    // Create a texture from the alpha mask
    sf::Texture maskTexture;
    maskTexture.loadFromImage(alphaMask);

    // Create a sprite for the outline using the mask texture
    sf::Sprite outlineSprite(maskTexture);
    outlineSprite.setColor(sf::Color::White); // Set the color of the outline

    // Set the position of the outline sprite
    outlineSprite.setPosition(100.0f, 100.0f); // Adjust the position based on your needs

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        // Draw only the outline sprite
        window.draw(outlineSprite);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
