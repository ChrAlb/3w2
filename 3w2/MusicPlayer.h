#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

namespace Musik
{
	enum ID
	{
		Intro,
	};
}



class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();

	void						play(Musik::ID theme);
	void						stop();

	void						setPaused(bool paused);
	void						setVolume(float volume);


private:
	sf::Music							mMusic;
	std::map<Musik::ID, std::string>	mFilenames;
	float								mVolume;
};