#include "stdafx.h"
#include "H_MakeTileSet.h"

MakeTileSet::MakeTileSet()
{
   amountTileFiles = 20;

	Size_DestinationFile = {25, amountTileFiles*25};
	Size_SourceFiles = { 25,25 };

	SourceFName = "xy.png";
	DestFName   = "Destination.png";
	Path = "MakeTileSet/";

	DestinationFile.create(Size_DestinationFile.x, Size_DestinationFile.y, sf::Color::Blue);
	

}

MakeTileSet::~MakeTileSet()
{
}

void MakeTileSet::create_TilSetFile()
{
}
