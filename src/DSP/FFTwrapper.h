/*
    FFTwrapper.h  -  A wrapper for Fast Fourier Transforms

    Original ZynAddSubFX author Nasca Octavian Paul
    Copyright (C) 2002-2005 Nasca Octavian Paul
    Copyright 2009-2010, Alan Calvert

    This file is part of yoshimi, which is free software: you can redistribute
    it and/or modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    yoshimi is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.   See the GNU General Public License (version 2 or
    later) for more details.

    You should have received a copy of the GNU General Public License along with
    yoshimi; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA  02110-1301, USA.

    This file is a derivative of a ZynAddSubFX original, modified October 2010
*/

#ifndef FFT_WRAPPER_H
#define FFT_WRAPPER_H

#include <fftw3.h>
#include <boost/shared_array.hpp>

typedef struct {
    boost::shared_array<float> boost_s;  // sine and cosine components
    float *s;
    boost::shared_array<float> boost_c;
    float *c;
} FFTFREQS;


class FFTwrapper
{
    public:
        FFTwrapper(int fftsize_);
        ~FFTwrapper();
        void smps2freqs(float *smps, FFTFREQS *freqs);
        void freqs2smps(FFTFREQS *freqs, float *smps);
        static void newFFTFREQS(FFTFREQS& f, int size);
        static void deleteFFTFREQS(FFTFREQS& f);

    private:
        int fftsize;
        int half_fftsize;
        boost::shared_array<float> boost_data1;
        float *data1;
        boost::shared_array<float> boost_data2;
        float *data2;
        fftwf_plan planBasic;
        fftwf_plan planInv;
};
#endif
