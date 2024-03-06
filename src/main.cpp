#include <string>

#include "liquid.hpp"
#include "HomePage.hpp"

int main()
{
    const auto page = HomePage();
    page();
    return 0;
}