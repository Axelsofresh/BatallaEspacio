//Yonathan Monge
//Axel Flores Lara
//Primer Semestre 2023
//Algoritmos y estructuras de datos

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet {
public:
    /**
     * @brief Constructor de la clase.
     * @param pos La posición inicial de la bala.
     * @param spd La velocidad de la bala.
     */
    Bullet(sf::Vector2f pos, float spd): position(pos), speed(spd) {
        if (!texture.loadFromFile("/home/axel/Escritorio/reepos/BattleSpace./BattleSpace/Multimedia/bullet.png")) {
            return;
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos);
    }
    /**
     * @brief Actualiza la posición de la bala en función de su velocidad..
     */
    void update() {
        position.x += speed *0.02f;
        sprite.setPosition(position);
    }
    /**
     * @brief Indica si la bala ha salido de la pantalla.
     * @return True si la bala ha salido de la pantalla, False en caso contrario.
     */
    bool isOffScreen() {
        return position.x > 800;
    }

    sf::Sprite sprite;/**< El sprite de la bala. */

private:
    sf::Texture texture;/**< La textura de la bala. */
    sf::Vector2f position;/**< La posición de la bala. */
    float speed;/**< La velocidad de la bala. */
};

/**
 * @brief Clase que representa una nave espacial en el juego.
 *
 * La nave se puede mover hacia arriba y hacia abajo, y también puede disparar proyectiles.
 * La nave mantiene una lista de los proyectiles que ha disparado y actualiza su posición.
 */
class Spaceship {
public:

    /**
     * @brief Constructor de la clase Spaceship.
     *
     * Carga la textura de la nave y la configura en su posición inicial.
     *
     * @param window Referencia a la ventana de renderizado de SFML.
     */
    Spaceship(sf::RenderWindow& window) {
        if (!texture.loadFromFile("/home/axel/Escritorio/reepos/BattleSpace./BattleSpace/Multimedia/navee.png")) {
            return;
        }
        sprite.setTexture(texture);
        sprite.setPosition(100, 100);
        windowRef = &window;
    }
    /**
     * @brief Mueve la nave hacia arriba.
     */
    void moveUp() {
        sprite.move(0, -10);
    }
    /**
     * @brief Mueve la nave hacia abajo.
     */
    void moveDown() {
        sprite.move(0, 10);
    }
    /**
     * @brief Dispara un proyectil desde la posición actual de la nave.
     *
     * Crea un nuevo objeto de la clase Bullet con la posición actual de la nave y
     * velocidad 20, y lo agrega a la lista de proyectiles.
     */
    void shoot() {
        Bullet bullet(sprite.getPosition(), 20 );
        bullets.push_back(bullet);
    }
    /**
     * @brief Actualiza la posición de los proyectiles disparados.
     *
     * Actualiza la posición de todos los proyectiles disparados por la nave.
     * Si un proyectil ha salido de la pantalla, lo elimina de la lista.
     */
    void update() {
        for (auto& bullet : bullets) {
            bullet.update();
            if (bullet.isOffScreen()) {
                bullets.erase(bullets.begin());
            }
        }
    }
    /**
     * @brief Dibuja todos los proyectiles disparados en la pantalla.
     *
     * Dibuja todos los proyectiles disparados por la nave en la pantalla.
     */
    void drawBullets() {
        for (auto& bullet : bullets) {
            windowRef->draw(bullet.sprite);
        }
    }

    sf::Sprite sprite;/**< Sprite de la nave. */

private:
    sf::Texture texture;/**< Textura de la nave. */
    std::vector<Bullet> bullets;/**< Vector de proyectiles disparados por la nave. */
    sf::RenderWindow* windowRef;/**< Referencia a la ventana de renderizado de SFML. */
};
class Enemy {
public:
    sf::Sprite sprite;

    Enemy(sf::Texture& texture, sf::Vector2f position) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }
};
/**
 * @brief Clase que representa el juego principal
 *
 * Esta clase representa el juego principal. Permite al usuario seleccionar la dificultad
 * y luego iniciar una partida en ese nivel de dificultad.
 */
class Game {
public:
    /**
     * @brief Constructor de la clase Game
     *
     * @param videoMode Un objeto de la clase sf::VideoMode que contiene la resolución y la profundidad de bits del modo de video deseado.
     * @param windowTitle El título de la ventana del juego
     */
    Game(sf::VideoMode videoMode, std::string windowTitle): window(videoMode, windowTitle) {
        // crear los 3 botones de dificultad
        easyButton = sf::RectangleShape(sf::Vector2f(200, 50));
        easyButton.setPosition(300, 200);
        easyButton.setFillColor(sf::Color::Green);

        mediumButton = sf::RectangleShape(sf::Vector2f(200, 50));
        mediumButton.setPosition(300, 300);
        mediumButton.setFillColor(sf::Color::Yellow);

        hardButton = sf::RectangleShape(sf::Vector2f(200, 50));
        hardButton.setPosition(300, 400);
        hardButton.setFillColor(sf::Color::Red);

    }

    /**
     * @brief Inicia el bucle principal del juego
     *
     * Este método se encarga de mantener el bucle principal del juego, procesando los eventos, actualizando el estado del juego y
     * renderizando los elementos en la pantalla.
     */
    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }
    
    /**
     * @brief Procesa los eventos del usuario
     *
     * Este método se encarga de procesar los eventos del usuario, como el cierre de la ventana o la selección de una dificultad.
     */
private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    startGame("Modo Fácil");
                }
                else if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    startGame("Modo Medio");
                }
                else if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    startGame("Modo Difícil");
                }
            }
        }
    }
public:
    void startGame(std::string gameMode) {

        sf::RenderWindow gameWindow(sf::VideoMode(800, 600), gameMode);
        Spaceship spaceship(gameWindow);


        sf::Texture enemyTexture;
        enemyTexture.loadFromFile("/home/axel/Escritorio/reepos/BattleSpace./BattleSpace/Multimedia/navee.png");
        std::vector<Enemy> enemies;
        enemies.emplace_back(enemyTexture, sf::Vector2f(700.f, gameWindow.getSize().y / 2.f)); // Create enemy

        sf::CircleShape circle(50.f);
        circle.setPosition(200.f, 200.f);
        circle.setFillColor(sf::Color::Red);

        //bucle principal para la pantalla de juego
        while (gameWindow.isOpen()) {
            sf::Event event;

            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                }
                else if(event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W) {
                        spaceship.moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::S) {
                        spaceship.moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Space) {
                        spaceship.shoot();
                    }
                }

            }
            spaceship.update();
            gameWindow.clear();
            gameWindow.draw(spaceship.sprite);
            spaceship.drawBullets();
            gameWindow.display();
        }
    }
    /**
     * @brief Actualiza el estado del juego
     *
     * Este método se encarga de actualizar el estado del juego en cada iteración del bucle principal.
     */
    void update() {}

    /**
     * @brief Renderiza los elementos en la pantalla
     *
     * Este método se encarga de renderizar los elementos en la pantalla en cada iteración del bucle principal.
     */
    void render() {
        window.clear();
        window.draw(easyButton);
        window.draw(mediumButton);
        window.draw(hardButton);
        window.display();
    }

    sf::RenderWindow window;///< La ventana del juego
    sf::RectangleShape easyButton;///< El botón de dificultad fácil
    sf::RectangleShape mediumButton;///< El botón de dificultad media
    sf::RectangleShape hardButton;///< El botón de dificultad dificil
};

/**
 * @brief Función principal que inicia el juego.
 *
 * La función crea el objeto del juego y lo ejecuta.
 *
 * @return Entero que indica el éxito o fracaso del programa.
 */
int main() {
    Game game(sf::VideoMode(800, 600), "Pantalla Principal");
    game.run();
    return 0;
}
//commit de prueba porque estoy como locoooooooooooooooooooooo
//prueeebaaaaaa