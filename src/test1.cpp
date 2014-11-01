#include <iostream>
#include "curses.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>

#define X_CHANGE_AXIS 0
#define Y_CHANGE_AXIS 1
#if defined(WIN32)
#define DEFINED_PAIRS 1000
#else
#define DEFINED_PAIRS 80
#endif

using namespace std;

char * c_str_list[] = 
	{
		"meme", "XD", "LOL", "SWAG", "TRENDY",
		"cool", "Apple", "Stylish", "wow", "le",
		"femenist", "troll face", "facenook", "forever alone",
		"meme face", "9gag", "2cool", "fun guy", "cool kid",
		"2spooky4me", "4chan", "edgy", "trololol", "maymay",
		"doge", "derp face", "mfw", "ur mom", "rekt", "senpai",
		"bro", "that feel", "rege face"
	};

class win_movable
{
private:
	int win_m_x_y_pos_last[2];
	int win_m_x_y_dimension_last[2];
	int win_m_x_y_pos[2];
	int win_m_x_y_dimension[2];
	bool draw_bool_win_m;
	WINDOW* base_win_m;
	void(*run_func_win_m)(WINDOW*, win_movable*);
	void erase_win_m()
	{
		werase(base_win_m);
		wrefresh(base_win_m);
		delwin(base_win_m);
	}
	void draw_win_m()
	{
		wrefresh(base_win_m);
		run_func_win_m(base_win_m, this);
		wrefresh(base_win_m);
	} 
public:
	win_movable(int x_pos, int y_pos, int x_dim, int y_dim, void(*run_func)(WINDOW*, win_movable*))
	{
		win_m_x_y_pos[0] = x_pos;
		win_m_x_y_pos[1] = y_pos;
		win_m_x_y_pos_last[0] = x_pos;
		win_m_x_y_pos_last[1] = y_pos;
		win_m_x_y_dimension[0] = x_dim;
		win_m_x_y_dimension[1] = y_dim;
		win_m_x_y_dimension_last[0] = x_dim;
		win_m_x_y_dimension_last[1] = y_dim;
		draw_bool_win_m = true;
		base_win_m = newwin(y_dim, x_dim, y_pos, x_pos);
		run_func_win_m = run_func;
		draw_win_m();
	}
	~win_movable()
	{
		erase_win_m();
	}
	void refresh_win_m()
	{
		if(draw_bool_win_m)
		{
			erase_win_m();
			base_win_m = newwin(win_m_x_y_dimension[1], win_m_x_y_dimension[0], win_m_x_y_pos[1], win_m_x_y_pos[0]);
			memcpy(win_m_x_y_pos_last, win_m_x_y_pos, sizeof(win_m_x_y_pos));
			memcpy(win_m_x_y_dimension_last, win_m_x_y_dimension, sizeof(win_m_x_y_dimension));
			draw_win_m();
				
		}
	}
	void toggle_visable_win_m()
	{
		draw_bool_win_m = !draw_bool_win_m;
	}
	int win_m_move_x_y_pos(int move_axis, int move_magnitude)
	{
		if(((win_m_x_y_pos[move_axis] + move_magnitude) > 0 && (win_m_x_y_pos[move_axis] + move_magnitude) < (move_axis == 0 ? COLS : LINES)))
		{
			try
			{
				win_m_x_y_pos[move_axis] += move_magnitude;
			}
			catch(...)
			{
				return 1;
			}
			return 0;
		}
	}
	int win_m_get_x_y_pos(int get_axis)
	{
		try
		{
			return win_m_x_y_pos[get_axis];
		}
		catch(...)
		{
			return 1;
		}
	}
	int win_m_set_x_y_pos(int set_axis, int set_val)
	{
		try
		{
			win_m_x_y_pos[set_axis] = set_val;
		}
		catch(...)
		{
			return 1;
		}
		return 0;
	}
	int win_m_incriment_x_y_dimensions(int incriment_axis, int incriment_magnitude)
	{
		try
		{
			win_m_x_y_dimension[incriment_axis] += incriment_magnitude;
		}
		catch(...)
		{
			return 1;
		}
		return 0;
	}
	int win_m_get_x_y_dimensions(int get_axis)
	{
		try
		{
			return win_m_x_y_dimension[get_axis];
		}
		catch(...)
		{
			return 1;
		}
	}
	int win_m_set_x_y_dimensions(int set_axis, int set_val)
	{
		try
		{
			win_m_x_y_dimension[set_axis] = set_val;
		}
		catch(...)
		{
			return 1;
		}
		return 0;
	}
};

void win_run_0 (WINDOW* base_win_ptr, win_movable* obj_ptr)
{
	box(base_win_ptr, 0, 0);
	mvwprintw(base_win_ptr , (obj_ptr->win_m_get_x_y_dimensions(Y_CHANGE_AXIS) / 2) - 1, (obj_ptr->win_m_get_x_y_dimensions(X_CHANGE_AXIS) / 2) - 1,". .");
	mvwprintw(base_win_ptr, (obj_ptr->win_m_get_x_y_dimensions(Y_CHANGE_AXIS) / 2) , (obj_ptr->win_m_get_x_y_dimensions(X_CHANGE_AXIS) / 2), "U");
}

void win_run_1 (WINDOW* base_win_ptr, win_movable* obj_ptr)
{
	box(base_win_ptr, 0, 0);
	mvwprintw(base_win_ptr , (obj_ptr->win_m_get_x_y_dimensions(Y_CHANGE_AXIS) / 2) - 1, (obj_ptr->win_m_get_x_y_dimensions(X_CHANGE_AXIS) / 2) - 1, c_str_list[rand() % ( sizeof(c_str_list) / sizeof(c_str_list[0] ))]);


}

int main (int argc, char *argv[])
{
	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	scrollok(stdscr, true);
	keypad(stdscr, true);
	refresh();
	start_color();
	refresh();
	int cursor_pos[2] = { 0, 0 };
	int current_color_pair = 0;
	int keytrack_int;
	int win_dim_array[2] = { 9, 5 };
	int win_x_pos = (COLS / 2) - (win_dim_array[0] / 2);
	int win_y_pos = (LINES / 2) - (win_dim_array[1] / 2);
	int velocity = 2;
	int num_other_windows = 4;
	init_color(1, 1000, 500, 500);
	init_color(4, 0, 0 , 1000);
	init_color(2, 500, 800, 0);
	mvprintw(LINES / 2 - 1, COLS / 2, "EPILEPSY WARN!");
	mvprintw(LINES / 2 + 1, COLS / 2, "ANY KEY TO CONTINUE!");
	while(true)
	{
		if((keytrack_int = getch()) != -1)
		{
			if(keytrack_int == KEY_F(5))
			{
				endwin();
				return 0;
			}
			break;
		}
	}
	//win_movable * win_obj = new win_movable(win_x_pos, win_y_pos, win_dim_array[0], win_dim_array[1], &win_run_0);
	vector<win_movable *> win_list;
	win_list.push_back(new win_movable(win_x_pos, win_y_pos, win_dim_array[0], win_dim_array[1], &win_run_0));
	for(int index_0 = 0; index_0 < num_other_windows; ++index_0)
	{
		win_list.push_back(new win_movable((rand() % COLS), (rand() % LINES), (rand() % 7) + 3, (rand() % 3) + 3, &win_run_1));
	}
	while(true)
	{
		current_color_pair = current_color_pair + 1 > DEFINED_PAIRS ? 1 : current_color_pair + 1 ; 
		keytrack_int = getch();
		switch(keytrack_int)
		{
			case KEY_LEFT:
				win_list[0]->win_m_move_x_y_pos(X_CHANGE_AXIS, -(velocity));
				//win_obj->win_m_move_x_y_pos(X_CHANGE_AXIS, -(velocity));
				break;
			case KEY_RIGHT:
				win_list[0]->win_m_move_x_y_pos(X_CHANGE_AXIS, (velocity));
				//win_obj->win_m_move_x_y_pos(X_CHANGE_AXIS, velocity);
				break;
			case KEY_UP:
				win_list[0]->win_m_move_x_y_pos(Y_CHANGE_AXIS, -(velocity));
				//win_obj->win_m_move_x_y_pos(Y_CHANGE_AXIS, -(velocity));
				break;
			case KEY_DOWN:
				win_list[0]->win_m_move_x_y_pos(Y_CHANGE_AXIS, (velocity));
				//win_obj->win_m_move_x_y_pos(Y_CHANGE_AXIS, velocity);
				break;
			case KEY_F(5):
				win_list.clear();
				//win_list.pop_back();
				//delete win_obj;
				endwin();
				return 0;
				cout<<"dsd";
		}
		init_pair(current_color_pair, int(rand() % 8), int(rand() % 8) );
		attron(COLOR_PAIR(current_color_pair));
		mvprintw(cursor_pos[1], cursor_pos[0], c_str_list[rand() % ( sizeof(c_str_list) / sizeof(c_str_list[0] ))]);
		printw(" ");
		attroff(COLOR_PAIR(current_color_pair));
		getyx(stdscr, cursor_pos[1], cursor_pos[0]);
		attron(A_BLINK);
		mvprintw(0, 0, "ARROW KEYS TO MOVE");
		mvprintw(1, 0, "F5 TO QUIT");
		attroff(A_BLINK);
		refresh();
		for(int index_0 = 0; index_0 < win_list.size(); ++index_0)
		{
			if (index_0 > 0) 
			{
				win_list[index_0]->win_m_move_x_y_pos(X_CHANGE_AXIS, -1 + (rand() % 3));
				win_list[index_0]->win_m_move_x_y_pos(Y_CHANGE_AXIS, -1 + (rand() % 3));
			}
			win_list[index_0]->refresh_win_m();
		}
		//win_list[0]->refresh_win_m();
		//win_obj->refresh_win_m();
	}
	win_list.clear();
	//win_list.pop_back();
	//delete win_obj;
	endwin();
	return 0;
}