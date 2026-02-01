#pragma once

#include "vectors/vectors.h"

struct UnityEngine_Touch_Fields
{
    int32_t m_FingerId;
    vectors::vector2 m_Position;
    vectors::vector2 m_RawPosition;
    vectors::vector2 m_PositionDelta;
    float m_TimeDelta;
    int32_t m_TapCount;
    int32_t m_Phase;
    int32_t m_Type;
    float m_Pressure;
    float m_maximumPossiblePressure;
    float m_Radius;
    float m_RadiusVariance;
    float m_AltitudeAngle;
    float m_AzimuthAngle;
};

enum TouchPhase
{
    Began = 0,
    Moved = 1,
    Stationary = 2,
    Ended = 3,
    Canceled = 4
};
