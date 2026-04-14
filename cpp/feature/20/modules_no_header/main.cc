#include <iostream>
import auth;

int main()
{
    const User admin {"alice", "admin"};
    const User dev {"bob", "developer"};

    std::cout << "alice -> /prod/restart : "
              << (CanAccess(admin, "/prod/restart") ? "allow" : "deny")
              << '\n';
    std::cout << "bob   -> /prod/restart : "
              << (CanAccess(dev, "/prod/restart") ? "allow" : "deny")
              << '\n';
    std::cout << "bob   -> /wiki         : "
              << (CanAccess(dev, "/wiki") ? "allow" : "deny") << '\n';

    return 0;
}
