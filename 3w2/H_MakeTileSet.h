#pragma once
#include <SFML\Graphics.hpp>
#include <string>


using namespace sf;

class MakeTileSet 

{
private:
	
	Image SourceFiles;
	Image DestinationFile;

	int amountTileFiles;

	int TileSize;
	int FilePosition;

	int hCounter;

	Vector2i Size_DestinationFile;
	Vector2i Size_SourceFiles;

	std::string SourceFName;
	std::string DestFName;
	
	
public:

	MakeTileSet();
	~MakeTileSet();

	void init_TileSetFile();
	void create_TilSetFile();

	void init_SpriteSheet();
	void create_SpriteSheet();

};
