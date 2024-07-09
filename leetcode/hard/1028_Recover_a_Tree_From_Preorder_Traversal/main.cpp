// std
#include <string>
#include <cassert>
#include <vector>

class Solution {

	// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/

	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};

	struct data_t {
		int depth = -1;
		int value = -1;
	};

	static auto extract(
		/*in*/ const std::string& traversal,
		/*in*/ const std::size_t start_pos,
		/*out*/data_t& d) {

		static constexpr auto NPOS = std::string::npos;

		if (auto nd = traversal.find_first_not_of('-', start_pos); nd != NPOS) {
			auto nx = traversal.find_first_of('-', nd);

			d.depth = nd - start_pos;
			d.value = std::stod(traversal.substr(nd, (nx == NPOS ? traversal.size() - nd : nx - nd)));

			return nx;
		}
		return NPOS;
	}

	static auto process(
		TreeNode* n,
		const std::size_t depth,
		const std::string& traversal,
		const std::size_t curr_pos) -> std::size_t {

		data_t d;
		auto pos = extract(traversal, curr_pos, d);
		if (d.depth > depth && d.depth - depth == 1) {
			if (!n->left) {
#ifdef __VERBOSE__
				std::printf("left %zu :: d depth %d, val %d\n", depth, d.depth, d.value);
#endif
				n->left = new TreeNode(d.value);
				auto sz = process(n->left, d.depth, traversal, pos);
				return process(n, depth, traversal, sz);
			}
			else if (!n->right) {
#ifdef __VERBOSE__
				std::printf("right %zu :: d depth %d, val %d\n", depth, d.depth, d.value);
#endif
				n->right = new TreeNode(d.value);
				return process(n->right, d.depth, traversal, pos);
			}
			else {
				assert(false); // must be unreacheable
			}
		}
		return curr_pos;
	}

public:
	static TreeNode* recoverFromPreorder(const std::string& traversal) {
		if (traversal.empty()) return nullptr;

		std::size_t pos = 0;
		data_t d;
		pos = extract(traversal, pos, d);
#ifdef __VERBOSE__
		std::printf("d depth %d, val %d\n", d.depth, d.value);
#endif
		auto root = new TreeNode(d.value);
		process(root, 0, traversal, pos);

		return root;
	}
};

int main() {

	std::vector<std::string> traversals = {
		"1-2--3--4-5--6--7",
		"1-2--3---4-5--6---7",
		"1-401--349---90--88"
	};
	for (const auto& t : traversals) {
		auto tree = Solution::recoverFromPreorder(t);
		// @TODO check answer !!!
	}
	return 0;
}
