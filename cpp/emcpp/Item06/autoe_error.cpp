#include <iostream>
#include <vector>

using Widget = int;

std::vector<bool> features(const Widget &w) {
    return {1, 0, 1};
}

Widget w = 5;

auto highPriority = features(w)[1];

void processWidget(const Widget &w, bool highPriority) {
    std::cout << w << ' ' << highPriority << std::endl;
}

int main() {
    processWidget(w, highPriority);
    return 0;
}