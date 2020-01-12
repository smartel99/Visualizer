#pragma once
#include <array>
#include <vector>

namespace Array
{
    // Function to get Greatest Common Divider of `a` and `b`.
    int gcd(int a, int b)
    {
        if ( b == 0 )
        {
            return a;
        }
        else
        {
            return gcd(b, a % b);
        }
    }

    // https://www.geeksforgeeks.org/array-rotation/
    template<typename T>
    void RotateLeft(std::vector<T>& array, int shifts)
    {
        int size = array.size();
        int g_c_d = gcd(shifts, size);

        for ( int i = 0; i < g_c_d; i++ )
        {
            // Move i-th values of each block.
            int temp = array[i];
            int j = i;

            while ( 1 )
            {
                int k = j + shifts;
                if ( k >= size )
                {
                    k -= size;
                }

                if ( k == i )
                {
                    break;
                }

                array[j] = array[k];
                j = k;
            }

            array[j] = temp;
        }
    }
}