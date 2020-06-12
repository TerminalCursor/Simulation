#include "Differentiation.h"

Particle** copyPpp(int n, Particle** p) {
	Particle** copy = (Particle**)malloc(sizeof(Particle*) * n);
	for(int i = 0; i < n; i++) {
		copy[i] = malloc(sizeof(Particle));
		copy[i] = copy_particle(p[i]);
	}
	return copy;
}

void clonePpp(int n, Particle** src, Particle** dest) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < DIM; j++) {
			dest[i]->pos[j] = src[i]->pos[j];
			dest[i]->vel[j] = src[i]->vel[j];
		}
		dest[i]->m = src[i]->m;
		dest[i]->q = src[i]->q;
	}
}

void freePpp(int n, Particle** p) {
	for(int i = 0; i < n; i++) {
		free_particle(p[i]);
	}
	free(p);
}

double* particle_force(int n, Particle** fin, int j, double (*potential)(int, Particle**, int)) {
	double* returnSlope = calloc(DIM, sizeof(double));
	for(int i = 0; i < n; i++) {
		if(j != i) {
			for(int k = 0; k < DIM; k++) {
				Particle** pCopyUp = copyPpp(n, fin);
				Particle** pCopyDown = copyPpp(n, fin);
				pCopyUp[i]->pos[k] += DERIV_STEP;
				pCopyDown[i]->pos[k] -= DERIV_STEP;
				double high = potential(n, pCopyUp, j);
				double low = potential(n, pCopyDown, j);
				freePpp(n, pCopyUp);
				freePpp(n, pCopyDown);
				returnSlope[k] += (high - low) / (2 * DERIV_STEP);
			}
		}
	}
	return returnSlope;
}
