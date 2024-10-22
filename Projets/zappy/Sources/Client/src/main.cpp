#include "Client.hpp"

int main(int argc, char **argv) {
	Client client;
	try {
		client.Initialize(argc, argv);
		client.Start();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
