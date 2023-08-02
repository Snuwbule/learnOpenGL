#include <iostream>
#include "errorOutput.h"


void outputError(const char* msg, bool box) {
	std::cerr << "ERROR: " << msg << '\n';

	if (!box) { return; }

	if (userOS == "win") {
		MessageBox(NULL, msg, "Error!", MB_ICONERROR | MB_OK);
	}
}