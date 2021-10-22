# Copyright 2021 NVIDIA Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import cunumeric as lg


def test():
    x = lg.array([[1, 2, 3], [4, 5, 6]])
    y = lg.transpose(x)
    assert lg.array_equal(y, [[1, 4], [2, 5], [3, 6]])
    z = lg.transpose(y)
    assert lg.array_equal(x, z)

    x = lg.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    y = x.transpose()
    assert lg.array_equal(y, [[1, 4, 7], [2, 5, 8], [3, 6, 9]])
    z = lg.transpose(y)
    assert lg.array_equal(x, z)
    return


if __name__ == "__main__":
    test()
