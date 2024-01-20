#include "headers/Policy71.h"
#include "headers/Global.h"
#include "./headers/Player.h"
#include <iostream>
#include <cmath>

Policy71::Policy71()
{
    sf::FloatRect bulletBounds = bullet.getLocalBounds();
    bullet.setOrigin(bulletBounds.left + bulletBounds.width / 2.0, bulletBounds.top + bulletBounds.height / 2.0);
    bullet.setPosition(screen_width, 0);
    enemy_speed = 0.075;
    for (int i = 1; i <= 4; i++)
    {
        if (!bullet_texture[i - 1].loadFromFile("./Textures/chakri" + std::to_string(i) + ".png"))
        {
            std::cerr << "Texture not loaded";
        }
    }
    bullet.scale(0.2, 0.2f);
    bullet.setTexture(bullet_texture[0]);
    animationFrames = 0.0;

    sf::FloatRect policyBounds = policy_text.getLocalBounds();
    policy_text.setOrigin(policyBounds.left + policyBounds.width / 2.0, policyBounds.top + policyBounds.height / 2.0);
    policy_text.setFont(font);
    policy_text.setString("Policy\n  71");
    policy_text.setCharacterSize(20);
    policy_text.setColor(sf::Color::White);
    policy_text.setStyle(1);
    policy_text.setPosition(bullet.getPosition());
}

void Policy71::movement(Player &player)
{
    animationFrames += 0.002 * dt;
    bullet.setTexture(bullet_texture[(int)floor(animationFrames)]);
    if (animationFrames >= 3.5)
    {
        animationFrames = 0;
    }
    if (bullet.getPosition().y >= (screen_length))
    {
        bullet.setPosition(screen_width, 0);
    }
    if (bullet.getPosition().x == (screen_width))
    {
        calculateConstants(player);
    }
    bullet.move(moved_distance);
    if (bullet.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds()))
    {
        deathcase = 3;
        death();
        previous_state = game_state;
        game_state = 0;
    }
    sf::Vector2f offset(12.5f, 12.5f);
    policy_text.setPosition(bullet.getPosition() + offset);
}

void Policy71::draw()
{
    window.draw(bullet);
    window.draw(policy_text);
}

void Policy71::reset()
{
    bullet.setPosition(screen_width, 0);
}

void Policy71::death()
{
    main_song.stop();
    if (death_sound.getStatus() != sf::Music::Playing)
    {
        death_sound.openFromFile("./Sounds/death.ogg");
    }
    death_sound.play();
}

void Policy71::calculateConstants(Player &player)
{
    direction = player.getPos() - bullet.getPosition();
    length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    moved_distance = normalizedDirection * dt * enemy_speed;
}
