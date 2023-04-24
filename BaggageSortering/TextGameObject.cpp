#include "TextGameObject.h"
#include "Game.h"

#include <SDL_TTF.h>

void TextGameObject::draw()
{
	TTF_Font* Sans = TTF_OpenFont("assets/fonts/OpenSans-regular.ttf", 24);
	SDL_Color White{ 255, 255, 255, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surfaceMessage);

	width = surfaceMessage->w;
	height = surfaceMessage->h;

	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = width;
	Message_rect.h = height;

	SDL_RenderCopy(TheGame::Instance()->getRenderer(), Message, NULL, &Message_rect);

	// Free the surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	// Close the font that was used
	TTF_CloseFont(Sans);
}

void TextGameObject::update() {}

void TextGameObject::clean() {
	delete this;
}