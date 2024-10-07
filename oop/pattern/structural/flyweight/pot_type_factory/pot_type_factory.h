#ifndef _POT_TYPE_FACTORY_H_
#define _POT_TYPE_FACTORY_H_

#include "pot.h"
#include <map>
#include <mutex>

class PotTypeFactory {
public:
    static PotTypeFactory *getInstance();
    PotType *getPot(std::string id, std::string color, double size);

private:
    PotTypeFactory();
    ~PotTypeFactory();
    PotTypeFactory &operator=(const PotTypeFactory &) = delete;
    PotTypeFactory(const PotTypeFactory &) = delete;

    class CleanUp {
    public:
        ~CleanUp();
    };

private:
    static PotTypeFactory *instance_;
    static std::mutex mutex_;
    std::map<std::string, PotType *> pot_types_;
};

#endif // _POT_TYPE_FACTORY_H_