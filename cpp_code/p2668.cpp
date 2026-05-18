#include <bits/stdc++.h>
using namespace std;

using Card = pair<int, int>;
using Hand = vector<Card>;

Hand hand;
int min_steps = 1e6;
int n;  // 缺少的全局变量

// 火箭
vector<vector<int>> get_rocket_indices(const Hand& hand) {
    vector<vector<int>> result;
    vector<int> indices;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].first == 0) {
            indices.push_back(i);
        }
    }
    if (indices.size() == 2) {
        result.push_back(indices);
    }
    return result;
}

// 炸弹
vector<vector<int>> get_bomb_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    for (const auto& [value, indices] : value_to_indices) {
        if (indices.size() == 4 && value != 0) {
            result.push_back(indices);
        }
    }
    return result;
}

// 单张
vector<vector<int>> get_single_indices(const Hand& hand) {
    vector<vector<int>> result;
    for (int i = 0; i < hand.size(); i++) {
        result.push_back({i});
    }
    return result;
}

// 对子
vector<vector<int>> get_pair_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    for (const auto& [value, indices] : value_to_indices) {
        if (indices.size() >= 2 && value != 0) {
            for (int i = 0; i < indices.size(); i++) {
                for (int j = i + 1; j < indices.size(); j++) {
                    result.push_back({indices[i], indices[j]});
                }
            }
        }
    }
    return result;
}

// 三张
vector<vector<int>> get_triple_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    for (const auto& [value, indices] : value_to_indices) {
        if (indices.size() >= 3 && value != 0) {
            for (int i = 0; i < indices.size(); i++) {
                for (int j = i + 1; j < indices.size(); j++) {
                    for (int k = j + 1; k < indices.size(); k++) {
                        result.push_back({indices[i], indices[j], indices[k]});
                    }
                }
            }
        }
    }
    return result;
}

// 三带一
vector<vector<int>> get_triple_with_one_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    for (const auto& [triple_val, triple_indices] : value_to_indices) {
        if (triple_indices.size() >= 3 && triple_val != 0) {
            for (const auto& [single_val, single_indices] : value_to_indices) {
                if (single_val != triple_val && single_val != 0 && !single_indices.empty()) {
                    for (int t1 = 0; t1 < triple_indices.size(); t1++) {
                        for (int t2 = t1 + 1; t2 < triple_indices.size(); t2++) {
                            for (int t3 = t2 + 1; t3 < triple_indices.size(); t3++) {
                                for (int s = 0; s < single_indices.size(); s++) {
                                    vector<int> pattern = {
                                        triple_indices[t1], triple_indices[t2], triple_indices[t3],
                                        single_indices[s]
                                    };
                                    result.push_back(pattern);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

// 三带二
vector<vector<int>> get_triple_with_pair_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    for (const auto& [triple_val, triple_indices] : value_to_indices) {
        if (triple_indices.size() >= 3 && triple_val != 0) {
            for (const auto& [pair_val, pair_indices] : value_to_indices) {
                if (pair_val != triple_val && pair_indices.size() >= 2 && pair_val != 0) {
                    for (int t1 = 0; t1 < triple_indices.size(); t1++) {
                        for (int t2 = t1 + 1; t2 < triple_indices.size(); t2++) {
                            for (int t3 = t2 + 1; t3 < triple_indices.size(); t3++) {
                                for (int p1 = 0; p1 < pair_indices.size(); p1++) {
                                    for (int p2 = p1 + 1; p2 < pair_indices.size(); p2++) {
                                        vector<int> pattern = {
                                            triple_indices[t1], triple_indices[t2], triple_indices[t3],
                                            pair_indices[p1], pair_indices[p2]
                                        };
                                        result.push_back(pattern);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

// 单顺子
vector<vector<int>> get_single_straight_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    vector<int> straight_vals;
    for (const auto& [val, _] : value_to_indices) {
        if (val >= 3 && val <= 13) {
            straight_vals.push_back(val);
        }
    }
    sort(straight_vals.begin(), straight_vals.end());
    
    for (size_t i = 0; i < straight_vals.size(); i++) {
        int len = 1;
        while (i + len < straight_vals.size() && straight_vals[i + len] == straight_vals[i] + len) {
            len++;
        }
        if (len >= 5) {
            for (int start = 0; start < len; start++) {
                for (int end = start + 4; end < len; end++) {
                    vector<int> pattern;
                    bool valid = true;
                    for (int k = start; k <= end; k++) {
                        int target_val = straight_vals[i + k];
                        if (value_to_indices[target_val].empty()) {
                            valid = false;
                            break;
                        }
                        pattern.push_back(value_to_indices[target_val][0]);
                    }
                    if (valid) {
                        result.push_back(pattern);
                    }
                }
            }
        }
        i += len - 1;
    }
    return result;
}

// 双顺子
vector<vector<int>> get_double_straight_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    vector<int> pair_vals;
    for (const auto& [val, indices] : value_to_indices) {
        if (val >= 3 && val <= 13 && indices.size() >= 2) {
            pair_vals.push_back(val);
        }
    }
    sort(pair_vals.begin(), pair_vals.end());
    
    for (size_t i = 0; i < pair_vals.size(); i++) {
        int len = 1;
        while (i + len < pair_vals.size() && pair_vals[i + len] == pair_vals[i] + len) {
            len++;
        }
        if (len >= 3) {
            for (int start = 0; start < len; start++) {
                for (int end = start + 2; end < len; end++) {
                    vector<int> pattern;
                    bool valid = true;
                    for (int k = start; k <= end; k++) {
                        int target_val = pair_vals[i + k];
                        if (value_to_indices[target_val].size() < 2) {
                            valid = false;
                            break;
                        }
                        pattern.push_back(value_to_indices[target_val][0]);
                        pattern.push_back(value_to_indices[target_val][1]);
                    }
                    if (valid) {
                        result.push_back(pattern);
                    }
                }
            }
        }
        i += len - 1;
    }
    return result;
}

// 三顺子
vector<vector<int>> get_triple_straight_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    vector<int> triple_vals;
    for (const auto& [val, indices] : value_to_indices) {
        if (val >= 3 && val <= 13 && indices.size() >= 3) {
            triple_vals.push_back(val);
        }
    }
    sort(triple_vals.begin(), triple_vals.end());
    
    for (size_t i = 0; i < triple_vals.size(); i++) {
        int len = 1;
        while (i + len < triple_vals.size() && triple_vals[i + len] == triple_vals[i] + len) {
            len++;
        }
        if (len >= 3) {
            for (int start = 0; start < len; start++) {
                for (int end = start + 2; end < len; end++) {
                    vector<int> pattern;
                    bool valid = true;
                    for (int k = start; k <= end; k++) {
                        int target_val = triple_vals[i + k];
                        if (value_to_indices[target_val].size() < 3) {
                            valid = false;
                            break;
                        }
                        pattern.push_back(value_to_indices[target_val][0]);
                        pattern.push_back(value_to_indices[target_val][1]);
                        pattern.push_back(value_to_indices[target_val][2]);
                    }
                    if (valid) {
                        result.push_back(pattern);
                    }
                }
            }
        }
        i += len - 1;
    }
    return result;
}

// 四带二
vector<vector<int>> get_four_with_two_indices(const Hand& hand) {
    vector<vector<int>> result;
    map<int, vector<int>> value_to_indices;
    for (int i = 0; i < hand.size(); i++) {
        value_to_indices[hand[i].first].push_back(i);
    }
    
    for (const auto& [four_val, four_indices] : value_to_indices) {
        if (four_indices.size() == 4 && four_val != 0) {
            // 四带两张单
            vector<int> single_vals;
            for (const auto& [val, indices] : value_to_indices) {
                if (val != four_val && val != 0 && !indices.empty()) {
                    single_vals.push_back(val);
                }
            }
            for (size_t i = 0; i < single_vals.size(); i++) {
                for (size_t j = i + 1; j < single_vals.size(); j++) {
                    vector<int> pattern = four_indices;
                    pattern.push_back(value_to_indices[single_vals[i]][0]);
                    pattern.push_back(value_to_indices[single_vals[j]][0]);
                    result.push_back(pattern);
                }
            }
            
            // 四带两对
            vector<int> pair_vals;
            for (const auto& [val, indices] : value_to_indices) {
                if (val != four_val && val != 0 && indices.size() >= 2) {
                    pair_vals.push_back(val);
                }
            }
            for (size_t i = 0; i < pair_vals.size(); i++) {
                for (size_t j = i + 1; j < pair_vals.size(); j++) {
                    vector<int> pattern = four_indices;
                    pattern.push_back(value_to_indices[pair_vals[i]][0]);
                    pattern.push_back(value_to_indices[pair_vals[i]][1]);
                    pattern.push_back(value_to_indices[pair_vals[j]][0]);
                    pattern.push_back(value_to_indices[pair_vals[j]][1]);
                    result.push_back(pattern);
                }
            }
        }
    }
    return result;
}

void remove_by_indices(Hand &hand, const vector<int> &indices) {
    vector<int> sorted = indices;
    sort(sorted.begin(), sorted.end(), greater<int>());
    for (int idx : sorted) {
        hand.erase(hand.begin() + idx);
    }
}

void dfs(Hand &hand, int &steps) {
    if (hand.size() == 0) {
        min_steps = min(min_steps, steps);
        return;
    }
    
    if (steps >= min_steps) return;
    
    Hand cpy = hand;
    vector<vector<int>> idxs_list;
    
    // 1. 四带二 (6张)
    idxs_list = get_four_with_two_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 2. 三顺子 (至少9张)
    idxs_list = get_triple_straight_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 3. 双顺子 (至少6张)
    idxs_list = get_double_straight_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 4. 单顺子 (至少5张)
    idxs_list = get_single_straight_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 5. 三带二 (5张)
    idxs_list = get_triple_with_pair_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 6. 三带一 (4张)
    idxs_list = get_triple_with_one_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 7. 炸弹 (4张)
    idxs_list = get_bomb_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 8. 三张 (3张)
    idxs_list = get_triple_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 9. 对子 (2张)
    idxs_list = get_pair_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 10. 火箭 (2张)
    idxs_list = get_rocket_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
    
    // 11. 单张 (1张)
    idxs_list = get_single_indices(hand);
    if (!idxs_list.empty()) {
        for (const auto &idxs : idxs_list) {
            remove_by_indices(hand, idxs);
            ++steps;
            dfs(hand, steps);
            --steps;
            hand = cpy;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T >> n;
    int a, b;
    while (T--) {
        hand.clear();
        min_steps = 1e6;
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            hand.push_back({a, b});
        }
        int steps = 0;
        dfs(hand, steps);
        cout << min_steps << "\n";
    }
}