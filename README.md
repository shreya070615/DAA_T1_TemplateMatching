# 🔍 DAA T1 — Template Matching Using Sequential C and OpenMP

A **Design and Analysis of Algorithms (DAA)** project that implements and compares sequential and parallel image template matching using **C and OpenMP**.

## 📌 About the Project

Template matching is an image-processing technique used to find a small image (called a *template*) inside a larger image.

This project uses **Sum of Squared Differences (SSD)** to measure how closely a region of an image matches the template. A lower SSD score indicates a closer match.

We implement and compare two approaches:

* 🐢 **Sequential C:** Processes images one at a time.
* ⚡ **OpenMP:** Processes multiple images in parallel using multiple threads.

🎯 **Goal:** Understand parallel programming, verify result consistency, and compare execution performance.

## ✨ Features

* 🖼️ Image dataset preparation and preprocessing.
* 💻 Sequential SSD implementation in C.
* ⚡ Parallel processing using OpenMP.
* 📄 CSV files containing matching coordinates and SSD scores.
* ✅ Result comparison using Python and Pandas.
* ☁️ Experimentation using Kaggle Notebooks.

## 🛠️ Technologies Used

| Technology       | Purpose                            |
| ---------------- | ---------------------------------- |
| C                | Implementing the SSD algorithm     |
| OpenMP           | Parallel processing                |
| GCC              | Compiling C programs               |
| Python           | Dataset preparation and validation |
| Pandas           | Comparing CSV results              |
| Kaggle Notebooks | Running experiments                |

## 📂 Project Structure

```text
DAA_T1_TemplateMatching/
├── 📓 daa-ssd-openmp-project.ipynb
├── 💻 ssd_seq.c
├── ⚡ ssd_omp.c
├── 📄 train_split.csv
├── 📄 test_split.csv
├── 📊 sequential_100.csv
├── 📊 openmp_100.csv
└── 📘 README.md
```

*Note: The notebook filename and file list should match the actual files in this repository. CSV files may contain generated results or dataset information.*

## ⚙️ How to Compile

You need GCC installed. OpenMP support is required for the parallel implementation.

### 1️⃣ Compile the sequential program

```bash
gcc -O3 -std=c11 ssd_seq.c -o ssd_seq
```

### 2️⃣ Compile the OpenMP program

```bash
gcc -O3 -std=c11 -fopenmp ssd_omp.c -o ssd_omp
```

✅ If no errors appear, the programs have compiled successfully.

**What do the flags mean?**

* `-O3` 🚀 Enables compiler optimizations.
* `-std=c11` 📘 Uses the C11 language standard.
* `-fopenmp` ⚡ Enables OpenMP support.

## ▶️ How to Run

Both programs accept three arguments:

`DATA_DIR` — Directory containing the binary input images.

`N` — Number of images to process.

`OUTPUT.csv` — File where the results will be saved.

### 🐢 Run the sequential version

```bash
./ssd_seq DATA_DIR N sequential.csv
```

### ⚡ Run the OpenMP version

```bash
OMP_NUM_THREADS=4 ./ssd_omp DATA_DIR N openmp.csv
```

Here, `OMP_NUM_THREADS=4` requests four OpenMP threads.

📌 **Important:** The input directory must contain the binary images expected by the program. The template binary must also exist at the path configured in the C source code. Update any Kaggle-specific paths before running the project elsewhere.

💡 Refer to the notebook for the complete dataset preparation and execution workflow.

## 🧪 Result Validation

We use Python and Pandas to compare the output CSV files from both implementations.

The comparison checks:

* 🆔 `image_id` — Input image identifier.
* 📍 `x`, `y` — Best-match coordinates.
* 📉 `ssd` — SSD score for the best match.

✅ If all these values match for every tested image, the sequential and OpenMP implementations produce identical recorded results for that experiment.

*Correctness and performance are evaluated separately.*

## 🖼️ Dataset

The notebook prepares image data for the template-matching experiment and generates binary inputs for the C programs.

The project uses a fixed-size image and template configuration for its SSD benchmark.

📌 The original image dataset and generated binary files may need to be downloaded or recreated when running the project in a new environment.

## 📚 Learning Outcomes

* 🧠 Understanding SSD-based template matching.
* 💻 Implementing algorithms using C.
* ⚡ Learning parallel programming with OpenMP.
* 🔄 Comparing sequential and parallel execution.
* ✅ Validating results using Python.
* 📊 Measuring execution time and speedup.

## 🚀 Future Improvements

* 📈 Benchmark larger datasets.
* 🧵 Experiment with different OpenMP thread counts.
* ⚡ Calculate speedup and parallel efficiency.
* 🧪 Validate results on the complete benchmark dataset.
* 🔧 Make file paths configurable for easier execution on different systems.

---

🎓 **Project Type:** Academic — Design and Analysis of Algorithms (DAA)
💻 **Languages:** C, Python
⚡ **Parallel Programming:** OpenMP
