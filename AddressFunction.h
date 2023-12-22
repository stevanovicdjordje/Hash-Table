#ifndef ASP2DZ3_ADDRESSFUNCTION_H
#define ASP2DZ3_ADDRESSFUNCTION_H

class AddressFunction {
public:
    virtual int get_address(long long int key, int base_address, int attempt, int size) = 0;

    virtual ~AddressFunction() = default;
};

#endif //ASP2DZ3_ADDRESSFUNCTION_H
