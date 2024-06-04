# SE4HPC Project

## Overview

This project implements a parallel matrix multiplication application using MPI. The application reads matrices from two files, `matrixA.txt` and `matrixB.txt`, where the first row contains the matrix dimensions and the subsequent rows contain the matrix data.

## Features

- Parallel matrix multiplication using MPI
- Automated build and test processes
- Containerization with Singularity
- Automated job submission to the Galileo100 cluster using SLURM

## Repository Structure
```
SE4HPCproject/
├── .github/
│ └── workflows/
│ └── ci.yml
├── include/
├── lib/
├── src/
│ └── matrix_multiplication.c
├── step2-galileo-out-files/
├── test/
│ └── test_matrix_multiplication.c
├── CMakeLists.txt
├── Singularity.def
├── artifacts_link.py
├── build.sh
├── job.sh
├── matrixA.txt
├── matrixB.txt
├── slurm-job.sh
└── README.md
```
markdown
Copia codice

## Setup and Usage

### Building and Testing

1. **Clone the Repository**
    ```bash
    git clone https://github.com/mattteochen/SE4HPC_project_2_ChenPisante.git
    cd SE4HPC_project_2_ChenPisante
    ```

2. **Build the Application**
    ```bash
    mpicc -o matrix_multiplication src/matrix_multiplication.c
    ```

3. **Run Unit Tests**
    ```bash
    gcc -o test_matrix_multiplication test/test_matrix_multiplication.c -lmpi
    ./test_matrix_multiplication
    ```

### Containerization

1. **Build the Singularity Image**
    ```bash
    singularity build matrix_multiplication.sif Singularity.def
    ```

2. **Test the Singularity Image**
    ```bash
    singularity exec matrix_multiplication.sif ./matrix_multiplication
    ```

### Continuous Integration

- The CI/CD pipeline is configured using GitHub Actions. It automates the build, test, and containerization processes. The workflow is defined in `.github/workflows/ci.yml`.
- On every push, the pipeline will:
  - Build the application
  - Run unit tests
  - Build and test the Singularity image
  - Upload the Singularity image as a GitHub artifact

### Cluster Execution

1. **Transfer to Galileo100**
    ```bash
    scp job.sh matrix_multiplication.sif user@galileo100:/path/to/your/directory
    ```

2. **Submit the Job**
    ```bash
    sbatch job.sh
    ```

3. **Check Output**
    - The standard output and error are redirected to text files as specified in `job.sh`.

### Automating Job Submission

- The CI/CD pipeline can be extended to automate the transfer and submission of jobs to the cluster. This involves securely handling secrets such as passwords and tokens using the [GitHub Secrets mechanism](https://docs.github.com/en/actions/security-guides/using-secrets-in-github-actions?tool=cli).

## Contributions
## Contributions

- Matteo Kaixi Chen
- Giuseppe Pisante 
