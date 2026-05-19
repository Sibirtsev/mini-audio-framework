#include <maf/core/Hello.h>

int main()
{
    if (maf::core::hello() != "hello")
    {
        return 1;
    }

    return 0;
}
