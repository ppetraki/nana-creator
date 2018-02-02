/*
 *		nana::pg_items Implementation
 *
 *      Nana C++ Library - Creator
 *      Author: besh81
 */

#include <iostream>
#include <algorithm>
#include <nana/gui/wvl.hpp> // used to create the form -> choises
#include "pg_items.h"
#include "lock_guard.h"
#include "choises.h"


#define PG_BORDER_X		1
#define PG_BORDER_Y		2


namespace nana
{
	/// helper functions
	nana::color to_color(const std::string& s, bool& inherited)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<int> items;

		inherited = false;

		try
		{
			while(getline(ss, item, ','))
			{
				if(item == "[inherited]")
					inherited = true;
				else
					items.push_back(item.empty() ? 0 : std::stoi(item));
			}
		}
		catch(...)
		{
			// reset
			items.clear();
		}
		for(size_t i = 0; i < 3; ++i)
		{
			if(i >= items.size())
				items.push_back(0);
			else
				items[i] = std::max(0, std::min(items[i], 255));
		}

		return nana::color(items[0], items[1], items[2]);
	}

	std::string to_string(const nana::color& c, bool inherited)
	{
		return (inherited ? "[inherited]," : "") + std::to_string(int(c.r())) + "," + std::to_string(int(c.g())) + "," + std::to_string(int(c.b()));
	}
	/// helper functions - end




	/// class pg_string
	void pg_string::value(const std::string& value)
	{
		value_ = value;

		lock_guard evt_lock(&evt_emit_, false);
		txt_.caption(value);
	}
	std::string pg_string::value() const
	{
		return value_;
	}

	void pg_string::set_accept(std::function<bool(wchar_t)> f)
	{
		txt_.set_accept(f);
	}

	void pg_string::create(window wd)
	{
		txt_.create(wd);
		txt_.multi_lines(false);
		txt_.caption(value_);

		txt_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		txt_.events().dbl_click([this](const nana::arg_mouse& arg)
		{
			txt_.select(true);
		});
		txt_.events().key_press([this](const nana::arg_keyboard& arg)
		{
			if(arg.key == nana::keyboard::enter)
			{
				value_ = txt_.caption();
				emit_event();
			}
		});
	}

	bool pg_string::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		txt_.move(PG_BORDER_X, PG_BORDER_Y);
		txt_.size(nana::size(rect.width - 2* PG_BORDER_X, size_ - 2* PG_BORDER_Y));
		return false;
	}
	/// class pg_string end


	/// class pg_string_int
	void pg_string_int::value(int value)
	{
		pg_string::value(std::to_string(value));
	}
	int pg_string_int::to_int() const
	{
		int int_val = -1;
		try
		{
			int_val = std::stoi(pg_string::value());
		}
		catch(...)
		{
		}
		return int_val;
	}

	void pg_string_int::create(window wd)
	{
		pg_string::create(wd);

		txt_.events().key_press.connect_front([this](const nana::arg_keyboard& arg)
		{
			if(arg.key == nana::keyboard::enter)
			{
				int int_val = -1;
				try
				{
					int_val = std::stoi(txt_.caption());
				}
				catch(...)
				{
					txt_.caption(value_);
					arg.stop_propagation();
					return;
				}

				value_ = std::to_string(int_val);
				txt_.caption(value_);

				emit_event();
				arg.stop_propagation();
			}
		});

		txt_.set_accept([](wchar_t c) -> bool
		{
			return (isdigit(c) || c == '-' || c == nana::keyboard::backspace) ? true : false;
		});
	}
	/// class pg_string_int end


	/// class pg_string_uint
	void pg_string_uint::value(unsigned value)
	{
		pg_string::value(std::to_string(value));
	}
	unsigned pg_string_uint::to_uint() const
	{
		unsigned u_val = -1;
		try
		{
			u_val = std::stoul(pg_string::value());
		}
		catch(...)
		{
		}
		return u_val;
	}

	void pg_string_uint::create(window wd)
	{
		pg_string::create(wd);

		txt_.set_accept([](wchar_t c) -> bool
		{
			return isdigit(c) || c == nana::keyboard::backspace ? true : false;
		});
	}
	/// class pg_string_uint end


	/// class pg_choice
	void pg_choice::value(const std::string& value_)
	{
		for(unsigned i = 0; i < cmb_.the_number_of_options(); ++i)
			if(cmb_.text(i) == value_)
			{
				lock_guard evt_lock(&evt_emit_, false);
				cmb_.option(i);
				return;
			}
	}
	std::string pg_choice::value() const
	{
		return (cmb_.option() != ::nana::npos) ? cmb_.text(cmb_.option()) : "";
	}
	void pg_choice::option(std::size_t value_)
	{
		lock_guard evt_lock(&evt_emit_, false);
		if(value_ < cmb_.the_number_of_options())
			cmb_.option(value_);
	}
	std::size_t pg_choice::option() const
	{
		return cmb_.option();
	}

	void pg_choice::push_back(const std::string& option)
	{
		cmb_.push_back(option);
	}

	void pg_choice::create(window wd)
	{
		cmb_.create(wd);

		cmb_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		cmb_.events().selected([this](const nana::arg_combox& arg)
		{
			value_ = std::to_string(arg.widget.option());
			emit_event();
		});
	}

	bool pg_choice::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		cmb_.move(PG_BORDER_X, PG_BORDER_Y);
		cmb_.size(nana::size(rect.width - 2 * PG_BORDER_X, size_ - 2 * PG_BORDER_Y));
		return false;
	}
	/// class pg_choice end


	/// class pg_check
	void pg_check::value(const std::string& value)
	{
		lock_guard evt_lock(&evt_emit_, false);
		if(value == "true")
			chk_.check(true);
		else if(value == "false")
			chk_.check(false);
	}
	std::string pg_check::value() const
	{
		return chk_.checked() ? "true" : "false";
	}

	void pg_check::check(bool value)
	{
		lock_guard evt_lock(&evt_emit_, false);
		chk_.check(value);
	}
	bool pg_check::checked() const
	{
		return chk_.checked();
	}

	void pg_check::create(window wd)
	{
		chk_.create(wd);
		value(value_); // set the initial value passed in ctr

		chk_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		chk_.events().checked([this](const nana::arg_checkbox& arg)
		{
			value_ = arg.widget->checked() ? "true" : "false";
			emit_event();
		});
	}

	bool pg_check::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		chk_.bgcolor(bgcolor);

		auto chksize = size_ - 2 * PG_BORDER_Y;
		chk_.move(PG_BORDER_X, PG_BORDER_Y);
		chk_.size(nana::size(chksize, chksize));
		return false;
	}
	/// class pg_check end


	/// class pg_spin
	void pg_spin::value(const std::string& value)
	{
		lock_guard evt_lock(&evt_emit_, false);
		spn_.value(value);
	}
	std::string pg_spin::value() const
	{
		return value_;
	}
	void pg_spin::range(int begin, int last, int step)
	{
		lock_guard evt_lock(&evt_emit_, false);
		spn_.range(begin, last, step);
	}

	void pg_spin::value(int value)
	{
		pg_spin::value(std::to_string(value));
	}
	int pg_spin::to_int() const
	{
		return spn_.to_int();
	}

	void pg_spin::create(window wd)
	{
		spn_.create(wd);

		spn_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		spn_.events().text_changed([this](const nana::arg_spinbox& arg)
		{
			value_ = arg.widget.value();
			emit_event();
		});
	}

	bool pg_spin::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		spn_.move(PG_BORDER_X, PG_BORDER_Y);
		spn_.size(nana::size(rect.width - 2 * PG_BORDER_X, size_ - 2 * PG_BORDER_Y));
		return false;
	}
	/// class pg_spin end


	/// class pg_color
#define COLORBOX_SIZE		15

	pg_color::pg_color(const std::string& label, const std::string& value, bool inherited)
		: pgitem(label, value), inherited_(inherited)
	{
		color_ = ::nana::to_color(value, inherited_value_);
	}

	void pg_color::value(const std::string& value)
	{
		color_ = ::nana::to_color(value, inherited_value_);

		lock_guard evt_lock(&evt_emit_, false);
		txt_.caption(to_string(color_, false));

		if(inherited_)
			chk_.check(inherited_value_);

		update();
	}
	std::string pg_color::value() const
	{
		return to_string(color_, inherited_value_);
	}

	void pg_color::value(::nana::color value)
	{
		color_ = value;

		lock_guard evt_lock(&evt_emit_, false);
		txt_.caption(to_string(color_, false));

		update();
	}
	::nana::color pg_color::to_color() const
	{
		return color_;
	}

	void pg_color::inherited(bool value)
	{
		inherited_value_ = value;

		lock_guard evt_lock(&evt_emit_, false);
		if(inherited_)
			chk_.check(inherited_value_);

		update();

	}
	bool pg_color::inherited() const
	{
		return inherited_value_;
	}

	unsigned pg_color::size() const
	{
		return inherited_ ? 2 * size_ : size_;
	}

	void pg_color::create(window wd)
	{
		txt_.create(wd);
		txt_.multi_lines(false);
		txt_.caption(to_string(color_, false));

		txt_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		txt_.events().dbl_click([this](const nana::arg_mouse& arg)
		{
			txt_.select(true);
		});
		txt_.events().key_press([this](const nana::arg_keyboard& arg)
		{
			if(arg.key == nana::keyboard::enter)
			{
				if(to_string(color_, false) == txt_.caption())
				{
					emit_event();
					return;
				}

				bool fake;
				color_ = ::nana::to_color(txt_.caption(), fake);

				txt_.caption(to_string(color_, false));
				emit_event();

				update();
			}
		});

		txt_.set_accept([this](wchar_t c) -> bool
		{
			if(isdigit(c) || c == nana::keyboard::backspace)
				return true;

			if(c != ',')
				return false;

			int sep = 0;
			for(auto c : txt_.caption())
				if(c == ',')
					++sep;

			return sep < 2 ? true : false;
		});


		// inherited checkbox
		if(inherited_)
		{
			chk_.create(wd);
			chk_.check(inherited_value_);

			if(inherited_value_)
				txt_.enabled(false);

			chk_.events().click.connect_front([this](const nana::arg_click& arg)
			{
				scroll();
			});
			chk_.events().checked([this](const nana::arg_checkbox& arg)
			{
				inherited_value_ = arg.widget->checked();
				txt_.enabled(!inherited_value_);

				emit_event();
			});
		}
	}

	bool pg_color::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		int x = PG_BORDER_X + 2;

		rectangle colorbox{ rect.x + x, rect.y + (static_cast<int>(size_) - COLORBOX_SIZE) / 2, COLORBOX_SIZE, COLORBOX_SIZE };
		graph->rectangle(colorbox, false, nana::colors::black);
		graph->rectangle(colorbox.pare_off(1), true, color_);

		x += COLORBOX_SIZE + 4;

		txt_.move(x, PG_BORDER_Y);
		txt_.size(nana::size(rect.width - 2 * PG_BORDER_X - (COLORBOX_SIZE + 6), size_ - 2 * PG_BORDER_Y));

		if(inherited_)
		{
			int y = size_;

			chk_.bgcolor(bgcolor);

			int chksize = size_ - 2 * PG_BORDER_Y;
			chk_.move(x, y + PG_BORDER_Y);
			chk_.size(nana::size(chksize, chksize));

			std::string text = "Inherited";
			//todo: remove y correction when using new_gui_style
			graph->string(point{ rect.x + x + chksize, rect.y + y + static_cast<int>((size_ - graph->text_extent_size(text).height)/2) - 3 }, text, fgcolor);
		}

		return false;
	}
	/// class pg_color end



	/// class pg_collection
#define CHOISES_BUTTON_SIZE		30

	void pg_collection::value(const std::string& value)
	{
		value_ = value;

		lock_guard evt_lock(&evt_emit_, false);
		txt_.caption(value);
	}
	std::string pg_collection::value() const
	{
		return value_;
	}

	void pg_collection::set_accept(std::function<bool(wchar_t)> f)
	{
		txt_.set_accept(f);
	}

	void pg_collection::create(window wd)
	{
		txt_.create(wd);
		txt_.multi_lines(false);
		txt_.caption(value_);
		txt_.editable(false);

		txt_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			scroll();
		});
		txt_.events().dbl_click([this](const nana::arg_mouse& arg)
		{
			txt_.select(true);
		});


		//button
		btn_.create(wd);
		btn_.caption("...");

		btn_.events().click.connect_front([this](const nana::arg_click& arg)
		{
			//choises dialog
			choises_dialog choises(arg.window_handle, nana::size(300, 400), appear::decorate<appear::taskbar>());
			choises.caption("Choises");

			choises.choises.value(txt_.caption());
			choises.modality();

			if(choises.choises.return_val() == nana::msgbox::pick_ok)
			{
				txt_.caption(choises.choises.value());
				value_ = txt_.caption();
				emit_event();
			}
		});
	}

	bool pg_collection::draw_value(paint::graphics* graph, rectangle rect, color bgcolor, color fgcolor) const
	{
		txt_.move(PG_BORDER_X, PG_BORDER_Y);
		txt_.size(nana::size(rect.width - 2 * PG_BORDER_X - CHOISES_BUTTON_SIZE, size_ - 2 * PG_BORDER_Y));

		btn_.move(PG_BORDER_X + txt_.size().width, PG_BORDER_Y);
		btn_.size(nana::size(CHOISES_BUTTON_SIZE, size_ - 2 * PG_BORDER_Y));
		return false;
	}
	/// class pg_collection end
}//end namespace nana
