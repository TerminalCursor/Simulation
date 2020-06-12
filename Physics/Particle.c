#include "Particle.h"

Particle* make_particle_at(int n, double* pos) {
	Particle* p = malloc(sizeof(Particle));
	for(int i = 0; i < n; i++) {
		if(i < DIM) {
			p->pos[i] = pos[i];
			p->vel[i] = 0;
		}
	}
	p->m = 1;
	p->q = 1;
	return p;
}

Particle* copy_particle(Particle* p) {
	Particle* copy = malloc(sizeof(Particle));
	for(int i = 0; i < DIM; i++) {
		copy->pos[i] = p->pos[i];
		copy->vel[i] = p->vel[i];
	}
	copy->m = p->m;
	copy->q = p->q;
	return copy;
}

void free_particle(Particle* p) {
	free(p);
}
