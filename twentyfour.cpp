#include <iostream>
// #include <string>
#include <sstream>

bool calculate(int x, int y, int results[]);
int runTheGamut(int x, int y);
bool find24(int numbers[]);

void testFunc();

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
    // std::cout << "Entered " << argc - 1 << " arguments.\n";
    if (argc != 5)  {
        std::cout << "Please enter exactly four numbers; no more, no less.\n";
        return 1;
    }

    //  ... all whole
    for (int i = 0; i < argc - 1; i++)
    {
// std::cout << "num[" << i << "]: " << nums[i] << "\n";
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

    for (int i = 0; i < argc - 2; ++i)
    {
        for (int j = i + 1; j < argc - 1; ++j)
        {
            calculate(nums[i], nums[j], results1);
            // runTheGamut(nums[i], nums[j]);
        }
// std::cout << "returned " << results1[2] << "\n";
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

int runTheGamut (int x, int y)  {
    std::cout << x << " " << y << ": ";
    (x > y) ? (std::cout << x) : (std::cout << y);
    std::cout << "\n";
}

void testFunc() {
    std::cout << "Yup, it works\n";
}

bool find24(int nums[])   {
    int first_results[4];
    int second_results[4];
    int third_results[4];
    int skip_quotient;
    bool swapped_first, swapped_second, swapped_third;

    swapped_first = calculate(nums[0], nums[1], first_results);
    skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
    for (int i = 0; i < 4 + skip_quotient; ++i)
    {
        swapped_second = calculate(nums[2], first_results[i], second_results);
        skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
        for (int j = 0; j < 4 + skip_quotient; ++j)
        {
            swapped_third = calculate(nums[3], second_results[j], third_results);
            skip_quotient = first_results[3] < 0 ? first_results[3] : 0;
            for (int k = 0; k < 4 + skip_quotient; ++k)
            {
                if (third_results[k] == 24)
                {
                    if (!swapped_first)
                    {
                        std::cout << nums[0] << " " << operations[i] << " " << nums[1] << " = " << first_results[i] << "\n";
                    }   else    {
                        std::cout << nums[1] << " " << operations[i] << " " << nums[0] << " = " << first_results[i] << "\n";
                    }
                    if (!swapped_second)
                    {
                        std::cout << nums[2] << " " << operations[j] << " " << first_results[i] << " = " << second_results[j] << "\n";
                    }   else    {
                        std::cout << first_results[i] << " " << operations[j] << " " << nums[2] << " = " << second_results[j] << "\n";
                    }
                    if (!swapped_third)
                    {
                        std::cout << nums[3] << " " << operations[k] << " " << second_results[j] << " = " << third_results[k] << "\n";
                    }   else    {
                        std::cout << second_results[j] << " " << operations[k] << " " << nums[3] << " = " << third_results[k] << "\n";
                    }
                    return true;
                }
            }
        }
    }
    return false;
}