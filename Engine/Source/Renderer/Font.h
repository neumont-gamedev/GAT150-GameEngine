#pragma once
#include "../Resources/Resource.h"
#include <SDL_ttf.h>
#include <string>

class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, int fontSize);

	// allow class access to private members
	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };
};