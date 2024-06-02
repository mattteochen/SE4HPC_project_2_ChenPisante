#!/bin/bash

# Define variables
OUTPUT_FILE="stdout.txt"
ERROR_FILE="stderr.txt"
OUT_ZIP_FILE="image.zip"

# Function to run a command and capture stdout and stderr
capture_output() {
    "$@" > >(tee -a "$OUTPUT_FILE") 2> >(tee -a "$ERROR_FILE" >&2)
}

# Function to echo to stdout
echo_stdout() {
    echo "$@" >> "$OUTPUT_FILE"
}

# Fetch the latest artifacts JSON
capture_output curl -L \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $GITHUB_ACCESS_TOKEN" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  https://api.github.com/repos/mattteochen/SE4HPC_project_2_ChenPisante/actions/artifacts \
  -o artifacts.json

# Extract the download URL of the latest artifact
LATEST_URL=$(jq -r '.artifacts | sort_by(.created_at) | last | .archive_download_url' artifacts.json)

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
  capture_output unzip "$OUT_ZIP_FILE"
  # Run image
  capture_output singularity run TestMultiplication.sif
else
  echo_stdout "No artifact found."
fi
