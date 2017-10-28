#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>

#include <GUI_Text.h>
#include <element.h>
#include <sprite.h>

class Textbox : public Element{
public:
	Textbox();
	Textbox(const Textbox&);
	~Textbox();

	void setText(std::string text);

	bool editMode();
	bool editMode(bool editModeOn);

	void draw();

private:

	Sprite _carriage;

	GUI_Text _text;

	std::string _number;

	bool _edit_mode;
};

#endif /*TEXTBOX_H*/