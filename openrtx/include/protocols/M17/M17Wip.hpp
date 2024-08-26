#ifndef M17_WIP
#define M17_WIP

#include <cstdint>
#include <cstdio>
#include <array>
#include <iir.hpp>

template <size_t SAMPLES_PER_SYMBOL>
class ClockRecovery
{
public:

    void sample(stream_sample_t& sample)
    {
        int32_t delta = (int32_t) sample - (int32_t) prevSample;

        if((sample + prevSample) < 0)
            delta = -delta;

        energy[curIdx] += delta;
        prevSample      = sample;
        curIdx          = (curIdx + 1) % SAMPLES_PER_SYMBOL;
        numSamples     += 1;
    }

    uint8_t update()
    {
        uint8_t index = 0;
        bool    is_positive = false;

        for (size_t i = 0; i < SAMPLES_PER_SYMBOL; ++i)
        {
            int32_t phase = energy[i];

            if (!is_positive && phase > 0)
            {
                is_positive = true;
            }
            else if (is_positive && phase < 0)
            {
                index = i;
                break;
            }
        }

        energy.fill(0);

        sp = (index == 0) ? SAMPLES_PER_SYMBOL - 1 : index - 1;
        return sp;
    }

    void reset()
    {
        curIdx = 0;
        prevSample = 0;
        numSamples = 0;
        energy.fill(0);
    }

    uint8_t samplePoint() { return sp; }

private:

    std::array< int32_t, SAMPLES_PER_SYMBOL > energy;
    size_t curIdx;
    size_t numSamples;
    stream_sample_t prevSample;
    uint8_t sp;
};

#endif
