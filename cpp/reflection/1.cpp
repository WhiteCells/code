#include <iostream>
#include <string>
#include <unordered_map>

#define REFLECT()                                                   \
    static std::unordered_map<std::string, std::string> GetFields() \
    {                                                               \
        return fields;                                              \
    }                                                               \
    static std::unordered_map<std::string, std::string> fields;

#define REGISTER_FIELD(classType, fieldName) \
    #classType::fields[#fieldName] = #fieldName;

class MyClass
{
public:
    int x;
    float y;

    REFLECT()
};

// 在全局作用域注册字段
std::unordered_map<std::string, std::string> MyClass::fields;
REGISTER_FIELD(MyClass, &MyClass::x)
REGISTER_FIELD(MyClass, &MyClass::y)

int main()
{
    for (const auto &[field, type] : MyClass::GetFields()) {
        std::cout << "Field: " << field << ", Type: " << type << std::endl;
    }
    return 0;
}
