#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define FP_SCALE_SHIFT  10
#define ANGLE_2_RAD   0.0174533
#define RAD_2_ANGLE   57.295780
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

constexpr uint16_t FP_SCALE = (1 << FP_SCALE_SHIFT);

#define FORCE_INLINE inline __attribute__((always_inline)) 
#define PROGMEM 
#endif