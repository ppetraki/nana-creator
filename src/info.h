/*****************************************************
 *	C++ code generated with Nana Creator (0.22.0)
 *	GitHub repo: https://github.com/besh81/nana-creator
 *
 * PLEASE EDIT ONLY INSIDE THE TAGS:
 *		//<*tag
 *			user code
 *		//*>
*****************************************************/

#ifndef INFO_H
#define INFO_H

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>

//<*includes
//*>


class info
	: public nana::form
{
public:
	info(nana::window wd, const ::nana::size& sz = {520, 330}, const nana::appearance& apr = {true, true, false, false, false, false, false})
		: nana::form(wd, sz, apr)
	{
		init_();

		//<*ctor
		_init_ctrls();
		//*>
	}

	~info()
	{
		//<*dtor

		//*>
	}


private:
	void init_()
	{
		_place.div("vert <weight=150 arrange=[50%,variable] field1><vert weight=30 margin=5 gap=2 arrange=[20] field2><grid=[5,5] margin=5 collapse(1,0,4,1) collapse(1,1,4,1) collapse(1,2,4,3) grid1><weight=40 margin=6 gap=2 arrange=[variable,90] field3>");
		caption("About Nana Creator");
		// picture1
		picture1.create(*this);
		_place["field1"] << picture1;
		picture1.load(nana::paint::image("c:/cppprojects/nana-creator/wdir/icons/nc.png"));
		picture1.align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));
		picture1.set_gradual_background(nana::color(255,255,255), nana::color(30,30,30), true);
		// panel1
		panel1.create(*this);
		panel1_place.bind(panel1);
		panel1_place.div("vert margin=10 _field_");
		panel1.bgcolor(nana::color(30,30,30));
		_place["field1"] << panel1;
		// label1
		label1.create(panel1);
		panel1_place["_field_"] << label1;
		label1.fgcolor(nana::color(255,255,255));
		label1.typeface(nana::paint::font("", 26, {600, false, false, false}));
		label1.caption("Nana Creator");
		label1.transparent(true);
		label1.text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(2));
		// _ver
		_ver.create(panel1);
		panel1_place["_field_"] << _ver;
		_ver.fgcolor(nana::color(255,255,255));
		_ver.typeface(nana::paint::font("", 16, {400, false, false, false}));
		_ver.caption("version");
		_ver.transparent(true);
		_ver.text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(0));
		// label2
		label2.create(*this);
		_place["field2"] << label2;
		label2.caption(" Nana Creator - a RAD tool for (and build with) Nana C++ Library");
		label2.text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));
		// label3
		label3.create(*this);
		_place["grid1"] << label3;
		label3.caption("Author:");
		// label31
		label31.create(*this);
		_place["grid1"] << label31;
		label31.caption("besh81");
		// label4
		label4.create(*this);
		_place["grid1"] << label4;
		label4.caption("website:");
		// label41
		label41.create(*this);
		_place["grid1"] << label41;
		label41.caption("https://github.com/besh81/nana-creator");
		// label5
		label5.create(*this);
		_place["grid1"] << label5;
		label5.caption("Thanks to ...");
		// _thanks_txt
		_thanks_txt.create(*this);
		_place["grid1"] << _thanks_txt;
		_thanks_txt.editable(false);
		// panel2
		panel2.create(*this);
		_place["field3"] << panel2;
		// _ok_btn
		_ok_btn.create(*this);
		_place["field3"] << _ok_btn;
		_ok_btn.caption("OK");

		_place.collocate();
		panel1_place.collocate();
	}


protected:
	nana::place _place{ *this };
	nana::picture picture1;
	nana::panel<true> panel1;
	nana::place panel1_place;
	nana::label label1;
	nana::label _ver;
	nana::label label2;
	nana::label label3;
	nana::label label31;
	nana::label label4;
	nana::label label41;
	nana::label label5;
	nana::textbox _thanks_txt;
	nana::panel<true> panel2;
	nana::button _ok_btn;


	//<*declarations
private:
	void _init_ctrls();
	//*>
};

#endif //INFO_H

