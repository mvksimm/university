#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include "classes.h"
#include "func.h"

SDL_Renderer* ren;
SDL_DisplayMode displayMode;
SDL_Window* win;
SDL_Surface* surface;
TTF_Font* font;
SDL_Color color;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0)); /*запоминание текущего времени*/
	// Инициализация SDL
	init();

	//подключаем шрифт
	font = TTF_OpenFont("allura.ttf", 40);

	color = { 0xFF, 0xFF, 0xFF };

	//подгружаем текстуры
	SDL_Texture* player_texture[6];
	player_texture[0] = IMG_LoadTexture(ren, "img//player//man_1.png");
	player_texture[1] = IMG_LoadTexture(ren, "img//player//man_2.png");
	player_texture[2] = IMG_LoadTexture(ren, "img//player//man_3.png");
	player_texture[3] = IMG_LoadTexture(ren, "img//player//man_4.png");
	player_texture[4] = IMG_LoadTexture(ren, "img//player//man_5.png");
	player_texture[5] = IMG_LoadTexture(ren, "img//player//man_6.png");


	SDL_Texture* background_texture = IMG_LoadTexture(ren, "img//bcg.png");
	if (player_texture[4] == nullptr)
		std::cout << "1";

	SDL_Texture* snow_texture = IMG_LoadTexture(ren, "img//snow.png");
	std::vector<Snow*> snows;
	Timer t;
	//создаем объекты
	Object bcg(background_texture);
	bcg.resize(displayMode.w, displayMode.h);
	Player player(player_texture);
	player.resize(100, 200);
	int raiting[11];
	while (1)
	{
		player.moveTo(displayMode.w / 2, displayMode.h - 200); /*установк игрока в начальное положение*/

		SDL_Event event;
		bool run = true;
		bool right = true;
		
		int lvl = 256;
		bool spawn;
		int time;
		t.reset();
		while (run)
		{

			//примерно каждые 11 секунд усложнение уровня

			if (lvl != 16)
				lvl /= 2;
			for (int i = 0; i < 512 && run; i++)
			{
				
				//спавн снежинок
				if (!(i % lvl))
					spawn_snow(snows, snow_texture);

				SDL_Delay(20);

				bcg.render();
				add_text(ren, font, color, "time: ", 0, 0);
				add_text(ren, font, color, std::to_string((int)t.elapsed()), 80, 0);

				//рендер текстуры игрока
				player.render(right);

				//движение снежинок
				snowfall(snows);

				//если игрок нажал на еск, то начинаем игру заново
				if (SDL_PollEvent(&event))
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						run = false;
						clear(snows);
					}
				}
				//для быстрого отклика срабатывает каждый раз, а не при sdl_pollevent
				player.moving(right);

				//если снежинка упала на игрока то конец игры
				if (player.hit(snows))
				{
					time = t.elapsed();

					std::fstream file;
					int size = 0;
					file.open("raiting.bin", std::ios::binary | std::ios::in);
					if (file.is_open())
					{
						file.seekg(0, std::ios::end);
						size = static_cast<int>(file.tellg()) / sizeof(int);
						std::cout << size;
						file.seekg(0, std::ios::beg);
						for (int i = 0; i < size; i++)
						{
							file.read((char*)&raiting[i], sizeof(int));
						}
						file.close();
					}

					raiting[size] = time;

					//сортируем по возрастанию
					int buff;
					int j;
					for (int i = 1; i <= size; i++)
					{
						buff = raiting[i];
						for (j = i - 1; j >= 0 && raiting[j] < buff; j--)
							raiting[j + 1] = raiting[j];
						raiting[j + 1] = buff;
					}

					SDL_RenderClear(ren);
					bcg.render();
					add_text(ren, font, color, "esc - new game", 0, 0);
					add_text(ren, font, color, "your time: ", displayMode.w / 2 - 150, 55);
					add_text(ren, font, color, std::to_string(time), displayMode.w / 2 + 80, 55);
					add_text(ren, font, color, "best scores: ", displayMode.w / 2 - 100, 110);
					for (int i = 0, j = 165; i < 10; i++, j += 50)
						add_text(ren, font, color, std::to_string(raiting[i]), displayMode.w / 2, j);

					std::remove("raiting.bin");

					file.open("raiting.bin", std::ios::out);
					for (int i = 0; i <= size && i < 10; i++)
						file.write((char*)&raiting[i], sizeof(int));

					file.close();
					SDL_RenderPresent(ren);
					//удаляем все снежинки
					clear(snows);
					while (run)
					{
						SDL_Delay(5);
						if (SDL_PollEvent(&event))
						{
							if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
								run = false;
						}
					}

				}
				SDL_RenderPresent(ren);

			}
		}
	}
	return 0;
}