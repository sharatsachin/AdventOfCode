
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    map<pair<TreeNode*, int>, int> mp;

    int rob(TreeNode* root, int nxt) {
        if (!root) return 0;

        if (mp.count({root, nxt})) {
            return mp[{root, nxt}];
        }

        if (nxt == 1) {
            mp[{root, 1}] = rob(root->left, 0) + rob(root->right, 0);
            return mp[{root, 1}];
        } else {
            mp[{root, 0}] = max(rob(root->left, 0) + rob(root->right, 0),
                                root->val + rob(root->left, 1) + rob(root->right, 1));
            return mp[{root, 0}];
        }
    }

    int rob(TreeNode* root) {
        mp.clear();
        return rob(root, 0);
    }
};