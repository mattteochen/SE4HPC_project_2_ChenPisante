#!/bin/bash

# Define variables
OUTPUT_FILE="stdout.txt"
ERROR_FILE="stderr.txt"

# Download Singularity image from GitHub Actions artifact
wget https://github.com/mattteochen/SE4HPC_project_2_ChenPisante/actions/runs/9331929835/artifacts/1559061128
unzip testmultiplication-image.zip

# Check if the download was successful
if [ $? -ne 0 ]; then
    echo "Failed to download Singularity image."
    exit 1
fi

# Run Singularity container and map stdout and stderr to files
singularity exec testmultiplication-image.sif \
    your_command_or_script \
    > "$OUTPUT_FILE" 2> "$ERROR_FILE"

if [ $? -ne 0 ]; then
    echo "Error occurred while running Singularity container."
    exit 1
fi

echo "Singularity container executed successfully."
