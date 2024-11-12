#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_LevelText;
	Text m_ScoreText;
	Text m_AmmoText;
	Text m_HealthText;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	Text getScore();
	Text getAmmo();
	Text getHealth();

	void setLevel(String text);
	void setScore(String text);
	void setStart(String text);
	void setAmmo(String text);
	void setHealth(String text);
};