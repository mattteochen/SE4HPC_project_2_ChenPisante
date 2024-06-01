#!/bin/bash

# Define variables
IMAGE_NAME="testmultiplication-image.sif"
ARTIFACT_URL="https://github.com/mattteochen/SE4HPC_project_2_ChenPisante/actions/runs/9331929835/artifacts/1559061128"
OUTPUT_FILE="stdout.txt"
ERROR_FILE="stderr.txt"

# Download Singularity image from GitHub Actions artifact
wget -O "$IMAGE_NAME" "$ARTIFACT_URL"

# Check if the download was successful
if [ $? -ne 0 ]; then
    echo "Failed to download Singularity image."
    exit 1
fi

# Run Singularity container and map stdout and stderr to files
singularity exec "$IMAGE_NAME" \
    your_command_or_script \
    > "$OUTPUT_FILE" 2> "$ERROR_FILE"

if [ $? -ne 0 ]; then
    echo "Error occurred while running Singularity container."
    exit 1
fi

echo "Singularity container executed successfully."
