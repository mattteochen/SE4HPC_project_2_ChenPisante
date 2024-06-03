#!/bin/bash

# Define variables
OUTPUT_FILE="stdout.txt"
ERROR_FILE="stderr.txt"
OUT_ZIP_FILE="image.zip"

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

# Function to run a command and capture stdout and stderr
capture_output() {
    "$@" > >(tee -a "$OUTPUT_FILE") 2> >(tee -a "$ERROR_FILE" >&2) 
}

# Function to echo to stdout
echo_stdout() {
    echo "$@" >> "$OUTPUT_FILE"
}

# Clear stdout and stderr files
: > "$OUTPUT_FILE"
: > "$ERROR_FILE"

# Fetch the latest artifacts JSON
capture_output curl -L \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $GITHUB_ACCESS_TOKEN" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  https://api.github.com/repos/mattteochen/SE4HPC_project_2_ChenPisante/actions/artifacts \
  -o artifacts.json

# Extract the download URL of the latest artifact
LATEST_URL=$(python3 artifacts_link.py)

echo_stdout "Latest artifact download URL: $LATEST_URL"

# Download the latest artifact
if [ -n "$LATEST_URL" ]; then
  capture_output curl -L \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $GITHUB_ACCESS_TOKEN" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  -o "$OUT_ZIP_FILE" \
  "$LATEST_URL"
  echo_stdout "Downloaded latest artifact to $OUT_ZIP_FILE"
  # Unzip artifact
  capture_output unzip -o "$OUT_ZIP_FILE"
  # Run image
  capture_output singularity run TestMultiplication.sif
  capture_output singularity exec --bind $TMPDIR:$TMPDIR TestMultiplication.sif bash -c "export OMPI_MCA_tmpdir_base=$TMPDIR && mpirun -n 2 /opt/build_files/build/main"
else
  echo_stdout "No artifact found."
fi
