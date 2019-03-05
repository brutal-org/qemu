/*
 *  Test program for MSA instruction ADDS_A.D
 *
 *  Copyright (C) 2019  Wave Computing, Inc.
 *  Copyright (C) 2019  Mateja Marjanovic <mateja.marjanovic@rt-rk.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <sys/time.h>
#include <stdint.h>

#include "../../../../include/wrappers_msa.h"
#include "../../../../include/test_inputs.h"
#include "../../../../include/test_utils.h"

#define TEST_COUNT_TOTAL (                                                \
            (PATTERN_INPUTS_SHORT_COUNT) * (PATTERN_INPUTS_SHORT_COUNT) + \
            (RANDOM_INPUTS_SHORT_COUNT) * (RANDOM_INPUTS_SHORT_COUNT))


int32_t main(void)
{
    char *instruction_name = "ADDS_A.D";
    int32_t ret;
    uint32_t i, j;
    struct timeval start, end;
    double elapsed_time;

    uint64_t b128_result[TEST_COUNT_TOTAL][2];
    uint64_t b128_expect[TEST_COUNT_TOTAL][2] = {
        { 0x0000000000000002ULL, 0x0000000000000002ULL, },    /*   0  */
        { 0x0000000000000001ULL, 0x0000000000000001ULL, },
        { 0x5555555555555557ULL, 0x5555555555555557ULL, },
        { 0x5555555555555556ULL, 0x5555555555555556ULL, },
        { 0x3333333333333335ULL, 0x3333333333333335ULL, },
        { 0x3333333333333334ULL, 0x3333333333333334ULL, },
        { 0x1c71c71c71c71c73ULL, 0x38e38e38e38e38e4ULL, },
        { 0x1c71c71c71c71c72ULL, 0x38e38e38e38e38e5ULL, },
        { 0x0000000000000001ULL, 0x0000000000000001ULL, },    /*   8  */
        { 0x0000000000000000ULL, 0x0000000000000000ULL, },
        { 0x5555555555555556ULL, 0x5555555555555556ULL, },
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0x3333333333333334ULL, 0x3333333333333334ULL, },
        { 0x3333333333333333ULL, 0x3333333333333333ULL, },
        { 0x1c71c71c71c71c72ULL, 0x38e38e38e38e38e3ULL, },
        { 0x1c71c71c71c71c71ULL, 0x38e38e38e38e38e4ULL, },
        { 0x5555555555555557ULL, 0x5555555555555557ULL, },    /*  16  */
        { 0x5555555555555556ULL, 0x5555555555555556ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c8ULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c7ULL, 0x7fffffffffffffffULL, },
        { 0x5555555555555556ULL, 0x5555555555555556ULL, },    /*  24  */
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c7ULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c6ULL, 0x7fffffffffffffffULL, },
        { 0x3333333333333335ULL, 0x3333333333333335ULL, },    /*  32  */
        { 0x3333333333333334ULL, 0x3333333333333334ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x6666666666666668ULL, 0x6666666666666668ULL, },
        { 0x6666666666666667ULL, 0x6666666666666667ULL, },
        { 0x4fa4fa4fa4fa4fa6ULL, 0x6c16c16c16c16c17ULL, },
        { 0x4fa4fa4fa4fa4fa5ULL, 0x6c16c16c16c16c18ULL, },
        { 0x3333333333333334ULL, 0x3333333333333334ULL, },    /*  40  */
        { 0x3333333333333333ULL, 0x3333333333333333ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x6666666666666667ULL, 0x6666666666666667ULL, },
        { 0x6666666666666666ULL, 0x6666666666666666ULL, },
        { 0x4fa4fa4fa4fa4fa5ULL, 0x6c16c16c16c16c16ULL, },
        { 0x4fa4fa4fa4fa4fa4ULL, 0x6c16c16c16c16c17ULL, },
        { 0x1c71c71c71c71c73ULL, 0x38e38e38e38e38e4ULL, },    /*  48  */
        { 0x1c71c71c71c71c72ULL, 0x38e38e38e38e38e3ULL, },
        { 0x71c71c71c71c71c8ULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c7ULL, 0x7fffffffffffffffULL, },
        { 0x4fa4fa4fa4fa4fa6ULL, 0x6c16c16c16c16c17ULL, },
        { 0x4fa4fa4fa4fa4fa5ULL, 0x6c16c16c16c16c16ULL, },
        { 0x38e38e38e38e38e4ULL, 0x71c71c71c71c71c6ULL, },
        { 0x38e38e38e38e38e3ULL, 0x71c71c71c71c71c7ULL, },
        { 0x1c71c71c71c71c72ULL, 0x38e38e38e38e38e5ULL, },    /*  56  */
        { 0x1c71c71c71c71c71ULL, 0x38e38e38e38e38e4ULL, },
        { 0x71c71c71c71c71c7ULL, 0x7fffffffffffffffULL, },
        { 0x71c71c71c71c71c6ULL, 0x7fffffffffffffffULL, },
        { 0x4fa4fa4fa4fa4fa5ULL, 0x6c16c16c16c16c18ULL, },
        { 0x4fa4fa4fa4fa4fa4ULL, 0x6c16c16c16c16c17ULL, },
        { 0x38e38e38e38e38e3ULL, 0x71c71c71c71c71c7ULL, },
        { 0x38e38e38e38e38e2ULL, 0x71c71c71c71c71c8ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },    /*  64  */
        { 0x7bd718d08a09e3b8ULL, 0x5e5ec67913bb0308ULL, },
        { 0x7fffffffffffffffULL, 0x733fd25ea9a6d520ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7bd718d08a09e3b8ULL, 0x5e5ec67913bb0308ULL, },
        { 0x0883ff3964d871f0ULL, 0x25ef76342a7ea5f8ULL, },
        { 0x57e750f1f89cad78ULL, 0x3ad08219c06a7810ULL, },
        { 0x749115ea109e1b46ULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x733fd25ea9a6d520ULL, },    /*  72  */
        { 0x57e750f1f89cad78ULL, 0x3ad08219c06a7810ULL, },
        { 0x7fffffffffffffffULL, 0x4fb18dff56564a28ULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x7fffffffffffffffULL, 0x7fffffffffffffffULL, },
        { 0x749115ea109e1b46ULL, 0x7fffffffffffffffULL, },
};

    gettimeofday(&start, NULL);

    for (i = 0; i < PATTERN_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < PATTERN_INPUTS_SHORT_COUNT; j++) {
            do_msa_ADDS_A_D(b128_pattern[i], b128_pattern[j],
                           b128_result[PATTERN_INPUTS_SHORT_COUNT * i + j]);
        }
    }

    for (i = 0; i < RANDOM_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < RANDOM_INPUTS_SHORT_COUNT; j++) {
            do_msa_ADDS_A_D(b128_random[i], b128_random[j],
                           b128_result[((PATTERN_INPUTS_SHORT_COUNT) *
                                        (PATTERN_INPUTS_SHORT_COUNT)) +
                                       RANDOM_INPUTS_SHORT_COUNT * i + j]);
        }
    }

    gettimeofday(&end, NULL);

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;

    ret = check_results(instruction_name, TEST_COUNT_TOTAL, elapsed_time,
                        &b128_result[0][0], &b128_expect[0][0]);

    return ret;
}
