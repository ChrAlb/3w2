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

	Vector2i Size_DestinationFile;
	Vector2i Size_SourceFiles;

	std::string SourceFName;
	std::string DestFName;
	
	
public:

	MakeTileSet();
	~MakeTileSet();

	void create_TilSetFile();

	

};