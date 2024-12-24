
#pragma once

#include <numeric>
#include <array>
#include <vector>
#include <string>

namespace jp
{
	using valueType = int16_t;
	constexpr valueType NUM_PEAKS{ 5 };
	constexpr valueType FFT_SIZE = 4096;
	typedef std::array<int, NUM_PEAKS> Fingerprint;

	struct Peaks
	{
		int frequency;
		float magnitude;
	};

	class Wav
	{
	public:
		Wav(const std::string& path) noexcept(false);

		Fingerprint generateFingeprint();

	private:
		const static uint32_t fmt{ 0x20746d66 };
		const static uint32_t data{ 0x61746164 };
		struct
		{
			uint32_t chunkId_{ 0x52494646 }; // "RIFF"
			uint32_t chunkSize_{};
			uint32_t format_{ 0x57415645 }; // "WAVE"
		} riff_;

		struct
		{
			uint32_t subChunk1Id_{ fmt };
			uint32_t subChunk1Size_{ 16u };
			uint16_t audioFormat_{ 1u };
			uint16_t numChannels_{ 2u };
			uint32_t sampleRate_{ 44100u };
			uint32_t byteRate_{};
			uint16_t blockAlign_{};
			uint16_t bitsPerSample_{ 16u };
		} fmt_;

		struct
		{
			uint32_t subChunk1Id_{ 0x61746164 }; // "data"
			uint32_t subChunk2Size_{};
		} data_;
		std::vector<valueType> samples_;
	};
}
