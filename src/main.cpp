#include "system/SBEngine.h"
#include <chrono>

int main(int argc, char* argv[])
{
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;

	double frame_time = 1.0f / 60.0f;

	pEngine = new Engine();

	while (pEngine && pEngine->running)
	{
		start = std::chrono::high_resolution_clock::now();
		pEngine->Update(frame_time);
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms = end - start;
		frame_time = ms.count() / 1000.0;
	}
	delete pEngine;
	return 0;
}
