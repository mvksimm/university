#pragma once /*директива процессора, контролирующая, чтобы исходный файл при компиляции подключался строго один раз*/

/*объекты находятся вне текущего файла, поэтому, для сообщения компилятору об этом, используем спецификатор extern*/
extern SDL_Renderer* ren;
extern SDL_DisplayMode displayMode;
extern SDL_Window* win;
extern SDL_Surface* surface;
extern TTF_Font* font;
extern SDL_Color color;

class Timer /*Таймер*/
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now()) /*засекаем время*/
	{
	}

	void reset() /*сброс времени счетчика*/
	{
		m_beg = clock_t::now();
	}

	double elapsed() const /*возврат значения затраченного времени*/
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

class Object /*абстрактный класс для объектов игры*/
{
protected:
	SDL_Rect* rect;
	SDL_Texture* texture;

	virtual bool check_confines(int x, int y) /*Проверка на выход объекта за приеделы игрового поля*/
	{
		if (rect->x + x + rect->w < displayMode.w && rect->x + x > 0 && rect->y + y + rect->h < displayMode.h && rect->y + y > 0)
			return true;
		return false;
	}

public:
	Object(SDL_Texture* texture) /*конструктор объекта*/
	{
		rect = new SDL_Rect;
		this->texture = texture;
		*rect = { 0, 0, 0, 0 };
	}

	void change_texture(SDL_Texture* _texture) /*смена текстуры объекта*/
	{
		texture = _texture;
	}

	void move(double x, double y)/*сдвиг объекта по координатам на заданную величину*/
	{
		rect->x += x;
		rect->y += y;
	}

	void moveTo(int x, int y) /*сдвиг объекта в заданные координаты*/
	{
		rect->x = x;
		rect->y = y;
	}

	int get_x() /*получение координаты x объекта*/
	{
		return rect->x;
	}

	int get_y() /*получение координаты y объекта*/
	{
		return rect->y;
	}

	int get_w() /*получение ширины объекта*/
	{
		return rect->w;
	}

	int get_h() /*получение высоты объекта*/
	{
		return rect->h;
	}

	void resizeOn(int w, int h) /*изменение размеров объекта на заданные величины*/
	{
		rect->w = w;
		rect->h = h;
	}

	void resize(int w, int h) /*увеличение размеров объекта на заданные величины*/
	{
		rect->w += w;
		rect->h += h;
	}

	virtual void render()
	{
		SDL_RenderCopy(ren, texture, NULL, rect);
	}

};

class Snow : public Object /*класс снег, производный от Object*/
{
private:
	int speed;
	bool check_confines(int x, int y)
	{
		if (displayMode.h && rect->y + y > 0)
			return true;
		return false;
	}

public:
	Snow(SDL_Texture* texture) : Object(texture) /*коструктор снежинки с начальной скоростью*/
	{
		speed = 2;
	}
	bool go()
	{
		if (check_confines(0, speed)) /*перемещение объекта с заданной скоростью до момента выхода за пределы экрана*/
		{
			move(0, speed);
			render();
			return true;
		}
		return false;
	}
};

class Player : public Object /*класс игрок, производный от Object*/
{
private:
	int speed;
	SDL_Texture** texture_pack;
	int i;

	bool check_confines(int x, int y)
	{
		if (rect->x + x + rect->w < displayMode.w && rect->x + x > 0)
			return true;
		return false;
	}

public:
	Player(SDL_Texture** texture) : Object(texture[0]) /*конструктор игрока с заданной скоростью и начальым изображением*/
	{
		speed = 10;
		texture_pack = texture;
		i = 0;
	}

	void render(bool tmp) /*проверка, в какую сторону сейчас смотрит игрок*/
	{
		if(tmp)
			SDL_RenderCopyEx(ren, texture, NULL, rect, 0, NULL, SDL_FLIP_NONE);
		else
			SDL_RenderCopyEx(ren, texture, NULL, rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	// Проверка на встречу человека и снежинки
	bool hit(std::vector<Snow*>& tmp)
	{
		std::vector<Snow*>::iterator at;
		for (at = tmp.begin(); at != tmp.end(); at++)
			if ((**at).get_x() <= rect->x + rect->w && (**at).get_x() + (**at).get_w() >= rect->x && (**at).get_y() + (**at).get_h() >= rect->y && (**at).get_y() <= rect->y + rect->h)
			{
				return true;
			}
		return false;
	}

	//перемещение по х координате, tmp - флаг поворота true - право, false - лево
	void moving(bool& tmp)
	{
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (((keyboardState[SDL_SCANCODE_LEFT]) || (keyboardState[SDL_SCANCODE_A])) && check_confines(-speed, 0))
		{
			//заменяем текстуры анимации. i - номер кадра. Делю на 5 для замедления смены кадров
			change_texture(texture_pack[(i++/5) % 6]);
			move(-speed, 0);
			SDL_RenderCopyEx(ren, texture, NULL,rect ,0, NULL, SDL_FLIP_HORIZONTAL);
			tmp = false;
		}

		if (((keyboardState[SDL_SCANCODE_RIGHT]) || (keyboardState[SDL_SCANCODE_D])) && check_confines(speed, 0))
		{
			change_texture(texture_pack[(i++/5) % 6]);
			move(speed, 0);
			SDL_RenderCopyEx(ren, texture, NULL, rect, 0, NULL, SDL_FLIP_NONE);
			tmp = true;
		}
	}
};