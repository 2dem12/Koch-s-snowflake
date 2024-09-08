#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include<chrono>
#include<thread>
// using namespace sf;
using namespace std;
// #define float long float

vector<vector<pair<long double, long double>>> a = {{{0.f, 70000.f}, {50000.f, 0.f}, {100000.f, 70000.f}}};

void build(int sc) {
    a.push_back({});
    for (int i = 0; i < a[sc].size(); i++) {
        auto [x2, y2] = a[sc][i+1];
        if (i == a[sc].size() - 1) {
            x2 = a[sc][0].first;
            y2 = a[sc][0].second;
        }
        auto [x1, y1] = a[sc][i];
        int x = x1 + (x2 - x1) / 3;
        int y = y1 + (y2 - y1) / 3;
        int x3 = (x1 - x) * (-0.5) - (y1 - y) * sqrt(3) / 2 + x;
        int y3 = (x1 - x) * sqrt(3) / 2 - (y1 - y) * (0.5) + y;
        int x4 = (x - x3) * 0.5 + (y - y3) * sqrt(3) / 2 + x3;
        int y4 = -(x - x3) * sqrt(3) / 2 + (y - y3) * 0.5 + y3;

        a[sc+1].push_back({x1, y1});
        a[sc+1].push_back({x, y});
        a[sc+1].push_back({x3, y3});
        a[sc+1].push_back({x4, y4});
    }
}

int main() {
    int sc = 0;
    int limit = 8;
    for (int i = 0; i < limit; i++) build(i);


    sf::RenderWindow window(sf::VideoMode(100000, 100000), "SFML");
    sf::View view = window.getDefaultView();
    float moveSpeed = 30.0f;
    // view.zoom(0.0001f);
    for (int i = 0; i < 37; i++) {
        view.zoom(1.15f);
        view.move(0, 1000);
        view.move(1200, 0);
    }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {if (event.type == sf::Event::Closed) window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (sc < limit) {
                sc++;
                this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (sc > 0) {
                sc--;
                this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.zoom(0.9f);
            this_thread::sleep_for(std::chrono::milliseconds(50));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.zoom(1.1f);
            this_thread::sleep_for(std::chrono::milliseconds(50));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0, -moveSpeed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0, moveSpeed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(-moveSpeed, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(moveSpeed, 0);
        }


        window.setView(view);
        window.clear();
        for (int i = 0; i < a[sc].size(); i++) {
        // for (int i = 0; i < 6; i++) {
            auto [x1, y1] = a[sc][i];
            auto [x2, y2] = a[sc][(i+1) % a[sc].size()];
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x1, y1)),
                sf::Vertex(sf::Vector2f(x2, y2))
            };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }
    return 0;
}