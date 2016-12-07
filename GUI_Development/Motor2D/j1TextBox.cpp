#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

void j1TextBox::SetText(const char * txt)
{
	text.text = txt;
}

const char * j1TextBox::GetText()
{
	return text.text.GetString();
}

bool j1TextBox::Draw(float dt, Element* item)
{
	j1TextBox* temp = (j1TextBox*)item;

	App->render->Blit(text_texture, item->position.x, item->position.y);
	
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
		text_box->text.text += App->input->char_input;
		text_texture = App->font->Print(text_box->text.text.GetString(), SDL_Color{ (255),(0),(100),(255) });
		App->input->new_char = false;
	}
		
	return true;
}
