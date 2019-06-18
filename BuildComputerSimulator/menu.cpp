#include "menu.h"

size_t menu(const std::string menuOptions[], const size_t NUM_OPTIONS) {
	std::cout << "To select a menu option, either input a number, or use the arrows keys to navigate and press ENTER.\n";

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

	csbi.dwCursorPosition.X++;
	csbi.dwCursorPosition.Y -= static_cast<SHORT>(NUM_OPTIONS);

	COORD cursorPos = csbi.dwCursorPosition;

	SetConsoleCursorPosition(outConsole, cursorPos);
	std::cout << '>';
	SetConsoleCursorPosition(outConsole, cursorPos);

	while (true) {
		ReadConsoleInput(inConsole, eventBuffer, EVENT_BUFFER_SIZE, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; i++) {
			if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
				WORD keyCode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;

				if (keyCode == VK_UP || keyCode == VK_LEFT) {
					std::cout << ' ';

					menuChoice = (menuChoice == 0) ? (NUM_OPTIONS - 1) : (menuChoice - 1);
					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += static_cast<SHORT>(menuChoice);

					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';
					SetConsoleCursorPosition(outConsole, cursorPos);
				}
				else if (keyCode == VK_DOWN || keyCode == VK_RIGHT) {
					std::cout << ' ';

					menuChoice = (menuChoice == NUM_OPTIONS - 1) ? 0 : (menuChoice + 1);
					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += static_cast<SHORT>(menuChoice);

					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';
					SetConsoleCursorPosition(outConsole, cursorPos);
				}
				else if (keyCode >= 0x30 && keyCode <= 0x2f + ((NUM_OPTIONS > 10) ? 10 : NUM_OPTIONS)) {
					std::cout << ' ';

					cursorPos = csbi.dwCursorPosition;
					cursorPos.Y += keyCode - 0x30;
					SetConsoleCursorPosition(outConsole, cursorPos);
					std::cout << '>';

					cursorPos = csbi.dwCursorPosition;
					cursorPos.X--;
					cursorPos.Y += static_cast<SHORT>(NUM_OPTIONS);
					SetConsoleCursorPosition(outConsole, cursorPos);

					return keyCode - 0x30;
				}
				else if (keyCode == VK_RETURN) {
					cursorPos = csbi.dwCursorPosition;
					cursorPos.X--;
					cursorPos.Y += static_cast<SHORT>(NUM_OPTIONS);
					SetConsoleCursorPosition(outConsole, cursorPos);

					return menuChoice;
				}
			}
		}
	}
}