#include "real_estate_mediator.h"
#include "tenant.h"
#include "landlord.h"

int main(int argc, char *argv[]) {
    Mediator *mediator = new RealEstateMediator();
    User *tenant1 = new Tenant("user1", "address1",
                               "4321243", 800, mediator);
    User *tenant2 = new Tenant("user2", "address2",
                               "234123", 900, mediator);
    User *landlord = new Landlord("user3", "address3",
                                  "4312323", 700, mediator);

    mediator->registerUser(tenant1);
    mediator->registerUser(landlord);
    mediator->registerUser(tenant2);

    tenant1->ask();
    tenant2->ask();
    landlord->ask();

    delete mediator;
    return 0;
}