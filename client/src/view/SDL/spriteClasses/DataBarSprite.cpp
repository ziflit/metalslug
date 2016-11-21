//
// Created by mfp on 21/11/16.
//

#include "DataBarSprite.h"

DataBarSprite::DataBarSprite(SDL_Renderer *renderer, Entity id) : Sprite(renderer) {
    this->sourceRect.w = 800;
    this->sourceRect.h = 100;
    this->setWidth(800);
    this->setHeight(600);
    this->set_position(0,100);
    this->setUpImage(path[id]);
    healthText = new TextBox(100, this->renderer, {255,0,0,1},12);
    scoreText = new TextBox(100, this->renderer, {255,0,0,1},12);
}

void DataBarSprite::handle(int health, int score) {
    this->healthText->changeText(health);
    this->scoreText->changeText(score);
}

void DataBarSprite::handle(struct event nuevoEvento) {}