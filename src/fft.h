
#pragma once

#include <complex>
#include <vector>

namespace jp
{
	class Fft
	{
	public:
		typedef std::complex<float> Complex;

		static void fft(std::vector<Complex>& a, bool invert = false) noexcept;
		static void ifft(std::vector<Complex>& a) noexcept;

	private:
		static inline void getNewIndex(size_t n, size_t& index) noexcept;
	};
}
