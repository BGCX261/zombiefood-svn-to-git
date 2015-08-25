#pragma once

#include <irrlicht.h>

using namespace irr;

class MyEventReceiver :
	public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		bool eventprocessed = false;

		//////////////////////////////
		// Keyboard Input Event
		//////////////////////////////
		if (event.EventType == EET_KEY_INPUT_EVENT)
		{
			if (processState == STARTED)
			{
				// if key is Pressed Down
				if (event.KeyInput.PressedDown == true)
				{
					// If key was not down before
					if (keyState[event.KeyInput.Key] != DOWN)
					{
						keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
					}
					else
					{
						// if key was down before
						keyState[event.KeyInput.Key] = DOWN; // Set to Down
					}
				}
				else
				{

					// if the key is down
					if (keyState[event.KeyInput.Key] != UP)
					{
						keyState[event.KeyInput.Key] = RELEASED; // Set to Released
					}
				}
			}

			eventprocessed = true;
		}

		//////////////////////////////
		// Mouse Input Event
		//////////////////////////////
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			if (processState == STARTED)
			{
				//Mouse changed position
				if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
				{
					mouse.Y = event.MouseInput.Y;
					mouse.X = event.MouseInput.X;
				}

				//Wheel moved.
				if (event.MouseInput.Event == EMIE_MOUSE_WHEEL)
				{
					mouse.wheel += event.MouseInput.Wheel;
				}

				//Left Mouse Button Pressed
				if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
				{
					//
					if (mouseButtonState[0] == UP || mouseButtonState[0] == RELEASED)
					{
						mouseButtonState[0] = PRESSED;
					}
					else
					{
						mouseButtonState[0] = DOWN;
					}
				}

				//Left Mouse Button Rleased
				if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
				{
					//
					if (mouseButtonState[0] != UP)
					{
						mouseButtonState[0] = RELEASED;
					}
				}

				//Middle Mouse Button Pressed
				if (event.MouseInput.Event == EMIE_MMOUSE_PRESSED_DOWN)
				{
					//
					if (mouseButtonState[1] == UP || mouseButtonState[1] == RELEASED)
					{
						mouseButtonState[1] = PRESSED;
					}
					else
					{
						mouseButtonState[1] = DOWN;
					}
				}

				//Middle Mouse Button Rleased
				if (event.MouseInput.Event == EMIE_MMOUSE_LEFT_UP)
				{
					//
					if (mouseButtonState[1] != UP)
					{
						mouseButtonState[1] = RELEASED;
					}
				}

				//Right Mouse Button Pressed
				if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
				{
					//
					if (mouseButtonState[2] == UP || mouseButtonState[2] == RELEASED)
					{
						mouseButtonState[2] = PRESSED;
					}
					else
					{
						mouseButtonState[2] = DOWN;
					}
				}

				//Right Mouse Button Rleased
				if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
				{
					//
					if (mouseButtonState[2] != UP)
					{
						mouseButtonState[2] = RELEASED;
					}
				}
			}

			eventprocessed = true;
		}

		if (event.EventType == EET_GUI_EVENT)
		{
			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
			{
				/*
				If a button was clicked, it could be one of 'our'
				three buttons. If it is the first, we shut down the engine.
				If it is the second, we create a little window with some
				text on it. We also add a string to the list box to log
				what happened. And if it is the third button, we create
				a file open dialog, and add also this as string to the list box.
				That's all for the event receiver.
				*/
				theLastEvent = event.EventType;
				theLastID = event.GUIEvent.Caller->getID();
			}
			else
			{
				theLastEvent = (irr::EEVENT_TYPE) -1;
				theLastID = 0;
			}
			eventprocessed = true;
		}

		return false;
	}

	bool keyPressed(char keycode)
	{
		if (keyState[keycode] == PRESSED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool keyDown(char keycode)
	{
		if (keyState[keycode] == DOWN || keyState[keycode] == PRESSED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool keyUp(char keycode)
	{
		if (keyState[keycode] == UP || keyState[keycode] == RELEASED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool keyReleased(char keycode)
	{
		if (keyState[keycode] == RELEASED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//////////////////////
	// Public functions
	//////////////////////
public:

	float mouseWheel()
	{
		return mouse.wheel;
	}

	int mouseX()
	{
		return mouse.X;
	}

	int mouseY()
	{
		return mouse.Y;
	}

	bool leftMouseReleased()
	{
		if (mouseButtonState[0] == RELEASED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool leftMouseUp()
	{
		if (mouseButtonState[0] == RELEASED || mouseButtonState[0] == UP)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool leftMousePressed()
	{
		if (mouseButtonState[0] == PRESSED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool leftMouseDown()
	{
		if (mouseButtonState[0] == PRESSED || mouseButtonState[0] == DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool middleMouseReleased()
	{
		if (mouseButtonState[1] == RELEASED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool middleMouseUp()
	{
		if (mouseButtonState[1] == RELEASED || mouseButtonState[1] == UP)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool middleMousePressed()
	{
		if (mouseButtonState[1] == PRESSED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool middleMouseDown()
	{
		if (mouseButtonState[1] == PRESSED || mouseButtonState[1] == DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rightMouseReleased()
	{
		if (mouseButtonState[2] == RELEASED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool rightMouseUp()
	{
		if (mouseButtonState[2] == RELEASED || mouseButtonState[2] == UP)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rightMousePressed()
	{
		if (mouseButtonState[2] == PRESSED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rightMouseDown()
	{
		if (mouseButtonState[2] == PRESSED || mouseButtonState[2] == DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//

	// This is used to check whether a key is being held down
	virtual bool IsButtonClicked(void) const
	{
		return (theLastEvent != (irr::EEVENT_TYPE) -1);
	}

	// This is used to check whether a key is being held down
	virtual int GetButtonID(void) const
	{
		return theLastID;
	}

	MyEventReceiver()
	{
		Initialise();
	}

	void Initialise(void)
	{
		theLastEvent = (irr::EEVENT_TYPE) -1;
		theLastID = 0;
	}

	// This is used so that the Key States will not be changed during execution of your Main game loop.
	// Place this function at the END of your Main Loop.
	void startEventProcess()
	{

		processState = STARTED;
		//Keyboard Key States
		for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
		{
			if (keyState[i] == RELEASED)
			{
				keyState[i] = UP;
			}

			if (keyState[i] == PRESSED)
			{
				keyState[i] = DOWN;
			}
		}
	}

	// This is used so that the Key States will not be changed during execution of your Main game loop.
	// Place this at the very START of your Main Loop
	void endEventProcess()
	{
		processState = ENDED;
	}

private:
	// Enumeration for Event Handling State.
	enum processStateENUM {STARTED, ENDED};

	processStateENUM processState; // STARTED = handling events, ENDED = not handling events

	// Enumeration for UP, DOWN, PRESSED and RELEASED key states. Also used for mouse button states.
	enum keyStatesENUM {UP, DOWN, PRESSED, RELEASED};

	// Keyboard key states.
	keyStatesENUM keyState[KEY_KEY_CODES_COUNT];

	// Mouse button states.
	keyStatesENUM mouseButtonState[2]; //Left(0), Middle(1) and Right(2) Buttons.

	// Mouse X/Y coordinates and Wheel data.
	struct mouseData
	{
		int X;
		int Y;
		float wheel; //wheel is how far the wheel has moved
	};
	struct mouseData mouse;

	// For buttons and other controls in the GUI
	irr::EEVENT_TYPE theLastEvent;
	int	theLastID;
};
