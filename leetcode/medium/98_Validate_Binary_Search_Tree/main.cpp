// std
#include <format>
#include <iostream>

class Solution {

    // https://leetcode.com/problems/validate-binary-search-tree/

public:
    struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};

private:
    static inline auto check(TreeNode* n) -> bool {
        return !n || ((!n->left || n->left->val < n->val) && (!n->right || n->right->val > n->val));
    }
    
    static bool process(TreeNode* n, TreeNode* lb, TreeNode* rb) {
        if (!n) return true;
        auto valid = check(n);
        if (lb) {
            valid &= (!n->left || n->left->val > lb->val);
        }
        if (rb) {
            valid &= (!n->right || n->right->val < rb->val);
        }
        return valid && process(n->left, lb, n) && process(n->right, n, rb);
    }
    
public:
    static bool isValidBST(TreeNode* root) {
        return process(root, nullptr, nullptr);
    }
};

int main() {

    auto root = new Solution::TreeNode(2);
    root->left = new Solution::TreeNode(1);
    root->right = new Solution::TreeNode(3);
    // @TODO free mem !!!
    std::printf(std::format("{}\n", Solution::isValidBST(root)).data());
    return 0;
}
