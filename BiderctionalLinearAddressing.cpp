#include "BidirectionalLinearAddressing.h"

int BLinearAddress::get_address(long long int key, int base_address, int attempt, int size) {
    if (attempt % 2 == 1) {
        return base_address + attempt * step;
    } else {
        return base_address - (attempt - 1) * step;
    }
}
