#include <stdio.h>
#include <math.h>
#include "Physics/Differentiation.h"
#include "Physics/Particle.h"
#include "Physics/Verlet.h"
#include "Physics/Potentials.h"

double mean_dist(int n, Particle** ps) {
	double mean = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			double rs = 0;
			for(int k = 0; k < DIM; k++) {
				rs += pow(ps[i]->pos[k]-ps[j]->pos[k], 2);
			}
			rs = sqrt(rs);
			mean += rs;
		}
	}
	return mean;
}

int main(int argc, const char* argv[]) {
	int MAX_STEP = 100;
	double (*pf[1])(int, Particle**, int);
	pf[0] = electrostaticPotential;
	double pos[] = { 0, 0, 0 };
	int len = 2;
	Particle* p1 = make_particle_at(3, pos);
	p1->q = -1;
	pos[0] = 2;
	Particle* p2 = make_particle_at(3, pos);
	Particle* rs[] = { p1, p2 };

	Particle** prev = copyPpp(len, rs);
	Particle** current = copyPpp(len, rs);
	Particle** next = copyPpp(len, rs);
	printf("t,1.x,1.y,1.z,2.x,2.y,2.z,mean distance\n");
	for(int step = 0; step < MAX_STEP; step++) {
		if(step % 10 == 0) {
			printf("%i,", step);
			for(int i = 0; i < len; i++) {
				printf("%f,%f,%f,", next[i]->pos[0], next[i]->pos[1], next[i]->pos[2]);
			}
			printf("%f\n", mean_dist(len, next));
		}
		clonePpp(len, current, prev);
		clonePpp(len, next, current);
		next_step(len, prev, current, next, 1, pf);
	}
	printf("%i,", MAX_STEP);
	for(int i = 0; i < len; i++) {
		printf("%f,%f,%f,", next[i]->pos[0], next[i]->pos[1], next[i]->pos[2]);
	}
	printf("%f\n", mean_dist(len, next));
	freePpp(len, next);
	freePpp(len, current);
	freePpp(len, prev);
	for(int i = 0; i < len; i++) {
		free_particle(rs[i]);
	}
	return 0;
}
