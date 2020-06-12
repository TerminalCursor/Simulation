#include "Potentials.h"

double electrostaticPotential(int n, Particle** ps, int j) {
	double retPot = 0;
	for(int i = 0; i < n; i++) {
		if(i != j) {
			double rs = 0;
			for(int k = 0; k < DIM; k++) {
				rs += pow(ps[i]->pos[k] - ps[j]->pos[k], 2);
			}
			rs = sqrt(rs);
			retPot += ps[i]->q * ps[j]->q * 9e9 / rs;
		}
	}
	return retPot;
}
