#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();


	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}
