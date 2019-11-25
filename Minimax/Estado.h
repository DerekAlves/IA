#pragma once

class Estado
{
public:
	unsigned posX;
	unsigned posY;

	Estado() { this->posX = 4; this->posY = 4; };

	Estado(unsigned x, unsigned y)
	{
		this->posX = x;
		this->posY = y;
	}

};
