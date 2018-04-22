#include "Generation.h"




Object * Generation::ChooseObject()
{
	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += wyn[i];
	int choosen = rand()%sum;
	sum = 0;
	for (int i = 0; i < num; i++)
	{
		sum += wyn[i];
		if (sum >= choosen)
			return gen[i];
	}	
	return gen[num-1];
}

Generation::Generation(int num): num(num)
{
	std::cout << "Initiating..." << std::endl;
	for (int i = 0; i < num; i++)
	{
		wyn.push_back(0.0);
		Object* tmp = new Object(9,18,4);
		gen.push_back(tmp);
	}
	mutationRate = 0.1;
}

void Generation::play()
{
	std::cout << "Playing..." << std::endl;
	for (int i = 0; i < num; i++)
	{
		if (i % 10 == 9)
			std::cout << "Objekt " << i + 1 << std::endl;
		wyn[i] = gen[i]->graj(0);
		//if you want to see best objects during training
		//if (wyn[i] > 300)
		//	gen[i]->graj(1);
	}
		
}

void Generation::nextGen()
{
	sort();
	srand(time(NULL)); // because in game.cpp when starting new game we call srand(2)
	std::cout << "Creating new generation..." << std::endl;
	std::vector < Object* > nextgen;
	nextgen.push_back(gen[0]);
	std::cout << "Mutating parents..." << std::endl;
	for (int i = 1; i < num/2; i++)
	{
		Object* tmp = new Object(*(ChooseObject()));
		if (!tmp)
			std::cout << "ERROR: Generation::nextGen - awful copying constructor of Object" << std::endl;
		tmp->mutate(mutationRate);
		nextgen.push_back(tmp);
	}
	std::cout << "Breeding children..." << std::endl;
	for (int i = num / 2; i < num; i++)
	{
		Object* tmp = ChooseObject()->crossover(ChooseObject());
		if (!tmp)
			std::cout << "ERROR: Generation::nextGen - awful copying crossover of Object" << std::endl;
		tmp->mutate(mutationRate);
		nextgen.push_back(tmp);
	}
	std::cout << "Killing old units..." << std::endl;
	for (int i = 1; i < num; i++)
		delete gen[i];
	for (int i = 1; i < num; i++)
		gen[i] = nextgen[i];
}

void Generation::sort()
{
	//std::cout << "Sorting..." << std::endl;
	for(int i=0;i<num;i++)
		for(int j=i+1;j<num;j++)
			if (wyn[i] < wyn[j])
			{
				Object* tmp = gen[i];
				gen[i] = gen[j];
				gen[j] = tmp; 
				double t = wyn[i];
				wyn[i] = wyn[j];
				wyn[j] = t;
			}
}


int Generation::maks()
{
	int m = 0;
	for (int i = 1; i < num; i++)
		if (wyn[i] > wyn[m])
			m = i;
	return m;
}

double Generation::score(int i)
{
	return wyn[i];
}

void Generation::visual(int i)
{
	gen[i]->graj(1);
}

void Generation::save(std::string file)
{
	std::fstream f;
	f.open(file, std::ios::out, std::ios::trunc);
	for (int i = 0; i < num; i++)
		f << wyn[i] << std::endl;
	for (int i = 0; i < num; i++)
		f << (*gen[i]) << std::endl;
	f.close();
}

void Generation::load(std::string file)
{
	std::fstream f;
	f.open(file, std::ios::in);
	for (int i = 0; i < num; i++)
		f >> wyn[i];
	for (int i = 0; i < num; i++)
		f >> (*gen[i]);
	f.close();
}
