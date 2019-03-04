// Copyright (c) 2016-2019 Anyar, Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "ascent/direct/State.h"

#include <vector>

namespace asc
{
   struct Module
   {
      Module() = default;
      Module(const Module&) = default;
      Module(Module&&) = default;
      Module& operator=(const Module&) = default;
      Module& operator=(Module&&) = default;
      virtual ~Module() = default;

      std::vector<State> states;

      template <class x_t, class xd_t>
      void make_states(x_t& x, xd_t& xd)
      {
         const size_t n = x.size();
         for (size_t i = 0; i < n; ++i)
         {
            states.emplace_back(x[i], xd[i]);
         }
      }

      virtual void init() {} // initialization
      virtual void operator()() {} // derivative updates
      virtual void postcalc() {} // post integration calculations
   };

   template <class modules_t>
   inline void init(modules_t& modules)
   {
      for (auto& module : modules)
      {
         module->init();
      }
   }

   template <class modules_t>
   inline void update(modules_t& modules)
   {
      for (auto& module : modules)
      {
         module->operator()();
      }
   }

   template <class modules_t>
   inline void postcalc(modules_t& modules)
   {
      for (auto& module : modules)
      {
         module->postcalc();
      }
   }
}