#include "mathfuncs.c"

int main(){
    struct Customer customer;
    getInfo(&customer);

    printf("\nYou entered:\n%s %s\n%s,\n%s, %s\n%s\n",
    customer.first,
    customer.last,
    customer.streetAdd,
    customer.city,
    customer.province,
    customer.postal);

    return 0;
}
