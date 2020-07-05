#pragma once

void clearTerminal(void)
{
	printf("\e[1;1H\e[2J");
}

float randRangeFloat(const float min, const float max)
{
	return ((max-min)*((float)rand()/RAND_MAX))+min;
}

int randRange(const int min, const int max)
{
	return (rand()%(max-min))+min;
}

void init(const uint winXlen, const uint winYlen)
{
	srand(time(NULL));
	gfx_init(winXlen, winYlen);
	img_init();
	text_init();
	//net_init();
}
