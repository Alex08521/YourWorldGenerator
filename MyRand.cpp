#include "pch.h"
#include "MyRand.h"
#include <iostream>

MyRand::MyRand()
{

	iterGlobRand = 1;
	previousGlobRand = 0;
	previous2GlobRand = 0;
	previous3GlobRand = 0;
	checkerGlobRand = 0;
	char buf[sizeof(int*) * 2 + 3];
	snprintf(buf, sizeof(buf), "%p", &bGlobRand);
	int b = 1;
	for (int i = 8; i > 2; i--)
	{
		bGlobRand = bGlobRand + ((buf[i] - '0') * b);
		b = b * 16;
	}
	bGlobRand = bGlobRand / 10;

	snprintf(buf, sizeof(buf), "%p", &cGlobRand);
	b = 1;
	for (int i = 8; i > 2; i--)
	{
		cGlobRand = cGlobRand + ((buf[i] - '0') * b);
		b = b * 16;
	}
	cGlobRand = cGlobRand / 10;
	
	snprintf(buf, sizeof(buf), "%p", &dGlobRand);
	b = 1;
	for (int i = 8; i > 2; i--)
	{
		dGlobRand = dGlobRand + ((buf[i] - '0') * b);
		b = b * 16;
	}
	dGlobRand = dGlobRand / 10;

	snprintf(buf, sizeof(buf), "%p", &eGlobRand);
	b = 1;
	for (int i = 8; i > 2; i--)
	{
		eGlobRand = eGlobRand + ((buf[i] - '0') * b);
		b = b * 16;
	}
	eGlobRand = eGlobRand / 10;
}

unsigned int MyRand::randomize(unsigned int lRand)
{
	unsigned int resRand = 0;
	if (lRand == 0)
	{
		return 0;
	}

	else if (lRand == 1)
	{
		return 1;
	}

	else if (lRand == 2)
	{
		if (previousGlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((dGlobRand + (iterGlobRand*3 + previousGlobRand)) % lRand) + 1;
				if (resRand != previousGlobRand) done = true;
				dGlobRand++;
			}
		}
		previousGlobRand = resRand;
		checkerGlobRand = 2;
		iterGlobRand++;
		eGlobRand += iterGlobRand;
		return (resRand);
	}

	else if (lRand == 3)
	{
		if (previousGlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((dGlobRand + (iterGlobRand*3 + previousGlobRand)) % lRand) + 1;
				if (resRand != previousGlobRand) done = true;
				dGlobRand += 246;
			}
		}
		if (previous2GlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((cGlobRand + (iterGlobRand*3 + previous2GlobRand)) % lRand) + 1;
				if (resRand != previous2GlobRand) done = true;
				cGlobRand += 156;
			}
		}
		switch (checkerGlobRand)
		{
		case 1:
			previousGlobRand = resRand;
			checkerGlobRand = 2;
			break;
		case 2:
			previous2GlobRand = resRand;
			checkerGlobRand = 1;
			break;
		}
		iterGlobRand++;
		eGlobRand += iterGlobRand;
		return (resRand);
	}
	else
	{
		resRand = ((eGlobRand / iterGlobRand*3 + previousGlobRand + previous2GlobRand + previous3GlobRand) % lRand) + 1;
		if (previousGlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((dGlobRand + (iterGlobRand*3 + previousGlobRand)) % lRand) + 1;
				if (resRand != previousGlobRand) done = true;
				dGlobRand += previousGlobRand;
			}
		}
		if (previous2GlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((cGlobRand + (iterGlobRand*3 + previous2GlobRand)) % lRand) + 1;
				if (resRand != previous2GlobRand) done = true;
				cGlobRand += previous2GlobRand;
			}
		}
		if (previous3GlobRand == resRand)
		{
			bool done = false;
			while (done == false)
			{
				resRand = ((bGlobRand + (iterGlobRand*3 + previous3GlobRand)) % lRand) + 1;
				if (resRand != previous3GlobRand) done = true;
				bGlobRand += previous3GlobRand;
			}
		}
		switch (checkerGlobRand)
		{
		case 1:
			previousGlobRand = resRand;
			checkerGlobRand = 2;
			break;
		case 2:
			previous2GlobRand = resRand;
			checkerGlobRand = 3;
			break;
		case 3:
			previous3GlobRand = resRand;
			checkerGlobRand = 1;
			break;
		}
		iterGlobRand++;
		eGlobRand += iterGlobRand;
		while(resRand > lRand)
		{
			resRand--;
		}
		return (resRand);
	}
}