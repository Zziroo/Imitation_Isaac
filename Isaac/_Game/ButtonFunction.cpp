#include "MainConfig.h"
#include "ButtonFunction.h"

void ButtonFunction::QuitProgram(ArgumentFuncPtr* argFunc)
{
	PostQuitMessage(0);
}
