// Copyright (c) 2018, The Safex Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers
// Parts of this file are originally copyright (c) 2014-2018 The Monero Project

#include "gtest/gtest.h"

#include "cryptonote_core/blockchain.h"

using namespace cryptonote;

namespace
{
  static uint64_t clamp_fee(uint64_t fee)
  {
    static uint64_t mask = 0;
    if (mask == 0)
    {
      mask = 1;
      for (size_t n = PER_KB_FEE_QUANTIZATION_DECIMALS; n < CRYPTONOTE_DISPLAY_DECIMAL_POINT; ++n)
        mask *= 10;
    }
    return (fee + mask - 1) / mask * mask;
  }

  //--------------------------------------------------------------------------------------------------------------------
  class fee : public ::testing::Test
  {
  };

  // try with blocks ~ 1GB. Passing 2 GB will break on 32 bit systems

  TEST_F(fee, 100sfx)
  {
    // CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 and lower are clamped
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1, 1), clamp_fee(166670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 2, 1), clamp_fee(166670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 2, 1), clamp_fee(166670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 100, 1), clamp_fee(166670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, 1, 1), 166670000);

    // higher is inverse proportional
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 2, 1), clamp_fee(166670000 / 2));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 10, 1), clamp_fee(166670000 / 10));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 1000, 1), clamp_fee(166670000 / 1000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(1000000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 20000ull, 1), clamp_fee(166670000 / 20000));
  }

  TEST_F(fee, 1sfx)
  {
    // CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 and lower are clamped
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1, 1), clamp_fee(1670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 2, 1), clamp_fee(1670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 100, 1), clamp_fee(1670000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, 1, 3), 1670000);

    // higher is inverse proportional
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 2, 1), clamp_fee(1670000 / 2));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 10, 1), clamp_fee(1670000 / 10));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 1000, 1), clamp_fee(1670000 / 1000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(10000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 20000ull, 1), clamp_fee(1670000 / 20000));
  }

  TEST_F(fee, dot3sfx)
  {
    // CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 and lower are clamped
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1, 1), clamp_fee(500000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 2, 1), clamp_fee(500000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 / 100, 1), clamp_fee(500000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, 1, 3), 500000);

    // higher is inverse proportional
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 2, 1), clamp_fee(500000 / 2));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 10, 1), clamp_fee(500000 / 10));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 1000, 1), clamp_fee(500000 / 1000));
    ASSERT_EQ(Blockchain::get_dynamic_per_kb_fee(3000000000, CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 20000ull, 1), clamp_fee(500000 / 20000));
  }

  static bool is_more_or_less(double x, double y)
  {
    return fabs(y - x) < 0.01;
  }

  static const double MAX_MULTIPLIER = 3.f;

  TEST_F(fee, double_at_full)
  {
    static const uint64_t block_rewards[] = {
      4800000000000ull, // 480 cash
      3000000000000ull, // 300 cash
      1000000000000ull, // 100 cash
      200000000000ull, // 20 cash
      130000000000ull, // 13 cash
      30000000000ull, // 3 cash
    };
    static const uint64_t median_block_sizes[] = {
      CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1,
      CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 2,
      CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 10,
      CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 * 1000,
    };

    for (uint64_t block_reward: block_rewards)
    {
      for (uint64_t median_block_size: median_block_sizes)
      {
        //checks calculated fee * median_block_size(kb) / block_reward for fee function optimum
        ASSERT_TRUE(is_more_or_less(Blockchain::get_dynamic_per_kb_fee(block_reward, median_block_size, 1) * (median_block_size / 1024.) * MAX_MULTIPLIER / (double)block_reward, 0.01));
      }
    }
  }
}
