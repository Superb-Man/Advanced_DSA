#include<bits/stdc++.h>
std::mt19937 rng(std::random_device{}());

int randomNumber(int l) {
    std::uniform_int_distribution<int> dist(0, l - 1);

    return dist(rng);
}