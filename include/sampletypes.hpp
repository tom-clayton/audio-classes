/**
 * @file sampletypes.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#pragma once

// All floating point types used in library are listed, set to double or float.

#ifdef USE_DOUBLES
typedef double audio_sample_t;
typedef double control_sample_t;
typedef double delta_time_t;
typedef double filter_coef_t;
typedef double floating_point_t;

#else
typedef float audio_sample_t;
typedef float control_sample_t;
typedef float delta_time_t;
typedef float filter_coef_t;
typedef float floating_point_t;

#endif