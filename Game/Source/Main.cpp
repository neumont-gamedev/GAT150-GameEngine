#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

void f()
{
	static int i = 5;
	i++;
	std::cout << i << std::endl;
}


int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();
	
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared ptr so texture can be shared
	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("beast.png", engine->GetRenderer());
	//res_t<Font> font = 

	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetRenderer().DrawTexture(texture.get(), randomf(800), randomf(600), randomf(360));

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}
