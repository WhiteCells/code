#include "../../head_file.h"

/*
problme: 

url: 
 */

class FrequencyTracker {
public:
    FrequencyTracker():freq(N), freq_cnt(N) {
        
    }

    void add(int number) {
        --freq_cnt[freq[number]];
        ++freq[number];
        ++freq_cnt[freq[number]];
    }
    
    void deleteOne(int number) {
        if (freq[number] == 0) {
            return;
        }
        --freq_cnt[freq[number]];
        --freq[number];
        ++freq_cnt[freq[number]];
    }
    
    bool hasFrequency(int frequency) {
        return freq_cnt[frequency];
    }

private:
    static constexpr int N = 100001;
    vector<int> freq;
    vector<int> freq_cnt;
};

int main() {
    
    return 0;
}