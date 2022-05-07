# include <iostream>
# include <vector>

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

    // look back for the next dies
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

    return dp[num_dice - 1][s] != -1 ? 
        dp[num_dice - 1][s] : 0;
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