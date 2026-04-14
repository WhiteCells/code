module;
#include <string>
#include <string_view>

export module auth;

// export namespace auth {

export struct User
{
    std::string name;
    std::string role;
};

export bool CanAccess(const User &user, std::string_view resource);

// } // namespace auth
