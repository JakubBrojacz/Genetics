#include "Game.h"


Game::Game(NeuralNet* owner) : owner(owner)
{
}

double Game::startGame(status st, bool visibility)
{
	if (st == HUMAN)
	{
		engine = new Engine();
		while (engine->update());
		int tmp = engine->endGame();
		delete engine;
		engine = nullptr;
		return tmp;
	}
	else
	{
		srand(2); //always sratr the same game - for teaching
		aiengine = new AIEngine(visibility);
		float* s;
		s = new float[9]; //sensor vector
		bool* d;
		d = new bool[4]; //output vector - keyboard keys
		float* d_begin; //output in raw form
		d_begin = new float[4];
		for (int i = 0; i < 9; i++)
			s[i] = 0; //first sensor informations
		do
		{

			delete d_begin;
			d_begin = owner->output(s, 9); //gain next move
			for (int i = 0; i < 4; i++)
				if (d_begin[i] > 0.8) //convert float to bool
					d[i] = 1;
				else
					d[i] = 0;
			delete s;
			s=aiengine->update(d);  //gain new sensor vector
			
		} while (s[0]<100); //s[0]>=100 == game is lost
		double tmp = aiengine->endGame(); //get score
		delete aiengine;
		aiengine = nullptr;
		return tmp;
	}
	
}

Game::~Game()
{
	if (engine) delete engine; 
	if (aiengine) delete aiengine; 
}
