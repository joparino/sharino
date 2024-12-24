
#include "sharino.h"
#include <iostream>
#include <filesystem>

jp::Sharino::Sharino()
{
	std::ifstream fileSavesFingerprints(saveFilename, std::ios::binary | std::ios::in);

	if (!fileSavesFingerprints.is_open())
	{
		throw std::runtime_error{ "Save fingerprint file is not accessible" };
	}

	std::string line;
	while (std::getline(fileSavesFingerprints, line))
	{
		std::istringstream iss(line);

		std::string key{};
		iss >> key;

		Fingerprint fingerprint{};
		for (int& value : fingerprint)
		{
			iss >> value;
		}
		_cachedFingerprints[key] = fingerprint;
	}

	fileSavesFingerprints.clear();
	fileSavesFingerprints.close();
}

jp::Sharino::~Sharino()
{
	std::ofstream fileSavesFingerprints(saveFilename, std::ios::binary | std::ios::out);

	if (fileSavesFingerprints.is_open())
	{
		for (const auto& [key, fingerprint] : _cachedFingerprints)
		{
			std::string strFingerprint{};
			for (const auto value : fingerprint)
			{
				strFingerprint += ' ' + std::to_string(value);
			}
			fileSavesFingerprints << key + strFingerprint << std::endl;
		}

		fileSavesFingerprints.close();
	}
}

jp::Fingerprint jp::Sharino::getFingerprint(const std::string& path)
{
	const auto& filename{ getFileName(path) };
	_cachedFingerprints[filename] = Wav(path).generateFingeprint();
	return _cachedFingerprints[filename];
}

const std::string jp::Sharino::getNameMatchSong(const Fingerprint& peaks) const
{
	for (const auto& [key, value] : _cachedFingerprints)
	{
		if (value == peaks)
		{
			return "Match song: " + key;
		}
	}

	return "Sorry didn't find song";
}

const std::string jp::Sharino::getFileName(const std::string& path) const
{
	std::filesystem::path file_path(path);
	return file_path.stem().string();
}
