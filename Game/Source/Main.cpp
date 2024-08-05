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
	res_t<Font> font = ResourceManager::Instance().Get<Font>("arcadeclassic.ttf", 12);
	std::unique_ptr<Text> text = std::make_unique<Text>(font);
	text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0, 1 });
	
	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		text->Draw(engine->GetRenderer(), 200, 200);
		engine->GetRenderer().DrawTexture(texture.get(), 50, 50, 0);

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}
