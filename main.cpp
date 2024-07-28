#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool czyMozliwe(const vector<int> &l, int n, int k, int maxDist, vector<int> &APpositions) {
    int usedAPs = 1;
    int lastAP = l[0] + maxDist;;
    if (lastAP + maxDist < l[1]) {
        lastAP = l[0];
    }
    APpositions = {lastAP};
    for (int i = 0; i < n; i++) {
        if (l[i] - lastAP > maxDist) {
            usedAPs++;
            lastAP = l[i] + maxDist;
            if (lastAP + maxDist < l[i + 1] && lastAP - maxDist > l[i - 1]) {
                lastAP = l[i];
            }
            APpositions.push_back(lastAP);
            if (usedAPs > k) {
                return false;
            }
        }
    }
    return true;
}

int rozmieszczenie(int n, int k, vector<int> l, vector<int> &APpositions) {
    if(n != l.size()) return -1;
    sort(l.begin(), l.end());
    int left = 0;
    int right = l[n - 1] - l[0];
    vector<int> smallestMaxDist;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (czyMozliwe(l, n, k, mid, APpositions)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    czyMozliwe(l, n, k, left, APpositions);
    smallestMaxDist.clear();
    for (int i = 0; i < n; i++) {
        int smallest = abs(l[i] - APpositions[0]);
        for (int j = 1; j < APpositions.size(); j++) {
            int distance = abs(l[i] - APpositions[j]);
            if (distance < smallest) {
                smallest = distance;
            }
        }
        smallestMaxDist.push_back(smallest);
    }
    return *max_element(smallestMaxDist.begin(), smallestMaxDist.end());
}

int main() {
    vector<int> APpositions;

    int result = rozmieszczenie(4, 2, {1, 8, 10, 14}, APpositions);

    for (int i: APpositions) {
        cout << i << " ";
    }
    cout << endl;
    cout << result << endl;
    return 0;
}
