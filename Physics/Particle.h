#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

#define DIM 3

typedef struct {
	double pos[DIM];
	double vel[DIM];
	double m, q;
} Particle;

Particle* make_particle_at(int, double*);

Particle* copy_particle(Particle*);

void free_particle(Particle*);

#endif
