
#include "src/sharino.h"
#include <iostream>

int main()
{
	std::string path{};
	jp::Sharino sharino{};

	std::cout << "To exit input: kekw" << std::endl;
	while (true)
	{
		std::cout << "Input path to song: ";
		std::cin >> path;

		if (path == "kekw")
		{
			break;
		}

		std::cout << sharino.getNameMatchSong(sharino.getFingerprint(path)) << std::endl;
		std::cout << "==================================================================" << std::endl;
	}

	return 0;
}
