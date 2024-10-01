#pragma once

using namespace sf;

class Engine
{
private:
	Player p;

	Enemy e;

	Gun g;

	TextureHolder Th;

	LevelLoader l;

	Arena a;

public:
	Engine();

	void run();
};