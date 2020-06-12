#ifndef VERLET_H
#define VERLET_H

#include <math.h>
#include <stdlib.h>
#include "Particle.h"
#include "Differentiation.h"

#define DT 0.00001

Particle* next_position(int n, Particle** prev, Particle** current, int i, int nf, double (*potential[])(int, Particle**, int));

Particle* next_velocity(int n, Particle** prev, Particle** next, int i);

void next_step(int n, Particle** prev, Particle** current, Particle** next, int nf, double (*potential[])(int, Particle**, int));

#endif
