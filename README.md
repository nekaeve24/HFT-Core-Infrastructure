# HFT-Core-Infrastructure

A high-performance C++ trading framework focused on sub-microsecond latency and deterministic execution.

## Technical Focus
* **Low-Latency Primitives**: Implementing Single-Producer Single-Consumer (SPSC) lock-free queues to minimize thread contention.
* **Hardware Optimization**: Leveraging SIMD (AVX-512) intrinsics for parallelized cross-sectional alpha calculations and signal processing.
* **Memory Management**: Utilizing custom arena allocators and cache-aligned data structures to prevent heap fragmentation and minimize L1/L2 cache misses.
* **Zero-Copy Architecture**: Binary packet parsing for optimized market data ingestion.
