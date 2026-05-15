#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include <vector>

using std::unique_ptr;
using std::shared_ptr;
int main() {
	std::shared_ptr<Airplane> at = std::make_shared<PrivateJet>("F16");
	unique_ptr<Airplane> uniquePlane1 = std::make_unique<PassengerPlane>("Boeing", 100);
	unique_ptr<Airplane> cloned1 = uniquePlane1->clone();

	shared_ptr<Airplane> shared = std::move(uniquePlane1);

	std::vector<shared_ptr<Airplane>> v;
	v.push_back(std::move(cloned1));
	v.push_back(shared);

	std::vector<shared_ptr<Airplane>> v2;
	v2.push_back(shared);

	for (const auto& p : v) {
		std::cout << p->info() << "\n";
	}
}