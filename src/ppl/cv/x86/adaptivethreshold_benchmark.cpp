// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <benchmark/benchmark.h>
#include "ppl/cv/x86/adaptivethreshold.h"
#include <memory>
#include "ppl/cv/debug.h"

namespace {

template<typename T, int32_t nc, int32_t filter_size, int32_t adaptive_method, int32_t threshold_type>
void BM_AdaptiveThreshold_ppl_x86(benchmark::State &state) {
    int32_t width = state.range(0);
    int32_t height = state.range(1);
    int32_t max_value = 155;
    int32_t delta = 5;
    std::unique_ptr<T[]> src(new T[width * height * nc]);
    std::unique_ptr<T[]> dst(new T[width * height * nc]);
    ppl::cv::debug::randomFill<T>(src.get(), width * height * nc, 0, 255);
    for (auto _ : state) {
        ppl::cv::x86::AdaptiveThreshold(height, width, width * nc, src.get(), width * nc, dst.get(), 
                max_value, adaptive_method, threshold_type, filter_size, delta, ppl::cv::BORDER_TYPE_REPLICATE);
    
    }
    state.SetItemsProcessed(state.iterations() * 1);
}

using namespace ppl::cv::debug;

BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_ppl_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});

#ifdef PPLCV_BENCHMARK_OPENCV
template<typename T, int32_t nc, int32_t filter_size, int32_t adaptive_method, int32_t threshold_type>
void BM_AdaptiveThreshold_opencv_x86(benchmark::State &state) {
    int32_t width = state.range(0);
    int32_t height = state.range(1);
    int32_t max_value = 155;
    int32_t delta = 5;
    std::unique_ptr<T[]> src(new T[width * height * nc]);
    std::unique_ptr<T[]> dst(new T[width * height * nc]);
    ppl::cv::debug::randomFill<T>(src.get(), width * height * nc, 0, 255);
    cv::Mat src_opencv(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), src.get(), sizeof(T) * width * nc);
    cv::Mat dst_opencv(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), dst.get(), sizeof(T) * width * nc);
    for (auto _ : state) {
        cv::adaptiveThreshold(src_opencv, dst_opencv, max_value, adaptive_method, threshold_type, filter_size, delta);
    }
    state.SetItemsProcessed(state.iterations() * 1);
}

BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_MEAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 3, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 5, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});
BENCHMARK_TEMPLATE(BM_AdaptiveThreshold_opencv_x86, uint8_t, 1, 7, ppl::cv::ADAPTIVE_THRESH_GAUSSIAN_C, ppl::cv::CV_THRESH_BINARY_INV)->Args({320, 240})->Args({640, 480})->Args({1280, 720})->Args({1920, 1080})->Args({3840, 2160});


#endif //! PPLCV_BENCHMARK_OPENCV
}