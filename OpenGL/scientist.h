#ifndef SCIENTIST_H_
#define SCIENTIST_H_

#include "humans.h"
#include "player.h" // Dodane dla dostępu do klasy Player

class Scientist : public Human
{
public:
    Scientist(modelImporter* importer, Physics* phys) : Human("resources/kleiner/klener.obj", importer, phys, glm::vec3(0.001, 0.1, 0.001))
    {
        double scale = 0.005;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    // Metoda do leczenia gracza
    void healPlayer(Player& player)
    {
        player.lives = 100; // Przywracanie pełnej liczby żyć
        std::cout << "Gracz został wyleczony do pełnego zdrowia!" << std::endl;
    }

    // Nadpisanie metody kolizji
    void collidedWithPlayer(Player& player)
    {
        healPlayer(player); // Wywołanie metody leczenia
    }
};

#endif
