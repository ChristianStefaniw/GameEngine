#include "States.h"

bool States::bPaused = false;

bool States::GetPausedState()
{
	return bPaused;
}

void States::SetPausedState(bool bState)
{
	bPaused = bState;
}
