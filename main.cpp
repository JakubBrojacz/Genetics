#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Object.h"
#include "Generation.h"
#include <iostream>
#include <sstream>

void human()
{
	Game game;
	game.startGame();
}

void hmmm()
{
	/*
	int a[5] = { 9, 13,13,13, 5 };
	Object obj(5,a);
	Object obj2(5, a);
	std::cout << "Object 1:" << std::endl;
	for(int i=0;i<10;i++)
		std::cout << obj.graj() << std::endl;
	std::cout << "Object 2:" << std::endl;
	for (int i = 0; i<10; i++)
		std::cout << obj2.graj() << std::endl;

	std::cin >> a[0];
	*/
}

void hmm2()
{
	int gen_number = 0;
	Generation gen(200);
	gen.play();
	while (true)
	{
		std::cout << "Generation number: " << gen_number++ << ", max score:" << gen.score(gen.maks()) << std::endl;
		//if (i % 10 == 0)
		{
			gen.visual(gen.maks());
			//std::cout << "Another? (Y/N) ";
			//std::cin >> a;
			//if (a == 'N')
				//break;
		}
		std::ostringstream ss;
		ss << gen_number;
		gen.save("Generacja_" + ss.str() + ".txt");
		gen.nextGen();
		gen.play();
	}
	std::cout << "End...";

	gen.visual(gen.maks());
}

void load()
{
	Generation gen(200);
	std::cout << "Podaj nazwe pliku:" << std::endl;
	std::string fileName;
	std::cin >> fileName;
	gen.load("fileName");
	gen.visual(gen.maks());

	int gen_number = 3;
	gen.play();
	while (true)
	{
		std::cout << "Generation number: " << gen_number++ << ", max score:" << gen.score(gen.maks()) << std::endl;
		{
			//gen.visual(gen.maks());
		}
		std::ostringstream ss;
		ss << gen_number;
		gen.save("Generacja_" + ss.str() + ".txt");
		gen.nextGen();
		gen.play();
	}
}

int main()
{
	srand(time(NULL));
	int a;
	std::cout << "JAki tryp? (1 - human; 2 - single object test; 3 - start teaching; 4 - load from file)" << std::endl;
	std::cin >> a;
	switch (a)
	{
	case 1:
		human();
		break;
	case 2:
		hmmm();
		break;
	case 3:
		hmm2();
		break;
	case 4:
		load();
		break;
	}
	return 0;
}