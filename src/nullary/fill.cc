/* Copyright 2021 NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "nullary/fill.h"
#include "nullary/fill_template.inl"

namespace legate {
namespace numpy {

using namespace Legion;

template <typename VAL, int32_t DIM>
struct FillImplBody<VariantKind::CPU, VAL, DIM> {
  void operator()(AccessorWO<VAL, DIM> out,
                  const VAL &fill_value,
                  const Pitches<DIM - 1> &pitches,
                  const Rect<DIM> &rect,
                  bool dense) const
  {
    size_t volume = rect.volume();
    if (dense) {
      auto outptr = out.ptr(rect);
      for (size_t idx = 0; idx < volume; ++idx) outptr[idx] = fill_value;
    } else {
      for (size_t idx = 0; idx < volume; ++idx) {
        const auto point = pitches.unflatten(idx, rect.lo);
        out[point]       = fill_value;
      }
    }
  }
};

void deserialize(Deserializer &ctx, FillArgs &args)
{
  deserialize(ctx, args.shape);
  deserialize(ctx, args.out);
  deserialize(ctx, args.fill_value);
}

/*static*/ void FillTask::cpu_variant(const Task *task,
                                      const std::vector<PhysicalRegion> &regions,
                                      Context context,
                                      Runtime *runtime)
{
  fill_template<VariantKind::CPU>(task, regions, context, runtime);
}

namespace  // unnamed
{
static void __attribute__((constructor)) register_tasks(void) { FillTask::register_variants(); }
}  // namespace

}  // namespace numpy
}  // namespace legate
