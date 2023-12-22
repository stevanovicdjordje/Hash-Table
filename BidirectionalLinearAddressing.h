#ifndef ASP2DZ3_BIDIRECTIONALLINEARADDRESSING_H
#define ASP2DZ3_BIDIRECTIONALLINEARADDRESSING_H

#include "AddressFunction.h"

class BLinearAddress : public AddressFunction {
    int step;
public:
    explicit BLinearAddress(int step) : step(step) {}

    int get_address(long long int key, int base_address, int attempt, int size) override;
};


#endif //ASP2DZ3_BIDIRECTIONALLINEARADDRESSING_H
