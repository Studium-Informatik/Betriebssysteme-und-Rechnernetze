#!/bin/bash
set -euo pipefail

# Configuration
BASE_URL="https://www.cs.uni-potsdam.de/bs/teaching/docs/courses/ws2025/gbr/folien/"
USER="bsstudent"
PASS="bsstudent"

# Fetch list of PDF files and download each one
curl -s -u "$USER:$PASS" "$BASE_URL" \
  | grep -oP '(?<=href=")[^"]+\.pdf' \
  | while IFS= read -r file; do
      echo "Downloading: $file"
      curl -s -u "$USER:$PASS" -O "${BASE_URL}${file}"
    done

