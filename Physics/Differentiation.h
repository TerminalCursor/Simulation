#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <stdlib.h>
#include <math.h>
#include "Particle.h"

#define DERIV_STEP 0.0000001

double* particle_force(int, Particle**, int, double (*potential)(int, Particle**, int));

Particle** copyPpp(int n, Particle** p);

void clonePpp(int n, Particle** src, Particle** dest);

void freePpp(int n, Particle** p);

#endif
