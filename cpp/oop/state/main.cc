#include "context.h"
#include "state_a.h"
#include "state_b.h"

int main()
{
    auto ctx = std::make_shared<Context>();
    ctx->setState(std::make_shared<StateA>());
    ctx->handle();
    ctx->setState(std::make_shared<StateB>());
    ctx->handle();
    return 0;
}