#include "headers/Psych.h"
#include "headers/Global.h"
#include "./headers/Player.h"

Psych::Psych()
{
    if (!psych_texture.loadFromFile("./Textures/depression.png"))
    {
        std::cerr << "Texture not loaded";
    }
    psych_enemy.setTexture(psych_texture);
    psych_enemy.setScale(0.12f, 0.12f);
    psych_enemy.setPosition(-800.0, 200);
    enemy_speed = -800.0;
    random_y = 0;
}

void Psych::movement(Player &player)
{
    if (enemy_speed >= screen_width)
    {
        enemy_speed = -screen_width;
        random_y = (rand() % 3 - 1);
    }
    psych_enemy.setPosition(enemy_speed, 200.0 + 150 * sin(enemy_speed / 65) + 100 * random_y);
    if (psych_enemy.getGlobalBounds().intersects(player.getPlayer().getGlobalBounds()))
    {
        deathcase = 2;
        death();
        previous_state = game_state;
        game_state = 0;
    }
}

void Psych::draw()
{
    window.draw(psych_enemy);
    decrementTimer();
}

void Psych::death()
{
    main_song.stop();
    if (death_sound.getStatus() != sf::Music::Playing)
    {
        death_sound.openFromFile("./Sounds/death.ogg");
    }
    death_sound.play();
}

void Psych::decrementTimer()
{
    enemy_speed += 0.1 * dt;
}

void Psych::reset()
{
    psych_enemy.setPosition(-800.0, 200);
    random_y = (rand() % 3 - 1);
    enemy_speed = -800.0;
}
