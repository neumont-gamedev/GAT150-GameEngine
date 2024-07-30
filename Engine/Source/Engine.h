#pragma once

// ** core **
#include "ETime.h"

// ** systems **
// renderer
#include "Renderer.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Font.h"
#include "Model.h"
// input
#include "Input.h"
// audio
#include "Audio.h"

// ** math **
#include "Vector2.h"
#include "Random.h"
#include "MathUtils.h"
#include "Transform.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>
#include <cassert>

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput()		{ return *m_input; }
	Audio& GetAudio()		{ return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }

	Time& GetTime()			{ return *m_time;  }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time>		m_time;

	std::unique_ptr<Renderer>	m_renderer;
	std::unique_ptr<Input>		m_input;
	std::unique_ptr<Audio>		m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;
};

