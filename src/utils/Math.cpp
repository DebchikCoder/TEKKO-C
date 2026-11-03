#include "../headers/utils/Math.hpp"

float Util::Math::MoveTowards(float current, float target, float step)
{
      float d = target - current;
      if(std::abs(d) <= step) return target;
      return current + (step/std::abs(d)) * d;
}
