#define _USE_MATH_DEFINES // Must be defined before including cmath

#include "Interpolated.hpp"
#include <cmath>

namespace Interpolation {



namespace EasingFunc {

const float easeInOutElastic(const float t) {
  const float c5 = (2 * M_PI) / 4.5;
  
  if (t == 0.f) {
    return 0.f;
  } else if (t == 1.f) {
    return 1.f;
  } else if (t < 0.5) {
    return -(powf(2.f, 20.f * t - 10.f) * sinf((20.f * t - 11.125) * c5)) / 2;
  } else {
    return (powf(2.f, -20.f * t + 10.f) * sinf((20.f * t - 11.125) * c5)) / 2 + 1;
  }
}

const float easeInElastic(const float t) {
  const float c4 = (2.f * M_PI) / 3.f;

  if (t == 0.f) {
    return 0.f;
  } else if (t == 1.f) {
    return 1.f;
  } else {
    return -powf(2.f, 10.f * t - 10.f) * sinf((t * 10.f - 10.75) * c4);
  }
}

const float easeOutElastic(const float t){
  const float c4 = (2.f * M_PI) / 3.f;

  if (t == 0.f) {
    return 0.f;
  } else if (t == 1.f) {
    return 1.f;
  } else {
    return powf(2.f, -10.f * t) * sinf((t * 10 - 0.75) * c4) + 1;
  }
}

const float easeOutBack(const float t) {
  const float c1 = 1.70158;
  const float c3 = 2.70158;

  return 1 + c3 * powf(t - 1, 3) + c1 * powf(t - 1, 2);
}

const float easeInBack(const float t) {
  const float c1 = 1.70158;
  const float c3 = 2.70158;

  return c3 * t * t * t - c1 * t * t;
}

const float easeInOutExponential(const float t){
  if (t == 0.f) {
    return 0.f;
  } else if (t == 1.f) {
    return 1.f;
  } else if (t < 0.5) {
    return powf(2.f, 20.f * t - 10.f) / 2.f;
  } else {
    return (2.f - powf(2.f, -20.f * t + 10.f)) / 2.f;
  }
}

const float easeOutExponential(const float t) {
  return t == 1.f ? 1.f : 1.f - powf(2.f, -10.f * t);
}

const float easeInExponential(const float t) {
  return t == 0 ? 0 : powf(2, 10 * t - 10);
}


}; // namespace EasingFunc

const float getRatio(const float t, const Easing transition) {
  switch (transition) {
    default:
      return t;
    case Easing::None:
      return 1.f;
    case Easing::easeInOutExponential:
      return EasingFunc::easeInOutExponential(t);
    case Easing::easeOutExponential:
      return EasingFunc::easeOutExponential(t);
    case Easing::easeOutBack:
      return EasingFunc::easeOutBack(t);
    case Easing::easeInBack:
      return EasingFunc::easeInBack(t);
    case Easing::easeInOutElastic:
      return EasingFunc::easeInOutElastic(t);
    case Easing::easeInElastic:
      return EasingFunc::easeInElastic(t);
    case Easing::easeOutElastic:
      return EasingFunc::easeOutElastic(t);
  }
}

}; // namespace Interpolation


