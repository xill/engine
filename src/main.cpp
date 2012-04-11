#include <iostream>

#include "controller.h"

int main(int argc, char **argv)
{
	std::cout << "welcome to engine framework test project." << std::endl;

	Controller::instance()->run();

	return 0;
}
