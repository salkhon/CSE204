# include <iostream>
# include <vector>

// num ways to get to s using n dices is the sum of numebr of ways to get to
// all of (s - faces in dice n) using n - 1 dices.

void roll_dice(int dice, int current_total, std::vector<int>& ways_to_get_to,
    int s, const std::vector<int>& faces_in_dice) {

    // std::cout << "recurring " << dice << " " << current_total << std::endl;

    int last_dice = int(faces_in_dice.size()) - 1;

    if (dice == last_dice) {
        for (int roll = 1; roll <= faces_in_dice[dice] && roll + current_total <= s; roll++) {
            ways_to_get_to[roll + current_total]++;
        }
    } else {
        for (int roll = 1; roll <= faces_in_dice[dice] && roll + current_total < s; roll++) {
            roll_dice(dice + 1, roll + current_total, ways_to_get_to, s, faces_in_dice);
        }
    }
}

int find_ways_to_get_to(const int s, const std::vector<int>& faces_in_dice) {
    std::vector<int> ways_to_get_to(s + 1, 0);

    roll_dice(0, 0, ways_to_get_to, s, faces_in_dice);

    return ways_to_get_to[s];
}

int main() {
    int n, s;
    std::cin >> n >> s;

    std::vector<int> faces_in_dice(n);
    for (int i = 0; i < n; i++) {
        std::cin >> faces_in_dice[i];
    }

    std::cout << find_ways_to_get_to(s, faces_in_dice);
    return 0;
}