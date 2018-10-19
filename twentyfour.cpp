#include <iostream>
// #include <string>
#include <sstream>

bool calculate(int x, int y, int results[]);
bool find24(int numbers[]);
void printResults(bool were_the_numbers_swapped[], int first_operation_index, int second_operation_index, int third_operation_index, int nums[], int first_result, int second_result);

const char operations[4] = {'+', '-', '*', '/'};

int main(int argc, char* argv[]) {
    int nums[4];
    int results1[4];

    //  Parse input
    for (int i = 1; i < argc; ++i)
    {
        std::stringstream str(argv[i]);
        str >> nums[i-1];
    }

    //  Check for proper input:
    //  four numbers...
    if (argc != 5)  {
        std::cout << "Please enter exactly four numbers; no more, no less.\n";
        return 1;
    }

    //  ... all whole
    for (int i = 0; i < argc - 1; i++)
    {
        if (nums[i] < 0)
        {
            std::cout << "Whole numbers only, please; no negatives.\n";
            return 1;
        }
    }

    if (find24(nums)) {
        std::cout << "Yup.\n";
        return 0;
    }   else    {
        std::cout << "Nope.\n";
        return 1;
    }

    return 0;
}

bool calculate (int x, int y, int array[])  {
    int temp;
    int quotient;
    float decimal_quotient;
    bool swapped = false;

    if (x < y)  {
        temp = x; x = y; y = temp;
        swapped = true;
    }
    array[0] = x + y;
    array[1] = x - y;
    array[2] = x * y;

    if (y <= 0)
    {
        array[3] = -1;
        return swapped;
    }
    quotient = x / y;
    decimal_quotient = (float)x / (float)y;
    array[3] = quotient == decimal_quotient ? quotient : -1;

    return swapped;
}

bool find24(int nums[])   {
    int first_results[4];
    int second_results[4];
    int third_results[4];
    int skip_quotient;
    bool swapped[3];

    swapped[0] = calculate(nums[0], nums[1], first_results);
    skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
    for (int i = 0; i < 4 + skip_quotient; ++i)
    {
        swapped[1] = calculate(nums[2], first_results[i], second_results);
        skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
        for (int j = 0; j < 4 + skip_quotient; ++j)
        {
            swapped[3] = calculate(nums[3], second_results[j], third_results);
            skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
            for (int k = 0; k < 4 + skip_quotient; ++k)
            {
                if (third_results[k] == 24)
                {
                    printResults(swapped, i, j, k, nums, first_results[i], second_results[j]);
                    return true;
                }
            }
        }
    }
    return false;
}

void printResults(bool swapped[], int op1, int op2, int op3, int nums[], int first_result, int second_result)  {
    if (!swapped[0])
    {
        std::cout << nums[0] << " " << operations[op1] << " " << nums[1] << " = " << first_result << "\n";
    }   else    {
        std::cout << nums[1] << " " << operations[op1] << " " << nums[0] << " = " << first_result << "\n";
    }
    if (!swapped[1])
    {
        std::cout << nums[2] << " " << operations[op2] << " " << first_result << " = " << second_result << "\n";
    }   else    {
        std::cout << first_result << " " << operations[op2] << " " << nums[2] << " = " << second_result << "\n";
    }
    if (!swapped[2])
    {
        std::cout << nums[3] << " " << operations[op3] << " " << second_result << " = 24\n";
    }   else    {
        std::cout << second_result << " " << operations[op3] << " " << nums[3] << " = 24\n";
    }
}