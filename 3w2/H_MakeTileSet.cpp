#include "stdafx.h"
#include "H_MakeTileSet.h"
#include <sstream>
#include "Utilities.h"

MakeTileSet::MakeTileSet()
{
	SourceFName = "";
	DestFName = "";
}

MakeTileSet::~MakeTileSet()
{
}

void MakeTileSet::init_TileSetFile()
{

	amountTileFiles = 51;
	TileSize = 128;
	Size_DestinationFile = { TileSize, amountTileFiles * TileSize };


	SourceFName = "MakeTileSet\\Tile (";
	DestFName = "Destination.png";

	FilePosition = 0;


	DestinationFile.create(Size_DestinationFile.x, Size_DestinationFile.y, sf::Color::Blue);

}

void MakeTileSet::create_TilSetFile()


{
	

	for (int i = 0; i < amountTileFiles; i++)
	{
		
		std::stringstream ss;
		ss << i;
		std::string str = ss.str();
		

		SourceFName = Utils::GetWorkingDirectory() + SourceFName + str + ").png";
		if (!SourceFiles.loadFromFile(SourceFName))
		{
			printf("Error");
			
		}
		else
		{
			DestinationFile.copy(SourceFiles, 0,FilePosition ,{ 0,0,TileSize,TileSize }, false);
			
		}

		SourceFName = "MakeTileSet\\Tile (";
		FilePosition = FilePosition + TileSize;
	}
	
	DestinationFile.saveToFile("GroundTileSheet.png");

}

void MakeTileSet::init_SpriteSheet()
{
	SourceFName = Utils::GetWorkingDirectory() + "\\Ressourcen\\Enemies\\slice 400x400 enemy_entity_000_die.png";
	DestFName = "Destination.png";

	amountTileFiles = 33;
	
	TileSize = 300;

	Size_DestinationFile = { amountTileFiles * TileSize, TileSize };


	FilePosition = 0;

    DestinationFile.create(Size_DestinationFile.x, Size_DestinationFile.y, sf::Color::Blue);

	hCounter = 0;
}

void MakeTileSet::create_SpriteSheet()
{
	
	if (!SourceFiles.loadFromFile(SourceFName))
	{
		printf("Error");

	}
	hCounter = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DestinationFile.copy(SourceFiles, FilePosition, 0, { 50 + 400 * hCounter,55 + 400 * i,TileSize,TileSize }, false);
			FilePosition = FilePosition + 300;
			hCounter++;
		}

		hCounter = 0;

	}
		
	DestinationFile.saveToFile("temp.png");
}


