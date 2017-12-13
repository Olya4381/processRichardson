#include "GeneralizedProcessR3.h"

void GeneralizedProcessR3::processR(int n) {
	for (int i = 0; i < n; i++) {
		int k = rand() % (sockets_x.size());
		//std::cout << "Add: (" << sockets_x[k] << " , " << sockets_y[k] << " , " << sockets_z[k] << ")\n";
		Diagram3::add_vertex(sockets_x[k], sockets_y[k], sockets_z[k]);
		//print_level();
		//if (i % 100000 == 0) {
		//	std::cout << i << "\n";
		//}
	}
}
