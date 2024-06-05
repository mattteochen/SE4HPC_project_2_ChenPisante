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

## Setup and Usage

### Building and Testing

1. **Clone the Repository**
    ```bash
    git clone https://github.com/mattteochen/SE4HPC_project_2_ChenPisante.git
    cd SE4HPC_project_2_ChenPisante
    ```

2. **Build the Application**
    ```bash
    chmod +x build.sh && ./build.sh
    ```

3. **Run Unit Tests**
    ```bash
    cd build && ./test_multilication
    ```

### Containerization

1. **Build the Singularity Image**
    ```bash
    singularity build matrix_multiplication.sif Singularity.def
    ```

2. **Test the Singularity Image**
    ```bash
    singularuty run YOUR_IMAGE_NAME.sif
    ```

### Continuous Integration

- The CI/CD pipeline is configured using GitHub Actions. It automates the build, test, and containerization processes. The workflow is defined in `.github/workflows/ci.yml`.
- On every push, the pipeline will:
  - automatically submit SLURM job to Galileo100
  - Build the application
  - Run unit tests
  - Build and test the Singularity image
  - Upload the Singularity image as a GitHub artifact
  - Execute the container remotely on the cluster using a remote call to SLURM 

## Cluster Execution

To run the job on a cluster with SLURM, simply execute the following commands:

```bash
chmod +x slurm-job.sh && sbatch slurm-job.sh
```

These commands fully automate the process. The ```slurm-job.sh``` file automatically downloads the image from GitHub Artifacts, avoiding to avoiding to copy it manually.

## Contributions

- Matteo Kaixi Chen
- Giuseppe Pisante 
