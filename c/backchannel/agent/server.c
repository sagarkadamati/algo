#include "server.h"

void server()
{
	int sskt, cskt;

	sskt = alloc_socket();
	bind_socket(sskt);

	while (1) {
		listen_for_connections(sskt);
		cskt = accept_connection(sskt);

		process_request(cskt);
	}

	release_socket(sskt);
}
