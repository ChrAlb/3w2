#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;

class MakeTileSet 

{
private:
	
	sf::Image SourceFiles;
	sf::Image DestinationFile;

	int amountTileFiles;

	Vector2f Size_DestinationFile;
	Vector2f Size_SourceFiles;

	String SourceFName;
	String DestFName;
	String Path;

public:

	MakeTileSet();
	~MakeTileSet();

	void create_TilSetFile();


};
