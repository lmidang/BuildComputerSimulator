/*
Created by Bennett Zhang
*/

#include "menu.h"

size_t menu(const std::string menuOptions[], const size_t NUM_OPTIONS) {
	std::cout << "To select a menu option, either input a number, or use the arrow keys to navigate and press ENTER.\n";

	for (size_t i = 0; i < NUM_OPTIONS; i++)
		std::cout << "   " << i << ") " << menuOptions[i] << std::endl;

	HANDLE inConsole = GetStdHandle(STD_INPUT_HANDLE);
	const DWORD EVENT_BUFFER_SIZE = 128;
	INPUT_RECORD eventBuffer[EVENT_BUFFER_SIZE];
	DWORD numEventsRead;

	HANDLE outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(outConsole, &csbi);

	size_t menuChoice = 0;

	// Initialize the cursor position
	csbi.dwCursorPosition.X++;
	csbi.dwCursorPosition.Y -= static_cast<SHORT>(NUM_OPTIONS);

	COORD cursorPos = csbi.dwCursorPosition;

	// Add an arrow pointing to the first menu option
	SetConsoleCursorPosition(outConsole, cursorPos);
	std::cout << '>';
	SetConsoleCursorPosition(outConsole, cursorPos);

	while (true) {
		ReadConsoleInput(inConsole, eventBuffer, EVENT_BUFFER_SIZE, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; i++) {
			if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
				WORD keyCode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;

				// If the user presses the up or left arrow
				if (keyCode == VK_UP || keyCode == VK_LEFT) {
					// Delete the current arrow
					std::cout << ' ';

					// Move the cursor up
					menuChoice = (menuChoice == 0) ? (NUM_OPTIONS - 1) : (menuChoice - 1);
					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += static_cast<SHORT>(menuChoice);

					// Print a new arrow
					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';
					SetConsoleCursorPosition(outConsole, cursorPos);
				}
				// If the user presses the down or right arrow
				else if (keyCode == VK_DOWN || keyCode == VK_RIGHT) {
					// Delete the current arrow
					std::cout << ' ';

					// Move the cursor down
					menuChoice = (menuChoice == NUM_OPTIONS - 1) ? 0 : (menuChoice + 1);
					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += static_cast<SHORT>(menuChoice);

					// Print a new arrow
					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';
					SetConsoleCursorPosition(outConsole, cursorPos);
				}
				// If the user presses a number key
				else if (keyCode >= 0x30 && keyCode <= 0x2f + ((NUM_OPTIONS > 10) ? 10 : NUM_OPTIONS)) {
					// Delete the current arrow
					std::cout << ' ';

					// Move the cursor to the appropriate position, the print a new arrow
					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += keyCode - 0x30;
					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';

					// Move the cursor below the menu
					cursorPos = csbi.dwCursorPosition;
					cursorPos.X--;
					cursorPos.Y += static_cast<SHORT>(NUM_OPTIONS);
					SetConsoleCursorPosition(outConsole, cursorPos);

					// Return the chosen menu optino
					return keyCode - 0x30;
				}
				// If the user presses the ENTER key
				else if (keyCode == VK_RETURN) {
					// Move the cursor below the menu
					cursorPos = csbi.dwCursorPosition;
					cursorPos.X--;
					cursorPos.Y += static_cast<SHORT>(NUM_OPTIONS);
					SetConsoleCursorPosition(outConsole, cursorPos);

					// Return the chosen menu option
					return menuChoice;
				}
			}
		}
	}
}