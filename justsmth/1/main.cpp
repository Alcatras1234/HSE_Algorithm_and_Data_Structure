#include <iostream>
#include <vector>
#include <map>
#include <stack>



 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

}

int main() {
    std::string s = "()[]{}";
    std::cout<<method(s);

    return 0;
}
