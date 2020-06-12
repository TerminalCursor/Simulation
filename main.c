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
	printf("Booting up a simple simulation that only considers the non-bonded electrostatic potential\n");
	int MAX_STEP = 10;
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
	for(int step = 0; step < MAX_STEP; step++) {
		for(int i = 0; i < len; i++) {
			printf("%i's position is now: (%f, %f, %f)\n", i, next[i]->pos[0], next[i]->pos[1], next[i]->pos[2]);
			printf("%i's velocity is now: (%f, %f, %f)\n", i, next[i]->vel[0], next[i]->vel[1], next[i]->vel[2]);
		}
		printf("Mean distance is: %f\n", mean_dist(len, next));
		clonePpp(len, current, prev);
		clonePpp(len, next, current);
		next_step(len, prev, current, next, 1, pf);
	}
	freePpp(len, next);
	freePpp(len, current);
	freePpp(len, prev);
	for(int i = 0; i < len; i++) {
		free_particle(rs[i]);
	}
	return 0;
}
