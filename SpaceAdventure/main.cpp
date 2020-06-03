#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>


using namespace sf;
//base class
class raketa {
protected:
	Texture texture;
	Sprite sprite;
public:
	virtual void movement() = 0;//purely virtual funtion for moving
};
//heir class
class space_raketa : public raketa
{
protected:
	float speed;
public:
	virtual Sprite get_sprite() = 0;
};
// the main class is the heir of the two
class raketa_shatle :public space_raketa
{
public:
	raketa_shatle(std::string tmp) {
		texture.loadFromFile(tmp);
		sprite.setTexture(texture);
		sprite.setPosition(800, 50);//set the position
		speed = 5;//set the rocket speed
	}
	void movement() {
		//movement for spaceship in the game
		if (Keyboard::isKeyPressed(Keyboard::Right))
			sprite.move(speed, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			sprite.move(-speed, 0);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			sprite.move(0, -speed);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			sprite.move(0, speed);
	}
	Sprite get_sprite() {
		return sprite;//get sprite for drawing in the main window
	}
	void posadka() {
		sprite.move(0, -3.5);
	}
	void ulet() {
		sprite.move(0, -5);
	}
};

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "LUNA!", sf::Style::Fullscreen);//make a full-screen window
	window.setFramerateLimit(60);//set the frame rate per second

	Music end_music, open_music, gimn;//music
	//download the files
	end_music.openFromFile("images/imagine.flac");
	open_music.openFromFile("images/opening.flac");
	gimn.openFromFile("images/ukraine.flac");
	//set the volume
	end_music.setVolume(50);
	open_music.setVolume(50);
	gimn.setVolume(50);
	open_music.play();//playing start music

	sf::SoundBuffer Tcosmonavts_in_moon, Tpilot_posadka, Tshatle_in_moon, Tshatle_in_space, Tshatle_to_raketa, Tzadanie;//buffer for audiofiles
	//download the files
	Tcosmonavts_in_moon.loadFromFile("images/cosmonavts_in_moon.ogg");
	Tpilot_posadka.loadFromFile("images/pilot_posadka.ogg");
	Tshatle_in_moon.loadFromFile("images/shatle_in_moon.ogg");
	Tshatle_in_space.loadFromFile("images/shatle_in_space.ogg");
	Tshatle_to_raketa.loadFromFile("images/shatle_to_raketa.ogg");
	Tzadanie.loadFromFile("images/zadanie.ogg");
	//sound variables
	sf::Sound cosmonavts_in_moon, pilot_posadka, shatle_in_moon, shatle_in_space, shatle_to_raketa, zadanie;
	cosmonavts_in_moon.setBuffer(Tcosmonavts_in_moon);
	pilot_posadka.setBuffer(Tpilot_posadka);
	shatle_in_moon.setBuffer(Tshatle_in_moon);
	shatle_in_space.setBuffer(Tshatle_in_space);
	shatle_to_raketa.setBuffer(Tshatle_to_raketa);
	zadanie.setBuffer(Tzadanie);
	cosmonavts_in_moon.setVolume(35);
	//set the volume
	pilot_posadka.setVolume(35);
	shatle_in_moon.setVolume(35);
	shatle_in_space.setVolume(35);
	shatle_to_raketa.setVolume(35);
	zadanie.setVolume(35);


	Font font;
	font.loadFromFile("images/19226.otf");//download
	Text opentxt2("", font, 150);//text variables, font - font, 150 - size
	opentxt2.setFillColor(Color::White);
	opentxt2.setOutlineColor(Color::Black);
	opentxt2.setOutlineThickness(1);
	opentxt2.setString(L"Thanks for playing");
	opentxt2.setPosition(350, 350);

	// VARIABLES FOR SAVER
	Texture bg, Tluna, open3t, open4t, open5t, tzastavka1, tzastavka2, tkonec1, tkonec2, tkonec3, tkonec4;//текстури
	//download
	bg.loadFromFile("images/fon.png");
	Tluna.loadFromFile("images/luna.png");
	open3t.loadFromFile("images/posadka.png");
	open4t.loadFromFile("images/human.png");
	open5t.loadFromFile("images/flag.png");
	tzastavka1.loadFromFile("images/zastavka1.jpg");
	tzastavka2.loadFromFile("images/zastavka2.jpg");
	tkonec1.loadFromFile("images/1.jpg");
	tkonec2.loadFromFile("images/2.jpg");
	tkonec3.loadFromFile("images/3.jpg");
	tkonec4.loadFromFile("images/4.jpg");
	//making sprites
	Sprite BG(bg), Luna(Tluna), Shatle(open3t), human1(open4t), human2(open4t), flag(open5t), zastavka1(tzastavka1), zastavka2(tzastavka2), konec1(tkonec1), konec2(tkonec2), konec3(tkonec3), konec4(tkonec4);

	//set positions for sprite
	Luna.setPosition(0, 860);
	zastavka2.setPosition(0, 1080);
	konec2.setPosition(1920, 0);
	konec3.setPosition(3840, 0);
	konec4.setPosition(5760, 0);


	raketa_shatle obj_ship("images/shattle.png");//make the object of our classes

	double coord_flag_end = 0, coord_flag_start = 0; // these changes are used for the distance the astronauts will travel
	int tik = 0;//change that counts ticks, 60 ticks = 1 second, this change will be needed. when you want to delay the screen
	//flags that will be needed in our game
	bool opening = true, game = false, ending = false, posadka = false, flaag = false, humans = false, end = false, vslet = false, stykovka = false, konec = false, zvyk_posadka = false;
	bool ending_music_is_play = true, sound_humans = true, flag_pilot_posadka = true, flag_shatle_posadka = true, flag_shatle_in_moon = true, zvyk_cosmonavti = false, flag_cosmonavts_in_shatle = true, flag_shatle_in_space = true;
	bool flag_gimn = true;
	while (window.isOpen())
	{
		// process a queue of events in a cycle
		Event event;
		while (window.pollEvent(event))
		{
			sf::Event event;
			while (window.pollEvent(event)) {

				if (event.type == sf::Event::Closed)
					window.close();
			}

		}

		if (opening == true)// condition, for screen saver 1, move 2 sprites in one direction, get "slideshow"
		{
			zastavka1.move(0, -4);
			zastavka2.move(0, -4);
		}

		if (konec == true)// condition, to check at the end of the game, ie for screen saver 3, move the slides too, like a slideshow
		{
			if (ending_music_is_play == true)//the flag we made earlier, it is needed in order to play ski music 1 time, if it is not, then music will be played on each stream, and this is incorrect
			{
				open_music.stop();
				end_music.play();
				ending_music_is_play = false;
			}
			konec1.move(-3, 0);
			konec2.move(-3, 0);
			konec3.move(-3, 0);
			konec4.move(-3, 0);
		}

		if (zvyk_posadka == true)//delay for landing sound
		{
			tik++;
			if (tik == 175)// wait 3 seconds
			{
				tik = 0;
				zvyk_posadka = false;//change flags
				humans = true;
			}
		}


		if (zvyk_cosmonavti == true)//a delay for sound when astronauts go out for a month
		{
			tik++;
			if (tik == 175)// wait 3 seconds
			{
				tik = 0;
				zvyk_cosmonavti = false;//change flags
				vslet = true;
			}
		}
		if (flaag == true)//this falg must in order to make a delay of 10 seconds when we play the anthem
		{
			tik++;
			if (tik == 600)
			{
				tik = 0;
				flaag = false;//do not forget to change the flags
				end = true;
			}
		}

		if (stykovka == true)//this flag is used to delay when the shuttle is already docked with the missile, and for the dispatcher to say his word
		{
			tik++;
			if (tik == 300)//wait 5 seconds
			{
				tik = 0;
				stykovka = false;//change flags
				ending = true;
			}
		}

		if (vslet == true)//flag, to move the shuttle up when the astronauts have already boarded
		{
			Shatle.move(0, -1);
		}

		if (ending == true)//flag when the shuttle joins the rocket and the rocket flies to the ground
		{
			obj_ship.ulet();
		}

		if (end == true)//flag when the astronauts move back to the shuttle
		{
			human1.move(-0.4, 0);
			human2.move(-0.4, 0);
		}

		if (humans == true)//flag when astronauts move to put the Ukrainian flag
		{
			human1.move(0.4, 0);
			human2.move(0.4, 0);
		}

		if (posadka == true)//this flag is needed when the rocket flies close to the moon, the shuttle will descend slowly, and the rocket will fly higher than the moon
		{
			Shatle.move(0, 1);
			obj_ship.posadka();
		}

		if (game == true)//flag to initialize the movement of the rocket
		{
			obj_ship.movement();
		}

		////////////////////CHECKS////////////////////////
		if (Shatle.getPosition().y > 850 && posadka == true)//check for finding the shuttle in the right position on the moon
		{
			Vector2f coord_of_human = Shatle.getPosition();//take the coordinates of the shuttle
			human1.setPosition(coord_of_human.x + 25 * 3, coord_of_human.y + 25);//spawn 1st astronaut
			human2.setPosition(coord_of_human.x + 50 * 2.5, coord_of_human.y + 25);//spawn 2st astronaut
			posadka = false;//change flags
			zvyk_posadka = true;
			coord_flag_start = human1.getPosition().x;//set how many astronauts need to go to put the flag
			coord_flag_end = coord_flag_start + 150;
		}

		if (human1.getPosition().x > coord_flag_end && humans == true)//checking whether the astronaut has reached the desired position
		{
			Vector2f coord_of_human = human1.getPosition();
			flag.setPosition(coord_of_human.x + 20, coord_of_human.y - 7);//we put the coordinates for the Ukrainian flag
			flaag = true;
			humans = false;//change flags

		}

		if (human1.getPosition().x <= coord_flag_start && end == true)//checking to see if the astronauts have returned to the shuttle
		{
			zvyk_cosmonavti = true;
			game = true;//if so, change the flags
			end = false;
		}

		if (obj_ship.get_sprite().getPosition().y <= 0 && ending == true)//when the shuttle joined the rocket and the rocket flew to the ground
		{
			ending = false;//change the flags to the screen saver 3
			konec = true;
		}

		if (zastavka2.getPosition().y <= 0 && opening == true)//condition for entry (screensaver 1) to finish the slideshow
		{
			opening = false;
			game = true;
		}

		if (konec4.getPosition().x <= 0 && konec == true)//similar to the entry
		{
			konec = false;
			window.close();
		}

		////////////////////COLLISION///////////////////////////
		if (obj_ship.get_sprite().getGlobalBounds().intersects(Luna.getGlobalBounds()))//check if the rocket collided with the moon
		{

			Shatle.setPosition(obj_ship.get_sprite().getPosition());//if so, we release the shuttle
			posadka = true;//change flags
			game = false;
		}

		if (obj_ship.get_sprite().getGlobalBounds().intersects(Shatle.getGlobalBounds()) && vslet == true)//if the shuttle joined the rocket
		{
			zadanie.play();
			vslet = false;//change flags
			game = false;
			stykovka = true;

		}

		////////////////DRAWING/////////////////////////////

		window.clear();
		if (opening == true)//output for opening, entry (screensavers 1)
		{
			window.draw(zastavka1);
			window.draw(zastavka2);
		}

		if (game == true)//output for the main game when we control the rocket
		{
			if (flag_pilot_posadka == true)//we play the sound once when we put the shuttle on the moon
			{
				pilot_posadka.play();
				flag_pilot_posadka = false;
			}
			window.draw(BG);//draw a background
			window.draw(Luna);//moon
			window.draw(obj_ship.get_sprite());//rocket
		}

		if (posadka == true)//for landing
		{
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(Shatle);
		}
		if (zvyk_posadka == true)//in order to play the sound once
		{
			if (flag_shatle_posadka == true)
			{
				shatle_in_moon.play();
				flag_shatle_posadka = false;
			}
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(Shatle);

		}
		else
		{
			if (humans == true)//output for astronauts
			{
				if (sound_humans == true)
				{
					cosmonavts_in_moon.play();
					sound_humans = false;
				}
				window.draw(BG);
				window.draw(Luna);
				window.draw(obj_ship.get_sprite());
				window.draw(Shatle);
				window.draw(human1);
				window.draw(human2);
			}
		}
		if (flaag == true)//for flag
		{
			if (flag_gimn == true)
			{
				open_music.pause();
				gimn.play();
				flag_gimn = false;

			}
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(Shatle);
			window.draw(human1);
			window.draw(human2);
			window.draw(flag);
		}

		if (end == true)//the astronauts go back to the shuttle
		{
			open_music.play();
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(Shatle);
			window.draw(human1);
			window.draw(human2);
			window.draw(flag);
		}

		if (zvyk_cosmonavti == true)
		{
			if (flag_cosmonavts_in_shatle == true)
			{
				shatle_to_raketa.play();
				flag_cosmonavts_in_shatle = false;
			}
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(Shatle);
			window.draw(flag);
		}
		else
		{
			if (vslet == true)// takeoff of the shuttle and joining the rocket
			{
				if (flag_shatle_in_space == true)
				{
					shatle_in_space.play();
					flag_shatle_in_space = false;
				}
				window.draw(BG);
				window.draw(Luna);
				window.draw(obj_ship.get_sprite());
				window.draw(Shatle);
				window.draw(flag);
			}
		}


		if (stykovka == true)//when the shuttle joined the rocket
		{
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(flag);
		}

		if (ending == true)
		{
			window.draw(BG);
			window.draw(Luna);
			window.draw(obj_ship.get_sprite());
			window.draw(flag);
		}

		if (konec == true)//screen saver 3, end
		{
			window.draw(konec1);
			window.draw(konec2);
			window.draw(konec3);
			window.draw(konec4);
			window.draw(opentxt2);
		}

		window.display();
	}

	return 0;
}