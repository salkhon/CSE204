# include <iostream>
# include <vector>

void print_dp_table(const std::vector<std::vector<int>>& dp) {
    std::cout << std::endl;
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            std::cout << dp[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int find_ways_to_get_to(const int s, const std::vector<int>& faces_in_dice) {
    if (s < faces_in_dice.size() || s < 0) {
        return 0;
    }

    // this dp [dice][total] represents num ways to get to `total` using `dice` dices.
    const int num_dice = (int)faces_in_dice.size();
    std::vector<std::vector<int>> dp(num_dice, std::vector<int>(s + 1, -1));

    // first roll of dice 0 is the base case.
    for (int first_roll = 1; first_roll <= faces_in_dice[0] && first_roll <= s; first_roll++) {
        dp[0][first_roll] = 1;
    }

    // further rolls will be looking back as far their face counts allow.
    // `dice` can roll on `dice` + 1 total at least. (with all prev `dice` rolling 1)
    // dp[dice][dice + 1] will be 1 for all dice. dp[dice][< dice + 1] are impossible.
    // face_in_dice[i] is different for dies, so on current dice dp, we check if the current dp is -1, not reached by prev dice.
    for (int dice = 1,
        max_total = faces_in_dice[0]; dice < num_dice; dice++) {

        max_total += faces_in_dice[dice];
        for (int total = dice + 1; total <= max_total && total <= s; total++) {
            dp[dice][total] = 0; // removing -1
            for (int roll = 1; roll <= faces_in_dice[dice] && total - roll >= dice; roll++) {
                if (dp[dice - 1][total - roll] != -1) {
                    dp[dice][total] += dp[dice - 1][total - roll];
                    dp[dice][total] %= 1000000000 + 7;
                }
            }
        }

    }

    // print_dp_table(dp);
    return dp[num_dice - 1][s];
}

int main() {
    int n, s;
    std::cin >> n >> s;

    std::vector<int> faces_in_dice(n);
    for (int i = 0; i < n; i++) {
        std::cin >> faces_in_dice[i];
    }

    int num_ways = find_ways_to_get_to(s, faces_in_dice);
    std::cout << num_ways << std::endl;

    return 0;
}