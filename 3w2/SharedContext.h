#pragma once
#include "Window.h"
#include "EventManager.h"
#include "FontManager.h"
#include "GUI_Manager.h"
#include "TextureManager.h"

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void						load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void						load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource&					get(Identifier id);
	const Resource&				get(Identifier id) const;


private:
	void						insertResource(Identifier id, std::unique_ptr<Resource> resource);


private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"



class Map;

struct SharedContext {
	SharedContext() :
		m_wind(nullptr),
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_fontManager(nullptr),
		
		m_gameMap(nullptr),
		m_guiManager(nullptr) {}

	Wind* m_wind;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	FontManager* m_fontManager;
	
	Map* m_gameMap;
	GUI_Manager* m_guiManager;
	
};