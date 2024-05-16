#include <vector>
#include <string>




int lcp(const std::string& str1, const std::string& str2) {
    int len = std::min(str1.size(), str2.size());
    int i = 0;
    while (i < len && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

void merge2(std::vector<std::string>& arr, int left, int mid, int right, int& comparisonCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::string> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int lcpLen = lcp(L[i], R[j]);
        comparisonCount += lcpLen + 1;

        if (L[i].compare(0, lcpLen + 1, R[j], 0, lcpLen + 1) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortLCP(std::vector<std::string>& arr, int left, int right, int& comparisonCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortLCP(arr, left, mid, comparisonCount);
        mergeSortLCP(arr, mid + 1, right, comparisonCount);
        merge2(arr, left, mid, right, comparisonCount);
    }
}