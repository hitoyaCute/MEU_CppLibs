#pragma once
/* special type of map that store its data on a array to give it the speed of arrays
 * but we store it on a way so that we dont access it directly, we use data index
 * to refer to the element, when removing an item located `at` we could swap that
 * element to the last element the and do the same for the data index array to make
 * the data index valid
 *
 * with that we also have ID tag so that we could  refer how we can access that
 * element indirectly which we make sure id[at] is tied to items[at]
 *
 * pseudocode or explenation for each trivial operation
 * 
 * automatic insert: insert 'data'
 *   
 *   we push the element to the item array, then whatever its corresponding
 *   id we just return that
 *
 *   function insert(data)
 *      items.append(data)
 *      return id.at(items.size - 1)
 * 
 * get: get element at 'at'
 *   
 *   take the index at 'at' and use that to index items
 *   
 *   function get(at)
 *      return items.at(index.at(at))
 *
 * set/manual insert: insert 'data' at 'at'  
 *
 *   we first check if the element at 'at' is "alive", if yes
 *   just do sam,eas get but we put an item instead of get
 *   if no we do the following
 *
 *   we need to swap the index[at] with index[id[items.size]]
 *   to make the index[at] poin to the current items.size
 *   assuming we didnt grow the items yet then swap
 *   id[items.size] with id[index[id[items.size]]] to make
 *   sure id[item.size] is pointing to the reverse pointer
 *
 *   function set(at, data)
 *      if index.at(at) < items.size
 *          items.at(index.at(at)) = data
 *      else
 *          swap(index.at(at), index.at(id.at(items.size)))
 *          swap(id.at(items.size), id.at(index.at(id.at(items.size))))
 *          items.append(data)
 * 
 * deletion: delete at `at`
 *    
 *  function pop_at(at)
 *      items.at(index.at(at)) = items.at(items.size()-1)
 *      items.pop_back()
 *      swap(id.at(index.at(at)), id.at(items.size))
 *      swap(index.at(at), index.at(id.at(items.size)))
 *
 *
 *
 * source "The magic container" by Pezzza's Work (YT)
 * */



#include "num_array.hpp"

#include <vector>
#include <cstddef>
#include <cstdlib>
#include <type_traits>




/////////////////////////////////////////////////////////////////////////////
/// special type of map like container on which store its data on a
/// array(std::vector) but allowed on having gaps to allow stable ID and fast
/// O(1) access, append, and deletion
/////////////////////////////////////////////////////////////////////////////
template <typename T = int, typename index_width = std::size_t>
struct slotmap {
    // item, dynamic array containing
    // the item while managing it
    std::vector<T>         items = {};
    // id, holds the index of the items used
    // to access the elements indirectly
    num_array<index_width> index = {};
    // index, holds the id index of each element
    // used to determin the item's id index for
    // deletion
    num_array<index_width> id    = {};

    slotmap() {
        this->index.reserve(1);
        this->id.reserve(1);
    }

    // raw index
    T& operator[](const index_width i) {
        return this->items[i];
    }

    // returns a read/write reference to the first element on the internal array
    T& front() {
        return this->items.front();
    }
    // returns a read/write reference to the last element on the internal array
    T& back() {
        return this->items.back();
    }
    // returns a read/write iterator to the first element on the internal array
    auto begin() {
        return this->items.begin();
    }
    // returns a read/write iterator that points one past the last element in the internal array
    auto end() {
        return this->items.end();
    }
    //  returns the number of elements in the internal array
    index_width size() {
        return this->items.size();
    }
};

template <typename T, typename index_width>
void slotmap_init(slotmap<T, index_width>*& map) {
    if (map != 0)
        return;
    map = new slotmap<T, index_width>{};
    map->items = {};
    map->id = {};
    map->id.reset();
    map->index = {};
    map->index.reset();
}

template <typename T, typename index_width>
void slotmap_free(slotmap<T, index_width>*& map) {
    if (map == 0)
        return;
    map->items.clear();
    map->items.shrink_to_fit();
    map->index.reset();
    map->id.reset();
    delete map;
    map = 0;
}


// returns a read/write reference to the first element on the internal array
template <typename T>
T& slotmap_front(slotmap<T>*& map) {
    return map->front();
}
// returns a read/write reference to the last element on the internal array
template <typename T>
T& slotmap_back(slotmap<T>*& map) {
    return map->back();
}
// returns a read/write iterator that points one past the last element in the internal array
template <typename T>
auto slotmap_end(slotmap<T>*& map) {
    return map->end();
}
//  returns the number of elements in the internal array
template <typename T, typename index_width>
index_width slotmap_size(const slotmap<T, index_width>*& map) {
    return map->size();
}

/////////////////////////////////////////////////////////////////////////////
/// automatic insert
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename index_width>
index_width slotmap_insert(slotmap<T, index_width>*& map, const std::type_identity_t<T>& data) {
    // push the data to the array
    map->items.push_back(data);

    return map->id[map->items.size() - 1];
}

/////////////////////////////////////////////////////////////////////////////
/// get
///
/// return 1 if item not found, 0 for normal funtion
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename index_width>
bool slotmap_get(slotmap<T, index_width>*& map, const std::type_identity_t<index_width>& at, std::type_identity_t<T>& data) {
    if (map->index[at] >= map->size())
        return 1;
    data = map[map->index[at]];
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
/// set/manual_insert
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename index_width>
void slotmap_set(slotmap<T, index_width>*& map, const std::type_identity_t<index_width>& at, const std::type_identity_t<T>& data) {
    // if index[at] is dead
    if (map->index[at] >= map->size()) {
        // swap id[item.size] with id[index[at]]
        const std::type_identity_t<index_width> item_pos = map->size();
        map->index.swap(at, map->id[item_pos]);
        map->id.swap(item_pos, map->index[map->id[item_pos]]);
        map->items.push_back(data);
    } else {
        (*map)[map->index[at]] = data;
    }
}

/////////////////////////////////////////////////////////////////////////////
/// remove/pop
///
/// returns 1 if no more item, 0 otherwise
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename index_width>
bool slotmap_pop(slotmap<T, index_width>*& map, const std::type_identity_t<index_width>& at, std::type_identity_t<T>*& data) {
    if (map->size() == 0)
        return 1;
    data = (*map)[map->index[at]];
    (*map)[map->index[at]] = map->back();
    map->items.pop_back();
    map->id.swap(map->size(), map->index[at]);
    map->index.swap(at, map->id[map->size()]);
    return 0;
}


/*
0: F
1: B
2: 

Pos   : 0 1 2 3 4 5 6 7 8 9
        | | | | | | |
Index : 4 5 6 0 2 3 1 
Id    : 3 6 4 5 0 1 2 
Items : D G E F A B C 

test:
#include <iostream>
#include <cstdint>
#include <print>

int main () {
    slotmap<char, uint8_t> data{};
    
    auto data_ref = &data;
    slotmap_set(data_ref, 3, 'D');
    slotmap_set(data_ref, 6, 'G');
    slotmap_set(data_ref, 4, 'E');
    slotmap_set(data_ref, 5, 'F');
    slotmap_set(data_ref, 0, 'A');
    slotmap_set(data_ref, 1, 'B');
    slotmap_set(data_ref, 2, 'C');

    std::cout << "Pos   : 0 1 2 3 4 5 6 7 8 9" << std::endl;
    std::cout << "Index : ";
    for (int i = 0; i < data_ref->index.len; i++) {
        std::print("{} ",(int)data_ref->index[i]);
    }
    std::cout << "\nId    : ";
    for (int i = 0; i < data_ref->id.len; i++) {
        std::print("{} ",data_ref->id[i]);
    }

    std::cout << "\nItems : ";
    for (auto d: data) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    return 0;
}


*/
