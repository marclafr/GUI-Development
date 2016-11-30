#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

void j1TextBox::SetText(const char * txt)
{
	text.text = txt;
}

const char * j1TextBox::GetText()
{
	return text.text.GetString();
}

bool j1TextBox::Draw(float dt)
{
	//SDL_Color color{ ((255),(255),(255),(255)) };
	
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == text_box && item->data->is_visible == true)
		{
			j1TextBox* temp = (j1TextBox*)item->data;
			App->render->Blit(App->font->Print(temp->text.text.GetString(), SDL_Color{ (255),(0),(100),(255) }), item->data->position.x, item->data->position.y);
		}
	}
	return true;
}

bool j1TextBox::Update(float dt)
{
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == text_box)
		{
			j1TextBox* temp = (j1TextBox*)item->data;
			if (temp->text.text == "Left clicked" || temp->text.text == "Right clicked" || temp->text.text == "Mouse inside" || temp->text.text == "Hello world")
			{
				if (item->data->l_click == true)
				{
					temp->SetText("Left clicked");
				}
				if (item->data->r_click == true)
				{
					temp->SetText("Right clicked");
				}
				else if (item->data->mouse_inside == true && item->data->l_click == false)
				{
					temp->SetText("Mouse inside");
				}

				if (item->data->mouse_inside == false)
				{
					if (temp->GetText() != "Hello world")
						temp->SetText("Hello world");
				}
			}
		}
	}
	return true;
}
