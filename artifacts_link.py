import json

# Load the artifacts JSON data from the file
with open('artifacts.json') as f:
    data = json.load(f)

# Sort artifacts by created_at timestamp
sorted_artifacts = sorted(data['artifacts'], key=lambda x: x['created_at'])

# Get the download URL of the latest artifact
latest_artifact_url = sorted_artifacts[-1]['archive_download_url']

print(latest_artifact_url)
