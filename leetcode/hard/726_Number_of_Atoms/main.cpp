// std
#include <string>
#include <cassert>
#include <vector>
#include <map>

class Solution {

	// https://leetcode.com/problems/number-of-atoms/?envType=daily-question&envId=2024-07-14

	struct data_t {
		std::string name = "";
		std::size_t count = 1;
	};

	static constexpr auto NPOS = std::string::npos;

	static auto extract(
		/*in*/ const std::string& formula,
		/*in*/ const std::size_t start_pos,
		/*out*/data_t& d) {

		auto pos = start_pos;
		std::string value;
		while (pos < formula.size()) {
			const auto& c = formula.at(pos);
			if (c == '(' || c == ')') {
				break;
			}
			if (std::isupper(c) && !d.name.empty()) {
				break;
			}
			if (std::isdigit(c)) {
				value += c;
			}
			else {
				d.name += c;
			}
			pos++;
		}
		if (!value.empty()) {
			d.count = std::stoull(value); // @NOTE may throw!!!
		}
		return (pos < formula.size() ? pos : NPOS);
	}

	static auto extractDigits(
		/*in*/ const std::string& formula,
		/*in*/ const std::size_t start_pos,
		/*out*/std::string& value) -> std::size_t {

		auto pos = start_pos;
		while (pos < formula.size()) {
			if (const auto& c = formula.at(pos);
				std::isdigit(c)) {
				value += c;
			}
			else {
				break;
			}
			pos++;
		}
		if (pos >= formula.size()) {
			pos = NPOS;
		}
		return pos;
	}

	using output_t = std::map<std::string, std::size_t>;

	static auto parseGroup(
		/*in*/ const std::string& formula,
		/*in*/ const std::size_t start_pos,
		/*out*/output_t& output) -> std::size_t {

		auto pos = start_pos;
		while (pos != NPOS && pos < formula.size()) {
			data_t data;
			pos = extract(formula, pos, data);
			if (!data.name.empty()) {
				output[data.name] += data.count;
#ifdef __VERBOSE__
				std::printf("ELEM :: `%s` x%zd\n", data.name.data(), data.count);
#endif
			}
			if (pos == NPOS) {
				return pos;
			}
			const auto c = formula.at(pos);
			if (c == '(') {
#ifdef __VERBOSE__
				std::printf("meet (\n");
#endif
				output_t child;
				pos++;
				pos = parseGroup(formula, pos, child);
				assert(formula.at(pos) == ')'); // @NOTE formula is always valid.
				pos++;
				std::string value;
				pos = extractDigits(formula, pos, value);
				std::size_t sf = 1;
				if (!value.empty()) {
					sf = std::stoull(value); // @NOTE may throw!!!
				}
				for (const auto& [name, count] : child) {
					output[name] += count * sf;
				}
			}
			if (c == ')') {
#ifdef __VERBOSE__
				std::printf("return )\n");
#endif
				return pos;
			}
			
		};
		return pos;
	}

public:
	static auto countOfAtoms(const std::string& formula) {
		std::size_t pos = 0;
		std::string result;
		do {
			output_t output;
			pos = parseGroup(formula, pos, output);
			for (const auto& [name, count] : output) {
				result += name;
				if (count > 1) result += std::to_string(count);
#ifdef __VERBOSE__
				std::printf("FINAL :: `%s` x%zd\n", name.data(), count);
#endif
			}
			assert(pos == NPOS); // @NOTE formula is always valid.
		} while (pos != NPOS);
		return result;
	}
};

int main() {

	std::vector<std::string> formulas = {
		"H2O",
		"H2O2",
		"Mg(OH)2",
		"H2O2He3Mg4",
		"(H2O2He3Mg4)2",
		"(H2O2(He3Mg4)2)2",
		"Mg(H2O)N",
		"K4(ON(SO3)2)2"
	};
	for (const auto& formula : formulas) {
		auto res = Solution::countOfAtoms(formula);
		std::printf("for `%s` RESULT is `%s`\n", formula.data(), res.data());
	}

	return 0;
}
