#include "DataBarSprite.h"

DataBarSprite::DataBarSprite(SDL_Renderer *renderer, Entity id) : Sprite(renderer) {
    this->sourceRect.w = 800;
    this->sourceRect.h = 100;
    this->setWidth(800);
    this->setHeight(100);
    this->set_position(0,0);
    this->setUpImage(path[id]);
    healthText = new TextBox(100, this->renderer, {255,255,0,1},12);
    scoreText = new TextBox(100, this->renderer, {255,255,0,1},12);
    healthText->setPosition(healthX[id],healthY[id]);
    scoreText->setPosition(scoreX[id],scoreY[id]);
}

void DataBarSprite::updateHealth(int health) {
    this->healthText->changeText(health);
}

void DataBarSprite::updateHealth(string health) {
    this->healthText->changeText(health);
}

void DataBarSprite::updateScore(int score) {
    this->scoreText->changeText(score);
}

void DataBarSprite::handle(struct event nuevoEvento) {}

void DataBarSprite::actualizarDibujo() {
    Sprite::actualizarDibujo();
    healthText->renderize();
    scoreText->renderize();
}