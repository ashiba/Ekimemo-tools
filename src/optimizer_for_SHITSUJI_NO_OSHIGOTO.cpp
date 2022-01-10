/* つかいかた
 * 1. YAMI_NO_BARA_NUM, YAKOU_CHO_NUM, UNMEI_NO_KAGI…… の9つの変数の値を自分が持っている個数に書き換える
 * 2. 実行する
 */

#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <queue>
#include <cassert>

const int YAMI_NO_BARA_NUM      = 184;
const int YAKOU_CHO_NUM         = 179;
const int UNMEI_NO_KAGI         = 5;
const int KURONEKO_NO_ASHIATO   = 0;
const int SHUEN_NO_HANE         = 55;
const int SHINGAN_NO_KESSYOU    = 16;
const int MUSOU_NO_PENDULUM     = 4;
const int KUUKYO_NO_SHIZUKU     = 3;
const int BOUKYAKU_NO_HA        = 3;

using Status = std::array<int, 9>;

struct DPVal {
    int val;
    Status from;
};

Status interArraySub(const Status& a, const Status& b) {
    Status ret;
    for (size_t i=0; i<a.size(); ++i) {
        ret[i] = a[i] - b[i];
    }
    return ret;
}

bool isValidStatus(const Status& a) {
    for (size_t i=0; i<a.size(); ++i) {
        if (a[i] < 0) return false;
    }
    return true;
}

void dumpArray(const Status& a) {
    for (const auto& elm: a) {
        std::cout << elm << " ";
    }
    std::cout << std::endl;
}

int main() {
    const std::vector<int> product_rewards = {30, 120, 200, 500, 700};
    const std::vector<Status> products = {
        {1, 1, 0, 0, 0, 0, 0, 0, 0}, // Anklet
        {1, 1, 0, 0, 1, 0, 0, 0, 0}, // Vial
        {1, 0, 1, 0, 0, 0, 0, 0, 1}, // Crown
        {0, 1, 0, 1, 1, 0, 1, 0, 0}, // Mirror
        {1, 0, 1, 0, 0, 1, 0, 1, 1}  // Orb
    };

    std::map<Status, DPVal> dp;
    
    Status init_status = {YAMI_NO_BARA_NUM, YAKOU_CHO_NUM, UNMEI_NO_KAGI, KURONEKO_NO_ASHIATO, SHUEN_NO_HANE, SHINGAN_NO_KESSYOU, MUSOU_NO_PENDULUM, KUUKYO_NO_SHIZUKU, BOUKYAKU_NO_HA};
    
    dp[init_status] = DPVal(0, init_status);
    
    std::queue<Status> que;
    que.push(init_status);
    
    while(not que.empty()) {
        const Status cur_status = que.front();
        que.pop();
        
        Status tmp;

        for (size_t i=0; i<products.size(); ++i) {
            tmp = interArraySub(cur_status, products[i]);
            if (isValidStatus(tmp)) {
                const int reward_sum = dp[cur_status].val + product_rewards[i];
                if(dp[tmp].val < reward_sum) {
                    que.push(tmp);
                    dp[tmp] = DPVal(reward_sum, cur_status);
                }
            }
        }
    }
    
    int best_reward = -1;
    Status best_status;
    
    for (const auto& elm: dp) {
        if (elm.second.val > best_reward) {
            best_reward = elm.second.val;
            best_status = elm.first;
        }
    }
    
    std::cout << "You will get " << best_reward << " pt." << std::endl;

    Status st = best_status;
    std::array<int, 5> made_each_product_num = {0, 0, 0, 0, 0};
    while(true) {
        Status bef_status = dp[st].from;
        if (st == bef_status) break;
        const Status status_diff = interArraySub(bef_status, st);
        bool did_find_same_status = false;
        for (size_t i=0; i<products.size(); ++i) {
            if (products[i] == status_diff) {
                made_each_product_num[i] += 1;
                did_find_same_status = true;
                break;
            }
        }    
        assert(did_find_same_status == true);
        
        st = bef_status;
    }
    
    std::cout << "You should make" << std::endl;
    std::cout << made_each_product_num[0] << " Anklet" << std::endl;
    std::cout << made_each_product_num[1] << " Vial" << std::endl;
    std::cout << made_each_product_num[2] << " Crown" << std::endl;
    std::cout << made_each_product_num[3] << " Mirror" << std::endl;
    std::cout << made_each_product_num[4] << " Orb" << std::endl;    
    
    // dumpArray(best_status);
}