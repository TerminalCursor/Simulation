#include "Verlet.h"

Particle* next_position(int n, Particle** prev, Particle** current, int i, int nf, double (*potential[])(int, Particle**, int)) {
	Particle* next = copy_particle(current[i]);
	// From the verlet algorithm - first terms for the next position
	for(int k = 0; k < DIM; k++) {
		next->pos[k] = 2 * current[i]->pos[k] - prev[i]->pos[k];
	}
	// Calculate the forces
	for(int j = 0; j < n; j++) {
		if(i != j) {
			for(int k = 0; k < nf; k++) {
				double* force = particle_force(n, current, i, potential[k]);
				for(int m = 0; m < DIM; m++) {
					next->pos[m] += force[m] / next->m * DT * DT;
				}
				free(force);
			}
		}
	}
	return next;
}

Particle* next_velocity(int n, Particle** prev, Particle** next, int i) {
	Particle* updated = copy_particle(next[i]);
	for(int k = 0; k < DIM; k++) {
		updated->vel[k] = (1 / (2.0 * DT)) * (updated->pos[k] - prev[i]->pos[k]);
	}
	return updated;
}

void next_step(int n, Particle** prev, Particle** current, Particle** next, int nf, double (*potentials[])(int, Particle**, int)) {
	Particle** next_p = (Particle**)malloc(sizeof(Particle*) * n);
	for(int i = 0; i < n; i++) {
		next_p[i] = next_position(n, prev, current, i, nf, potentials);
	}
	for(int i = 0; i < n; i++) {
		next[i] = next_velocity(n, prev, next_p, i);
	}
	for(int i = 0; i < n; i++) {
		free_particle(next_p[i]);
	}
	free(next_p);
}
