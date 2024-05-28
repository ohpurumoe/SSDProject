#pragma once
#include "..\TestShell\Command.h"

#ifdef CREATEDLL_EXPORTS
#define MYDLL_DECLSPEC __declspec(dllexport)
#else
#define MYDLL_DECLSPEC __declspec(dllimport)
#endif

extern "C" {
	Command* getScenario(const string& str, IReceiver* receiver);
}
