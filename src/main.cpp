#include <bitset>
#include <iostream>
#include <unistd.h>

#include <extoll/extoll.h>

using std::cerr;
using std::cout;
using std::hex;

using namespace extoll::library;


#include <cassert>

int _main(RMA2_Nodeid node, uint8_t hicann)
{
	using namespace rf;
	using namespace jtag;

	auto rf = Extoll::Instance().register_file(node);
	auto fpga = Extoll::Instance().fpga(node);

	std::cout << "Driver: 0x" << std::hex << rf.read<Driver>().version() << "\n";

	rf.write<JtagSend>({0xffffffffffff});
	rf.write<JtagCmd>({JtagCmd::IR, 6 * 8, false, true});
	usleep(1000);

	rf.write<JtagSend>({1});
	rf.write<JtagCmd>({JtagCmd::DR, 9, false, true});
	usleep(1000);

	uint64_t shifted = rf.read<JtagReceive>().raw % 512;
	int hicanns_in_chain = -1;
	while (shifted) {
		shifted >>= 1u;
		++hicanns_in_chain;
	}

	std::cout << "Jtag Chain: " << hicanns_in_chain << "\n";

	auto jtag = Extoll::Instance().jtag(node);
	jtag.reset();
	std::cout << "Hicann ID: 0x" << std::hex << jtag.read<ID>(hicann) << "\n";


	std::cout << "configuring partner host ...\n";
	fpga.configure_partner_host();
	std::cout << "done\n";


	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		cerr << "usage: " << argv[0] << " NODE Hicann\n";
		return EXIT_FAILURE;
	}

	auto node = RMA2_Nodeid(std::stoi(argv[1], nullptr, 0));
	auto hicann = uint8_t(std::stoi(argv[2], nullptr, 0));

	if (hicann > 7) {
		cerr << "Hicann must be in range [0, 7]\n";
		return EXIT_FAILURE;
	}

	try {
		return _main(node, hicann);
	} catch (std::exception& e) {
		cerr << "ERROR: " << e.what() << "\n";
	}
}
