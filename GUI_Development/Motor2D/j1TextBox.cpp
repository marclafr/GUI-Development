#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

j1TextBox::j1TextBox(p2SString txt, SDL_Texture& tex, int size, bool is_password, SDL_Rect& rect, int id) : text(txt, size), text_texture(&tex), is_password(is_password), Element(elem_type::text_box, rect, id)
{
	text.SetFont("fonts/open_sans/OpenSans-Regular.ttf", size);
	if (txt != NULL)
		write_pos = txt.Length();
}

j1TextBox::~j1TextBox()
{

}

void j1TextBox::SetText(const char * txt)
{
	text.text = txt;
	write_pos = text.text.Length();
}

const char * j1TextBox::GetText()
{
	return text.text.GetString();
}

bool j1TextBox::Draw(float dt, Element* item)
{
	j1TextBox* text_box = (j1TextBox*)item;

	App->render->Blit(text_texture, item->position.x - App->render->camera.x, item->position.y - App->render->camera.y);
	if (text_box->text_clicked == true)
	{
		int w, h;
		text_box->text.text.StringSegment(0, write_pos, partial_text);
		App->font->CalcSize(partial_text.GetString(), w, h, text_box->text.font);
		App->render->DrawQuad(SDL_Rect{ item->position.x + w - App->render->camera.x, item->position.y + h / 2 - App->render->camera.y, 2, h }, 255, 255, 255);
	}
	
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Draw(dt, childs_item->data);
	}

	return true;
}

bool j1TextBox::Update(float dt, Element* item)
{
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Update(dt, childs_item->data);
	}

	j1TextBox* text_box = (j1TextBox*)item;
	if (App->input->new_char == true && text_box->text_clicked == true)
	{
		//if you write way fast write_pos gets exceded
		if (write_pos > text_box->text.text.Length())
			write_pos = text_box->text.text.Length();

		text_box->text.text.InsertString(write_pos, App->input->char_input);
		text_texture = App->font->Print(text_box->text.text.GetString(), SDL_Color{ (255),(0),(100),(255) }, text_box->text.font);
		write_pos++;
		App->input->new_char = false;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN && text_box->text_clicked == true)
	{
		if (write_pos > 0)
			write_pos--;
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && text_box->text_clicked == true)
	{
		if (write_pos < text_box->text.text.Length())
			write_pos++;
	}

	else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
		if (text_box->text_clicked == true && write_pos > 0)
		{
			text_box->write_pos--; 
			text_box->text.text.DeleteChar(write_pos);
			text_box->text_texture = App->font->Print(text_box->text.text.GetString(), SDL_Color{ (255),(0),(100),(255) }, text_box->text.font);
		}
	}
		
	return true;
}
