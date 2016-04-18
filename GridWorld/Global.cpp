#include "stdafx.h"
#include "Global.h"


default_random_engine Global::generator{};
uniform_real_distribution<float> Global::realDist(0.0, 1.0);

