//
// Created by simon on 4/11/26.
//

#ifndef WHEEL_H
#define WHEEL_H
#include <raylib.h>

namespace Simulation {
    class Wheel {
    public:
        void setDrive(const bool drive) {m_drive = drive;}
    private:
        bool m_drive {false};
        Vector2 position {};
    };
}

#endif //WHEEL_H
