module;
#include <string>
#include <string_view>
#include <unordered_set>

module auth;

// namespace auth {

bool CanAccess(const User &user, std::string_view resource)
{
    static const std::unordered_set<std::string_view> kAdminOnly {
        "/prod/restart", "/prod/ops", "/finance/payroll"};
    if (kAdminOnly.contains(resource)) {
        return user.role == "admin";
    }
    return true;
}

// } // namespace auth
