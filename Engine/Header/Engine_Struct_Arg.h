#pragma once

struct Message
{
	bool	bArg1;
	bool	bArg2;

	int		iArg1;
	int		iArg2;

	float	fArg1;
	float	fArg2;

	Message() : bArg1(false), bArg2(false)
		, iArg1(0), iArg2(0), fArg1(0.0f), fArg2(0.0f) {}
};