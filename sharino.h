
#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include "wav.h"

namespace jp
{
	static const std::string saveFilename{ "savesFingerprints.txt" };

	class Sharino
	{
	public:
		Sharino();
		~Sharino();

		Fingerprint getFingerprint(const std::string& path);
		const std::string getNameMatchSong(const Fingerprint& peaks) const;

	private:
		const std::string getFileName(const std::string& path) const;

	private:
		std::unordered_map<std::string, Fingerprint> _cachedFingerprints;
	};
}
