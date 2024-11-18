#include "stdafx.h"
#include "Shuttle.h"
#include "TextureHolder.h"
#include <iostream>

Shuttle::Shuttle()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/Shuttle.png"));

}






