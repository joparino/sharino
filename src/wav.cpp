
#include <fstream>
#include <exception>
#include <algorithm>
#include "wav.h"
#include "fft.h"

jp::Wav::Wav(const std::string& path) noexcept(false)
{
	std::fstream file(path, std::ios::binary | std::ios::in);

	if (!file.is_open())
	{
		throw std::runtime_error{ "File is not accessible" };
	}

	file.read(reinterpret_cast<char*>(&riff_), sizeof(riff_));

	while (!file.eof())
	{
		uint32_t id{};
		file.read(reinterpret_cast<char*>(&id), sizeof(id));

		switch (id)
		{
		case fmt:
			file.read(reinterpret_cast<char*>(&fmt_.subChunk1Size_),
				static_cast<std::streamsize>(sizeof(fmt_) - sizeof(uint32_t)));
			break;
		case data:
			file.read(reinterpret_cast<char*>(&data_.subChunk2Size_),
				static_cast<std::streamsize>(sizeof(data_) - sizeof(uint32_t)));
			samples_.resize(data_.subChunk2Size_);
			file.read(reinterpret_cast<char*>(const_cast<valueType*>(samples_.data())),
				samples_.size() * sizeof(valueType));
			break;
		default:
			uint32_t subChunkSize{};
			file.read(reinterpret_cast<char*>(&subChunkSize), sizeof(subChunkSize));
			file.seekg(static_cast<std::streamoff>(subChunkSize), std::ios_base::cur);
			break;
		}
	}
	file.close();
}

jp::Fingerprint jp::Wav::generateFingeprint()
{
	std::vector<Fft::Complex> spectrum(FFT_SIZE);

	for (size_t i{}; i < FFT_SIZE; ++i)
	{
		spectrum[i] = (i < samples_.size()) ? Fft::Complex{ static_cast<float>(samples_[i]), 0.0f } : Fft::Complex{ 0.0f, 0.0f };
	}

	Fft::fft(spectrum);

	std::vector<Peaks> peaks{};
	for (size_t i{}; i < FFT_SIZE / 2; ++i)
	{
		peaks.emplace_back(i, std::abs(spectrum[i]));
	}

	std::sort(peaks.begin(), peaks.end(), [&](const Peaks& a, const Peaks& b) {
		return a.magnitude > b.magnitude;
	});

	Fingerprint fingerprint{};
	for (size_t i{}; i < NUM_PEAKS; ++i)
	{
		fingerprint[i] = peaks[i].frequency;
	}
	return fingerprint;
}
