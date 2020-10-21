#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#define MINUS_INT_MAX INT_MAX * (-1);

/*
    Input:  [1,2,3,4]
    Output: [24,12,8,6]
*/

int my_div(int num, int den) {
    int frac;
    for (frac = 0; num >= den; num -= den, frac++)
        ;
    return frac;
}


class Solution {
public:

    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        // without using division
        if(nums.size() <= 0) {
            return nums;
        }

        std::vector<int> output;

        /*
                                    [     1     2     3     4     ]
        the product of the                ^ 
        elements from left to right:      ->
        get: [1,2,6,24] 

        the product of the                                  ^ 
        elements from right to left:                       <-
        get: [24,24,12,4]   

        the product of all the elements
        except self (ith) will be left[i-1] * right[i+1]
        for i == 1, output[i]: 1 * 12 = 12
        [24,12,8,6]

        */

        std::vector<int> left(nums.size(),1), right(nums.size(),1);
        left[0] = nums[0];
        right[nums.size()-1] = nums[nums.size()-1];

        printf("left array:\n");
        for(int i = 1 ; i < nums.size() ; i++) {
            left[i] = nums[i] * left[i-1];
        }
        for(int i = 0 ; i < nums.size() ; i++) {
            printf("%d\t", left[i]);
        }

        printf("\nright array:\n");
        for(int i = nums.size()-2 ; i >= 0 ; i--) {
            right[i] = nums[i] * right[i+1];
        }
        for(int i = 0 ; i < nums.size() ; i++) {
            printf("%d\t", right[i]);
        }

        for(int i = 0 ; i < nums.size() ; i++) {
            int left_candidate = 1, right_candidate = 1;
            if(i > 0)             left_candidate  = left[i-1];
            if(i < nums.size()-1) right_candidate = right[i+1];
            int tmp_val = left_candidate * right_candidate;
            output.push_back(tmp_val);
        }
        printf("\noutput:\n");

        return output;
    }

    std::vector<int> productExceptSelf_OPT(std::vector<int>& nums) {
        // optimization

        // go through all elements from left to right
        std::vector<int> res(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i) {
            res[i] = res[i - 1] * nums[i - 1];
        }
        // go through all elements from right to left
        int right = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            res[i] *= right;
            right  *= nums[i];
        }
        return res;
    }


    std::vector<int> productExceptSelf_EasyWay(std::vector<int>& nums) {
        // will use division
        if(nums.size() <= 0) {
            return nums;
        }
        std::vector<int> output;
        int num_of_zeros = 0;

        // find zero index, find if zero exist in the array, check if the nums[i] if zero
        for(int i = 0 ; i < nums.size() ; i++) {
            if(nums[i] == 0)
                num_of_zeros++;
        }

        // calculate the product of all the non-zero elements
        int total_product = 1;
        for(int i = 0 ; i < nums.size() ; i++) {
            if(nums[i] != 0) {
                total_product = total_product * nums[i];
            }
        }
        printf("the product of all the non-zero elements: %d\n", total_product);
        
        // deal with all the conditions
        for(int i = 0 ; i < nums.size() ; i++) {
            if(num_of_zeros > 1) {
                output.push_back(0);
                continue;
            }

            if(nums[i] == 0) { // nums[i] is zero
                if(num_of_zeros > 1) {
                    // more than 2 zeros exist in the array
                    // ex: [0,1,0,5] => output: [0,0,0,0]
                    output.push_back(0);
                } else {
                    // only one zero exist in the array
                    // ex: [0,1,2,5] => output: [10,0,0,0]
                    output.push_back(total_product);
                }
            } else { // nums[i] > 0
                if(num_of_zeros > 0) {
                    // if the array exist a zero
                    // ex: [0,1,2,5] => output: [10,0,0,0], the non-zero num will output 0
                    output.push_back(0);
                } else {
                    // use product of all the non-zero elements to divide the nums[i]
                    int tmp_val = my_div(total_product, nums[i]);
                    output.push_back(tmp_val);
                }
            }
        }
        return output;
    }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();

    printf("=== Solution1 ===\n");
    std::vector<int> nums1{ 1,2,3,4 };
    std::vector<int> output_arr1 = s -> productExceptSelf(nums1);
    for(int i = 0 ; i < output_arr1.size() ; i++) {
        printf("%d\t", output_arr1[i]);
    }
    printf("\n");

    printf("=== Solution2 ===\n");
    std::vector<int> nums2{ 1,2,0,3,4 };
    std::vector<int> output_arr2 = s -> productExceptSelf(nums2);
    for(int i = 0 ; i < output_arr2.size() ; i++) {
        printf("%d\t", output_arr2[i]);
    }
    printf("\n");
}