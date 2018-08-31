#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		TitleScreen,
		Player,
		Enemy,
		Level1Bg,
		Level2Bg,
		Tileset1,
		Tileset2,
		Tree,
		Bullet,
		FinishLine,
		Hufeisen,
		
	};
}

namespace Shaders
{
	enum ID
	{
		
	};
}

namespace Fonts
{
	enum ID
	{
		Arial,
		ComicS,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Explosion,
		Jump,
		Colt,
	};
}



// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
