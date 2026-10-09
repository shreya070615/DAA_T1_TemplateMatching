# DAA T1 — Template Matching using Sequential C and OpenMP

A Design and Analysis of Algorithms (DAA) project implementing and comparing sequential and parallel approaches to image template matching using C and OpenMP.

## 📌 Project Overview

Template matching is an image-processing technique used to locate a smaller template image within a larger target image.

This project explores the **Sum of Squared Differences (SSD)** method for measuring the difference between a template and candidate regions of an image. The SSD score helps identify how closely a region matches the template.

The project compares two implementations:

* **Sequential implementation:** Processes the computation sequentially.
* **OpenMP implementation:** Uses OpenMP to parallelize suitable parts of the computation.

The goal is to examine correctness and understand the performance implications of parallel processing.

## ✨ Features

* Image dataset preparation and preprocessing.
* Sequential implementation in C.
* Parallel implementation using OpenMP.
* CSV output generation for computed results.
* Result comparison to check consistency between implementations.
* Execution in a Kaggle notebook environment.

## 🛠️ Technologies Used

* **C** — Algorithm implementation.
* **OpenMP** — Shared-memory parallel programming.
* **GCC** — C compilation with OpenMP support.
* **Python and Pandas** — Dataset handling and result validation.
* **Kaggle Notebooks** — Development and experimentation.

## 📂 Project Structure

```text
DAA_T1_TemplateMatching/
├── DAA_SSD_OpenMP_Project.ipynb
├── ssd_seq.c
├── ssd_omp.c
├── train_split.csv
├── test_split.csv
├── sequential_100.csv
├── openmp_100.csv
└── README.md
```

*Note: The CSV files are generated outputs or dataset split files. Their availability depends on which files have been uploaded to the repository.*

## ⚙️ Compilation

Make sure GCC is installed and supports OpenMP.

### 1. Compile the sequential implementation

```bash
gcc -O3 -std=c11 ssd_seq.c -o ssd_seq
```

### 2. Compile the OpenMP implementation

```bash
gcc -O3 -std=c11 -fopenmp ssd_omp.c -o ssd_omp
```

The `-O3` flag enables compiler optimizations, while `-fopenmp` enables OpenMP support.

## ▶️ Running the Project

The OpenMP executable accepts three command-line arguments:

```text
./ssd_omp DATA_DIR N OUTPUT.csv
```

Where:

* `DATA_DIR` is the path to the input dataset.
* `N` is the input parameter expected by the program.
* `OUTPUT.csv` is the path where results will be saved.

Example:

```bash
./ssd_omp ./data 100 ./openmp_100.csv
```

Adjust the dataset path and `N` value to match your actual program configuration.

Refer to the notebook for the complete dataset preparation, execution, and validation workflow.

## 🧪 Correctness Validation

The project compares the sequential and OpenMP result files using Python and Pandas.

The validation checks the following columns when present:

* `image_id`
* `x`
* `y`
* `ssd`

Matching results indicate that the implementations agree on the checked outputs for the tested inputs. Correctness should be checked separately from performance.

## 📊 Dataset

The Kaggle workflow prepares a dataset containing 5,000 images:

| Split     |    Images | Percentage |
| --------- | --------: | ---------: |
| Training  |     4,000 |        80% |
| Testing   |     1,000 |        20% |
| **Total** | **5,000** |   **100%** |

The notebook contains the dataset preparation workflow. The original image dataset may need to be downloaded separately rather than stored in this repository.

## 🎯 Learning Outcomes

* Understanding template matching and the SSD method.
* Implementing algorithms in C.
* Exploring parallel programming with OpenMP.
* Comparing sequential and parallel computation.
* Validating computational results using Python.

## 🚀 Future Improvements

* Benchmark execution time across different input sizes.
* Evaluate performance with different OpenMP thread counts.
* Calculate speedup and parallel efficiency.
* Extend validation to the complete test dataset.

---

**Project Type:** Academic — Design and Analysis of Algorithms (DAA)
**Languages:** C, Python
**Parallel Programming:** OpenMP
