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

	// !! this code is not neccessary, it just shows the contents of the file !!
	std::string buffer;
	File::ReadFile("json.txt", buffer);
	// show the contents of the json file
	std::cout << buffer << std::endl;

	// create json document from the json file contents
	rapidjson::Document document;
	Json::Load("json.txt", document);

	// read the data from the json
	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);

	// show the data
	std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;

	{
		// create texture, using shared ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("beast.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("arcadeclassic.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0, 1 });


		Transform t{ { 30, 30 } };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));
		
		while (!engine->IsQuit())
		{
			// update
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			// render
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			text->Draw(engine->GetRenderer(), 200, 200);
			//engine->GetRenderer().DrawTexture(texture.get(), 50, 50, 0);
			actor->Draw(engine->GetRenderer());


			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}
