#include <iostream>
#include <string>
#include <vector>

int res_num = 0;

enum ops {
    MRG = 0,
    MUL = 1,
    ADD = 2,
    SUB = 3,
};

void printSum (int target, const std::vector<long>& nums, const std::vector<int>& state);

int numLen (int number) {
    if (number == 0)
        return 0;
    else
        return 1 + numLen(number / 10);
}

long toPow (int num, int pow) {
    long res = 1;
    for (int i = 0; i < pow; i++) {
        res *= num;
    }
    return res;
}

long merge (long number1, long number2) {
    if (number1 == 0)
        return number2;
    std::string str1 = (std::to_string(number1));
    std::string str2 = (std::to_string(number2));
    str1.append(str2);

    return std::stoi(str1);

    //return number1 * toPow(10, numLen(number2)) + number2;
}

int calculate (std::vector<long> numbers, std::vector<int> state) {

    if (numbers.size() == 1)
        return numbers[0];

    std::vector<long> merged;
    std::vector<int> merged_state;

    if (state[0] == MRG)
    {
        merged.push_back(merge(numbers[0], numbers[1]));
    }

    else {

        merged.push_back(numbers[0]);
        merged.push_back(numbers[1]);
        merged_state.push_back(state[0]);
    }
    for (int i = 1; i < state.size(); i++) {
        if (state[i] == MRG)
            merged[merged.size() - 1] = merge(merged[merged.size() - 1], numbers[i + 1]);
        else {
            merged.push_back(numbers[i + 1]);
            merged_state.push_back(state[i]);
        }
    }
    if (merged.size() == 1)
    {
        return merged[0];
    }


    std::vector<long> muled;
    std::vector<int> muled_state;

    if (merged_state[0] == MUL)
        muled.push_back(merged[0] * merged[1]);
    else {
        muled.push_back(merged[0]);
        muled.push_back(merged[1]);
        muled_state.push_back(merged_state[0]);
    }
    for (int i = 1; i < merged_state.size(); i++) {
        if (merged_state[i] == MUL)
            muled[muled.size() - 1] = muled[muled.size() - 1] * merged[i + 1];
        else {
            muled.push_back(merged[i + 1]);
            muled_state.push_back(merged_state[i]);
        }
    }
    if (muled.size() == 1)
        return muled[0];

    long res = muled[0];

    for (int i = 0; i < muled_state.size(); i++) {
        if (muled_state[i] == ADD)
            res += muled[i + 1];
        else
            res -= muled[i + 1];
    }
    return res;
}

int sortOut (int target, std::vector<long> numbers, int index, std::vector<int>& state) {
    if (index != numbers.size() - 1) {
        for (int i = 0; i < 4; i++) {
            state[index] = i;
            if (!sortOut(target, numbers, index + 1, state))
                {
                    return 0;
                }
        }
    }
    else
    {
        if (target == calculate(numbers, state)) {
            printSum(target, numbers, state);
            res_num++;
        }
        else
        {
                return 1;
        }
    }
}

void printSum (int target, const std::vector<long>& nums, const std::vector<int>& state)
{
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == MRG)
            std::cout << nums[i];
        else if (state[i] == MUL)
            std::cout << nums[i] << ' ' << '*' << ' ';
        else if (state[i] == ADD)
            std::cout << nums[i] << ' ' << '+' << ' ';
        else if (state[i] == SUB)
            std::cout << nums[i] << ' ' << '-' << ' ';
    }
    std::cout << nums[nums.size() - 1];

    std::cout <<  " = " << target << std::endl;

}

int main(int argc, char* argv[])
{
    if (argc == 1 || argc == 2)
    {
        std::cerr << "Nothing to count\n";
        return 1;
    }

    std::vector <long> nums;
    long result = std::atoi(argv[1]);

    for (uint i = 2; i < argc; i++)
    {
        nums.push_back(std::atoi(argv[i]));
    }

    std::vector <int> state(nums.size() - 1);
    sortOut(result, nums, 0, state);
    if (!res_num)
    {
        std::cout << "Empossible to put signs\n";
        return 0;
    }

    return 0;
}
