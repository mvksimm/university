#pragma once /*директива процессора, контролирующая, чтобы исходный файл при компиляции подключался строго один раз*/

/*объекты находятся вне текущего файла, поэтому, для сообщения компилятору об этом, используем спецификатор extern*/
extern SDL_Renderer* ren;
extern SDL_DisplayMode displayMode;
extern SDL_Window* win;
extern SDL_Surface* surface;
extern TTF_Font* font;
extern SDL_Color color;

bool init() /*инициализация всех подключенных файлов*/
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (SDL_GetDesktopDisplayMode(0, &displayMode))
	{
		std::cout << "SDL_display Error: " << SDL_GetError() << std::endl;
		return false;
	}

	win = SDL_CreateWindow("SDL_testing", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);

	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	std::cout << "init complete sucsesseful" << std::endl;
	return true;
}
//Добавление текста на экран
void add_text(SDL_Renderer* ren, TTF_Font* font, SDL_Color color, std::string msg, int x, int y) 
{
	SDL_Surface* text = TTF_RenderText_Solid(font, msg.c_str(), color);

	if (!text)
	{
		std::cout << "Failed to render text: " << TTF_GetError();
	}
	else
	{
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text);
		SDL_Rect dest = { x, y, text->w, text->h };
		SDL_RenderCopy(ren, text_texture, NULL, &dest);
		SDL_DestroyTexture(text_texture);
	}
	SDL_FreeSurface(text);
}
//Добавление снежинки
void spawn_snow(std::vector<Snow*>& tmp, SDL_Texture* t)
{
	tmp.push_back(new Snow(t));
	tmp.back()->move(rand() % displayMode.w, 0);
	tmp.back()->resize(64, 64);
	tmp.back()->render();
}

//движение снежинок. Если выходит за пределы поля, то удаляем
void snowfall(std::vector<Snow*>& tmp)
{
	std::vector<Snow*> copy;
	auto newEnd = std::remove_if(tmp.begin(),tmp.end(),
		[&copy](Snow* tmp) {
			if (!tmp->go())
			{
				copy.push_back(tmp);
				return true;
			}
			else
				return false; });
	tmp.erase(newEnd, tmp.end());

	std::vector<Snow*>::iterator at;
	for (at = copy.begin(); at != copy.end(); at++)
		delete (*at);

	copy.clear();
}
// полная очистка экрана от снежинок
void clear(std::vector<Snow*>& tmp)
{
	std::vector<Snow*>::iterator at;
	for (at = tmp.begin(); at != tmp.end(); at++)
		delete (*at);

	tmp.clear();
}
