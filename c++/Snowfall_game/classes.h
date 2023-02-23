#pragma once /*��������� ����������, ��������������, ����� �������� ���� ��� ���������� ����������� ������ ���� ���*/

/*������� ��������� ��� �������� �����, �������, ��� ��������� ����������� �� ����, ���������� ������������ extern*/
extern SDL_Renderer* ren;
extern SDL_DisplayMode displayMode;
extern SDL_Window* win;
extern SDL_Surface* surface;
extern TTF_Font* font;
extern SDL_Color color;

class Timer /*������*/
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now()) /*�������� �����*/
	{
	}

	void reset() /*����� ������� ��������*/
	{
		m_beg = clock_t::now();
	}

	double elapsed() const /*������� �������� ������������ �������*/
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

class Object /*����������� ����� ��� �������� ����*/
{
protected:
	SDL_Rect* rect;
	SDL_Texture* texture;

	virtual bool check_confines(int x, int y) /*�������� �� ����� ������� �� �������� �������� ����*/
	{
		if (rect->x + x + rect->w < displayMode.w && rect->x + x > 0 && rect->y + y + rect->h < displayMode.h && rect->y + y > 0)
			return true;
		return false;
	}

public:
	Object(SDL_Texture* texture) /*����������� �������*/
	{
		rect = new SDL_Rect;
		this->texture = texture;
		*rect = { 0, 0, 0, 0 };
	}

	void change_texture(SDL_Texture* _texture) /*����� �������� �������*/
	{
		texture = _texture;
	}

	void move(double x, double y)/*����� ������� �� ����������� �� �������� ��������*/
	{
		rect->x += x;
		rect->y += y;
	}

	void moveTo(int x, int y) /*����� ������� � �������� ����������*/
	{
		rect->x = x;
		rect->y = y;
	}

	int get_x() /*��������� ���������� x �������*/
	{
		return rect->x;
	}

	int get_y() /*��������� ���������� y �������*/
	{
		return rect->y;
	}

	int get_w() /*��������� ������ �������*/
	{
		return rect->w;
	}

	int get_h() /*��������� ������ �������*/
	{
		return rect->h;
	}

	void resizeOn(int w, int h) /*��������� �������� ������� �� �������� ��������*/
	{
		rect->w = w;
		rect->h = h;
	}

	void resize(int w, int h) /*���������� �������� ������� �� �������� ��������*/
	{
		rect->w += w;
		rect->h += h;
	}

	virtual void render()
	{
		SDL_RenderCopy(ren, texture, NULL, rect);
	}

};

class Snow : public Object /*����� ����, ����������� �� Object*/
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
	Snow(SDL_Texture* texture) : Object(texture) /*���������� �������� � ��������� ���������*/
	{
		speed = 2;
	}
	bool go()
	{
		if (check_confines(0, speed)) /*����������� ������� � �������� ��������� �� ������� ������ �� ������� ������*/
		{
			move(0, speed);
			render();
			return true;
		}
		return false;
	}
};

class Player : public Object /*����� �����, ����������� �� Object*/
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
	Player(SDL_Texture** texture) : Object(texture[0]) /*����������� ������ � �������� ��������� � �������� ������������*/
	{
		speed = 10;
		texture_pack = texture;
		i = 0;
	}

	void render(bool tmp) /*��������, � ����� ������� ������ ������� �����*/
	{
		if(tmp)
			SDL_RenderCopyEx(ren, texture, NULL, rect, 0, NULL, SDL_FLIP_NONE);
		else
			SDL_RenderCopyEx(ren, texture, NULL, rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	// �������� �� ������� �������� � ��������
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

	//����������� �� � ����������, tmp - ���� �������� true - �����, false - ����
	void moving(bool& tmp)
	{
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (((keyboardState[SDL_SCANCODE_LEFT]) || (keyboardState[SDL_SCANCODE_A])) && check_confines(-speed, 0))
		{
			//�������� �������� ��������. i - ����� �����. ���� �� 5 ��� ���������� ����� ������
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