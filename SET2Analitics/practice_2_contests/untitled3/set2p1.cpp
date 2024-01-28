#include <iostream>
#include <vector>

struct Interval {
    int left;
    int right;

    [[nodiscard]] size_t length() const {
        return left > right ? 0 : right - left + 1;
    }
    Interval overlap(Interval& other) const {
        Interval cross{};
        cross.left = std::max(left, other.left);
        cross.right = std::min(right, other.right);
        return cross;
    }


}
;

std::vector<Interval> merge (std::vector<Interval> &left, std::vector<Interval> &right) {
    std::vector<Interval> result;
    int i = 0;
    int j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].left < right[j].left) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }

    }
    while (i < left.size()) {
        result.push_back(left[i++]);
    }
    while (j < right.size()) {
        result.push_back(right[j++]);
    }

    return result;
}
std::vector<Interval> MergeSort(std::vector<Interval> &a) {
    size_t size = a.size();
    if(size <= 1) {
        return a;
    }
    int mid = size / 2;
    std::vector<Interval> left (a.begin(), a.begin() + mid);
    std::vector<Interval> right (a.begin() + mid, a.end());
    left = MergeSort(left);
    right = MergeSort(right);
    return merge(left, right);
}
Interval Search_max_cross(std::vector<Interval> &arr, size_t n) {
    size_t i = 0;
    size_t j = 0;
    Interval max_l{};
    max_l.right = -1;
    max_l.left = 0;

    while (j < n) {
        if (i == j) {
            ++j;
            continue;
        }
        if (arr[i].overlap(arr[j]).length() > max_l.length()) {
            max_l = arr[i].overlap(arr[j]);
        }
        if (arr[i].right < arr[j].right) {
            i = j;
        }
        ++j;
    }
    return max_l;
}

//
void Print(Interval &a) {
    if (a.length() == 0) {
        std::cout<<"0";
        return;
    }
    std::cout<<std::to_string(a.length())<<std::endl;
    std::cout<< std::to_string(a.left) << " " << std::to_string(a.right) << std::endl;
}

//
int main() {
    int number_el;
    std::cin>>number_el;
    std::vector<Interval> objects;
    objects.reserve(number_el);
    for (int i = 0; i < number_el; ++i) {
        Interval el{};
        std::cin>>el.left>> el.right;
        objects.push_back(el);
    }
    objects = MergeSort(objects);
    Interval noLishnie = Search_max_cross(objects, objects.size());
    Print(noLishnie);

    return 0;
}
