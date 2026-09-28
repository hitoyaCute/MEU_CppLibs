#include "slotmap.hpp"
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <print>

int main () {
    slotmap<char, uint8_t>* map{};

    slotmap_init(map);

    slotmap_set(map, 3, 'D');
    slotmap_set(map, 6, 'G');
    slotmap_set(map, 4, 'E');
    slotmap_set(map, 5, 'F');
    slotmap_set(map, 0, 'A');
    slotmap_set(map, 1, 'B');
    slotmap_set(map, 2, 'C');

    std::cout << "Pos   : 0 1 2 3 4 5 6 7 8 9" << std::endl;
    std::cout << "Index : ";
    for (std::size_t i = 0; i < map->index.size(); i++) {
        std::print("{} ",(int)map->index[i]);
    }
    std::cout << "\nId    : ";
    for (std::size_t i = 0; i < map->id.size(); i++) {
        std::print("{} ",map->id[i]);
    }

    std::cout << "\nItems : ";
    for (auto d: (*map)) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    slotmap_free(map);

    return 0;
}
