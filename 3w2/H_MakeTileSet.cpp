#include "stdafx.h"
#include "H_MakeTileSet.h"
#include <sstream>
#include "Utilities.h"

MakeTileSet::MakeTileSet()
{
    amountTileFiles = 51;
    TileSize = 128;
	Size_DestinationFile = { TileSize, amountTileFiles*TileSize };
	

	SourceFName = "MakeTileSet\\Tile (";
	DestFName   = "Destination.png";
	
	FilePosition = 0;
	

	DestinationFile.create(Size_DestinationFile.x, Size_DestinationFile.y, sf::Color::Blue);
	

}

MakeTileSet::~MakeTileSet()
{
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


