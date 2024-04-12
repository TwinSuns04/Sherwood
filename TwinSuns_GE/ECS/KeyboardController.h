// Keyboard Controller component, adds a controller comp to a ECS ojbect

#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


class KeyboardController : public Component
{
	
public:

	TransformComponent* transform;
	SpriteComponent* sprite;
	GameMode* gameMode = new GameMode();
	Game* gameBug = new Game();

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void Update() override
	{

		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (Game::event.button.button)
			{
			case SDL_BUTTON_LEFT:
				//std::cout << "Left Click" << std::endl;
				if (gameMode->PuzzleCollisionCheck())
				{
					std::cout << "Puzzle Piece Clicked" << std::endl;
					gameMode->PuzzlePieceInteraction();
				}
				break;

			case SDL_BUTTON_RIGHT:
				//std::cout << "Right Click" << std::endl;
				if (gameMode->GetExpoHintActive())
				{
					std::cout << "EpxoHintUI Active and Right Click" << std::endl;
					gameMode->HintRequestToggle();
				}
				break;

			default:
				break;
			}
		}

		// check if events exists
		// down key press
		if (Game::event.type == SDL_KEYDOWN)
		{
			// switch statement to check which key was pressed
			switch (Game::event.key.keysym.sym)
			{

				// Commented out because don't want movement
			/*
			case SDLK_w:
				transform->velocity.y = -2;
				//sprite->PlayAnim("Walk"), how to play anim on key press
				//std::cout << "xPos: " << transform->position.x <<
					//"yPos: " << transform->position.y << std::endl;
				break;

			case SDLK_a:
				transform->velocity.x = -2;
				break;

			case SDLK_s:
				transform->velocity.y = 2;
				break;

			case SDLK_d:
				transform->velocity.x = 2;
				break;
			*/

			case SDLK_p:
				std::cout << "The game is paused" << std::endl;
				break;

			case SDLK_SPACE:
				std::cout << "SDLK_SPACE" << std::endl;
				if (gameMode->GetStartEndUIActive())
				{
					gameMode->GameStart();
				}
				break;

			case SDLK_ESCAPE:
				std::cout << "Escape Pressed" << std::endl;
				Game::isRunning = false;
				break;

			// Key for hint
			case SDLK_h:
				std::cout << "Hint Requested" << std::endl;
				gameMode->HintRequestToggle();
				break;

			// Pause / Play music
			case SDLK_m:
				std::cout << "Pause / Play Music" << std::endl;

				// no music playing
				if (Mix_PlayingMusic() == 0) 
				{
					// Play music
					gameMode->PlayBackgroundMusic();
				}
				// music is playing
				else 
				{
					// If music is paused
					if (Mix_PausedMusic() == 1)
					{
						gameMode->ResumeBGMusic();
					}
					// if music is playing
					else
					{
						gameMode->PauseBGMusic();
					}
				}
				break;

			// Stop music altogether
			case SDLK_n:
				std::cout << "Stop Music" << std::endl;
				gameMode->StopBGMusic();
				break;

			// Keys not in use
			/*
			case SDLK_l:
				std::cout << "SDLK_l" << std::endl;
				break;

			case SDLK_k:
				std::cout << "SDLK_k" << std::endl;
				break;
			*/

			case SDLK_0:
				std::cout << "Debug" << std::endl;
				gameBug->DebugOne();
				break;

			default:
				break;
			}
		}

		// key release
		if (Game::event.type == SDL_KEYUP)
		{
			// switch statement to check which key was pressed
			// resets velocity to zero
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				break;

			case SDLK_SPACE:


			default:
				break;
			}
		}
	}

};
