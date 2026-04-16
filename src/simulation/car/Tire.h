//
// Created by simon on 4/16/26.
//

#ifndef CARSIMULATOR_TIRE_H
#define CARSIMULATOR_TIRE_H

namespace Simulation
{
    struct PacejkaCoefficients {
        float a1, a2, a3, a4, a5, a6, a7, a8;
        float a9, a10, a11, a12, a13;
    };
    struct TireCoefficients {
        PacejkaCoefficients Fx;
        PacejkaCoefficients Fy;
        PacejkaCoefficients Mz;
    };


    inline TireCoefficients defaultTire {

        .Fx = {
            .a1 = -21.3,
            .a2 = 1144,
            .a3 = 49.6,
            .a4 = 226,
            .a5 = 0.069,
            .a6 = -0.006,
            .a7 = 0.056,
            .a8 = 0.486,
            .a9 = 0.0,
            .a10 = 0.0,
            .a11 = 0.0,
            .a12 = 0.0,
            .a13 = 0.0
        },

        .Fy = {
            .a1 = -22.1,
            .a2 = 1011,
            .a3 = 1078,
            .a4 = 1.82,
            .a5 = 0.208,
            .a6 = 0.0,
            .a7 = -0.354,
            .a8 = 0.707,
            .a9 = 0.028,
            .a10 = 0.0,
            .a11 = 14.8,
            .a12 = 0.022,
            .a13 = 0.0
        },

        .Mz = {
            .a1 = -2.72,
            .a2 = -2.28,
            .a3 = -1.86,
            .a4 = -2.73,
            .a5 = 0.110,
            .a6 = -0.070,
            .a7 = 0.643,
            .a8 = -4.04,
            .a9 = 0.015,
            .a10 = -0.066,
            .a11 = 0.945,
            .a12 = 0.030,
            .a13 = 0.070
        }
    };
}

#endif //CARSIMULATOR_TIRE_H
