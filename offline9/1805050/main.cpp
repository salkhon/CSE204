# include <iostream>
# include <vector>
# include <algorithm>

int minimum_cost_to_buy_all_plants(const int num_friends, const std::vector<int>& plant_price) {
    std::vector<int> sorted_plant_price(plant_price);
    std::sort(sorted_plant_price.rbegin(), sorted_plant_price.rend());

    int total_cost = 0;
    for (int i = 0, coeff = 0; i < sorted_plant_price.size(); i++) {
        if (i == 0 || i % num_friends == 0) {
            coeff++;
        }
        
        total_cost += coeff * sorted_plant_price[i];
    }
    return total_cost;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> plant_price(n);

    for (int i = 0; i < n; i++) {
        std::cin >> plant_price[i];
    }

    std::cout << minimum_cost_to_buy_all_plants(k, plant_price);
    return 0;
}