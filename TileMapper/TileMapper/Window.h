#pragma once
#include <string>

#include <SDL.h>
#define SDL_WINDOW_WINDOWED 0
#define DEFAULT_RES_X 1024
#define DEFAULT_RES_Y 768

namespace TileMapper {

	// We aren't likely to deal with resolutions beyond 65535x65535.
	typedef unsigned short int res;

	// We want to shorten things up by making sure that we have access to STD types and classes.
	using std::string;
	
	class Window {
	private:
		res WindowX, WindowY; // The resolution of the screen.
		res WinposX, WinposY; // The position of the window on screen.

		SDL_Window *window;
		SDL_Renderer *renderer;
		string windowTitle;

	public:
		Window(const string title, res posX, res posY, res resX, res resY) : windowTitle(title), WinposX(posX), WinposY(posY), WindowX(resX), WindowY(resY) { SDL_Init(SDL_INIT_VIDEO); }
		Window(const string title, res resX, res resY) : windowTitle(title), WinposX(SDL_WINDOWPOS_UNDEFINED), WinposY(SDL_WINDOWPOS_UNDEFINED), WindowX(resX), WindowY(resY) { SDL_Init(SDL_INIT_VIDEO); }
		Window(const string title) : windowTitle(title), WinposX(SDL_WINDOWPOS_UNDEFINED), WinposY(SDL_WINDOWPOS_UNDEFINED), WindowX(DEFAULT_RES_X), WindowY(DEFAULT_RES_Y) { SDL_Init(SDL_INIT_VIDEO); }
		~Window() { Close(); } // Just call the close function upon destroying any variable that makes use of this class.

		void Show() { // This will overwrite our class variables if we decide to recall the constructor for this class, just be aware of this.
			window = SDL_CreateWindow(windowTitle.c_str(), WinposX, WinposY, WindowX, WindowY, SDL_WINDOW_WINDOWED | SDL_WINDOW_OPENGL);
			/* SDL_WINDOW_FULLSCREEN			| Fullscreen window
			 * SDL_WINDOW_FULLSCREEN_DESKTOP	| Fullscreen window at the current desktop resolution
			 * SDL_WINDOW_OPENGL				| Window usable with OpenGL context
			 * SDL_WINDOW_VULKAN				| Window usable with a Vulkan instance
			 * SDL_WINDOW_SHOWN					| Window is visible
			 * SDL_WINDOW_HIDDEN				| Window is not visible
			 * SDL_WINDOW_BORDERLESS			| No window decoration
			 * SDL_WINDOW_RESIZABLE				| Window can be resized
			 * SDL_WINDOW_MINIMIZED				| Window is minimized
			 * SDL_WINDOW_MAXIMIZED				| Window is maximized
			 * SDL_WINDOW_INPUT_GRABBED			| Window has grabbed input focus, please don't do this to people
			 * SDL_WINDOW_INPUT_FOCUS			| Window has input focus, please don't do this to people
			 * SDL_WINDOW_MOUSE_FOCUS			| Window has mouse focus, please don't do this to people
			 * SDL_WINDOW_FOREIGN				| Window was not created by SDL
			 * SDL_WINDOW_ALLOW_HIGHDPI			| Window should have High-DPI support >= SDL 2.0.1
			 * SDL_WINDOW_MOUSE_CAPTURE			| Window has mouse captured >= SDL 2.0.4, please don't do this to people
			 * SDL_WINDOW_ALWAYS_ON_TOP			| Window should always be above others >= SDL 2.0.5, this can conflict with other windows that are set to "always on top"
			 * SDL_WINDOW_SKIP_TASKBAR			| Don't show up in the taskbar >= SDL 2.0.5
			 * SDL_WINDOW_UTILITY				| Treat the window as a utility window >= SDL 2.0.5
			 * SDL_WINDOW_TOOLTIP				| Treat the window as a tooltip window >= SDL 2.0.5
			 * SDL_WINDOW_POPUP_MENU			| Treat the window as a popup window >= SDL 2.0.5
			 */

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue color (Red, Green, Blue, Alpha (Opacity))
			SDL_RenderClear(renderer);   // Clear the window screen to change from white to our sky blue color.
			SDL_RenderPresent(renderer); // Show the new sky blue color.
		}

		void Close() {
			SDL_RenderClear(renderer);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
	};
}