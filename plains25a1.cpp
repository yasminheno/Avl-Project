#include "plains25a1.h"
#include "AVLTree.h"
#include <iostream>

Plains::Plains() {}

Plains::~Plains() {}

StatusType Plains::add_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Herd* added_herd = new Herd(herdId);
        if (empty_herds.find(herdId) != nullptr || herds.find(herdId) != nullptr ) {
            delete added_herd; // Avoid memory leak
            return StatusType::FAILURE;
        }
        empty_herds.insert(added_herd, herdId);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if (empty_herds.find(herdId) != nullptr) {
            empty_herds.remove(herdId);
            return StatusType::SUCCESS;
        }
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType Plains::add_horse(int horseId, int speed) {
    if (horseId <= 0 || speed <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if (horses.find(horseId) != nullptr) {
            return StatusType::FAILURE;
        }
        Horse* added_horse = new Horse(horseId, speed);
        horses.insert(added_horse, horseId);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::join_herd(int horseId, int herdId) {
    if (herdId <= 0 || horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        TreeNode<int, Horse*>* horse_node = horses.find(horseId);
        TreeNode<int, Herd*>* herd_node = empty_herds.find(herdId);

        if (!herd_node) {
            herd_node = herds.find(herdId);
        }

        if (!horse_node || !horse_node->getData() || !herd_node || !herd_node->getData() || horse_node->getData()->getHerd() != 0) {
            return StatusType::FAILURE;
        }

        empty_herds.remove(herdId);
        herds.insert(herd_node->getData(), herdId);

        herd_node->getData()->getHorsesTree()->insert(horse_node->getData(), horseId);

        horse_node->getData()->setHerd(herdId);
        horse_node->getData()->set_my_count(horse_node->getData()->getMyCount() + 1);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId) {
    if (horseId <= 0 || horseToFollowId <= 0 || horseId == horseToFollowId) {
        return StatusType::INVALID_INPUT;
    }
    try {
        TreeNode<int, Horse*>* current_horse = horses.find(horseId);
        TreeNode<int, Horse*>* followed_horse = horses.find(horseToFollowId);

        if (!current_horse || !current_horse->getData() || !followed_horse || !followed_horse->getData()) {
            return StatusType::FAILURE;
        }

        if (!current_horse->getData()->getHerd() || !followed_horse->getData()->getHerd() ||
            current_horse->getData()->getHerd() != followed_horse->getData()->getHerd()) {
            return StatusType::FAILURE;
        }

        current_horse->getData()->setfollow(followed_horse->getData());
        current_horse->getData()->set_follow_count(followed_horse->getData()->getMyCount());
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId) {
    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        TreeNode<int, Horse*>* horse = horses.find(horseId);

        if (!horse || !horse->getData() || horse->getData()->getHerd() == 0) {
            return StatusType::FAILURE;
        }

        int current_herd_id = horse->getData()->getHerd();
        TreeNode<int, Herd*>* current_herd_node = herds.find(current_herd_id);

        if (!current_herd_node || !current_herd_node->getData()) {
            return StatusType::FAILURE;
        }

        Herd* current_herd = current_herd_node->getData();
        current_herd->getHorsesTree()->remove(horseId);

        horse->getData()->set_my_count(horse->getData()->getMyCount() + 1);
        if (current_herd->getHorsesTree()->getSize() == 0) {
            herds.remove(current_herd->getID());
            empty_herds.insert(current_herd, current_herd->getID());
        }

        horse->getData()->setfollow(nullptr);
        horse->getData()->set_follow_count(0);
        horse->getData()->setHerd(0);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId) {
    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        TreeNode<int, Horse*>* horse_node = horses.find(horseId);
        if (!horse_node || !horse_node->getData()) {
            return StatusType::FAILURE;
        }

        return output_t<int>(horse_node->getData()->getSpeed());
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    if (horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId) {
        return StatusType::INVALID_INPUT;
    }
    try {
        TreeNode<int, Horse*>* current_horse_node = horses.find(horseId);
        TreeNode<int, Horse*>* other_horse_node = horses.find(otherHorseId);

        if (!current_horse_node || !current_horse_node->getData() || !other_horse_node || !other_horse_node->getData()) {
            return StatusType::FAILURE;
        }

        int current_horse_herd = current_horse_node->getData()->getHerd();
        int other_horse_herd = other_horse_node->getData()->getHerd();

        if (current_horse_herd != other_horse_herd || current_horse_herd == 0 || other_horse_herd == 0) {
            return output_t<bool>(false);
        }

        int current_id = horseId;
        int count = 1;
        TreeNode<int, Herd*>* current_herd = herds.find(current_horse_herd);

        if (!current_herd || !current_herd->getData()) {
            return StatusType::FAILURE;
        }

        int size = current_herd->getData()->getHorsesTree()->getSize();
        Horse* current_horse = current_horse_node->getData();
        Horse* other_horse = other_horse_node->getData();

        while (current_id != otherHorseId) {
            if (count > size || !current_horse->getfollow() ||
                current_horse->getFollowCount() != current_horse->getfollow()->getMyCount()) {
                return output_t<bool>(false);
            }
            current_horse = current_horse->getfollow();
            current_id = current_horse->getID();
            count++;
        }
        return output_t<bool>(true);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<bool> Plains::can_run_together(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        TreeNode<int, Herd*>* herd_node = herds.find(herdId);

        if (!herd_node || !herd_node->getData()) {
            return StatusType::FAILURE;
        }

        auto tree = herd_node->getData()->getHorsesTree();
        if (!tree || tree->getSize() == 0 || !tree->getRoot()) {
            return StatusType::FAILURE;
        }

        int size = tree->getSize();
        if (size == 1) {
            return output_t<bool>(true);
        }

        TreeNode<int, Horse*>** array = new TreeNode<int, Horse*>*[size];
        bool* visitedNow = new bool[size]();

        try {
            int index = 0;
            tree->inorderToArray(tree->getRoot(), array, index);

            for (int i = 0; i < size; ++i) {
                if (!array[i] || !array[i]->getData()) {
                    delete[] array;
                    delete[] visitedNow;
                    return StatusType::FAILURE;
                }
                array[i]->getData()->setIndex(i);
            }

            int edges = 0;
            for (int i = 0; i < size; ++i) {
                Horse* current = array[i]->getData();
                std::fill(visitedNow, visitedNow + size, false);

                while (current) {
                    if (current->getVisited()) break;

                    current->setVisited(true);
                    visitedNow[current->getIndex()] = true;

                    if (!current->getfollow()) break;

                    if (visitedNow[current->getfollow()->getIndex()] &&
                        (current->getFollowCount() == current->getfollow()->getMyCount())) {
                        for (int j = 0; j < size; ++j) {
                            array[j]->getData()->setVisited(false);
                        }
                        delete[] array;
                        delete[] visitedNow;
                        return output_t<bool>(false);
                    }

                    current = current->getfollow();
                    edges++;
                }
            }

            for (int i = 0; i < size; ++i) {
                array[i]->getData()->setVisited(false);
            }

            delete[] array;
            delete[] visitedNow;

            return output_t<bool>(edges == size - 1);
        } catch (...) {
            delete[] array;
            delete[] visitedNow;
            throw;
        }

    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
}
