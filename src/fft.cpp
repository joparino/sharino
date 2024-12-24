
#include <numbers>
#include "fft.h"

void jp::Fft::fft(std::vector<Complex>& a, bool invert) noexcept
{
	const auto n{ a.size() };

	for (size_t i{ 1 }, j{}; i < n; ++i)
	{
		getNewIndex(n, j);
		if (i < j)
		{
			std::swap(a[i], a[j]);
		}
	}

	for (size_t length{ 2 }; length <= n; length *= 2)
	{
		const float angel{ 2.f * std::numbers::pi_v<float> / length * (invert ? -1.f : 1.f) };
		const Complex primitiveFirstRoot{ std::cos(angel), std::sin(angel) };

		for (size_t i{}; i < n; i += length)
		{
			Complex w{ 1.f };
			for (size_t j{}; j < length / 2; ++j)
			{
				const Complex u{ a[i + j] };
				const Complex v{ a[i + j + length / 2] * w };
				a[i + j] = u + v;
				a[i + j + length / 2] = u - v;
				w *= primitiveFirstRoot;
			}
		}
	}
	if (invert)
	{
		const Complex complexN{ static_cast<float>(n) };
		for (size_t i{}; i < n; ++i)
		{
			a[i] /= complexN;
		}
	}
}


void jp::Fft::ifft(std::vector<Complex>& a) noexcept
{
	fft(a, true);
}


inline void jp::Fft::getNewIndex(size_t n, size_t& index) noexcept
{
	size_t bit{ n >> 1u };

	for (; index >= bit; bit >>= 1)
	{
		index -= bit;
	}

	index += bit;
}
