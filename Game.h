#pragma once

#include "Engine.h"
#include "AIEngine.h"
#include "Object.h"
#include "NeuralNet.h"
#include <iostream>
#include <vector>

enum status {AI,HUMAN};

class Game
{
private:
	Engine* engine;
	AIEngine* aiengine;
	NeuralNet* owner;
public:
	Game(NeuralNet* owner = nullptr);
	double startGame(status = HUMAN, bool visibility = 1);
	~Game();
};