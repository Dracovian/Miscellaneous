#include "Window.h"

// Obligatory entrypoint function for most C/C++ standard libraries.
int main(int argc, char **argv) {
	const std::string title = "Test Window";
	auto window = TileMapper::Window(title, 0, 32, 1280, 720); // Create a 720p window and place it at least 32 pixels down to account for any overscan that hides the window title and close button.

	bool isClosed = false;
	window.Show();

	while (!isClosed) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isClosed = true;
				break;

			default:
				break;
			}
		}
	}

	window.Close();
	SDL_Quit();
	return 0;
}