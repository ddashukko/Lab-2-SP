#include <iostream>
#include <vector>
#include <iomanip>

void compute_polynomial(std::vector<float>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        float x = data[i];
        data[i] = 3.0f * x * x * x - 2.0f * x * x + 5.0f * x - 1.5f;
    }
}

void apply_filter(std::vector<float>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] > 1000.0f) data[i] = 1000.0f;
        if (data[i] < -1000.0f) data[i] = -1000.0f;
    }
}

// Згортка / 3-точковий фільтр
double compute_convolution(const std::vector<float>& data) {
    double sum = 0.0;
    for (size_t i = 1; i < data.size() - 1; ++i) {
        sum += data[i - 1] * 0.25f + data[i] * 0.5f + data[i + 1] * 0.25f;
    }
    return sum;
}

int main() {
    const size_t SIZE = 12 * 1024 * 1024;
    std::vector<float> data(SIZE, 1.1f);

    double final_result = 0.0;
    for (int k = 0; k < 10; ++k) {
        compute_polynomial(data);
        apply_filter(data);
        final_result += compute_convolution(data);
    }

    std::cout << std::fixed << std::setprecision(2) << "Result: " << final_result << "\n";
    return 0;
}
