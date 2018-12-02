#pragma once
#include "Window.h"
#include "EventManager.h"


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
struct SharedContext{
	SharedContext():
		m_wind(nullptr),
		m_eventManager(nullptr),
		m_gui(nullptr),
		
		//m_entityManager(nullptr),
		m_gameMap(nullptr){}

	Wind* m_wind;
	EventManager* m_eventManager;
	GUI_Manager* m_gui;
	
	//EntityManager* m_entityManager;
	Map* m_gameMap;
	
};